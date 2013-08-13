// in this module , we are going to keep a group of editor to send the message

"use strict";
(function() {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;
// config:
//1 facebook message new 
// div id="pagelet_web_messenger" -- a good starting point
//editor : textarea : name="message_body", 
//send button : input value="Send" type="submit"
//tobox : td #text="To:" this element's next sibling element

//common 
var selector_editor = 'textarea[name="message_body"]';
var selector_sendbox = 'input[value="Send"][type="submit"]';
var selector_tobox = "//td[contains(.,'To:')]";

 
var new_message_editor_group = 
{
    "id":null,
    "editor": null, 
    "sendbox": null, 
    "tobox": null, 
};

var message_editor_group = new_message_editor_group;

function find_Editor_group()
{
  var a_id = WEB_CMM.uniqID(20);
  var role_name = WEB_CMM.PROJECT_NAME_PREFIX + WEB_CMM.INTEGRATING_ROLE_NAME + a_id;
  // find editor
  if(!message_editor_group.editor || message_editor_group.editor.length == 0)
  {
    var editors$ = $(selector_editor);

    var log_str = "find edtiors count is : " ;
    log_str += editors$.length;
    WEB_CMM.log( "facebook message-new : " + log_str + " " +a_id );

    if(editors$.length == 1)//shoult there is only one
    {
      editors$.attr(role_name, WEB_CMM.ROLE_NAME_EDIT_BOX);
      message_editor_group.editor = editors$;
      editors$.get(0).wrappedJSObject.fnhookedFlag = true; ////unsafe 
      message_editor_group.id = a_id;
    }
  }
  
  //find send button
  if(!message_editor_group.sendbox  || message_editor_group.sendbox.length == 0)
  {
    var send_boxes$ = $(selector_sendbox);

    var log_str = "find sendbox count is : " ;
    log_str += send_boxes$.length;
    WEB_CMM.log( "facebook message-new : " + log_str + " " +a_id );

    if(send_boxes$.length == 1)//shoult there is only one
    {
          send_boxes$.attr(role_name, WEB_CMM.ROLE_NAME_SEND_BOX);
          message_editor_group.sendbox = send_boxes$;
          hook_Send_box();
    }
  }
  
  //recepient box
    if(!message_editor_group.tobox || message_editor_group.tobox.length == 0)
    {
        var to_boxes$ =  $.xpath(selector_tobox).next("td");
        
        var log_str = "find to_boxe count is : " ;
        log_str += to_boxes$.length;
        WEB_CMM.log( "facebook message-new : " + log_str + " " +a_id );
      
        if(to_boxes$.length == 1)//shoult there is only one
        {
          to_boxes$.attr(role_name, WEB_CMM.ROLE_NAME_TO_BOX);
          message_editor_group.tobox = to_boxes$;
          //test code
          M_TEST.insert_data_ToBox(to_boxes$.get(0) );
        }
    }

}

function clean_Editor_group()
{
    var role_name = WEB_CMM.PROJECT_NAME_PREFIX + WEB_CMM.INTEGRATING_ROLE_NAME + message_editor_group.id;
    if( message_editor_group.editor)
    {
        delete message_editor_group.editor.get(0).wrappedJSObject.fnhookedFlag;//unsafe 
        WEB_CMM.log("facebook message-new :  clean " +  "editor_group.editor  " + message_editor_group.editor);
        message_editor_group.editor.removeAttr(role_name);
        WEB_CMM.log("facebook message-new : clean " + "editors removeAttr " + role_name);
        message_editor_group.editor = null;
    }

    if( message_editor_group.sendbox)
    {
        unhook_Send_box();
        message_editor_group.sendbox.removeAttr(role_name);
        WEB_CMM.log("facebook message-new : clean " +  "sendbox removeAttr " + role_name);
        message_editor_group.sendbox =  null;
    }

    if( message_editor_group.tobox)
    {
        message_editor_group.tobox.removeAttr(role_name);
        WEB_CMM.log("facebook message-new : clean " + "tobox removeAttr +  " + role_name);
        message_editor_group.tobox =  null;
    }
}

function call_simulate_mouse_click_jquery( box_obj$, timeout)
{
    if(!box_obj$)
        return;
    setTimeout(function(){
                box_obj$.trigger('click');
            }	, timeout);
}

function on_fnaction_over(evt)	
{
    try
    {
		WEB_CMM.log("facebook message-new : on_fnaction_over  " );
        if(evt.attrName == "fnremotehtmlreq-event-param"  )
        {
            if(evt.newValue=="true" || evt.newValue == "false")
            {
                document.body.removeEventListener("DOMAttrModified",on_fnaction_over, false);
                $(document.body).removeAttr("fnremotehtmlreq-event-param");
                message_editor_group.tobox.removeAttr("fnremotehtmlreq-event-param");
                message_editor_group.editor.removeAttr("fnremotehtmlreq-event-param");
                if (evt.newValue=="true") {
					WEB_CMM.log("facebook message-new : on_fnaction_over  evt.newValue==true " );
                    //should add invitation . when it comes, it is from CIA mode only
                    var untrustedEmails =  $(document.body).attr("fnremotehtmlreq-event-param-subvalue");
                    $(document.body).removeAttr("fnremotehtmlreq-event-param-subvalue");
                    if (untrustedEmails.length > 0) {
						WEB_CMM.log("facebook message-new : on_fnaction_over  untrustedEmails "  + untrustedEmails.toString() );
                        WEB_CMM.onprepare_send_invitation( message_editor_group.editor.get(0), untrustedEmails);
                    }
                }
                //click the button again
                call_simulate_mouse_click_jquery(  message_editor_group.sendbox, 300)
            }
        }
    }
    catch(err)
    {
        //alert(err)
    }
}

function on_sendbox_click(evt)
{
	WEB_CMM.log("facebook message-new : on_sendbox_click  " );
    //not fn toggle, just return 
    var fn_toggle_option = message_editor_group.editor.attr('fn-toggle-option');
    if (!fn_toggle_option ) {
        return;
    }
    /*
    //this may have risk, if hj_cocntrol_release_once is not set, the message can not be sent anymore
    if (evt.target.hj_cocntrol_release_once)
        evt.target.hj_cocntrol_release_once =  false;
        return ;
    }
    */
    //if uers trigger more times just let it go
	WEB_CMM.log("facebook message-new : on_sendbox_click  evt.target.hj_cocntrol : " + evt.target.hj_cocntrol );
	
    if(!evt.target.hj_cocntrol || evt.target.hj_cocntrol == 0)
    {
        evt.target.hj_cocntrol = 1;
    }
    else
    {
        evt.target.hj_cocntrol = 0;
		WEB_CMM.log("facebook message-new : on_sendbox_click  return 2dn time" );
        return;
    }
    evt.stopPropagation();
    evt.preventDefault();
                                    
    try{
        WEB_CMM.tell_to_box(message_editor_group.tobox.get(0))
        
        WEB_CMM.tell_editor( message_editor_group.editor.get(0) )
        
        WEB_CMM.fill_recepients( message_editor_group.editor.get(0), message_editor_group.tobox.get(0) )
        //alert("WEB_CMM.trigger_preSending")
        WEB_CMM.trigger_preSending()
        
        WEB_CMM.onAfter_preSending_event(on_fnaction_over);
        
    }
    catch( err )
    {
        //alert(err);
    }
}

function hook_Send_box()
{
    if( message_editor_group.sendbox)
    {
        var send_obj = message_editor_group.sendbox;
        if(send_obj)
        {
            send_obj.get(0).parentNode.addEventListener('click' , on_sendbox_click,true);
			WEB_CMM.log("facebook message-new : addEventListener sendbox click " );
        }
    }
    /*if(message_editor_group.editor)
    {
        var editor  = message_editor_group.editor.get(0);
        if (editor) {
            editor.addEventListener("fn_togglebackfinished", function(evt){
								
								WEB_CMM.log("facebook message-new : on event fn_togglebackfinished  will call_simulate_mouse_click_jquery" );
                                call_simulate_mouse_click_jquery(  message_editor_group.sendbox, 100)
                            }, false);
			WEB_CMM.log("facebook message-new : editor: addEventListener fn_togglebackfinished  " );
        }
    }*/
}

function unhook_Send_box()
{
    if( message_editor_group.sendbox)
    {
        var send_obj = message_editor_group.sendbox;
        if(send_obj)
        {
            send_obj.get(0).parentNode.removeEventListener('click' , on_sendbox_click,true);
			WEB_CMM.log("facebook message-new : removeEventListener sendbox click " );
        }
    }
}

function is_my_page(url_spec)
{
    var reg_URL = /^https:\/\/www.facebook.com\/messages\/new(\/?)/ ;
    var match = reg_URL.test( url_spec );
    return match;
}


self.port.on("getEditors", function(url_spec) {

    if( is_my_page(url_spec) )
    {
        if(document.URL == url_spec)
        {
            find_Editor_group();
        }
    }
    else
    {
        clean_Editor_group();
    }
});



//li class="fbTimelineUnit lastCapsule fbTimelineTwoColumn clearfix fbTimelineComposerCapsule"
//-- div class="timelineUnitContainer fbTimelineComposerUnit"
//----div data-referrer="timeline_composer"
//------ ... div class="uiMentionsInput _11a"
// ------- ...  textarea class="uiTextareaAutogrow input autofocus mentionsTextarea textInput DOMControl_placeholder" name="xhpc_message_text"

/*

form rel="async" action="/ajax/updatestatus.php" method="post" onsubmit="return window.Event &amp;&amp; Event.__inlineSubmit &amp;&amp; Event.__inlineSubmit(this,event)" 
id="u_0_1g"><input type="hidden" name="fb_dtsg" value="AQAqKbtk" autocomplete="off">

*/
})();

