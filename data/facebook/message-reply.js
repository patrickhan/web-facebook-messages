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

function find_Editor_group_replay_Message()
{
    var a_id = WEB_CMM.uniqID(20);
    var role_name = WEB_CMM.PROJECT_NAME_PREFIX + WEB_CMM.INTEGRATING_ROLE_NAME + a_id;
    // find editor
    if(!reply_message_editor_group.editor)
    {
        var editors$ = $(selector_editor_replay_Message);
        
        var log_str = "find edtiors count is : " ;
        log_str += editors$.length;
        WEB_CMM.log(log_str + " " +a_id );
        
        if(editors$.length == 1)//shoult there is only one
        {
            editors$.attr(role_name, WEB_CMM.ROLE_NAME_EDIT_BOX);
            reply_message_editor_group.editor = editors$;
        
            reply_message_editor_group.id = a_id;
        }
    }
  
    //find send button
    if(!reply_message_editor_group.sendbox)
    {
        var send_boxes$ = $(selector_sendbox_replay_Message);
      
        var log_str = "find sendbox count is : " ;
        log_str += send_boxes$.length;
        WEB_CMM.log(log_str+ " " +a_id );
      
        if(send_boxes$.length == 1)//shoult there is only one
        {
          send_boxes$.attr(role_name, WEB_CMM.ROLE_NAME_SEND_BOX);
          reply_message_editor_group.sendbox = send_boxes$;
        }
    }
  
    //recepient box
    if(!reply_message_editor_group.tobox)
    {
        var to_boxes$ = $('<div></div>').appendTo(document.body).hide();
        to_boxes$.attr(role_name, WEB_CMM.ROLE_NAME_TO_BOX);
        reply_message_editor_group.tobox = to_boxes$;
        WEB_CMM.log("find to_boxe count is -- create new  and hide : " + " " +a_id );
        
        //test code
        M_TEST.insert_data_ToBox(to_boxes$.get(0) );
    }
}

function clean_Editor_group_replay_Message()
{
  // editor
    var role_name = WEB_CMM.PROJECT_NAME_PREFIX + WEB_CMM.INTEGRATING_ROLE_NAME + reply_message_editor_group.id;
    if( reply_message_editor_group.editor)
    {
        WEB_CMM.log("clean_Editor_group " +  "editor_group.editor  " + reply_message_editor_group.editor);
        reply_message_editor_group.editor.removeAttr(role_name);
        WEB_CMM.log("clean_Editor_group editors removeAttr +  " + role_name);
        reply_message_editor_group.editor = null;
    }

    if( reply_message_editor_group.sendbox)
    {
        reply_message_editor_group.sendbox.removeAttr(role_name);
        WEB_CMM.log("sendbox removeAttr +  " + role_name);
        reply_message_editor_group.sendbox =  null;
    }

    if( reply_message_editor_group.tobox)
    {
        reply_message_editor_group.tobox.remove();
        WEB_CMM.log("getEditor", "tobox$ remove  " );
        reply_message_editor_group.tobox =  null;
    }
}

function is_my_page(url_spec)
{
    var reg_URL = /^https:\/\/www.facebook.com\/messages\/(?!new)./ ;
    var match = reg_URL.test( url_spec );
    return match;
}


self.port.on("getEditors", function(url_spec) {

    if( is_my_page(url_spec) )
    {
        if(document.URL == url_spec)
        {
            WEB_CMM.log("** match the url ***" + url_spec );
            if(reply_message_editor_group.url != document.URL )
            {
                    clean_Editor_group_replay_Message();
            }
            find_Editor_group_replay_Message();
            reply_message_editor_group.url = document.URL;
        }
    }
    else
    {
        clean_Editor_group_replay_Message();
    }
});
 

})(); // end of hidden function
