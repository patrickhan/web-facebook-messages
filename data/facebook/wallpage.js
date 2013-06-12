/*
 * This js is for the 'wall' page in face book.
 * It will scratch the 'What do you mind' post message editor/recepients/submit
 */


"use strict";

(function(){
    
//var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;
var WEB_TEST = facebook_test_ns;//.create_test_panel =  create_test_panel;

var facebook_wall_editor_group = 
{
    "editor": null, 
    "sendbox": null, 
    "tobox": null,
    "audiencebox":null
};


var message_editor_group = facebook_wall_editor_group;


//string map:
var Audience_map = new Object;
Audience_map["Your friends"] =  "Friends";
Audience_map["Only you"] =  "Friends"
Audience_map["Cutom"] =  "Cutom"



function collect_wall_message_composer(editor) {
    
    if (message_editor_group.editor) {
        return true;
    }
    //editor is TEXTAREA and onkeydown has 'window'
    if(editor.tagName == "TEXTAREA" && editor.getAttribute("onkeydown") != null &&
	                   editor.getAttribute("onkeydown").indexOf("window") == 0)
    {
        ///ancestor form tag action="/ajax/updatestatus.php"
       var form$ =  $(editor).parents("form[action='/ajax/updatestatus.php']");
       //var form$ =  $(editor).parents("form:first");
       if (form$ ) {
            //then get the child div id="composerTourAudience" -- > a [aria-label="Your friends"]
            //recepeint
	    //its id changed , using classs "uiSelector inlineBlock audienceSelector composerAudienceSelector dynamicIconSelector uiSelectorRight uiSelectorNormal uiSelectorDynamicLabel uiSelectorDynamicTooltip"
            var audience = form$.find("div[class~='composerAudienceSelector']");

            //post button
            //<button value="1" class="_42ft _4jy0 _11b _4jy3 _4jy1 selected" type="submit">Post</button>
            var submit_button = form$.find("button[type='submit']");
	    
            message_editor_group.editor = $(editor);
	    editor.wrappedJSObject.fnhookedFlag = true; 
            message_editor_group.sendbox = submit_button;
            message_editor_group.audiencebox = audience;
            if (message_editor_group.editor &&
                message_editor_group.sendbox &&
                message_editor_group.audiencebox) {
		    hook_Send_box();
		    
		    //create a to box
		    var to_boxes$ = $('<div></div>').appendTo(document.body).hide();
		    message_editor_group.tobox = to_boxes$;
		    
		    listen_editor_change();
		    listen_audiencebox_change();
		    
		    WEB_CMM.log("collect_wall_message_composer ok ")
		    return true;
            }
       }
    }
    return false;
}


function on_editor_change(evt)	
{
    try
    {
        if(evt.attrName == "getemailsofanobject_facebook_forremotewebpage_res"  )
        {// this is the fn client users emails according to the audience in face book
	    var new_val = evt.newValue;
	    if (new_val) {
		message_editor_group.tobox.text(new_val);
	    }
        }
    }
    catch(err)
    {
        //alert(err)
    }
}

function listen_editor_change()
{
    var editor  = message_editor_group.editor.get(0);
    if( editor )
    {
        editor.addEventListener("DOMAttrModified", on_editor_change, false);   
    }
}
function on_audiencebox_change(evt) {
    try
    {
        if(evt.attrName == "aria-label"  )
        {// this is the fn client users emails according to the audience in face book
	    var new_val = evt.newValue;
	    if (new_val) {
	        askfor_eamil_from_facebook_names();
	    }
        }
    }
    catch(err)
    {
        //alert(err)
    }
}
function listen_audiencebox_change(){
    
    var audience_values_box = message_editor_group.audiencebox.find("a");
	    
    if (audience_values_box) {
	audience_values_box.get(0).addEventListener("DOMAttrModified", on_audiencebox_change, false);
    }
}


function get_audiences() {
    try {
 
	if(message_editor_group.audiencebox)
	{
	    //then get the child div id="composerTourAudience" -- > a [aria-label="Your friends"]
	    var audience_values_box = message_editor_group.audiencebox.find("a");
	    
	    if (audience_values_box) {
		var audience_values = audience_values_box.attr("aria-label");
		WEB_CMM.log("get_audiences audience_values   " + audience_values);
		var audience_value_list  = audience_values.split(",");
		WEB_CMM.log("get_audiences audience_value_list   " + audience_value_list);
		return audience_value_list;
	    }
	}
    } catch(e) {
	WEB_CMM.log("get_audiences err " + e)
    }
    return [];
}

//getEmailsOfAnObject_facebook_forRemoteWebpage

function askfor_eamil_from_facebook_names()
{
    var recepients = get_audiences();
    if (recepients.length > 0) {
	
	var editor  = message_editor_group.editor;
	var transobj = {funname:"setReceiptobjForInivitation_forRemoteWebpage", param:recepients};    	        
        editor.attr("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
        //$(tobox).trigger("fnRemoteHtmlReq-event") // is it work
        var event = document.createEvent("HTMLEvents");        
        event.initEvent("fnRemoteHtmlReq-event", true, false);            
        editor.get(0).dispatchEvent(event);
    }
}
function get_recepients() {
    var emails  = message_editor_group.tobox.text().split(',');
    return emails;
}
function fill_recepients()
{
    
    WEB_CMM.log("fill_recepients")
    var editor = message_editor_group.editor.get(0);
    var recepients  = get_recepients();
    var recepients_val  = "";
    if (recepients) {
	for (var index = 0; index < recepients.length ; index++) {
	    var arecepient = recepients[index];
	    WEB_CMM.log("(var arecepient in recepients): " +arecepient );
	    fill_a_recepient(editor, arecepient);
	    if (recepients_val.length > 0) {
		recepients_val +=";"
	    }
	    recepients_val +=arecepient;
	}
	WEB_CMM.log("fill recepients : " +recepients_val );
    }
}

function fill_a_recepient(editor, arecepient) {
    var mapped_val =  Audience_map[arecepient];
    WEB_CMM.log("Audience_map + key : " +arecepient + " val =  " +  mapped_val)
    
    if (mapped_val) {
	 arecepient = mapped_val;
    }
    WEB_CMM.log("fill_a_recepient : " +arecepient )
    //todo // get email from facebook account
    WEB_CMM.fill_a_recepient(editor, arecepient );
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
}


function sending_msg_routing() {
    WEB_CMM.log("sending_msg_routing")
    try{
        WEB_CMM.tell_to_box(message_editor_group.tobox.get(0));
        
        WEB_CMM.tell_editor( message_editor_group.editor.get(0) );
        
        fill_recepients();
        
        WEB_CMM.trigger_preSending();
        
        WEB_CMM.onAfter_preSending_event(on_fnaction_over);
    }
    catch( err )
    {
        //alert(err);
    } 
}

 
function on_sendbox_click(evt)
{
    WEB_CMM.log("on_sendbox_click")
    //not fn toggle, just return 
    var fn_toggle_option = message_editor_group.editor.attr('fn-toggle-option');
    if (!fn_toggle_option ) {
        return;
    }
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

function call_simulate_mouse_click_jquery( box_obj$, timeout)
{
    if(!box_obj$)
        return;
    setTimeout(function(){
                box_obj$.trigger('click');
            }	, timeout);
}

function hook_Send_box()
{
    WEB_CMM.log("hook_Send_box 0 ")
    if( message_editor_group.sendbox)
    {
	WEB_CMM.log("hook_Send_box 1 ")
        var send_obj = message_editor_group.sendbox;
        if(send_obj)
        {
	    WEB_CMM.log("hook_Send_box 2 " + send_obj.get(0));
            send_obj.get(0).parentNode.addEventListener('click' , on_sendbox_click,true);
	    
	     WEB_CMM.log("hook_Send_box 3")
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
            send_obj.get(0).parentNode.removeEventListener('click' , on_sendbox_click,true);
        }
    }
}

function hookedToggleBackFunctionHandle(evt) {

    call_simulate_mouse_click_jquery(  message_editor_group.sendbox, 100)
}

function listen_fn_togglebackfinished( )
{
    if(message_editor_group.editor)
    {
        message_editor_group.editor.get(0).addEventListener("fn_togglebackfinished", hookedToggleBackFunctionHandle, false);
    }
}

function _FNToggle_editor_focus_listener(evt) {
    var target = evt.target;
    var paramobjJsonstring = target.getAttribute("fnRemoteHtmlReq-event-param");
    if(paramobjJsonstring)
    {
         var paramobj = JSON.parse(paramobjJsonstring);
         if(paramobj.funname == "userFireClickOnInputElementForWebpage")
         {
            collect_wall_message_composer(target);
         }
    }   
}
    
//hook ... it is no need to release?
function add_FNToggle_editor_focus_listener() {
    document.addEventListener("fnRemoteHtmlReq-event", _FNToggle_editor_focus_listener, true);
}
        

function is_my_page(url_spec)
{
    var reg_URL = /^https:\/\/www.facebook.com\/(?!messages)./ ;
    //match 'https://www.facebook.com/profile.php?id=550901973&ref=tn_tnmn
    //mismatch 'https://www.facebook.com/messages
    //facebook message page has their own js files 
    
    var match = reg_URL.test( url_spec );
    return match;
}        
        
self.port.on("getEditors", function(url_spec) {

    if( is_my_page(url_spec) )
    {
	WEB_CMM.log("is_my_page")
        add_FNToggle_editor_focus_listener();
	WEB_TEST.create_test_panel();
    }

});
         
})(); // end of (function(){


