// in this module , we are going to keep a group of editor to send the message





"use strict";
(function() {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;
var  g_status_action = "start";

var selector_gmail_composer = "div[class='Am Al editable'] > iframe"   //"//div[contains(@class, 'Am') and contains(@class, 'Al') and contains(@class, 'editable')]/iframe";

var selector_gmail_composer_parent_table = "table";
var selector_gmail_composer_parent_table_td = "td";
var selector_gmail_composer_parent_td_Show_trimmed_content_element = "div[data-tooltip='Show trimmed content'] > div > img";
var selector_gmail_composer_sendbox = "div:contentIs('Send')"; //using plugin in jquery_xpath.js
var gmail_composers = [];




//$('a:contentIs("Baxter")')
var  gmail_composer_struct = 
{
	"gmail-composer-fn-id":null,//WEB_CMM.uniqID(20)
	"composer" : null,
	"show_trimmed_content" : null,//is reply or not
	"send_button" : null,
	"msg_sending" : null,
	"msg_last" 	  : null,
}


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
	

	var reply_token = check_for_reply(acomposer)
	if(!reply_token)
	{
		return;
	}
	
	var hooked  = hookSendButton(acomposer)
	if(!hooked)
	{
		return;
	}
	expand_show_trimmed_content(reply_token);
	
	if(!acomposer.handled_in_fn_conversation)
	{
		acomposer.handled_in_fn_conversation = true;
	}

}

function expand_show_trimmed_content(reply_token)
{
	$(reply_token).click();
}


function hookSendButton(acomposer)
{
	WEB_CMM.log( "hookSendButton :  + "  +  acomposer );
	var parent_table$ =  $(acomposer).closest(selector_gmail_composer_parent_table);
	var parent_table_table$ =  parent_table$.parent().closest(selector_gmail_composer_parent_table);
	if(parent_table_table$ && parent_table_table$.length > 0)
	{
		//WEB_CMM.log( "hookSendButton : parent_table_table$.length  is " + parent_table_table$.length   );
	
		
		var sendbox$ = $(selector_gmail_composer_sendbox, parent_table_table$);
		
		if(sendbox$ && sendbox$.length > 0)
		{
			WEB_CMM.log( "sendbox$ : found + " );
			return true;
		}
	}
	return false;
}

function check_for_reply(acomposer)
{
	WEB_CMM.log( "check_for_reply :  + "  +  acomposer );
	var parent_table$ =  $(acomposer).closest(selector_gmail_composer_parent_table);
	var parent_table_td$ =  parent_table$.closest(selector_gmail_composer_parent_table_td);
	if(parent_table_td$ && parent_table_td$.length > 0)
	{
		WEB_CMM.log( "check_for_reply :  parent_td$  ok"  );
		var show_trimmed_content_element$ = parent_table_td$.find( selector_gmail_composer_parent_td_Show_trimmed_content_element );
		if(show_trimmed_content_element$ && show_trimmed_content_element$.length > 0)
		{
			WEB_CMM.log( "findgmail_composer :  show_trimmed_content  found"   );
			return show_trimmed_content_element$[0];
		}
	}
	
	return null;
}


function searchElementPresent_findgmail_composer()
{
	if(g_status_action !=  "start")
	{
		return; //stop 
	}
	var acomposer$  =  findgmail_composer()
	if(acomposer$ && acomposer$.length > 0)
	{
		handle_gmail_composer(acomposer$[0]);
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

function run_gmail_fn()
{
	
	searchElementPresent_findgmail_composer();
	WEB_CMM.log( "run_gmail_fn : start waitforElementPresent_findgmail_composer "   );
}

self.port.on("status-gmail-action", function(status) {

	g_status_action = status;

});

function is_my_page(url_spec)
{
    var reg_URL = /^https:\/\/mail.google.com/ ;
    var match = reg_URL.test( url_spec );
    return match;
}


self.port.on("get-gmail-composer", function(url_spec) {

	WEB_CMM.log( "run_gmail_fn : get-gmail-composer"   );
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

// we use waitforelementpresent to detect the gmail composer, so it has no need to addeventlistener for the page modification
})();

