// in this module , we are going to keep a group of editor to send the message




;
"use strict";
var fn_webpage_parser_outlook_ns  = (undefined === fn_webpage_parser_outlook_ns) ? {}: fn_webpage_parser_outlook_ns;

(function(ns) {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;

const selector_outlook_composer = "#ComposeRteEditor_surface"   //iframe and id = ComposeRteEditor_surface

const selector_outlook_composer_sendbox = "#SendMessage"; //div and  id = SendMessage
const selector_outlook_composer_subjectbox = "#fSubject"; // input and id = fSubject
const reply_token_in_subject = "RE:";

function get_latest_HJContentID(acomposer)
{//composer is a iframe , get its content text
	var content  = $(acomposer).contents().find("body").text();
	WEB_CMM.log( "$(acomposer).contents() :  + "  +   content );
	var results = content.match( WEB_CMM.HJContentIDRegEx );
	if(results)
	{
		var docid = esults[0];
		docid =  docid.subString( docid.indexOf(":") + 1 );// remove the prefix 
		
		WEB_CMM.log( "get_latest_HJContentID :  + "  +   docid );
		return docid;
	}
}

////////////////send box part[
function findSendButton_from_composer(acomposer)
{
	WEB_CMM.log( "hookSendButton :  + "  +  acomposer );
	var sendbox$ = $(selector_outlook_composer_sendbox);
	
	if(sendbox$ && sendbox$.length > 0)
	{
		WEB_CMM.log( "sendbox$ : found  " );
		return sendbox$[0];
	}
	
	return null;	
}

///////////////send box part]

///////////////reply token part[
//please note , we check the subject box , if it starts with "RE:" , then we think it is for reply
function isForReply(acomposer)
{
	var outlook_subjectbox$ = $(selector_outlook_composer_subjectbox);
	try
	{
		var subject = outlook_subjectbox$.val();
		var isreply = subject.indexOf(reply_token_in_subject) == 0;
		return !!isreply;
	
	}
	catch(err)
	{
	}
	return false;	
}

 
///reply token part]


///outlook composer part
function findoutlook_composer()
{
	try
	{
		var outlook_composer$ = $(selector_outlook_composer);
		if(!outlook_composer$ || outlook_composer$.length == 0)
		{
			WEB_CMM.log( "findoutlook_composer :  not found"   );
			return false;
		}
		WEB_CMM.log( "findoutlook_composer :  found"   );
		return outlook_composer$;
	}
	catch(err)
	{
		WEB_CMM.log( "findoutlook_composer :  excpetion " +  err  );
	}
	return null;
	
}
///outlook composer part

//export
    //functions
	ns.findSendButton_from_composer = findSendButton_from_composer;
	ns.isForReply =  isForReply;
	ns.findoutlook_composer = findoutlook_composer;
	ns.get_latest_HJContentID = get_latest_HJContentID;
	ns.expand_show_trimmed_content = expand_show_trimmed_content;

})(fn_webpage_parser_outlook_ns);

