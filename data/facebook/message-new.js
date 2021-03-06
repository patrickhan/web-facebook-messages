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

function find_Editor_group()
{
  var a_id = WEB_CMM.uniqID(20);
  var role_name = WEB_CMM.PROJECT_NAME_PREFIX + WEB_CMM.INTEGRATING_ROLE_NAME + a_id;
  // find editor
  if(!new_message_editor_group.editor)
  {
    var editors$ = $(selector_editor);

    var log_str = "find edtiors count is : " ;
    log_str += editors$.length;
    WEB_CMM.log( log_str + " " +a_id );

    if(editors$.length == 1)//shoult there is only one
    {
      editors$.attr(role_name, WEB_CMM.ROLE_NAME_EDIT_BOX);
      new_message_editor_group.editor = editors$;
      editors$.get(0).wrappedJSObject.fnhookedFlag = true; 
      new_message_editor_group.id = a_id;
    }
  }
  
  //find send button
  if(!new_message_editor_group.sendbox)
  {
    var send_boxes$ = $(selector_sendbox);

    var log_str = "find sendbox count is : " ;
    log_str += send_boxes$.length;
    WEB_CMM.log( log_str + " " +a_id );

    if(send_boxes$.length == 1)//shoult there is only one
    {
          send_boxes$.attr(role_name, WEB_CMM.ROLE_NAME_SEND_BOX);
          new_message_editor_group.sendbox = send_boxes$;
          hook_Send_box();
    }
  }
  
  //recepient box
    if(!new_message_editor_group.tobox)
    {
        var to_boxes$ =  $.xpath(selector_tobox).next("td");
        
        var log_str = "find to_boxe count is : " ;
        log_str += to_boxes$.length;
        WEB_CMM.log( log_str + " " +a_id );
      
        if(to_boxes$.length == 1)//shoult there is only one
        {
          to_boxes$.attr(role_name, WEB_CMM.ROLE_NAME_TO_BOX);
          new_message_editor_group.tobox = to_boxes$;
          //test code
          M_TEST.insert_data_ToBox(to_boxes$.get(0) );
        }
    }

  find_Editor_group_test(a_id);
}

function clean_Editor_group()
{
    var role_name = WEB_CMM.PROJECT_NAME_PREFIX + WEB_CMM.INTEGRATING_ROLE_NAME + new_message_editor_group.id;
    if( new_message_editor_group.editor)
    {
        delete editors$.get(0).wrappedJSObject.fnhookedFlag;
        
        WEB_CMM.log("clean " +  "editor_group.editor  " + new_message_editor_group.editor);
        
        new_message_editor_group.editor.removeAttr(role_name);

        WEB_CMM.log("clean " + "editors removeAttr " + role_name);
        new_message_editor_group.editor = null;
    }

    if( new_message_editor_group.sendbox)
    {
        unhook_Send_box();
        new_message_editor_group.sendbox.removeAttr(role_name);
        WEB_CMM.log("clean " +  "sendbox removeAttr " + role_name);
        new_message_editor_group.sendbox =  null;
    }

    if( new_message_editor_group.tobox)
    {
        new_message_editor_group.tobox.removeAttr(role_name);
        WEB_CMM.log("clean " + "tobox removeAttr +  " + role_name);
        new_message_editor_group.tobox =  null;
    }
    
    clean_Editor_group_test();
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
        if(evt.attrName == "fnremotehtmlreq-event-param"  )
        {
            if(evt.newValue=="true" || evt.newValue == "false")
            {	
                document.body.removeEventListener("DOMAttrModified",on_fnaction_over, false);
                $(document.body).removeAttr("fnRemoteHtmlReq-event-param");
                new_message_editor_group.tobox.removeAttr("fnRemoteHtmlReq-event-param");   
                new_message_editor_group.editor.removeAttr("fnRemoteHtmlReq-event-param");   
               if (evt.newValue=="true") {
                    //should add invitation
                    var untrustedEmails =  $(document.body).attr("fnRemoteHtmlReq-event-param-subvalue");
                    $(document.body).removeAttr("fnRemoteHtmlReq-event-param-subvalue");
                    if (untrustedEmails.length > 0) {
                        onprepare_send_invitation(untrustedEmails);
                    }
                }
                //click the button again
                call_simulate_mouse_click_jquery(  new_message_editor_group.sendbox, 300)
            }
        }
    }
    catch(err)
    {
        //alert(err)
    }
}

function on_mousedown(evt)
{
    if(!evt.target.hj_cocntrol || evt.target.hj_cocntrol == 0)
    {
        evt.target.hj_cocntrol = 1;
    }
    else
    {
        evt.target.hj_cocntrol = 0;
        return;
    }
    evt.stopPropagation();
    evt.preventDefault();
                                    
    try{
        WEB_CMM.tell_to_box(new_message_editor_group.tobox.get(0))
        
        WEB_CMM.tell_editor( new_message_editor_group.editor.get(0) )
        
        WEB_CMM.fill_recepients( new_message_editor_group.editor.get(0), new_message_editor_group.tobox.get(0) )
        
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
    if( new_message_editor_group.sendbox)
    {
        var send_obj = new_message_editor_group.sendbox;
        if(send_obj)
        {
            send_obj.get(0).parentNode.addEventListener('click' , on_mousedown,true);
        }
    }
}

function unhook_Send_box()
{
    if( new_message_editor_group.sendbox)
    {
        var send_obj = new_message_editor_group.sendbox;
        if(send_obj)
        {
            send_obj.get(0).parentNode.removeEventListener('click' , on_mousedown,true);
        }
    }
}

function find_Editor_group_test(a_id)
{
    //to do: plan to open a panel or frame to tell the manager the page status with QUint
}

function clean_Editor_group_test()
{
    //to do: plan to  tell the manager the page status in a panel or a frame  with QUint
}

function is_my_page(url_spec)
{
    var reg_URL = /^https:\/\/www.facebook.com\/messages\/new(\/?)/ ;
    var match = reg_URL.test( url_spec );
    return match;
}

/*
 self.port.on("send-message", function(data) {
    if( is_my_page(data) && new_message_editor_group.sendbox)
    {
        var send_obj = new_message_editor_group.sendbox;
        if(send_obj)
        {
            call_simulate_mouse_click_jquery(send_obj.parent(), 1 );
        }
    }
});
*/

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

///for comment reply:
///textarea class="textInput mentionsTextarea uiTextareaAutogrow uiTextareaNoResize UFIAddCommentInput"  name="add_comment_text_text"