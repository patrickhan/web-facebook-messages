
/*
 * define globle values for fn_web_common
 */

"use strict";

var fn_web_common_ns  = (undefined === fn_web_common_ns) ? {}: fn_web_common_ns;

(function(ns)
{
    var charstoformid = '_0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz'.split('');
    function uniqID(idlength) {
        //var charstoformid = '_0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz'.split('');
        if (! idlength) {
            idlength = Math.floor(Math.random() * charstoformid.length);
        }
        var uniqid = '';
        for (var i = 0; i < length; i++) {
            uniqid += charstoformid[Math.floor(Math.random() * charstoformid.length)];
        }
        return uniqid;
    }
    
    function log( msg)
    {
        if( !ns.nolog)
        {
            console.log("*****" + msg  );
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
        }, timeout);
    }
    
    
    function tell_to_box( tobox)
    {
        var transobj = {funname:"setReceiptobjForInivitation_forRemoteWebpage", param:null};    	        
        $(tobox).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
        //$(tobox).trigger("fnRemoteHtmlReq-event") // is it work
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        tobox.dispatchEvent(event);
    }
    
    function fill_a_recepient(editor, email )
    {
        var transobj = {funname:"addReceiptsToAnInput_ForWebPage", param:email};    	        
        $(editor).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));              
        //$(editor).trigger("fnRemoteHtmlReq-event") // is it work
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        editor.dispatchEvent(event)   
        
    }
    
    function fill_recepients(editor, tobox)
    {
        //file the recepients
        var emailAddrFinder = new RegExp('(\\w+\\.)*\\w+@(\\w+\\.)+[A-Za-z]+', 'gm');
        var htmlString = tobox.innerHTML;
        if (tobox.tagName === "INPUT" || tobox.tagName === "TEXTAREA") {
            //code
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
        //$(editor).trigger("fnRemoteHtmlReq-event") // is it work
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        editor.dispatchEvent(event);
    }
    
    function trigger_preSending()
    {
        var transobj = {funname:"SendInvitation_ForWebPage", param:null};    	        
        $(document.body).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
        //$(document.body).trigger("fnRemoteHtmlReq-event") // is it work?
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        document.body.dispatchEvent(event);
    }
    
    function onAfter_preSending_event(callback)
    {
        document.body.addEventListener("DOMAttrModified", callback, false);   
    }
    
    function onprepare_send_invitation(untrustedEmails)
    {
        var transobj = {funname:"AppenddInvitation_ForWebPage", param:untrustedEmails};    	        
        $(document.body).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
        //$(document.body).trigger("fnRemoteHtmlReq-event") // is it work?
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        document.body.dispatchEvent(event);
    }

    //export
    //functions
    ns.nolog = true;;
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
    ns.onAfter_preSending_event = onAfter_preSending_event;
    ns.onprepare_send_invitation = onprepare_send_invitation;
    
    //const values
    ns.PROJECT_NAME_PREFIX   = "fbm";
    ns.INTEGRATING_ROLE_NAME = "_integerating_role_";
    ns.ROLE_NAME_TO_BOX   = "to_box_";
    ns.ROLE_NAME_EDIT_BOX = "edit_box_";
    ns.ROLE_NAME_SEND_BOX = "send_box_";
    ns.ROLE_NAME_SEND_BY_KEYPRESS_ENTER = "keypress_enter";
    ns.ROLE_NAME_SEND_BY_MOUSE_CLICK = "mouse_click";
    //const FN_INTEGRATING_ATTR_NAME = "fn-integrating";
    //const FN_INTEGRATING_ATTR_VALUE = "emailbody";
    //new_message_editor_group.editor.removeAttr("fn-integrating") == "emailbody";
    
})(fn_web_common_ns);