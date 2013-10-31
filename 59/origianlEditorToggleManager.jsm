/*
* Toggle using original editor logic is defined in this js file 
//OET : original Editor Toggle
// do toggle : 
1 onblur and onfocus  --- pref : "fn.stealthbrowser.editable.element.toggle.onfocuseblur" true or false
2 when user click a button special  -- pref "fn.stealthbrowser.editable.element.toggle.onbutton"  true or false
//debug control 
*/
;//in case other bad js file is loaded before this file


var using_OETManager_debug = true; // = false when release
var using_OETManager_debug_log = true; // = false when do alert

//


//const
const Cc = Components.classes;
const Ci = Components.interfaces;
const Cu = Components.utils;
Cu.import("resource://gre/modules/XPCOMUtils.jsm");
Cu.import("resource://gre/modules/Services.jsm");

// Glue to add in the observer API to this object.  This allows us to share code with chrome tests
//var jsloader = Cc["@mozilla.org/moz/jssubscript-loader;1"].getService(Ci.mozIJSSubScriptLoader);
//loader.loadSubScript("chrome://webpagesvr/content/webpgjs/helperFunctions.js")

const gObserver = Services.obs;
const gPref = Services.prefs;
const gconsole = Services.console;


function OET_window_unload( event )
{
	//event.target is a document.body
	//remove the original Editor controlling 
	if(g_OETManager)
	{
		g_OETManager.remove_document(event.target)
	}
}

function elementInDOM(aElement)
{
	if(aElement)
	{
		if(aElement.ownerDocument)
		{
			if(aElement == aElement.ownerDocument.body)
			{
				return true;
			}
			else if(aElement == aElement.ownerDocument.documentElement)
			{
				return true;
			}
			else
			{
				let parent =  aElement.parentNode;
				while(parent)
				{
					
					if(parent == aElement.ownerDocument.body)
					{
						return true;
					}
					parent =  parent.parentNode;
					
					if(parent && parent ==  parent.parentNode)//dead loop
					{
						return false;
					}
					
				}
			}
		}
	}
	return false;
}


Components.utils.import("resource://webpagesvrmoudleLoader/webpgjs/eventEmiter.jsm");
Components.utils.import("resource://webpagesvrmoudleLoader/webpgjs/fndocidHarvestor.jsm"); // for addFnDocid

const EmailDataCollectionEventName = "FnWillSendEvt"; 

//class OETController
function OETController(aEditor)
{
	this.originalEditor = aEditor;
	this.initialized =  false;
	this.fncipher_cache = "";
	this.lastEncryptActionTime = null;
	this.emailDataCollectionEvent_listener = null;
}

let OETController_ExtendedProp = {

	add_handler: function()
	{
		if(!this.initialized)
		{
			let aOETController =  this;

			this.addTogleListener();
		
			this.initialized =  true; 
			this.emit("OETControllerAdd", null);    
			let abrowser = getCurrentTabBrowserFromHTMLDoc(this.originalEditor.ownerDocument);
			if(abrowser )
			{
				if(g_OETManager.is_fn_integrating_Editor( this.originalEditor) )
				{
					let self = this;
					self.emailDataCollectionEvent_listener = abrowser.ownerDocument.addEventListener(EmailDataCollectionEventName, 
						function(evt){
							self.sendoutData(evt);
						}, false );
				}
			}
		}

	},
	addTogleListener : function ()
	{
		let eventHolder = this.originalEditor;
		let is_fn_integrating =  false;
		if(g_OETManager.is_fn_integrating_Editor( eventHolder ) )
		{
			is_fn_integrating =  true;
		}
		if(is_fn_integrating)
		{
			if(this.originalEditor.tagName == "IFRAME" ) 
			{
				eventHolder = this.originalEditor.contentDocument;
			}
			eventHolder.addEventListener("blur", this.onblur	, false);
			eventHolder.addEventListener("focus", this.onfocus ,false);
		}
		else
		{
			eventHolder.addEventListener("DOMAttrModified", this.onToggleCommandChecked, false);
		}
		
		alert_log__("addTogleListener")
	},
	
	removeTogleListener : function ()
	{
		alert_log__("removeTogleListener ")
		let eventHolder = this.originalEditor;
		let is_fn_integrating =  false;
		if(g_OETManager.is_fn_integrating_Editor( eventHolder ) )
		{
			is_fn_integrating =  true;
		}
		
		if(is_fn_integrating)
		{
			if(this.originalEditor.tagName == "IFRAME" ) 
			{
				eventHolder = this.originalEditor.contentDocument;
			}
			eventHolder.removeEventListener("blur", this.onblur	, false);
			eventHolder.removeEventListener("focus", this.onfocus ,false);
		}
		else
		{
			eventHolder.removeEventListener("DOMAttrModified", this.onToggleCommandChecked, false);
		}
	},
	
	fnpresent: function()
	{
		alert_log__("fnpresent ");
		let is_fn_integrating =  false;
		if(g_OETManager.is_fn_integrating_Editor( this.originalEditor ) )
		{
			is_fn_integrating =  true;
		}
		if(!is_fn_integrating)
		{
			if(this.originalEditor.currentReaders === undefined)
			{// "select readers" will popup first time , so do nothing when the option is "SetReader" , wait the ser reader action
				return ;
			}
		}
			
		if(this.lastEncryptActionTime)
		{
			let newTime = new Date();
			let timespan =  newTime.getTime() - this.lastEncryptActionTime.getTime();
			if(timespan)
			{
				if(timespan < 1000)
				{
					return;
				}
			}
		}
		let self = this;
		this.on("uploadFinished", function(arg){
		    let ele = self.originalEditor;
			ele.ownerDocument.defaultView.setTimeout(
				function(){
					if(!is_fn_integrating)
					{
						ele.blur();
					}
				},1000);
		});
		this.try_encrypt();	
	},
	
	originalPresent : function()
	{
		alert_log__("originalPresent ");
		let is_fn_integrating =  false;
		if(g_OETManager.is_fn_integrating_Editor( this.originalEditor ) )
		{
			is_fn_integrating =  true;
		}
		
		if(!is_fn_integrating)
		{
			if(this.originalEditor.currentReaders === undefined)
			{// "select readers" will popup first time , so do nothing when the option is "SetReader" , wait the ser reader action
				//return ;
			}
		}
		if(this.lastEncryptActionTime)
		{
			let newTime = new Date();;
			let timespan =  newTime.getTime() - this.lastEncryptActionTime.getTime();
			if(timespan)
			{
				if(timespan < 1000)
				{
					return;
				}
			}
		}
			
		this.try_decrypt();
	},
	
	remove_handler : function()
	{
		if(this.initialized )
		{
			this.fncipher_cache = "";
			let abrowser = getCurrentTabBrowserFromHTMLDoc(this.originalEditor.ownerDocument);
			if(abrowser && this.emailDataCollectionEvent_listener)
			{
				abrowser.ownerDocument.removeEventListener(EmailDataCollectionEventName, this.emailDataCollectionEvent_listener  ,false );
			}
			
			this.removeTogleListener();
			this.initialized =  false;
			this.emit("OETControllerRemove", null);

		}

	},
	
	onToggleCommandChecked: function (evt)
	{
		
		if(evt.attrName.toLowerCase() == "togglecommandchecked")
		{
			let aOETController =  g_OETManager.find_editorHandler(evt.target);
			if(evt.newValue == "true")
			{
				evt.target.removeAttribute("toggleCommandChecked");			
				aOETController.fnpresent();
			}
			else if(evt.newValue == "false")
			{
				aOETController.originalPresent();
			}
		}
	},
	
	onfocus: function(event)
	{
		//decrypt if there is any fndocid
		/*
		let aOETController =  g_OETManager.find_editorHandler(event.target);
		if(aOETController)
		{
			aOETController.originalPresent();
		}
		*/
		
	},
	
	onblur : function (event)
	{
		//going to encrypt content into a fndocid
		/*
		let aOETController =  g_OETManager.find_editorHandler(event.target);
		if(aOETController)
		{
			aOETController.fnpresent();
		}*/
		
	},
	
	
	try_encrypt:function()
	{ 
		alert_log__("try_encrypt ");
		var aBrowserXULDOMWindow = getATopBrowserXulwindow();
		if(!aBrowserXULDOMWindow )
		{
			return false;
		}
		
		var content =  this.getEditorContent(true); // using html content
		if(!content || content.length == 0)
			return false;
	    
		var aPlainTextFNCipherCombiner = Cc["@fntechnologies.com/firefoxhelper/plaintextfnciphercombiner;1"].
                createInstance(Ci.IPlainTextFNCipherCombiner);
    
		if(!aPlainTextFNCipherCombiner)
			return  false;
			
		let self  = this;
		let editor =  self.originalEditor;
		let is_fn_integrating =  false;
		if(g_OETManager.is_fn_integrating_Editor( editor ) )
		{
			is_fn_integrating =  true;
		}

		var fncontent_array = matchFnDocIdFromString (content);
		//has onlye 1 fndocid : already encrypted , do nothing;
		if( !fncontent_array || fncontent_array.length ==0 )
		{
			var aJsonFormat_readers =  new Object();
			var aFneBinaryData_base64 =  new Object(); 
			var afndocid  = null;
			try
			{
				afndocid =  aPlainTextFNCipherCombiner.fneEncodeTextWithMe(  content, 
											   aJsonFormat_readers, 
											   aFneBinaryData_base64 );
			}
			catch(err)
			{
				return false;
			}
                                           
			afndocid = atob(afndocid);

			aJsonFormat_readers = aJsonFormat_readers.value
			aFneBinaryData_base64 = aFneBinaryData_base64.value

			try
			{
				var sentdataObj = JSON.parse(aJsonFormat_readers );        
			}
			catch(err)
			{
				return false;
			}
	        
			var sentdataArray = [];	  
			for(var counter =0; counter <sentdataObj.length; ++counter)
			{
			  var areader = sentdataObj[counter];
			  if(areader.ownerid == "fnDocId")
			  {
				 fndocid = atob(areader.pkey);
			  }
			  else
			  {
				 sentdataArray.push(areader);
			  }    
			}           
			var msgData = aFneBinaryData_base64            
       
			if(fndocid == "")
				return false;

			
			// set up a call back function for aBrowserXULDOMWindow.sendOneDoc	
			function sentcallback(successFndocids)
			{
				if(is_fn_integrating )
				{
					self.fncipher_cache = successFndocids;
					//to not relase what the user typed, clean the content
				}
				//if !is_fn_integrating, upload the readers if it has
				else
				{
					for ( let key in editor.currentReaders)
					{
						sendInvitation = false;
						let ownerID = editor.currentReaders[key];
						if(ownerID && ownerID > 0)
						{
							aBrowserXULDOMWindow.createAKeyForADocByOwnerId(fndocid, ownerID);
						}
						else if(ownerID == 0 && sendInvitation == false)
						{
							//If invitation has not been sent then send fndocid as invitation
							aBrowserXULDOMWindow.addInvitationFndoc(fndocid);
							editor.shouldSendInvitation = true;
							sendInvitation = true;
						}
					}
					alert_log__("setEditorContent successFndocids: " +  successFndocids);				
					g_OETManager.setEditorContent(editor, successFndocids, true, false); //paste the fndocid to the Editor
				}
				self.lastEncryptActionTime = new Date();
				self.emit("uploadFinished", null);
			} // end of sentcallback fucntion ]]
			  
			let uploadTextType = "text_plain" ;
			self.fncipher_cache = fndocid;
			self.fncipher_key = sentdataArray[0].pkey;
			aBrowserXULDOMWindow.sendOneDoc(sentdataArray, fndocid, fndocid, "3423423ssadsad_anystring_reserved", msgData, uploadTextType , sentcallback);
			if(is_fn_integrating )
			{
				//to not relase what the user typed, clean the content
				// this is only a temperory solution, think about what if the encyption error and upload error..., user will lose what he typed!!

				alert_log__("setEditorContent_inner_  empty editor ");				
				g_OETManager.setEditorContent_inner_(editor ,"", false, false, false);
			}
			
		}//if(!fncontent_array || fncontent_array.length ==0)
		return true;
	},
	
	try_decrypt : function()
	{
		var content =  this.getEditorContent(true); // using html content
		
		var fncontent_array = matchFnDocIdFromString (content );
		if(!fncontent_array || fncontent_array.length != 1) // Do not care about multiple fndocids
		{
		    return false;
		}
		
		var afndocid = fncontent_array[0];
		let adocGuid = remove_fndocid_prefix(afndocid);
		this.try_decrypt_a_fndocid ( adocGuid );
		return true;
	},
	
	try_decrypt_a_fndocid : function(afndocid )
	{
		var aBrowserXULDOMWindow = getATopBrowserXulwindow();
		if(!aBrowserXULDOMWindow )
		{
			return false;
		}
		this.getplainTextFromFNDocID(aBrowserXULDOMWindow, afndocid);
		return true;
		
	},
	
	getplainTextFromFNDocID : function ( aBrowserXULDOMWindow , afndocid )
	{
		let aOETController   =  this;
		let adocGuid = afndocid ;
		let ownerId = aBrowserXULDOMWindow.ECHelperNS.getOwnerId();
		let fndocProcessor = new aBrowserXULDOMWindow.processAFnDoc_Gneral(adocGuid, ownerId);
		fndocProcessor.on("getDocById", function(responseContent){
		       let docinfo = fndocProcessor.getInfoFromGetDocByIdResult(responseContent);        
		       if(docinfo != null)
		       {
			   if(docinfo[0] == "text_plain")
			   {
			   
			       fndocProcessor.downloadFnDoc(docinfo[1]);
			   }
			   else if(docinfo[0] == "image")
			   {
				//todo
			   }
			   else
			   {
				//todo
			   }
		       }
		   }	);
    
		function showText(aOETController, gotBlob)
		{
		    if(!aOETController.initialized)//canceled
		    {
			return ;  
		    }
		    oFReaader = new aBrowserXULDOMWindow.FileReader();
		    oFReaader.onload = function(oFRevent)
		    {
		       let msgEncodedTxt = oFRevent.target.result;
		       msgEncodedTxt = aBrowserXULDOMWindow.btoa(msgEncodedTxt);	
		       msgEncodedTxt = "BEGIN_FN_SECURE_MESSAGE_" + msgEncodedTxt + "_END_FN_SECURE_MESSAGE";
		       
		       aOETController.show_plainTextFromFNECiphertext ( msgEncodedTxt);
		    }
		    oFReaader.readAsBinaryString(gotBlob);
		}
    
        
		fndocProcessor.on("downloaded", function(gotBlob){
			let docinfo = fndocProcessor.m_docinfo;
			if(docinfo[0] == 'text_plain')
			{
			    showText(aOETController, gotBlob);
			}
			else if(docinfo[0] == 'image')
			{
				//todo
			}        
		    });
    
		fndocProcessor.on("error", function(errorMessage){
		
			//alert_log__("getplainTextFromFNDocID happen erros: " + errorMessage.msg);
		   });    
		fndocProcessor.getDocById();
	 
		return ;
 	},
 	
 	show_plainTextFromFNECiphertext : function ( aFNEEncodedTxt)
 	{
 	
 		let aPlainTextFNCipherCombiner = Cc["@fntechnologies.com/firefoxhelper/plaintextfnciphercombiner;1"].
                     createInstance(Ci.IPlainTextFNCipherCombiner);
		if(!aPlainTextFNCipherCombiner)
		{
			return false;
		}
    
		aPlainTextFNCipherCombiner.appendText(  aFNEEncodedTxt, true);//true : need_decrypt
		aPlainTextFNCipherCombiner.showInElement(this.originalEditor.ownerDocument.defaultView , this.originalEditor, true );//this.initialized
		return true;
	},
	
	
	
	getEditorContent : function(useHTML)
	{
		let editor =  this.originalEditor;
		
		return g_OETManager.getEditorContent (editor , useHTML );
	},
	 
	sendoutData : function (evt)
	{
		alert_log__("sendoutData")
		if(!g_OETManager.is_fn_integrating_Editor( this.originalEditor) )
		{
		    return ;
		}
					
		if( !elementInDOM(this.originalEditor) )
		{
			this.fncipher_cache = "";
			return;
		}
		//send out this.fncipher_cache ;
		if(evt.target == this.originalEditor.ownerDocument)
		{
			this.fnpresent(); // this is bug fixing work around : sometimes the send button is clicked but the editor is not blur. if so , there is no encryption called 
		
			let self = this;
			this.originalEditor.ownerDocument.defaultView.setTimeout( function()
				{	
					alert_log__( " will call addFnDocid in a timeout 100 : " + self.fncipher_cache);
					if(self.fncipher_cache.length > 0)
					{
						let data = const_fndocidprefix + self.fncipher_cache;
						
						let aFnDocid_type_obj = {biztype: 0 , fndocid :self.fncipher_cache, pkey: self.fncipher_key}; // biztyp: 0  : mean : the fndoic is text 
						addFnDocid(self.originalEditor.ownerDocument, aFnDocid_type_obj);
						self.fncipher_cache = "";//discards the cache
					}
				},100);;
			
		}
	},
	
}
//class extend
OETController.prototype = new ECEventEmitter();

(function(oriProto, extendedProp){    
	for(let key in extendedProp)
	{
		oriProto[key] = extendedProp[key];
	}
	return this;
})(OETController.prototype, OETController_ExtendedProp);



/// util functions 
function array_removeat(arrayObj, index)
{
	if(index >= 0 && index <  arrayObj.length)
	{
		arrayObj.splice(index, 1);// use splice to remove a  content
	}	
}
function getATopBrowserXulwindow()
{
    let windowMediator = Cc["@mozilla.org/appshell/window-mediator;1"].
                     getService(Ci.nsIWindowMediator);
    let windowsEnum = windowMediator.getEnumerator("navigator:browser");
    while (windowsEnum.hasMoreElements()) 
    {
        let win = windowsEnum.getNext();
        if (win.closed)
            continue;

       if(win.location == "chrome://browser/content/browser.xul" )
       {
         return win;
       }
    }
    return null;
}
function getCurrentTabBrowserFromHTMLDoc(htmlDocument)
{
	let aTopBrowser = getATopBrowserXulwindow();
	if(aTopBrowser )
	{
			return aTopBrowser.ECHelperNS.getCurrentTabBrowserFromHTMLDoc(htmlDocument);
	}
	return null;
}

//exports
const const_fndocidprefix = "HJContentID:"
const const_uuid_pattern = "([a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12})";
const const_fndocid_pattern = const_fndocidprefix + const_uuid_pattern;


function matchFnDocIdFromString (theString)
{
    var fnidFinder = new RegExp(const_fndocid_pattern , 'gm');        	    
 	var match = theString.match(fnidFinder);
    return match;
};
function remove_fndocid_prefix( afndocid)
{
    return afndocid.substr(const_fndocidprefix.length, afndocid.length - const_fndocidprefix.length  )  ;
}

/////////

// class OETManager
function OETManager(){

	this.editorHandlers = [];
	this.documents = []; // the documents which are being taking care
}

OETManager.prototype = {

	log: function (whattosay)
	{
		alert_log__(whattosay)
	},
	
	handle: function (aEditor)
	{

		var index = this.find_editorHandler_index(aEditor);
		if(index  == -1) // not exist
		{
			var anOETController = new OETController(aEditor);
			anOETController.add_handler();
			let same  = anOETController.originalEditor == aEditor;
			this.editorHandlers.push( anOETController );
			this.add_body_unload_listener( aEditor );
		}
	},
	
	release: function(aEditor)
	{
		var index = this.find_editorHandler_index(aEditor);
		if(index  != -1) //  exists
		{
			var anOETController = this.editorHandlers[index];
			if(anOETController)
			{
				anOETController.remove_handler();
			}
			array_removeat(this.editorHandlers, index);
		}
	},
	
	release_all : function ()
	{
		this.editorHandlers.splice(start, editorHandlers.length);// use splice to clear the content
		
	},
	
	find_editorHandler_index: function(aObject)
	{
		let aObject_new = aObject;
		//return  the index of the found editorHandler, -1 : not found
		var found_index =  -1;
		let aObject_is_document =  false
		//if (aObject instanceof HTMLDocument)
		//{
		//	aObject_is_document = true;
		//}
		if (Object.prototype.toString.call(aObject) == "[object HTMLDocument]")
		{
			aObject_is_document = true;
		}
		if(aObject_is_document) //aObject is a document
		{
			for (var index = 0 ; index <  this.editorHandlers.length; index++ )
			{
				var anOETController = this.editorHandlers[index];
				if(anOETController)
				{
					if( anOETController.originalEditor.tagName == "IFRAME" )
					{
						if(anOETController.originalEditor.contentDocument === aObject)
						{
							found_index = index;
							break;
						}
					}
				}
			}
		}
		else
		{
			for (var index = 0 ; index <  this.editorHandlers.length; index++ )
			{
				var anOETController = this.editorHandlers[index];
				if(anOETController)
				{	
					let originalEditor  = anOETController.originalEditor;
				
					if( originalEditor == aObject_new)
					{
						found_index = index;
						break;
					}
				}
			}
		}	
		
		return found_index;
	},
	find_editorHandler: function(aEditor)
	{
		var found_index =  this.find_editorHandler_index(aEditor);
		if(found_index !=  -1)
		{
			var anOETController = this.editorHandlers[found_index];
			return anOETController;
		}
		return null;
	},
	
	release_body_unload: function(body)
	{
	},
	
	add_body_unload_listener:function(aEditor)
	{
		this.add_document(aEditor.ownerDocument);
	},
	
	add_document:function(aDocument)
	{
		var i = 0;
		var found  = false;
		for(i ; i < this.documents.length; i++ )
		{
			var adocument_in = this.documents[i];
			if(adocument_in  == aDocument)
			{
				found =  true;
				break;
			}
		}
		if(!found)
		{
			this.documents.push(aDocument) ;		
			aDocument.defaultView.addEventListener("unload", OET_window_unload, false);
		}
	
	},
	
	remove_document:function(aDocument)
	{
	
		//remove_handler
		for (var index = 0 ; index <  this.editorHandlers.length;  )
		{
			var anOETController = this.editorHandlers[index];
			if(anOETController)
			{
				if( anOETController.originalEditor.ownerDocument == aDocument)
				{
					anOETController.remove_handler();
					array_removeat(this.editorHandlers, index);
					continue;
				}
			}
			index++;
		}	
	
		var i = 0;
		var found  = false;
		for(i ; i < this.documents.length; i++  )
		{
			var adocument_in = this.documents[i];
			if(adocument_in  == aDocument)
			{
				found =  true;
				break;
			}
		}
		if(found)
		{
			aDocument.defaultView.removeEventListener("unload", OET_window_unload, false);
			array_removeat(this.documents, i);
		}

	},
	
	set_as_fn_integrating  : function( aEditor)
	{
		try
		{
			aEditor.setAttribute('fn-integrating', "emailbody");
			aEditor.ownerDocument.body.setAttribute('fn-integrating' ,"email" );
		}
		catch(err)
		{
		
		}
	},
	
	is_fn_integrating_page  : function( aDoc)
	{
		return aDoc.body.getAttribute('fn-integrating') == "email";
	},
	
	is_fn_integrating_Editor  :function( aEditor)
	{
		return aEditor.getAttribute('fn-integrating') == "emailbody";
	},
	
	isFNRTE_toggleOption : function(aEditor)
	{
		return aEditor.getAttribute('fn-toggle-option') == "FNRTE";
	},
	
	getEditorContent  :function(editor, useHTML )
	{//todo
		//iframe
		//textarea
		
		if(editor.tagName == "TEXTAREA" || editor.tagName == "INPUT" )
		{
			return editor.value;
		}
		if(editor.tagName == "IFRAME" )
		{
			if(useHTML)
			{
				return editor.contentDocument.body.innerHTML
			}
			else
			{
				return editor.contentDocument.body.contentText
			}
		}
		if(useHTML)
		{
			return editor.innerHTML
		}
		else
		{
			return editor.ContentText
		}
	},
	// this is a function provides insert invitation not for 'original' type of editor and not for integrated editor
	append_invitation: function(editor, untrustedEmails_in, usingHTML)
	{
		let untrustedEmails = "";
		if (editor.currentReaders) {
			for ( let key in editor.currentReaders)
			{
				let ownerID = editor.currentReaders[key];
				if(ownerID && ownerID != 0)
				{
				}
				else
				{
					if(untrustedEmails.length > 0 )
					{
						untrustedEmails +=";"
					}
					untrustedEmails += key
				}
			}//for	
		}
		else{
			untrustedEmails = untrustedEmails_in;
		}
		if(untrustedEmails.length > 0)
		{
			if(!g_OETManager.is_fn_integrating_Editor(editor ) )
			{
				{
					var FNJSAPICaller = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
									createInstance(Components.interfaces.IFNWebSvrJSHelper);
					alert_log__("Components.interfaces.IFNWebSvrJSHelper")
					FNJSAPICaller.sendInvitation(untrustedEmails, 
						//this is a async function
						{call_withString: function(data_ivi ){
						alert_log__("Components.interfaces.IFNWebSvrJSHelper call  back")
							content = data_ivi;
							g_OETManager.setEditorContent_inner_(editor , content, usingHTML, true, false); // need append, nedd a stroke?
						} });
				}
			}
		 }
	},
	setEditorContent  :function(editor , content, usingHTML, append)
	{
		content =  "HJContentID:"+content;
		//shouldSendInvitation is set before call this function 
		
		alert_log__("setEditorContent editor.shouldSendInvitation: " +  editor.shouldSendInvitation);				
		
		if(editor.shouldSendInvitation !== undefined)	
		{
			if(editor.shouldSendInvitation == true)
			{
				content = "HackJacket Protected \n" + 
					  "Start communicating securely (It's free!) \n" +
					"Go To: http://download.HacketJacket.com \n" + content;
			}
			// invitation data
			try
			{
				let untrustedEmails = "";
				for ( let key in editor.currentReaders)
				{
					let ownerID = editor.currentReaders[key];
					if(ownerID && ownerID != 0)
					{
					}
					else
					{
						if(untrustedEmails.length > 0 )
						{
							untrustedEmails +=";"
						}
						untrustedEmails += key
					}
				}//for
				alert_log__("setEditorContent editor.shouldSendInvitation untrustedEmails :  " +  untrustedEmails.toString() );	
				if(untrustedEmails.length > 0)
				{
					var FNJSAPICaller = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
									createInstance(Components.interfaces.IFNWebSvrJSHelper);
					FNJSAPICaller.sendInvitation(untrustedEmails, 
					//this is a async function
					{call_withString:function(data_ivi ){
						content += "\n" + data_ivi;
						alert_log__("setEditorContent editor.shouldSendInvitation FNJSAPICaller.sendInvitation callback  data_ivi : " +  data_ivi);
						g_OETManager.setEditorContent_inner_(editor , content, usingHTML, append, false);
					}} );
				 }
			
			}//try
			catch(Err)	           
			{
				alert_log__(Err);
			}

			delete editor.shouldSendInvitation;
		}
		editor.removeAttribute("toggleCommandChecked");
		var fncontent_array = matchFnDocIdFromString (content );
		if(!fncontent_array  || fncontent_array.length != 1) // fndocid and only one
		{
			return ;
		}
		this.setEditorContent_inner_(editor , content, usingHTML, append);
	},
	
	setEditorContent_inner_ :function(editor , content, usingHTML, append, need_simulate_keystroke)
	{
		//iframe
		//textarea
		if(editor.tagName == "TEXTAREA" || editor.tagName == "INPUT" )
		{
			//simulate a key stroke, in some page like pacebook the editor need a focus->stroke and then can be used
			if(need_simulate_keystroke)
			{
				let aTopBrowser = getATopBrowserXulwindow();
				aTopBrowser.toMakeAkeyDownAction(editor);
			}
			
			if(append)
			{
				editor.value += content;
			}
			else{
				editor.value = content;
			}
		}
		else if(editor.tagName == "IFRAME" )
		{
			if(usingHTML)
			{
				if(append)
				{
					editor.contentDocument.body.innerHTML +=  content;
				}
				else{
					editor.contentDocument.body.innerHTML =  content
				}
			}
			else
			{
				if(append)
				{
					editor.contentDocument.body.contentText  +=  content;
				}
				else{
					editor.contentDocument.body.contentText  =  content
				}
			}
			return ;	
		}
		//for other element , like div
		else if(usingHTML)
		{
			if(append)
			{
				editor.innerHTML += content
			}
			else
			{
				editor.innerHTML = content
			}
		}
		else
		{// not been tested
			if(append)
			{
				editor.ContentText += content;
			}
			else
			{
				editor.ContentText = content;
			}
		}
	}
}//end of class



function alert_log__( whattosay )
{
	if(!using_OETManager_debug )
		return ;
	if(using_OETManager_debug_log)
	{
		gconsole.logStringMessage( " ---- " + whattosay)
		return ;
	}	
	var ww = Components.classes["@mozilla.org/embedcomp/window-watcher;1"].
	         getService(Components.interfaces.nsIWindowWatcher);
	
	var activewin = ww.activeWindow;

	var mainWindow = activewin.QueryInterface(Components.interfaces.nsIInterfaceRequestor).
	                     getInterface(Components.interfaces.nsIWebNavigation).
	                     QueryInterface(Components.interfaces.nsIDocShellTreeItem).
	                     rootTreeItem.
	                     QueryInterface(Components.interfaces.nsIInterfaceRequestor).
	                     getInterface(Components.interfaces.nsIDOMWindow);
	                     
	mainWindow.alert( " ---- " + whattosay)	;
}

var g_OETManager =  new OETManager();

var EXPORTED_SYMBOLS = ["g_OETManager"];
