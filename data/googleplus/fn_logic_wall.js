// in this module , we are going to keep a group of editor to send the message
//we start from here: user must selete fn toggle option to enbale fn feature
//if the editor has fn toggle option , then it will dispatch a specail event 
// we listen the event and find out all we want




;
"use strict";
(function() {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;
var TOGGLE_OPT_PERSIST = fn_web_common_persist_fn_toggle_option_ns;

//gmail page parser
var PAGE_PARSER = fn_webpage_parser_googleplus_wall_ns;

//const 
const g_interesting_webpage_url_rule = "^https:\/\/plus.google.com\/.*";//"^https:\/\/plus.google.com\/u\/0\/*";
const g_interesting_webpage_reg_ex  = new RegExp(g_interesting_webpage_url_rule) ;

const c_msg_name_get_composer = "get-googleplus_share-composer";

const c_msg_name_status_fnlogic_action = "status-fnlogic-action";// tell the page content js to start/stop  fn logic by 'status'

var  g_status_action = true; // run fnlogic or not

function Wall_editor_group(editor, sendbox, tobox, id)
{
   this.editor =  editor;
   this.sendbox =  sendbox; 
   this.tobox =  tobox;
   
   this.editor.wall_editor_group_id 	= id;
   this.sendbox.wall_editor_group_id	= id;
   this.tobox.wall_editor_group_id 		= id;
};

var g_wall_editor_groups ={};//dict {id:wall_editor_group}
//main logic 
function collect_wall_share_composer(editor) {
	if(editor.handled_in_fn_wall)
	{
		return;
	}

    var is_wall_share = PAGE_PARSER.is_wall_share_editor(editor);
	
	var is_wall_reply = PAGE_PARSER.is_wall_reply_editor(editor);
    //is for replying ?
	//is for sharing
    if(is_wall_share )
    {
		handle_wall_share_composer(editor)
    	return;
    }
	else if(is_wall_reply)
	{
		handle_wall_reply_composer(editor)
	}

   
}

//////////reply part
function handle_wall_reply_composer(acomposer)
{
	if(!acomposer)
	{
		return;
	}
	if(acomposer.handled_in_fn_conversation)
	{
		return;
	}
	log( "handle google plus composer : forReply  " +  acomposer );
	TOGGLE_OPT_PERSIST.persist(acomposer, g_interesting_webpage_url_rule);
	
	var hooked  = hookReplyButton(acomposer)
	if(!hooked)
	{
		return;
	}
	//log( "handle google plus composer : forReply222  " +  acomposer );
	var latest_HJContentID = PAGE_PARSER.get_Reply_latest_HJContentID_v2(acomposer);
	
	if(latest_HJContentID)
	{
		log("latest_HJContentID is :" + latest_HJContentID)
		//todo : store it into document.body or elsewhere
	}
	//there is not subject in google plus 
	//var subject = PAGE_PARSER.getReplySubject(acomposer);
	//if(subject)
	//{
		//todo : store it into document or elsewhere
	//}
		
	if(!acomposer.handled_in_fn_conversation)
	{
		acomposer.handled_in_fn_conversation = true;
	}
}


function hookReplyButton(acomposer)
{
	var reply_box = PAGE_PARSER.findReplyButton_from_composer(acomposer);
	if(!!reply_box)
	{
	//to do hook the click/command event for reply_box;
		return true;
	}
	
	return false;
}


//////////share part
function handle_wall_share_composer(acomposer)
{
//log("handle_wall_share_composer  in " + acomposer.outerHTML);
	if(!acomposer)
	{
		return;
	}
	if(acomposer.handled_in_fn_wall)
	{
		return;
	}
	var sendbox = PAGE_PARSER.get_sendbox(acomposer);
	var tobox = PAGE_PARSER.get_tobox(acomposer);
	
	var uniqID = WEB_CMM.uniqID(10);
	var a_wall_editor_group =  new Wall_editor_group(acomposer, sendbox, tobox, uniqID);
	g_wall_editor_groups[uniqID] = a_wall_editor_group;
	//log("handle_wall_share_composer  uniqID: " + uniqID);
	//log("handle_wall_share_composer  sendbox: " + sendbox);
	//log("handle_wall_share_composer  tobox: " + tobox);
	hookSendButton(sendbox);
	hookEditorToggleOption(acomposer);
	markEditor_fnIntegrated(acomposer);

	
	if(!acomposer.handled_in_fn_wall)
	{
		acomposer.handled_in_fn_wall = true;
	}
}

function release_wall_share_composer(acomposer)
{
	if(!acomposer)
	{
		return;
	}
	if(!acomposer.handled_in_fn_wall)
	{
		return;
	}
	if(!acomposer.wall_editor_group_id)
	{
		return;
	}
	var uniqID = acomposer.wall_editor_group_id;
	var a_wall_editor_group = g_wall_editor_groups[uniqID];
	if(!a_wall_editor_group)
	{
		return ;
	}
	unhookSendButton(a_wall_editor_group.sendbox);
	unhookEditorToggleOption(acomposer);
	unmarkEditor_fnIntegrated(acomposer);
	delete acomposer.handled_in_fn_wall;
	delete acomposer.wall_editor_group_id;
	delete g_wall_editor_groups[uniqID];
	
	log("release_wall_share_composer end");
}

//main logic ]

function markEditor_fnIntegrated(acomposer)
{
	WEB_CMM.markEditor_fnIntegrated_flag(acomposer);
}
function unmarkEditor_fnIntegrated(acomposer)
{
	WEB_CMM.removeEditor_fnIntegrated_flag(acomposer);
}

function sending_msg_routing(uniqID) 
{
	
	var a_wall_editor_group = g_wall_editor_groups[uniqID];
	if(!a_wall_editor_group)
	{
		return ;
	}
    log("sending_msg_routing");
    try{
        WEB_CMM.tell_to_box(a_wall_editor_group.tobox);
        
        WEB_CMM.tell_editor( a_wall_editor_group.editor );
        WEB_CMM.fill_recepients(a_wall_editor_group.editor, a_wall_editor_group.tobox)
        
        WEB_CMM.trigger_preSending();
        
        WEB_CMM.listen_After_preSending_event(on_fnaction_over, {editor_gourp_id:uniqID} );//to get editor_gourp_id , using evt.data.editor_gourp_id	
    }
    catch( err )
    {
    	log("sending_msg_routing: exception : " + err)
    } 
}

function on_fnaction_over(evt$)	//I use jquery , uniqID is evt.data.editor_gourp_id
{
    try
    {
    	var evt =  evt$.originalEvent;
        if(evt.attrName == "fnremotehtmlreq-event-param"  )
        { 
            if(evt.newValue=="true" || evt.newValue == "false")
            {	 
				var uniqID = evt$.data.editor_gourp_id;
				WEB_CMM.unlisten_After_preSending_event(on_fnaction_over);
                //[
                var a_wall_editor_group = g_wall_editor_groups[uniqID];
				if(a_wall_editor_group)
				{//log("on_fnaction_over:  removeAttr a_wall_editor_group  :\n " + a_wall_editor_group.editor )
					$(a_wall_editor_group.tobox).removeAttr("fnremotehtmlreq-event-param");   
	                $(a_wall_editor_group.editor).removeAttr("fnremotehtmlreq-event-param");   
				}
                
                //]
                if (evt.newValue=="true") {
                    //should add invitation . when it comes, it is from CIA mode only
					
                    var untrustedEmails =  $(document.body).attr("fnremotehtmlreq-event-param-subvalue");
					var arr_untrustedEmails = untrustedEmails.split(";");
					arr_untrustedEmails = WEB_CMM.Array_getUnique(arr_untrustedEmails);
					untrustedEmails =  arr_untrustedEmails.toString();
					
                    $(document.body).removeAttr("fnremotehtmlreq-event-param-subvalue");
                    if (untrustedEmails.length > 0) {
                        WEB_CMM.onprepare_send_invitation(a_wall_editor_group.editor, untrustedEmails);
						//log("on_fnaction_over:  onprepare_send_invitation  :\n " + untrustedEmails )
                    }
                }
                //click the button again
				WEB_CMM.call_simulate_mouse_click(  a_wall_editor_group.sendbox, 1000);
            }
        }
    }
    catch(err)
    {
    	log("on_fnaction_over: exception : " + err)
    }
}




function on_sendbox_click(evt)
{
	log("on_sendbox_click evt.target." +evt.target)
    //not fn toggle, just return 
	try{
		var uniqID = evt.target.wall_editor_group_id;
		if(!uniqID)
		{
			return;
		}
		//log("on_sendbox_click evt.target.wall_editor_group_id " +evt.target.wall_editor_group_id)
        var a_wall_editor_group = g_wall_editor_groups[uniqID];	
		//log("on_sendbox_click evt.target.a_wall_editor_group.editor " +a_wall_editor_group.editor)
	    //var fn_toggle_option = $(a_wall_editor_group.editor).attr('fn-toggle-option');
	    //if (!fn_toggle_option ) {
		//	//log("on_sendbox_click !fn_toggle_option return" );
	    //    return;
	    //}
	    if(!evt.target.hj_cocntrol || evt.target.hj_cocntrol == 0)
	    {
	        evt.target.hj_cocntrol = 1;// we hook and invoke this event later on;
	    }
	    else
	    {
	        evt.target.hj_cocntrol = 0;
	        return;// let the other event listener does this
	    }
	    evt.stopPropagation();
	    evt.preventDefault();
	    sending_msg_routing(uniqID);
	}
	catch(err)
	{
		log("on_fnaction_over: exception : " + err)
	}

}

function call_simulate_mouse_click_jquery( box_obj$, timeout)
{
    if(!box_obj$)
        return;
    setTimeout(function(){
                box_obj$.trigger('click');
            }, timeout);
}


function hookEditorToggleOption(acomposer)
{
	if(acomposer)
	{
		$(acomposer).on("DOMAttrModified",  {editor_gourp_id:acomposer.wall_editor_group_id}, on_fn_toggle_option_changed);
	}
}
function unhookEditorToggleOption(acomposer)
{
	$(acomposer).off("DOMAttrModified",   on_fn_toggle_option_changed);
}

function on_fn_toggle_option_changed(evt$)
{
	var evt =  evt$.originalEvent;
	var target  =  evt.target;
	if(evt.attrName == "fn-toggle-option"  )
    {
    	//log("on_fn_toggle_option_changed:  fn-toggle-option newValue is : "  + evt.newValue);
    	//log("on_fn_toggle_option_changed:  fn-toggle-option event.prevValue is : "  + evt.prevValue);
    	//if(evt.prevValue === "FNRTE" && evt.newValue !=="FNRTE" )
		if(!evt.newValue)
		{
			//setTimeout(release_wall_share_composer, 0, target);
			release_wall_share_composer(target);
		}
    }
}
//
//////////////send box part[
function hookSendButton(sendbox)
{
    if( sendbox)
    {
    	sendbox.parentNode.addEventListener('click' , on_sendbox_click,true);
    	//sendbox.addEventListener('click' , on_sendbox_click,true);
		//sendbox.addEventListener('mouseup' , on_sendbox_click,true);
    }
}

function unhookSendButton(sendbox)
{
    if( sendbox)
    {
    	sendbox.parentNode.removeEventListener('click' , on_sendbox_click,true);
    	//sendbox.removeEventListener('click' , on_sendbox_click,true);
		//sendbox.removeEventListener('mouseup' , on_sendbox_click,true);
    }
}

///////////////send box part]

function on_FNToggle_editor_focus(evt) {
	try
	{
		if(!fn_logic_enabled())
			return;	
	    var target = evt.target;
	    var paramobjJsonstring = target.getAttribute("fnRemoteHtmlReq-event-param");
	    if(paramobjJsonstring)
	    {
	         var paramobj = JSON.parse(paramobjJsonstring);
	         if(paramobj.funname == "userFireClickOnInputElementForWebpage")
	         {
	            collect_wall_share_composer(target);
	         }
	    }
    }
	catch(err)
    {
		log("on_FNToggle_editor_focus: exception : " + err);
    }
         
}
    
//hook ... it is no need to release?
function add_FNToggle_editor_focus_listener() {
    document.addEventListener("fnRemoteHtmlReq-event", on_FNToggle_editor_focus, true);
}
function remove_FNToggle_editor_focus_listener() {
    document.removeEventListener("fnRemoteHtmlReq-event", on_FNToggle_editor_focus, true);
}      

function run_fn_logic()
{
	if(!fn_logic_enabled())
		return;
	add_FNToggle_editor_focus_listener();
}

function fn_logic_enabled()
{
	return g_status_action;
}
function enable_fn_logic()
{
	g_status_action = true;// status is boolean
}

function diable_fn_logic()
{
	g_status_action = false;// status is boolean
}

/////////////messages [

self.port.on(c_msg_name_status_fnlogic_action, function(status) {

	g_status_action = status;// status is boolean
	if(status)
	{
		enable_fn_logic();
	}
	else
	{
		diable_fn_logic();
	}
	

});

function is_my_page(url_spec)
{
	log( " googleplus_fn : is_my_page : " + g_interesting_webpage_reg_ex + " ==match==" + url_spec);
    var match = g_interesting_webpage_reg_ex.test( url_spec );
    return !!match;
}


self.port.on(c_msg_name_get_composer, function(url_spec) {
    if( is_my_page(url_spec) )
    {
    	log( "run_googleplus_fn : is_my_page"   );
        if(document.URL == url_spec)
        {
        	log( "run_googleplus_fn : document.URL == url_spec"   );
        	run_fn_logic();
        }
    }

});
/////////////messages]
function log(msg)
{
	WEB_CMM.log( msg  );
}
// we use waitforelementpresent to detect the gmail composer, so it has no need to addeventlistener for the page modification
})();

