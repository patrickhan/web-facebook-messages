// in this module , we are going to keep a array for the editors  for facebook message reply




// config:
//1 facebook message reply 
// div id="pagelet_web_messenger" -- a good starting point
//editor : textarea : name="message_body", 
//send button : input value="Reply" type="submit"
//tobox : there is no a to box , we are going to create a new one.

( function(){


var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;

var selector_editor_replay_Message = 'textarea[name="message_body"]';
var selector_sendbox_replay_Message = 'input[value="Reply"][type="submit"]';
var selector_tobox_replay_Message = null;


var reply_message_editor_group = 
{
    "id":null,
    "editor": null, 
    "sendbox": null, 
    "tobox": null, 
    "url": null,
};

var message_editor_group = reply_message_editor_group;

function find_Editor_group_replay_Message()
{
    var a_id = WEB_CMM.uniqID(20);
    var role_name = WEB_CMM.PROJECT_NAME_PREFIX + WEB_CMM.INTEGRATING_ROLE_NAME + a_id;
    // find editor
    if(!message_editor_group.editor)
    {
        var editors$ = $(selector_editor_replay_Message);
        
        var log_str = "find edtiors count is : " ;
        log_str += editors$.length;
        WEB_CMM.log(log_str + " " +a_id );
        
        if(editors$.length == 1)//shoult there is only one
        {
            editors$.attr(role_name, WEB_CMM.ROLE_NAME_EDIT_BOX);
            message_editor_group.editor = editors$;
            editors$.get(0).wrappedJSObject.fnhookedFlag = true; 
            message_editor_group.id = a_id;
        }
    }
  
    //find send button
    if(!message_editor_group.sendbox)
    {
        var send_boxes$ = $(selector_sendbox_replay_Message);
      
        var log_str = "find sendbox count is : " ;
        log_str += send_boxes$.length;
        WEB_CMM.log(log_str+ " " +a_id );
      
        if(send_boxes$.length == 1)//shoult there is only one
        {
          send_boxes$.attr(role_name, WEB_CMM.ROLE_NAME_SEND_BOX);
          message_editor_group.sendbox = send_boxes$;
          
          hook_Send_box();
        }
    }
  
    //recepient box
    if(!message_editor_group.tobox)
    {
        var to_boxes$ = $('<div></div>').appendTo(document.body).hide();
        to_boxes$.attr(role_name, WEB_CMM.ROLE_NAME_TO_BOX);
        to_boxes$.attr('id', a_id);
        message_editor_group.tobox = to_boxes$;
        WEB_CMM.log("find to_boxe count is -- create new  and hide : " + " " +a_id );
        
        //test code
        M_TEST.insert_data_ToBox(to_boxes$.get(0) );
    }
}

function clean_Editor_group_replay_Message()
{
  // editor
    var role_name = WEB_CMM.PROJECT_NAME_PREFIX + WEB_CMM.INTEGRATING_ROLE_NAME + message_editor_group.id;
    if( message_editor_group.editor)
    {
        delete message_editor_group.editor.get(0).wrappedJSObject.fnhookedFlag;
        WEB_CMM.log("clean_Editor_group " +  "editor_group.editor  " + message_editor_group.editor);
        message_editor_group.editor.removeAttr(role_name);
        message_editor_group.editor.removeAttr("fn-toggle-option");
        WEB_CMM.log("clean_Editor_group editors removeAttr +  " + role_name);
        message_editor_group.editor = null;
    }

    if( message_editor_group.sendbox)
    {
        unhook_Send_box();
        message_editor_group.sendbox.removeAttr(role_name);
        WEB_CMM.log("sendbox removeAttr +  " + role_name);
        message_editor_group.sendbox =  null;
    }

    if( message_editor_group.tobox)
    {
        message_editor_group.tobox.remove();
        WEB_CMM.log("getEditor", "tobox$ remove  " );
        message_editor_group.tobox =  null;
    }
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
                $(document.body).removeAttr("fnremotehtmlreq-event-param");
                message_editor_group.tobox.removeAttr("fnremotehtmlreq-event-param");   
                message_editor_group.editor.removeAttr("fnremotehtmlreq-event-param");   
               if (evt.newValue=="true") {
                    //should add invitation
                    var untrustedEmails =  $(document.body).attr("fnremotehtmlreq-event-param-subvalue");
                    $(document.body).removeAttr("fnremotehtmlreq-event-param-subvalue");
                    if (untrustedEmails.length > 0) {
                        WEB_CMM.onprepare_send_invitation(untrustedEmails);
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

function call_simulate_mouse_click_jquery( box_obj$, timeout)
{
    if(!box_obj$)
        return;
    setTimeout(function(){
                box_obj$.trigger('click');
            }	, timeout);
}

//it is not easy to detect the send box is visible
//so detect the sendbox.parent.parent.css.left == 0 to check the 'press enter to send message'
function check_send_button_hidden()
{
    var parent_css_left = message_editor_group.sendbox.parent().parent().css("left");
    var parent_css_left_int = parseInt(parent_css_left);
    return 0 != parent_css_left_int;
}

function on_editorbox_keypress(evt)
{
    //notice the shiftKey + enter is linefeed , not send
    const keyCode_enter =  13;
    if(evt.keyCode == keyCode_enter && evt.shiftKey == 0)
    {
        if (check_send_button_hidden() ) {
            evt.preventDefault();
            evt.stopPropagation();  
            sending_msg_routing();
            
            if(!message_editor_group.sendbox.get(0).hj_cocntrol || message_editor_group.sendbox.get(0).hj_cocntrol == 0)
            {
                message_editor_group.sendbox.get(0).hj_cocntrol = 1;
            }
        }
    }
}

function fill_a_recepient_reply_message(editor, tobox)
{
    var transobj = {funname:"addReceiptsToAnInput_Forfacebook_replyMsg", param:tobox.id};    	        
    $(editor).attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));              
    //$(editor).trigger("fnRemoteHtmlReq-event") // is it work
    var event = document.createEvent("HTMLEvents");        
    event.initEvent("fnRemoteHtmlReq-event", true, false);            
    editor.dispatchEvent(event)   
    
}

function sending_msg_routing() {
    try{
        WEB_CMM.tell_to_box(message_editor_group.tobox.get(0));
        
        WEB_CMM.tell_editor( message_editor_group.editor.get(0) );
        
        fill_a_recepient_reply_message(message_editor_group.editor.get(0), message_editor_group.tobox.get(0));
        
        //WEB_CMM.fill_recepients( message_editor_group.editor.get(0), message_editor_group.tobox.get(0) );
        
        WEB_CMM.trigger_preSending();
        
        WEB_CMM.onAfter_preSending_event(on_fnaction_over);
    }
    catch( err )
    {
        //alert(err);
    } 
}

function on_replybox_click(evt)
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
    sending_msg_routing();
}

function hook_Send_box()
{
    if( message_editor_group.sendbox)
    {
        var send_obj = message_editor_group.sendbox;
        if(send_obj)
        {
            send_obj.get(0).parentNode.addEventListener('click' , on_replybox_click,true);
            
        }
    }
    // in message reply page , user can select 'press enter to send', so the editor's key press event must be hooked
    if(message_editor_group.editor)
    {
        var editor  = message_editor_group.editor.get(0);
        if (editor) {
            //in this case, the keydown event is hook for the editor.parentNode 
            editor.parentNode.addEventListener('keydown' , on_editorbox_keypress,true);
            //below is for reference for hooking the event later
            //editor.parentNode.addEventListener('keypress' , on_editorbox_keypress,true);
            //editor.parentNode.addEventListener('keyup' , on_editorbox_keypress,true);
        }
    }
}

function unhook_Send_box()
{
    if( message_editor_group.sendbox)
    {
        var send_obj = message_editor_group.sendbox;
        if(send_obj)
        {
            send_obj.get(0).parentNode.removeEventListener('click' , on_replybox_click,true);
        }
    }
}

function is_my_page(url_spec)
{
    var reg_URL = /^https:\/\/www.facebook.com\/messages\/(?!new)./ ;
    //match 'https://www.facebook.com/messages/xxxx
    //mismatch 'https://www.facebook.com/messages/new
    //mismatch 'https://www.facebook.com/messages/
    
    var match = reg_URL.test( url_spec );
    return match;
}


self.port.on("getEditors", function(url_spec) {

    if( is_my_page(url_spec) )
    {
        if(document.URL == url_spec)
        {
            WEB_CMM.log("** match the url ***" + url_spec );
            if(message_editor_group.url != document.URL )
            {
                    clean_Editor_group_replay_Message();
            }
            find_Editor_group_replay_Message();
            message_editor_group.url = document.URL;
        }
    }
    else
    {
        clean_Editor_group_replay_Message();
    }
});
 

})(); // end of hidden function
