
/*
 * define globle values for fn_web_common and common functions
 */

"use strict";

var fn_web_common_ns  = (undefined === fn_web_common_ns) ? {}: fn_web_common_ns;

(function(ns)
{
	const HJContentIDRegEx = new RegExp('HJContentID:([a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12})', 'gm');        	    

	const emailAddrRegEx = new RegExp('(\\w+\\.)*\\w+@(\\w+\\.)+[A-Za-z]+', 'gm');
    var charstoformid = '_0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz'.split('');
    function uniqID(idlength) {
        if (! idlength) {
            idlength = Math.floor(Math.random() * charstoformid.length);
        }
        var uniqid = '';
        for (var i = 0; i < idlength; i++) {
            uniqid += charstoformid[Math.floor(Math.random() * charstoformid.length)];
        }
        return uniqid;
    }
    
    function log( msg)
    {
        if( !ns.nolog)
        {
            console.error("*****" + msg  );
        }
    }
    
    function setflag_toggle_notshowToBox(editor)
    {
        editor.wrappedJSObject.fnhookedFlag = true;
    }
    function clearflag_toggle_notshowToBox(editor)
    {
        delete editor.wrappedJSObject.fnhookedFlag;
    }
    
    
    function call_simulate_mouse_click( box_obj, timeout)
    {
        if(!box_obj)
            return;
        setTimeout(function(){
            var getX = function( obj ) {
                    if( obj == null ) {
                      return 0;
                    } else {
                      return obj.offsetLeft + getX( obj.offsetParent );
                    }
              }
              var getY = function( obj ) {
                    if( obj == null ) {
                      return 0;
                    } else {
                      return obj.offsetTop + getY( obj.offsetParent );
                    }
              }
              var evt = document.createEvent("MouseEvents");
              evt.initMouseEvent("mousedown", true, true, window,
                    0, 0, 0, 0, 0, false, false, false, false, 0, null);
              box_obj.dispatchEvent(evt);
              
            //top : it is window object
            try
            {
                var x = getX( box_obj );//getX( top ) - getX( box_obj ), 
                var y = getY( box_obj );//getY( top ) - getY( box_obj ),
                evt = document.createEvent("MouseEvents");
                evt.initMouseEvent("mousemove", true, true, window,
                        0, 0, 0, x,y, 
                        false, false, false, false, 0, null);
                box_obj.dispatchEvent(evt);
            }
            catch(err)
            {
            }

            var evt = document.createEvent("MouseEvents");
            evt.initMouseEvent("mouseup", true, true, window,
                      0, 0, 0, 0, 0, false, false, false, false, 0, null);
                    box_obj.dispatchEvent(evt);
			var evt2 = document.createEvent("MouseEvents");
            evt2.initMouseEvent("click", true, true, window,
                      0, 0, 0, 0, 0, false, false, false, false, 0, null);
            box_obj.dispatchEvent(evt2);
        }, timeout);
    }
    
    
    function tell_to_box( tobox)
    {
        var transobj = {funname:"setReceiptobjForInivitation_forRemoteWebpage", param:null};    	        
        $(tobox).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        tobox.dispatchEvent(event);
    }
    
    function fill_a_recepient(editor, email )
    {
        var transobj = {funname:"addReceiptsToAnInput_ForWebPage", param:email};    	        
        $(editor).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));              
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        editor.dispatchEvent(event); 
        
    }
    
    function fill_recepients(editor, tobox)
    {
        //file the recepients
        var emailAddrFinder = emailAddrRegEx;
        var htmlString = tobox.innerHTML;
        if (tobox.tagName === "INPUT" || tobox.tagName === "TEXTAREA") {
            htmlString  = tobox.value;
        }
        var results = htmlString.match(emailAddrFinder);
        for(var counter = 0; counter < results.length; ++counter)
        {
            var anEmailAddr = results[counter];
            fill_a_recepient(editor, anEmailAddr );
        } 
    }
    
    function tell_editor(editor)
    {
        var transobj = {funname:"setEditorobjForInivitation_forRemoteWebpage", param:null};    	        
        $(editor).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        editor.dispatchEvent(event);
    }
    
    function trigger_preSending()
    {
        var transobj = {funname:"SendInvitation_ForWebPage", param:null};    	        
        $(document.body).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        document.body.dispatchEvent(event);
    }
    
    
    /*function common_routing_on_After_preSending_event(evt)
    {
    	 try
    	    {
    	        if(evt.attrName == "fnremotehtmlreq-event-param"  )
    	        {
    	            if(evt.newValue=="true" || evt.newValue == "false")
    	            {	
    	                document.body.removeEventListener("DOMAttrModified",on_fnaction_over, false);
    	                $(document.body).removeAttr("fnremotehtmlreq-event-param");
    	                message_editor_group.tobox.removeAttr("fnremotehtmlreq-event-param");   
    	                message_editor_group.editor.removeAttr("fnremotehtmlreq-event-param");   
    	                if (evt.newValue=="true") {
    	                    //should add invitation . when it comes, it is from CIA mode only
    	                    var untrustedEmails =  $(document.body).attr("fnremotehtmlreq-event-param-subvalue");
    	                    $(document.body).removeAttr("fnremotehtmlreq-event-param-subvalue");
    	                    if (untrustedEmails.length > 0) {
    	                        WEB_CMM.onprepare_send_invitation(message_editor_group.editor.get(0), untrustedEmails);
    	                    }
    	                }
    	                //click the button again
    	                call_simulate_mouse_click_jquery(  message_editor_group.sendbox, 1000);
    			//WEB_CMM.call_simulate_mouse_click(  message_editor_group.sendbox.get(0), 1000);
    	            }
    	        }
    	    }
    	    catch(err)
    	    {
    	        //alert(err)
    	    }
    }*/
    
    function onAfter_preSending_event(callback)//should be rename as listen_After_preSending_event
    {
        document.body.addEventListener("DOMAttrModified", callback, false);  	
    }
    
    function listen_After_preSending_event(callback$, attached_data)//callback$ is for jquery 
    { 
		$(document.body).on("DOMAttrModified",  attached_data, callback$);	
    }
	function unlisten_After_preSending_event(callback$)
    {
		$(document.body).off("DOMAttrModified", callback$);	
		$(document.body).removeAttr("fnremotehtmlreq-event-param");		
    }
    function onprepare_send_invitation(editor, untrustedEmails)
    {
        var transobj = {funname:"AppenddInvitation_ForWebPage", param:untrustedEmails};    	        
        $(editor).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        editor.dispatchEvent(event);
    }
	
	//FN RTE related
	function fnrte_util_clean_content(afnrte)
	{
		try
		{
			var rteobj = afnrte['wrappedJSObject']; //rteobj is a plugin in webpage
			rteobj.ShowPlainTextMsg("", "", "") ;  
		}
		catch(err)
        {
			log("excpetion : util_clean_fndocid_from_fnrte : " + err  );
        }
	}
	
	function fnrte_util_get_fndocid(afnrte)
	{
		var fndocid="";
		try
		{
			var rteobj = afnrte['wrappedJSObject']; //rteobj is a plugin in webpage  and we are in sandbox , Notice the wrappedJSObject is workign or not
			var ret_content = rteobj.GetFNRTEContent();    
			ret_content = ret_content.replace("BEGIN_FN_SECURE_MESSAGE_", "");
			ret_content = ret_content.replace("_END_FN_SECURE_MESSAGE", "");
			
	        var sentdataObj = JSON.parse(rteobj.GetSendData(ret_content) );        
			if(sentdataObj.length <= 1)
			{
				WEB_CMM.log("error: rteobj plugin call GetSendData : length <= 1"  );
			}
			else
			{	   	      
			    for(var counter =0; counter <sentdataObj.length; ++counter)
			    {
				    var areader = sentdataObj[counter];
				    if(areader.ownerid == "fnDocId")
				    {
					   fndocid = atob(areader.pkey);
					   break;
				    }
				}
			}
		}
		catch(err)
        {
			log("excpetion : util_get_fndocid_from_fnrte : " + err  );
            return null;
        }
		log("util_get_fndocid_from_fnrte is :  " + fndocid  );		
		return fndocid;
    }	
	function markEditor_fnIntegrated_flag(editors)
	{
		editors.wrappedJSObject.fnhookedFlag = true; ////unsafe 
	}
	
	function removeEditor_fnIntegrated_flag(editors)
	{
		delete editors.wrappedJSObject.fnhookedFlag ; ////unsafe 
	}
	
	Array.prototype.getUnique = function(){
		var u = {}, a = [];
		for(var i = 0, l = this.length; i < l; ++i){
		  if(u.hasOwnProperty(this[i])) {
			 continue;
		  }
		  a.push(this[i]);
		  u[this[i]] = 1;
		}
		return a;
	}
    //export
    //functions
	function Array_getUnique(array_in)
	{
		var u = {}, a = [];
		for(var i = 0, l = array_in.length; i < l; ++i){
		  if(u.hasOwnProperty(array_in[i])) {
			 continue;
		  }
		  a.push(array_in[i]);
		  u[array_in[i]] = 1;
		}
		return a;
		
	}
	
	ns.Array_getUnique = Array_getUnique;
    ns.HJContentIDRegEx = HJContentIDRegEx;
    ns.emailAddrRegEx = emailAddrRegEx;
    ns.nolog = false;
    ns.uniqID = uniqID;
    ns.log = log;
    ns.setflag_toggle_notshowToBox =  setflag_toggle_notshowToBox;
    ns.clearflag_toggle_notshowToBox =  clearflag_toggle_notshowToBox;
    ns.call_simulate_mouse_click =  call_simulate_mouse_click;
    
    ns.tell_to_box = tell_to_box;
    ns.fill_a_recepient = fill_a_recepient;
    ns.fill_recepients = fill_recepients;
    ns.tell_editor = tell_editor;
    ns.trigger_preSending = trigger_preSending;
    ns.onAfter_preSending_event = onAfter_preSending_event;//use listen_After_preSending_event instead
    ns.listen_After_preSending_event = listen_After_preSending_event;
	ns.unlisten_After_preSending_event = unlisten_After_preSending_event;
    ns.onprepare_send_invitation = onprepare_send_invitation;
	
    
    ns.markEditor_fnIntegrated_flag = markEditor_fnIntegrated_flag;
	ns.removeEditor_fnIntegrated_flag = removeEditor_fnIntegrated_flag;
	
	//fntre
	ns.fnrte_util_clean_content = fnrte_util_clean_content;
	ns.fnrte_util_get_fndocid =  fnrte_util_get_fndocid;
    
    //const values
    ns.PROJECT_NAME_PREFIX   = "fbm";
    ns.INTEGRATING_ROLE_NAME = "_integerating_role_";
    ns.ROLE_NAME_TO_BOX   = "to_box_";
    ns.ROLE_NAME_EDIT_BOX = "edit_box_";
    ns.ROLE_NAME_SEND_BOX = "send_box_";
    ns.ROLE_NAME_SEND_BY_KEYPRESS_ENTER = "keypress_enter";
    ns.ROLE_NAME_SEND_BY_MOUSE_CLICK = "mouse_click";
	ns.FIND_COMPOSER_TIMER_SPAN = 200;
    
})(fn_web_common_ns);

//fn_web_conversation_common_ns has some common functions for fn web conversation logic
/*var fn_web_conversation_common_ns  = (undefined === fn_web_conversation_common_ns) ? {}: fn_web_conversation_common_ns;
(function(ns)
{
	const c_save_Stream_topic_msg = "save-Stream-topic";
	function Struct_conversation_tobox_obj_define()
	{
		this.attrName="";
		this.attrVal="";
	}
	
	function create_Struct_conversation_tobox_obj_define()
	{
		var obj =  new Struct_conversation_tobox_obj_define();
		obj.attrName = fn_web_common_ns.uniqID(10);
		obj.attrVal  = fn_web_common_ns.uniqID(10);
		return obj;
	}
	
	
	function save_Stream_topic(aworker, topic, tobox)//tobox is html Element
	{
		var aconversation_tobox_obj = create_Struct_conversation_tobox_obj_define();
		$(tobox).attr(aconversation_tobox_obj.attrName, aconversation_tobox_obj.attrVal);
		var ajson_str = JSON.stringify({"topic":topic,"tobox":aconversation_tobox_obj});
		aworker.port.emit(c_save_Stream_topic_msg, ajson_str, tobox);
	}
	
    //export
    //functions
    ns.save_Stream_topic = save_Stream_topic;
    ns.conversation_tobox_obj_define = conversation_tobox_obj_define;
    ns.create_Struct_conversation_tobox_obj_define = create_Struct_conversation_tobox_obj_define;
    

    
})(fn_web_conversation_common_ns);*/