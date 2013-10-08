// in this module , we are going to keep a group of editor to send the message




;
"use strict";
(function() {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;
//yahoo page parser
var PAGE_PARSER = fn_webpage_parser_yahoo_ns;

//const 
const g_interesting_webpage_reg_ex  = /mail.yahoo.com/ ;
const g_msg_name_get_yahoo_composer = "get-yahoo-composer";
const g_msg_name_status_yahoo_action = "status-yahoo-action";
const g_msg_val_status_yahoo_action_start = "start";
const g_msg_val_status_yahoo_action_stop = "stop";

var  g_status_action = true;

var yahoo_composers = [];


var  yahoo_composer_struct = 
{
	"yahoo-composer-fn-id":null,//using WEB_CMM.uniqID(20)
	"composer" : null,
	"show_trimmed_content" : null,//is reply or not
	"send_button" : null,
	"msg_sending" : null,
	"msg_last" 	  : null,
};

//main logic 
function handle_yahoo_composer(acomposer)
{
	if(!acomposer)
	{
		return;
	}
	if(acomposer.handled_in_fn_conversation)
	{
		return;
	}
	WEB_CMM.log( "handle_yahoo_composer :  " +  acomposer );
	
	var forReply = isForReply(acomposer);
	if(!forReply)
	{
		return;
	}
	WEB_CMM.log( "handle_yahoo_composer : it is for reply  "  );
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
	//setTimeout( function(){
		var latest_HJContentID = PAGE_PARSER.get_latest_HJContentID(acomposer);
		
		if(latest_HJContentID)
		{
			//todo : store it into document.body or elsewhere
		}
	//},500);
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

//to be able to get the last email content, we must click the reply_token element()



function isForReply(acomposer)
{// check the to box is filled or not, if it is filled then it is  for reply
	var toBoxIsFilled = PAGE_PARSER.toBoxIsFilled(acomposer);
	if(toBoxIsFilled )
	{
		return true;
	}
	
	return false;
}

///reply token part]


///yahoo composer part
function searchElementPresent_findyahoo_composer()
{
	if(!g_status_action )
	{
		return; //stop 
	}
	var acomposer$  =  PAGE_PARSER.findyahoo_composer();
	if(acomposer$ && acomposer$.length > 0)
	{
		if(acomposer$ && acomposer$.length > 0)
		{
			acomposer$.each(function( index ){
				handle_yahoo_composer(this);//this is the element of the index
			});
			
		}
	}
	
	window.setTimeout( searchElementPresent_findyahoo_composer, 200);
}

function findyahoo_composer()
{
	try
	{
		var yahoo_composer$ = $(selector_yahoo_composer);
		if(!yahoo_composer$ || yahoo_composer$.length == 0)
		{
			WEB_CMM.log( "findyahoo_composer :  not found"   );
			return false;
		}
		WEB_CMM.log( "findyahoo_composer :  found"   );
		return yahoo_composer$;
	}
	catch(err)
	{
		WEB_CMM.log( "findyahoo_composer :  excpetion " +  err  );
	}
	return null;
	
}
///yahoo composer part

function run_yahoo_fn()
{
	
	searchElementPresent_findyahoo_composer();
	WEB_CMM.log( "run_yahoo_fn : start waitforElementPresent_findyahoo_composer "   );
}

/////////////messages [
self.port.on(g_msg_name_status_yahoo_action, function(status) {

	g_status_action = (status===g_msg_val_status_yahoo_action_start);

});

function is_my_page(url_spec)
{
    var match = g_interesting_webpage_reg_ex.test( url_spec );
    return !!match;
}


self.port.on(g_msg_name_get_yahoo_composer, function(url_spec) {

	WEB_CMM.log( " yahoo get a command :"    + g_msg_name_get_yahoo_composer);
    if( is_my_page(url_spec) )
    {
    	WEB_CMM.log( "run_yahoo_fn : is_my_page"   );
        if(document.URL == url_spec)
        {
        	WEB_CMM.log( "run_yahoo_fn : document.URL == url_spec"   );
            run_yahoo_fn();
        }
    }

});
/////////////messages]

// we use waitforelementpresent to detect the yahoo composer, so it has no need to addeventlistener for the page modification
})();

