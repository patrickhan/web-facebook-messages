Components.utils.import("resource://webpagesvrmoudleLoader/webpgjs/fndocidHarvestor.jsm"); // for addFnDocid
function SetEmailReceiptsElementByFnAttr_ForWebPage(doc, param, receipObj)
{
    doc.m_FN_receiptsObj = receipObj;
}

function SwitchCanvasPointerEvents_ForWebPage(doc, param)
{
    let PointerEventsVal = param;
    if(doc.hasFnDrawLay !== undefined)
    {
        let stackCanvasObj = doc.hasFnDrawLay;        
        stackCanvasObj.style.pointerEvents = PointerEventsVal;
    }
}

function release_initationElements(doc)
{
    if(doc.fntoggledPlg !== undefined)
    {
        delete doc.fntoggledPlg;
    }
    if(doc.m_FN_receiptsObj !== undefined)
    {
        delete doc.m_FN_receiptsObj;
    }
}

function SendInvitation_ForWebPage(doc, param, receipObj)
{
    //doc.fntoggledPlg is the editor 
    //for fn integrated webpage and the editor is a  non-fnrte editor
    //we trigger a event to do encryption by set the attribute 'togglecommandchecked =true' of the editor
	
	
    if(doc.fntoggledPlg !== undefined && doc.fntoggledPlg != null)
    {
	    let anOETController = g_OETManager.find_editorHandler(doc.fntoggledPlg);
	    if(anOETController)
	    {
		doc.fntoggledPlg.setAttribute('togglecommandchecked','true');// this will trigger anOETController to do a encryption
	    }
    }
    doc.m_FN_ToggledBackFndocids = [];
    let evt = document.createEvent("CustomEvent");
    evt.initCustomEvent("FnWillSendEvt", true, false, null);
    doc.dispatchEvent(evt);    
    if(doc.wrappedJSObject.EA1FC341_D9DC_4f03_9491_AEF9CD9803B4 !== undefined)
    {
        doc.fntoggledPlg = doc.wrappedJSObject.EA1FC341_D9DC_4f03_9491_AEF9CD9803B4;
    }
    setTimeout(processGotFndocids, 1000, doc);
    
    function processGotFndocids(doc)
    {
	try
	{
	    sortFnDocidOfADoc(doc);
	}
	catch(err)
	{
	   alert(err);
	}
		console.log(doc.m_FN_receiptsObj + "   " + doc.fntoggledPlg + " dfsdfsd   " + doc.m_FN_ToggledBackFndocids + " sdfasdfasd " + doc.m_FN_ToggledBackFndocids.length);
        if(doc.m_FN_receiptsObj !== undefined && doc.fntoggledPlg !== undefined
           && doc.m_FN_ToggledBackFndocids !== undefined &&
           doc.m_FN_ToggledBackFndocids.length > 0)
        {  
           let receiptsStringFromReceiptsString = ""
           let receiptsobj = doc.m_FN_receiptsObj;
		   
           if(receiptsobj.tagName == "INPUT" || receiptsobj.tagName == "TEXTAREA")
           {
               receiptsStringFromReceiptsString = receiptsobj.value;
           }
           else
           {
               receiptsStringFromReceiptsString = receiptsobj.innerHTML;
           }

           receiptsStringFromReceiptsString = ECHelperNS.removeNonSenseChars(receiptsStringFromReceiptsString);           
           let match = ECHelperNS.matchEmailFromString(receiptsStringFromReceiptsString);
           let isSendInivation = false;
           if(match != null && match.length > 0)
           {
		        let untrustedEmails ="";
                for(let i = 0; i < match.length; i++)
                {
                    let aEmail = match[i];
                    //Use the email to get ownerid
                    ContactModule.getOwnerIdByEmail(aEmail, function(result){
                        if(result != null && result.length > 0)
                        {
                            for(let resultCount = 0; resultCount < result.length; ++resultCount)
                            {
                                let ownerid = result[resultCount].ownerid;
                                let fndocids = doc.m_FN_ToggledBackFndocids;
                                for(let fndocidCounter = 0; fndocidCounter < fndocids.length; ++fndocidCounter)
                                {
                                    let fndocid = fndocids[fndocidCounter].fndocid;
				    let key =  fndocids[fndocidCounter].pkey;
                                    //Upload fndocid with this ownerid to server                           
                                    createAKeyForADocByOwnerId(fndocid, ownerid, key);
                                }
                            }
                        }
                        else
                        {
			   if(untrustedEmails.length > 0 )
			    {
				untrustedEmails +=";"
			    }
			    untrustedEmails += aEmail
                            if(isSendInivation == false)
                            {
                                isSendInivation = true;
                                let fndocids = doc.m_FN_ToggledBackFndocids;                                                
                                //Add an invitation fndoc to fn_inviation_doc_key                        
                                for(let fndocidCounter = 0; fndocidCounter < fndocids.length; ++fndocidCounter)
                                {
                                    let fndocid = fndocids[fndocidCounter].fndocid; 
				                    let key =  fndocids[fndocidCounter].pkey;					                    								
                                    addInvitationFndoc(fndocid, key);
                                }    
                            }                                            
                        }

                        
                        if(i == match.length)
                        {
                                
			    let temparray = [];
			    for(let count = 0; count < doc.m_FN_ToggledBackFndocids.length; ++count)
			    {
				temparray.push(doc.m_FN_ToggledBackFndocids[count].fndocid);
			    }
			    doc.m_FN_ToggledBackFndocids = temparray;
			    toggleBack_v2(doc, doc.m_FN_ToggledBackFndocids, null, false); //false Don't set focus when write back
			    if(isSendInivation == true)
                            {
				                doc.body.setAttribute("fnRemoteHtmlReq-event-param-subvalue", untrustedEmails);
                                doc.body.setAttribute("fnRemoteHtmlReq-event-param", "true");
				                release_initationElements(doc);
                            } 
                            else
                            {                            
                                doc.body.setAttribute("fnRemoteHtmlReq-event-param", "false");
                                release_initationElements(doc);
                            }
                        }
                    });
                }
            }
            else
            {                                        
                doc.body.setAttribute("fnRemoteHtmlReq-event-param", "false");
                release_initationElements(doc);
            }
        }
        else
        {                                    
            doc.body.setAttribute("fnRemoteHtmlReq-event-param", "false");
            release_initationElements(doc);
        }
    }
}

function RTEobjShowPlainTextMsgMixFormat_ForWebpage(doc, param, rteobj)
{
    let FNMessageMixFormat = Components.classes["@FNTechnologies.com/Mozilla/FNMessageMixFormat;1"].
		                      createInstance(Components.interfaces.IFNMessageMixFormat);
    for(let counter = 0; counter < param.length; ++counter)
    {
        let atxtobj = param[counter];
        if('plainText' in atxtobj)
        {
            FNMessageMixFormat.addPlainText(atxtobj.plainText);
        }
        else if('fndocid' in atxtobj)
        {            
            FNMessageMixFormat.addEncrpText(ECHelperNS.getOwnerId(), atxtobj.data, atxtobj.key);
        }
    }
    ECHelperNS.showTextInRTEWithMixFormater(rteobj, FNMessageMixFormat);
}

function RTEobjShowPlainTextMsgMixFormat_ForWebpage_V2(doc, param, rteobj)
{   
    let FNMessageMixFormat = Components.classes["@FNTechnologies.com/Mozilla/FNMessageMixFormat;1"].
		                      createInstance(Components.interfaces.IFNMessageMixFormat);
    for(let counter = 0; counter < param.length; ++counter)
    {
        let atxtobj = param[counter];
        if('plainText' in atxtobj)
        {
            FNMessageMixFormat.addPlainText(atxtobj.plainText);
        }
        else if('fndocid' in atxtobj)
        {            
            FNMessageMixFormat.addEncrpText(ECHelperNS.getOwnerId(), atxtobj.data, atxtobj.key);
        }
    }
    var aJsonFormat_readers =  new Object();
	var aFneBinaryData_base64 =  new Object(); 
	var afndocid  = null;
	try
	{
		afndocid =  FNMessageMixFormat.getNewEncrpytedText( 
											   aJsonFormat_readers, 
											   aFneBinaryData_base64);
	}
	catch(err)
	{
	  return;
	}
	
	aJsonFormat_readers = aJsonFormat_readers.value;
	aFneBinaryData_base64 = aFneBinaryData_base64.value;
	try
	{
		var sentdataObj = JSON.parse(aJsonFormat_readers );        
	}
	catch(err)
	{
		return;
	}
	var thepkey = null;
	var theownerid = null;
	for(var counter =0; counter <sentdataObj.length; ++counter)
	{
	  var areader = sentdataObj[counter];
	  if(areader.ownerid != "fnDocId")
	  {
		 thepkey = areader.pkey;		 
		 break;
	  }	  
	}  
	if(thepkey && aFneBinaryData_base64)     
	{	
	    rteobj.setAttribute("ownerid", ECHelperNS.getOwnerId());
	    rteobj.setAttribute("FnEnMsg", "BEGIN_FN_SECURE_MESSAGE_" +  aFneBinaryData_base64 + "_END_FN_SECURE_MESSAGE");
	    rteobj.setAttribute("Fnpkey", thepkey);
	    var winhandle = rteobj.getAttribute("fnpluginwindow");
	    ECHelperNS.postMsgToWindow(parseInt(winhandle), 0x410, 0, 0);
	}
}


function addReceiptsToAnInput_ForWebPage(doc, param, inputEle)
{
    //inputEle.currentReaders !== undefined
    if(inputEle.currentReaders !== undefined)
    {
	    let aEmail = param;		
		ContactModule.getOwnerIdByEmail(aEmail, function(result){		    
			if(result == null || result.length == 0)
			{
				inputEle.currentReaders[aEmail] = 0;
			}
			else
			{
				inputEle.currentReaders[aEmail] = result[0];
			}			
		});
        
    }
}

function setReceiptobjForInivitation_forRemoteWebpage(doc, param, receiptObj)
{
    doc.m_FN_receiptsObj = receiptObj; 
}

function setEditorobjForInivitation_forRemoteWebpage(doc, param, editObj)
{
    doc.fntoggledPlg = editObj; 
}

function AppenddInvitation_ForWebPage (doc, param, editObj) // new logic , should not be conflict with c++ logic
{
    let anOETController = g_OETManager.append_invitation(editObj, param);
}

function addReceiptsToAnInput_Forfacebook_replyMsg(doc, param, editObj)
{
    var to_box  = doc.getElementById(param);
    Components.utils.import("resource://browsercontent/FnGlobalObject.jsm");
    var pageMsg = doc.getElementById("pagelet_web_messenger");
    if(pageMsg == null) {
	return;
    }
    var objName = "webMessageEmails";
    var emailObj = FnGlobalObject.getObject(objName, node);
    if(emailObj) {
	if(emailObj.length > 0) {
	    //concat original emails
	    emailObj = emailObj[0];
	    g_OETManager.log(emailObj);
	    if (to_box) {
		to_box.innerHTML = emailObj;
	    }
	    
	    var inputEle = editObj;
	    if(inputEle.currentReaders !== undefined)
	    {
		let aEmail = emailObj;		
		    ContactModule.getOwnerIdByEmail(aEmail, function(result){		    
			if(result == null || result.length == 0)
			{
			    inputEle.currentReaders[aEmail] = 0;
			}
			else
			{
			    inputEle.currentReaders[aEmail] = result[0];
			}			
		    });
	    }
	}
    }
}

EcselfDefineGlobalScope.FnTextBoxBlurEvtProcess = function(doc, fnboxEle)
{
    var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
        createInstance(Components.interfaces.IFNWebSvrJSHelper);
	if(FnComHelper)
	{
	    var indexVal = FnComHelper.getFNTextBoxIndex(doc, fnboxEle);        
        if(indexVal.length > 0)
        {
            indexVal = "Fn_" + indexVal;            
        }
        else
        {
            indexVal = "";
        }
        //fnboxEle.nextElementSibling.setAttribute("value", indexVal);
        fnboxEle.nextElementSibling.value = indexVal;
        fnboxEle.removeAttribute("FNEncrypedCotent");
    }    
}

function getEmailsOfAnObject_facebook_forRemoteWebpage(doc, param, theobj)
{
    
    ContactModule.getfacebook_names(param, function(rets){
	alert(rets)
	if (!rets) {
	    return;
	}
	var names = [];
	for (var index = 0; index <rets.length; index++ ) {
	    names.push(rets[index].name);
	}
	var chattersArray =  names;
	theobj.m_tempchattersArray = chattersArray;
	var data = {"serviceName":"getImEmailByHandleAndName", "message": {
	    data : {"imName": "facebookName", "imHandle": chattersArray},
	    args : theobj,
	    finish: function(ret, ele1) {
		let responseEmails = [];
		    if(ret.length < ele1.m_tempchattersArray.length) {		        
			    responseEmails.push("iva@fn.com");
		    }	        
				    
		    for(var i=0;i<ret.length;++i) {
			    responseEmails.push(ret[i].emailAddress);
		    }
		    delete ele1.m_tempchattersArray;
		    ele1.setAttribute("getemailsofanobject_facebook_forremotewebpage_res", JSON.stringify(responseEmails));
	    },
	}};    
	new MessageProcessor.MsgServer().sendMsg(doc, new MessageProcessor.MsgServer().newMsg("selfMessageProcessor", data));
    });
}


