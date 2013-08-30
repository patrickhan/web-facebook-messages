/*
 * This js is for the 'chat'  in face book.
 * It will pupup fn UI if the chat input toggle selects CIA mode
  */


"use strict";

(function(){
    
//var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;
var WEB_TEST = facebook_test_ns;//.create_test_panel =  create_test_panel;


    const g_facebook_chat_div_classname =  "fbNubFlyout fbDockChatTabFlyout";
	const g_fn_toggle_init_event_name = "FnInputEleFocus";
	const g_facebookchat_fndocid_prefix = "fnfacebookchatid:";
	const g_APP_NAME = "facebook";
	
	function findFacebookChatTabElementFromInputbox(anInput)
	{
        if(!anInput)
	    {
	      return null;
	    }
		var chatTag$ =  $(anInput).closest("div[class='"+ g_facebook_chat_div_classname +"']");
		if(chatTag$)
		{
			return chatTag$
		}
	    return null;
	}
	
	function isFacebookChatInputbox( anInput )
	{
        if(findFacebookChatTabElementFromInputbox ( anInput) )
	    {
	      return true;
	    }
	    return false;
	}
	
	//const g_fn_html_chat_tag_str1 = '<div class="fn-facebook-chat"><div class="fn-facebook-chat-uppart"><object type="application/fn-richeditor-proxy" class="RichTextEditorR"><param name="create_param" value="&winmode=readonly&scrollintoview=true"/> </object></div><div class="fn-facebook-chat-downpart"><object type="application/fn-richeditor-proxy" class="RichTextEditorS"></object></div></div>';
const g_fn_html_chat_tag_str='	<div class="fn-facebook-chat">\
	  <div class="fn-facebook-chat-title">\
	  <a>FN chat UI</a><a class="close-button">x</a>\
	  </div>\
	  <div class="fn-facebook-chat-uppart" >\
	    <object type="application/fn-richeditor-proxy" class="RichTextEditorR"  >\
		  <param name="create_param" value="&winmode=readonly&scrollintoview=true"/>\
		</object>\
      </div>\
	  <div class="fn-facebook-chat-downpart"  >\
	   <span class="RichTextEditorS-holder">\
        <object type="application/fn-richeditor-proxy" class="RichTextEditorS"  >\
		</object>\
		</span>\
		<a class="send-button">&#8629</a>\
	  </div>	  \
	</div>\
	</div>';
	
	function get_fnchatTag_in_facebookchatTag(afacebookchatTag)
	{
		var afntag$ = $(afacebookchatTag).find(".fn-facebook-chat");
		return afntag$;
	}
	
	function get_inputbox_in_facebookchatTag(afacebookchatTag)
	{
		var input$ = $(afacebookchatTag).find("textarea");
		return input$;
	}
	
	function triggerkeypress_enter(target)
	{
	    var keyEvt = document.createEvent("KeyboardEvent");
        keyEvt.initKeyEvent("keypress", true, true, null, false, false, false, false, 13, 13);
        target.dispatchEvent(keyEvt);       
	}
	
	function jquery_triggerkeypress_enter(input$)
	{//this dose not work!!!
	    var e_keydown = jQuery.Event("keydown");
		e_keydown.which = 13; //enter
		e_keydown.keyCode = 13;
		input$.trigger(e_keydown);
		
		var e_keypress = jQuery.Event("keypress");
		e_keypress.which = 13; //enter
		e_keypress.keyCode = 13;
		input$.trigger(e_keypress);
		
		var e_keyup = jQuery.Event("keyup");
		e_keyup.which = 13; //enter
		e_keyup.keyCode = 13;
		input$.trigger(e_keyup);     
	}
	
	function sendmsg_in_facebookchatTag(afacebookchatTag, amsg)
	{
		WEB_CMM.log(" sendmsg_in_facebookchatTag:   "  + amsg);
		try
		{
		  var input$ =get_inputbox_in_facebookchatTag(afacebookchatTag);
		  input$.val(amsg);
		  triggerkeypress_enter(input$[0]);
		  //jquery_triggerkeypress_enter(input$);
		}
		catch(err)
		{
			WEB_CMM.log(" sendmsg_in_facebookchatTag:   error : "  + err);
		}
	}
	
	function get_closebutton_in_fnchattag(achatTag$)
	{
		return achatTag$.find(".close-button");
	}
	function get_sendbutton_in_fnchattag(achatTag$)
	{
		return achatTag$.find(".send-button");
	}
	function on_fntag_close(evt)
	{
		WEB_CMM.log(" on_fntag_close:   "  );
		if(evt.data)
		{
			show_fn_chatTag(evt.data.fnchattag, false);
		}
	}
	
	function get_reader_in_fnchattag(fnchattag$)
	{
		return fnchattag$.find(".RichTextEditorR");
	}
	function get_input_in_fnchattag(fnchattag$)
	{
		//return fnchattag$.children(".RichTextEditorS") // this not work ?
		return fnchattag$.find(".RichTextEditorS-holder > object");
	}
	
	function fillRecipientsTo_fnrecipients(the_A_Node, facebookchattag)
	{
	    var target = facebookchattag;
	    if(the_A_Node.getAttribute("aria-label") == null)
        {   
            target.m_fnrecipients.push(the_A_Node.innerHTML);
            WEB_CMM.log(" fillRecipientsTo_fnrecipients: m_fnrecipients :  " + target.m_fnrecipients );
            return;
        }
        else
        {	 
            
            setTimeout(function(){
                var funobj = null;
                document.body.addEventListener("DOMNodeInserted", funobj = function(evt){	                                        
                    document.body.removeEventListener("DOMNodeInserted", funobj, false);	                                                      
                    //alert(evt.target.textContent);
                    var nameTextNodes = document.evaluate('.//i/following-sibling::div/text()', 
                        evt.target, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null);
                    
                    for(var counter = 0; counter < nameTextNodes.snapshotLength; ++counter)
                    {   
                        target.m_fnrecipients.push(nameTextNodes.snapshotItem(counter).nodeValue);
                    }
                    WEB_CMM.log(" fillRecipientsTo_fnrecipients: m_fnrecipients:  " + target.m_fnrecipients );
                }, false)
                var evObj = document.createEvent('MouseEvents');
                evObj.initEvent( 'mouseenter', true, false );
                the_A_Node.dispatchEvent(evObj);	  
                var evObj = document.createEvent('MouseEvents');
                evObj.initEvent( 'mouseover', true, false );
                the_A_Node.dispatchEvent(evObj);	                                                                   
            }, 300);	
        }
	}	
	
	/*function set_fntag_recipients(facebookchattag, fnchattag$)
	{
		WEB_CMM.log(" set_fntag_recipients: in  " + facebookchattag);
		//get the titlebar text in a facebook chat tag
		var the_A_Node$ =  $.xpath('.//a[contains(@class,"titlebarText") and @role="button"]', facebookchattag);
		if(the_A_Node$.length > 0)
		{	                            
			var the_A_Node = the_A_Node$[0];	
			the_A_Node.m_fnEditObject = facebookchattag;
			alert(the_A_Node.m_fnEditObject )
			//add listener for user adding new recipients
			the_A_Node.addEventListener("DOMAttrModified", function(evt){
				var tempANode = evt.target;
				tempANode.m_fnEditObject.m_fnrecipients = [];
				fillRecipientsTo_fnrecipients(tempANode);//tempANode is the_A_Node
			}, false);
			the_A_Node.m_fnEditObject.m_fnrecipients = [];	                           
			fillRecipientsTo_fnrecipients(the_A_Node);
		}
	}*/
	
	function get_FacebookChat_Recipients(facebookchattag)
	{
		return facebookchattag.m_fnrecipients;
	}
	
	
	function access_FacebookChat_Recipients(facebookchattag)
	{
		WEB_CMM.log(" access_FacebookChat_Recipients: in  " + facebookchattag);
		try
		{
			//get the titlebar text in a facebook chat tag
			var the_A_Node$ =  $.xpath('.//a[contains(@class,"titlebarText") and @role="button"]', facebookchattag);
			if(the_A_Node$.length > 0 )
			{	                            
				var the_A_Node = the_A_Node$[0];	
				var target = facebookchattag;
				
				//add listener for user adding new recipients
				the_A_Node.addEventListener("DOMAttrModified", function(evt){
					var tempANode = evt.target;
					tempANode.m_fnEditObject.m_fnrecipients = [];
					fillRecipientsTo_fnrecipients(tempANode,target);//tempANode is the_A_Node
				}, false);
				target.m_fnrecipients = [];	                           
				fillRecipientsTo_fnrecipients(the_A_Node, target);
			}
		}
		catch(err)
		{
			WEB_CMM.log(" access_FacebookChat_Recipients: exception:  " + err);
		}
	}
	
	function get_fntag_inputmessage(fnchattag$)
	{
		var input$ =  get_input_in_fnchattag(fnchattag$);
		var msg = WEB_CMM.fnrte_util_get_fndocid(input$[0]);
		if(msg && msg.length > 0)
		{
			return  msg;
		}
		return null;
	}
	
	function clean_fntag_inputmessage(fnchattag$)
	{
		var input$ =  get_input_in_fnchattag(fnchattag$);
		WEB_CMM.fnrte_util_clean_content(input$[0]);
	}
	
	function callback_for_invitation(unknowReaders)
	{//todo , get the unknowReaders, must do invitation
		alert("callback_for_invitation : unknowReaders is " + unknowReaders);
	}
	
	function on_fntag_send(evt)
	{
		WEB_CMM.log(" on_fntag_send: in and evt.data.facebookchattag is   " + evt.data.facebookchattag );
		try
		{
			if(evt.data)
			{
				// we do not set the recipients to FNRTE , instead we add the recipients to the FNDOCID
				//set_fntag_recipients(evt.data.facebookchattag, evt.data.fnchattag);
				var Rcipients = get_FacebookChat_Recipients(evt.data.facebookchattag);
				var msg  = get_fntag_inputmessage(evt.data.fnchattag);
				if(msg)
				{
					//addReadersToDoc is in another js
					WEB_CMM.log("calling addReadersToDoc :g_APP_NAME=" + g_APP_NAME +" ,Rcipients=" + Rcipients + " ,msg="+msg ); 
					addReadersToDoc(g_APP_NAME, Rcipients, msg, callback_for_invitation);
					msg = g_facebookchat_fndocid_prefix + msg;
					sendmsg_in_facebookchatTag(evt.data.facebookchattag, msg);
					clean_fntag_inputmessage(evt.data.fnchattag);
				}
			}
		}
		catch(err)
		{
			WEB_CMM.log(" on_fntag_send: exception : "  + err);
		}
	}
	
	function add_listeners_for_buttons(afnchatTag$, chatTag)
	{
		var closebtn$ = get_closebutton_in_fnchattag(afnchatTag$);
		if(closebtn$.length > 0)
		{
			WEB_CMM.log(" create_fn_chatTag:  add closebtn listeners"  );
			closebtn$.on("click",{ fnchattag: afnchatTag$}, on_fntag_close);
		}
		var sendbtn$ = get_sendbutton_in_fnchattag(afnchatTag$);
		if(sendbtn$.length > 0)
		{
			WEB_CMM.log(" create_fn_chatTag:  add sendbtn listeners"  );
			sendbtn$.on("click",{ fnchattag: afnchatTag$ , facebookchattag: chatTag}, on_fntag_send);
		}
	}
	
	//facebook chat conversation struct
	function facebook_chat_conversation_class()
	{
		
		this.timestamp_="";// when the message is sent
		this.conversation_items_ = [];// array of facebook_chat_conversation_item_class
		this.toStringf = function toString_fun()
		{
			var outStr = "";
			for(var i = 0; i < this.conversation_items_.length; i++)
			{
				var item  =  this.conversation_items_[i];
				outStr +=item.toStringf(); 
			}
			return outStr;
			
		};
		
	}
	
	function diff_facebook_chat_conversation_class_objs(afacebook_chat_conversation_class_pre , afacebook_chat_conversation_class_pro)
	{
		var newobj = new facebook_chat_conversation_class();
		var pre = afacebook_chat_conversation_class_pre;
		var pro = afacebook_chat_conversation_class_pro;
		//by desing 	difflen > 0, because the chat history has more content in pro
		var len_pre = pre.conversation_items_.length;
		var len_pro = pro.conversation_items_.length;
		if(len_pro <= 0)
		{
			return null;
		}
		
		 
		var difflen = len_pro - len_pre;
		if(difflen < 0 )
		{
			WEB_CMM.log("   diff_facebook_chat_conversation_class_objs : difflen < 0  return pro" );
			return pro;
		}
		else if(difflen  == 0  )
		{
			WEB_CMM.log("   diff_facebook_chat_conversation_class_objs : difflen = 0  check the messages" );
			var items_diff =  diff_facebook_chat_conversation_item_class(pre.conversation_items_[len_pre-1], pro.conversation_items_[len_pro-1]);
			if(items_diff)
			{
				newobj.conversation_items_.push( items_diff ) ;
				WEB_CMM.log("   diff_facebook_chat_conversation_class_objs : items_diff   return newobj with items_diff " );
				return newobj;
			}
		}
		else
		{
			for(var i = pre.conversation_items_.length; i < pro.conversation_items_.length; i++)
			{
				newobj.conversation_items_.push(pro.conversation_items_[i]) ;
			}
			WEB_CMM.log("   diff_facebook_chat_conversation_class_objs : difflen > 0  return newobj" );
			return newobj;
			
		}
		return null;
	}
	
	
	
	//facebook chat conversation item struct
	function facebook_chat_conversation_item_class()
	{
		//this.id=0;//sequence
		this.sender_ = ""; //You[for memyself] or "John Smith"
		this.messages_ = []; //can have n messages
		this.timestamp_="";// when the message is sent
		this.toStringf = function toString_fun()
		{
			var outStr = "";
 
			var item  =  this 
			var sender = "sender=" + item.sender_ + "\n";
			outStr +=sender;
			for(var j = 0; j < item.messages_.length; j++)
			{
				var smg = "----msg"+j + "="+item.messages_[j]+ "\n";
				outStr +=smg;
			}
			var time = "datetime="+ item.timestamp_+ "\n";
			outStr +=time;
 
			return outStr;
			
		};
	}
	
	function diff_facebook_chat_conversation_item_class(conversation_item1, conversation_item2)
	{
		 if(conversation_item1.sender_ == conversation_item2.sender_)
		 {
			 var newitem = new facebook_chat_conversation_item_class();
			 newitem.sender_ = conversation_item1.sender_;
			 if(conversation_item1.messages_.length < conversation_item2.messages_.length)
			 {
				 for(var i = conversation_item1.messages_.length; i < conversation_item2.messages_.length; i++)
				 {
					 newitem.messages_.push(conversation_item2.messages_[i]) ;
				 }
				 return newitem;
			 }
		 }
		 else
		 {
			 return conversation_item2
		 }
		 
		 return null;
		 
	}
	
	//this function parse the dom in chatTag, and get the useful information, should be update based on the webpage!!!
	function get_facebook_chat_conversation_data( counter, chatTag)
	{
		WEB_CMM.log(" in  get_facebook_chat_conversation_data: counter=" + counter +",chatTag.change_counting['counter']="+chatTag.change_counting["counter"] );
		if(!chatTag.change_counting)
		{
			return;
		}
		
		if(chatTag.change_counting["counter"] != counter)
		{
			WEB_CMM.log(" return  get_facebook_chat_conversation_data: counter=" + counter +",chatTag.change_counting="+chatTag.change_counting["counter"]  );
			return;
		}
		delete chatTag.change_counting; // for next round
		get_facebook_chat_conversation_data_impl(  chatTag);
	}
	
	function get_facebook_chat_conversation_data_impl(  chatTag)	
	{	
		try
		{
		//WEB_CMM.log(" call get_facebook_chat_conversation_data: " + chatTag );
		var afacebook_chat_conversation_obj =  new facebook_chat_conversation_class();
		var fbChatConvItem$ = $(chatTag).find(".conversation").children(".fbChatConvItem");
		//WEB_CMM.log(" in  get_facebook_chat_conversation_data: fbChatConvItems len: " + fbChatConvItem$.length );
		
		fbChatConvItem$.each(  
			function( index ) {
				// 'this' is the element whose class is fbChatConvItem
				//WEB_CMM.log(" in  get_facebook_chat_conversation_data: get a fbChatConvItem, it is: " + this);
				var afacebook_chat_conversation_item_obj =  new facebook_chat_conversation_item_class();
				afacebook_chat_conversation_obj.conversation_items_.push(afacebook_chat_conversation_item_obj);				
				var afbChatConvItem = this;
				var profileLink$ = $(afbChatConvItem).find(".profileLink");
				
				//WEB_CMM.log("   get_facebook_chat_conversation_data: a fbChatConvItem, its 'profileLink'=" + profileLink$ +",its len="+profileLink$.length);
				if(profileLink$.length > 0 )
				{
					var sender  = profileLink$.attr("aria-label");
					if(sender && sender.length > 0)
					{
						//WEB_CMM.log("  get_facebook_chat_conversation_data: get a fbChatConvItem, sender is: " + sender);
						afacebook_chat_conversation_item_obj.sender_ = sender;
					}
				}//if(profileLink$.length > 0 )
				
				var messages_g$ = $(afbChatConvItem).find(".messages");
				//WEB_CMM.log("  get_facebook_chat_conversation_data: get a fbChatConvItem's '.messages' ==  messages group len:  " +messages_g$.length);
				if(messages_g$.length > 0)
				{
					var message_items$ =  messages_g$.children("div[data-jsid='message']");
					//WEB_CMM.log("  get_facebook_chat_conversation_data: get a fbChatConvItem's message items  len:  " +message_items$.length);
					if(message_items$.length > 0)
					{
						message_items$.each(
							function( index ) {
								var message = this;
								//WEB_CMM.log(" in  get_facebook_chat_conversation_data: get a message item it is: " +message);
								var content = $(message).text();
								if(content && content.length > 0)
								{
									//WEB_CMM.log("    get_facebook_chat_conversation_data: get a message, content is: " + content);
									afacebook_chat_conversation_item_obj.messages_.push( content );// this is the message content
								}
							}
						); //message_items$.each
					}//if(message_items$.length > 0)
				}//if(messages_g$.length > 0)
			}); //end of fbChatConvItem$.each
		    WEB_CMM.log("   get_facebook_chat_conversation_data: chat_conversation : " + afacebook_chat_conversation_obj.toStringf());
		    handle_conversation_content(chatTag,afacebook_chat_conversation_obj );
		}
		catch(err)
		{
			WEB_CMM.log("   get_facebook_chat_conversation_data: exception: " + err);
		}
		
		
	}
	
	function handle_conversation_content(chatTag, afacebook_chat_conversation_obj )
	{
		if(!chatTag.conversation_obj)
		{
			chatTag.conversation_obj = afacebook_chat_conversation_obj;
			//todo ... call sth to show afacebook_chat_conversation_obj
			 WEB_CMM.log("   please show these : " + afacebook_chat_conversation_obj.toStringf());
			//var afnchatTag$ = get_fnchatTag_in_facebookchatTag(chatTag); 
		}
		else
		{
			var diff = diff_facebook_chat_conversation_class_objs(chatTag.conversation_obj, afacebook_chat_conversation_obj);
			if(diff)
			{
				chatTag.conversation_obj = afacebook_chat_conversation_obj;
				WEB_CMM.log("   please show these : " + diff.toStringf());
				//var afnchatTag$ = get_fnchatTag_in_facebookchatTag(chatTag);
				//var afnchatTag$ = get_fnchatTag_in_facebookchatTag(chatTag);
				//var fn_rte_Reader$ = get_reader_in_fnchattag(afnchatTag$);
				//var fn_rte_Reader_ID = fn_rte_Reader$.attr('id');
				 
			}
		}
	}
	
	
	function listener_for_facebook_chat_changing(evt)
	{//todo
	
		WEB_CMM.log(" in listener_for_facebook_chat_changing: " + evt.data.facebookchattag );
		var target  =  evt.data.facebookchattag
		if(!target.change_counting )
		{
			target.change_counting = {"counter":0};
		}
		else
		{
			target.change_counting["counter"] +=1;
		}
		
		
		setTimeout(get_facebook_chat_conversation_data, 1000, target.change_counting["counter"] ,target)
	}
	
	function add_listener_for_facebook_chat_changing(chatTag)
	{//DOMAttrModified ? or DOMNodeInserted ? or other event
		WEB_CMM.log(" in add_listener_for_facebook_chat_changing: " + chatTag );
		 
		var fbNubFlyoutBody$ = $(chatTag).find(".fbNubFlyoutBody");
		if(fbNubFlyoutBody$.length > 0)
		{
			fbNubFlyoutBody$.on("DOMNodeInserted",  { facebookchattag: chatTag}, listener_for_facebook_chat_changing);
		}
	}
	
	function create_fn_chatTag(input, chatTag)
	{//to do : if user remove the CIA mode , clean the created fnchattag
		var afnchatTag$ = get_fnchatTag_in_facebookchatTag(chatTag);
		if(!afnchatTag$ || !afnchatTag$.length)
		{
			WEB_CMM.log(" create_fn_chatTag: " + chatTag );
			afnchatTag$ = $(g_fn_html_chat_tag_str).appendTo(chatTag);
			if(afnchatTag$ && afnchatTag$.length > 0)
			{
				
				add_listeners_for_buttons(afnchatTag$, chatTag);
				add_listener_for_facebook_chat_changing(chatTag);
				
				//add a id to fnrte reader object
				var fn_rte_Reader$ = get_reader_in_fnchattag(afnchatTag$);
				var uniqID = WEB_CMM.uniqID(8);
				fn_rte_Reader$.attr('id',uniqID);
				
			}
		}
	    return afnchatTag$;
	}
	
	function show_fn_chatTag(afn_chatTag$, show)
	{
		if(show)
		{
			afn_chatTag$.css("width","");
			afn_chatTag$.css("height","");
		}
		else
		{
			afn_chatTag$.css("width","1px");
			afn_chatTag$.css("height","1px");
		}
	}
	
	function firstTimedump_converstationContent(chatTag)
	{
		setTimeout( get_facebook_chat_conversation_data_impl, 2000,chatTag);
	}
	
	function toggle_FacebookChat( input, chatTag ,show)
	{
	    WEB_CMM.log(" toggle_FacebookChat: " + chatTag );
		if(!input || !chatTag)
		{
			return ;
		}
		
		try
		{
		  var afn_chatTag$ = create_fn_chatTag(input, chatTag);
		  if(afn_chatTag$.length > 0){
			  access_FacebookChat_Recipients(chatTag);
			  show_fn_chatTag(afn_chatTag$, show);
			  firstTimedump_converstationContent(chatTag);
		  }
		}
		catch(ee)
		{
		    WEB_CMM.log(" toggle_FacebookChat: on except :  " + ee );
		}
	}
	
	function editor_is_CIA_mode(editor)
	{//"fn-toggle-option" == "FNRTE"
		if(editor)
		{
			var is_CIA = $(editor).attr("fn-toggle-option") == "FNRTE";
			return is_CIA;
		}
		return false;
	}
	
	function _FNToggle_editor_focus_listener(evt) 
	{
		try
		{
			var editor = evt.target;
			if( !editor_is_CIA_mode(editor) )
			{
				return ;
			}
			var chatTag$ = findFacebookChatTabElementFromInputbox(evt.target);
		   if(chatTag$ &&  chatTag$.length > 0 )
		   {
		   
			  WEB_CMM.log(" trapped the event : " + g_fn_toggle_init_event_name);
			  evt.preventDefault();
			  evt.stopPropagation();
			  //by design : do toggle here
			  setTimeout( toggle_FacebookChat, 0, evt.target, chatTag$.get(0), true); 
			  
			  /*editor.addEventListener("keydown", function(evt)
			  {WEB_CMM.log(" keydown the event : " + evt);}, true);
			  
			  editor.addEventListener("keypress", function(evt)
			  {WEB_CMM.log(" keypress the event : " + evt);}, true);
			  
			  editor.addEventListener("keyup", function(evt)
			  {WEB_CMM.log(" keyup the event : " + evt);}, true);
			  */
		   }
		}catch(e)
		{
			WEB_CMM.log("error : " +  e);
		}
	}
		
	//hook ... it is no need to release?
	function add_FNToggle_editor_focus_listener() {
		document.addEventListener(g_fn_toggle_init_event_name, _FNToggle_editor_focus_listener, true);
	}
			

	function is_my_page(url_spec)
	{
		return true; //chat is in everywhere
	}        
			
	self.port.on("getEditors", function(url_spec) {

		if( is_my_page(url_spec) )
		{
			WEB_CMM.log(" face book chat is_my_page")
			add_FNToggle_editor_focus_listener();
			//WEB_TEST.create_test_panel();
		}

	});
         
})(); // end of (function(){


