// in this module , we are going to keep a group of editor to send the message




;
"use strict";
(function() {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;
//gmail page parser
var PAGE_PARSER = fn_webpage_parser_gmail_ns;

//const 
const g_interesting_webpage_reg_ex  = /^https:\/\/mail.google.com/ ;
const g_msg_name_get_gmail_composer = "get-gmail-composer";
const g_msg_name_status_gmail_action = "status-gmail-action";
const g_msg_val_status_gmail_action_start = "start";
const g_msg_val_status_gmail_action_stop = "stop";

var  g_status_action = true;

var gmail_composers = [];


var  gmail_composer_struct = 
{
	"gmail-composer-fn-id":null,//using WEB_CMM.uniqID(20)
	"composer" : null,
	"show_trimmed_content" : null,//is reply or not
	"send_button" : null,
	"msg_sending" : null,
	"msg_last" 	  : null,
};

//main logic 
function handle_gmail_composer(acomposer)
{
	if(!acomposer)
	{
		return;
	}
	if(acomposer.handled_in_fn_conversation)
	{
		return;
	}
	WEB_CMM.log( "handle_gmail_composer :  " +  acomposer );
	

	var forReply = isForReply(acomposer);
	if(!forReply)
	{
		return;
	}
	
	var reply_token = PAGE_PARSER.find_reply_token(acomposer); 
	if(reply_token)
	{//to be able to get the last email content, we must click the reply_token element()
		PAGE_PARSER.expand_show_trimmed_content(reply_token);
	}
	
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
	if(!subject)
	{
		//todo : store it into document or elsewhere
	}
		
	if(!acomposer.handled_in_fn_conversation)
	{
		acomposer.handled_in_fn_conversation = true;
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



function isForReply(acomposer)
{// check the to box is filled or not, if it is filled then it is  for reply
	var reply = PAGE_PARSER.toBoxIsFilled(acomposer);
	return !!reply;
}

///reply token part]


///gmail composer part
function searchElementPresent_findgmail_composer()
{
	if(!g_status_action )
	{
		return; //stop 
	}
	var acomposer$  =  PAGE_PARSER.findgmail_composer();
	if(acomposer$ && acomposer$.length > 0)
	{
		acomposer$.each(function( index ){
			handle_gmail_composer(this);//this is the element of the index
		});
		
	}
	
	window.setTimeout( searchElementPresent_findgmail_composer, 200);
}

function findgmail_composer()
{
	try
	{
		var gmail_composer$ = $(selector_gmail_composer);
		if(!gmail_composer$ || gmail_composer$.length == 0)
		{
			WEB_CMM.log( "findgmail_composer :  not found"   );
			return false;
		}
		WEB_CMM.log( "findgmail_composer :  found"   );
		return gmail_composer$;
	}
	catch(err)
	{
		WEB_CMM.log( "findgmail_composer :  excpetion " +  err  );
	}
	return null;
	
}
///gmail composer part

function run_gmail_fn()
{
	
	searchElementPresent_findgmail_composer();
	WEB_CMM.log( "run_gmail_fn : start waitforElementPresent_findgmail_composer "   );
}

/////////////messages [
self.port.on(g_msg_name_status_gmail_action, function(status) {

	g_status_action = (status===g_msg_val_status_gmail_action_start);

});

function is_my_page(url_spec)
{
    var match = g_interesting_webpage_reg_ex.test( url_spec );
    return !!match;
}


self.port.on(g_msg_name_get_gmail_composer, function(url_spec) {

	WEB_CMM.log( " gmail get a command :"    + g_msg_name_get_gmail_composer);
    if( is_my_page(url_spec) )
    {
    	WEB_CMM.log( "run_gmail_fn : is_my_page"   );
        if(document.URL == url_spec)
        {
        	WEB_CMM.log( "run_gmail_fn : document.URL == url_spec"   );
            run_gmail_fn();
        }
    }

});
/////////////messages]

// we use waitforelementpresent to detect the gmail composer, so it has no need to addeventlistener for the page modification
})();

