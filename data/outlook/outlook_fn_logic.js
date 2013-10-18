// in this module , we are going to keep a group of editor to send the message




;
"use strict";
(function() {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;
var TOGGLE_OPT_PERSIST = fn_web_common_persist_fn_toggle_option_ns;
//outlook page parser
var PAGE_PARSER = fn_webpage_parser_outlook_ns;

//const 
const g_interesting_webpage_url_rule = "mail.live.com"
const g_interesting_webpage_reg_ex  = new RegExp(g_interesting_webpage_url_rule) ;

const g_msg_name_get_outlook_composer = "get-outlook-composer";
const g_msg_name_status_outlook_action = "status-outlook-action";

var  g_status_action = true;
/*
var outlook_composers = [];


var  outlook_composer_struct = 
{
	"outlook-composer-fn-id":null,//using WEB_CMM.uniqID(20)
	"composer" : null,
	"show_trimmed_content" : null,//is reply or not
	"send_button" : null,
	"msg_sending" : null,
	"msg_last" 	  : null,
};
*/
//main logic 
function handle_outlook_composer(acomposer)
{
	if(!acomposer)
	{
		return;
	}
	if(acomposer.handled_in_fn_conversation)
	{
		//log( "return handle_outlook_composer  :   "  + acomposer.handled_in_fn_conversation);
		return;
	}
	if(!acomposer.handled_in_fn_conversation)
	{
		acomposer.handled_in_fn_conversation = true;
	}	
	var forreply = PAGE_PARSER.isForReply(acomposer); 
	if(!forreply)
	{
		return;
	}

	log( "handle outlook isForReply :   "  + forreply);
	TOGGLE_OPT_PERSIST.persist(acomposer, g_interesting_webpage_url_rule);
	var hooked  = hookSendButton(acomposer)
	if(!hooked)
	{
		return;
	}
	 
	var latest_HJContentID = PAGE_PARSER.get_latest_HJContentID(acomposer);
	
	if(latest_HJContentID)
	{
		//todo : store it into document.body or elsewhere
	}
	var subject = PAGE_PARSER.getSubject(acomposer);
	if(subject)
	{
		//todo : store it into document or elsewhere
	}

}

//main logic ]


////////////////send box part[

function hookSendButton(acomposer)
{
	var sand_box = PAGE_PARSER.findSendButton_from_composer(acomposer);
	if(!!sand_box)
	{
	//to do hook the click/command event for sand_box;
		return true;
	}
	
	return false;
}

///////////////send box part]

///////////////reply token part[

//to be able to get the last email content, we must click the reply_token element()

///reply token part]


///outlook composer part
function searchElementPresent_findoutlook_composer()
{
	if(!g_status_action )
	{
		return; //stop 
	}
	var acomposer$  =  PAGE_PARSER.findoutlook_composer();
	if(acomposer$ && acomposer$.length > 0)
	{
		handle_outlook_composer(acomposer$[0]);
	}
	
	window.setTimeout( searchElementPresent_findoutlook_composer, WEB_CMM.FIND_COMPOSER_TIMER_SPAN);
}
///outlook composer part

function run_outlook_fn()
{
	
	searchElementPresent_findoutlook_composer();
	log( "run_outlook_fn : start waitforElementPresent_findoutlook_composer "   );
}

/////////////messages [
self.port.on(g_msg_name_status_outlook_action, function(status) {

	g_status_action = status;

});

function is_my_page(url_spec)
{
    var match = g_interesting_webpage_reg_ex.test( url_spec );
    return !!match;
}


self.port.on(g_msg_name_get_outlook_composer, function(url_spec) {

	log( " outlook get a command :"    + g_msg_name_get_outlook_composer);
    if( is_my_page(url_spec) )
    {
    	log( "run_outlook_fn : is_my_page"   );
        if(document.URL == url_spec)
        {
        	log( "run_outlook_fn : document.URL == url_spec"   );
            run_outlook_fn();
        }
    }

});
/////////////messages]
function log(msg)
{
	WEB_CMM.log( msg  );
}
// we use waitforelementpresent to detect the outlook composer, so it has no need to addeventlistener for the page modification
})();

