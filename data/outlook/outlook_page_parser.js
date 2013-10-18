// in this module , we are going to parse the html page DOM in hotmail- outlook




;
"use strict";
var fn_webpage_parser_outlook_ns  = (undefined === fn_webpage_parser_outlook_ns) ? {}: fn_webpage_parser_outlook_ns;

(function(ns) {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;

const selector_outlook_composer = "#ComposeRteEditor_surface:visible"   //iframe and id = ComposeRteEditor_surface

const selector_outlook_composer_sendbox = "#SendMessage"; //div and  id = SendMessage
const selector_outlook_composer_subjectbox = "#fSubject"; // input and id = fSubject
const selector_outlook_composer_tobox = "#toCP"; // div and id = toCP
const selector_outlook_composer_tobox_input = "input[type='email']"; 
const selector_outlook_composer_subject_input = "#fSubject"; 
//id="ComposeContentHeader" > class="Subject"    input : id="fSubject"
const reply_token_in_subject = "RE: ";

function get_latest_HJContentID(acomposer)
{//composer is a iframe , get its content text
	var content  = $(acomposer).contents().find("body").text();
	log( "$(acomposer).contents() :  + "  +   content );
	var results = content.match( WEB_CMM.HJContentIDRegEx );
	if(results)
	{
		var docid = results[0];
		docid =  docid.substring( docid.indexOf(":") + 1 );// remove the prefix 
		
		log( "get_latest_HJContentID :  + "  +   docid );
		return docid;
	}
	return null
}

////////////////send box part[
function findSendButton_from_composer(acomposer)
{
	log( "hookSendButton :  + "  +  acomposer );
	var sendbox$ = $(selector_outlook_composer_sendbox);
	
	if(sendbox$ && sendbox$.length > 0)
	{
		log( "sendbox$ : found  " );
		return sendbox$[0];
	}
	
	return null;	
}

///////////////send box part]
////////////////////////// tobox[  div:id='toCP'  input:type=email
function find_tobox(acomposer)
{
	var outlook_tobox$ = $(selector_outlook_composer_tobox);
	return outlook_tobox$;
	
	//const selector_outlook_composer_tobox_input = "input[type='email']"; 
}

//////////////////////////tobox]
///////////////reply token part[
//please note , we check the subject box , if it starts with "RE:" , then we think it is for reply
function isForReply(acomposer)
{
	
	//subject has "RE:"
	var subject_has_RE = false;
	var outlook_subjectbox$ = $(selector_outlook_composer_subjectbox);
	try
	{
		var subject = outlook_subjectbox$.val();
		subject_has_RE = subject.indexOf(reply_token_in_subject) == 0;
	
	}
	catch(err)
	{
	}
	if(!subject_has_RE)
	{
		return false;
	}
	
	
	//recipient is not empty
	var recipient_not_empty = false;
	var outlook_tobox$ = find_tobox(acomposer);
	if(outlook_tobox$ && outlook_tobox$.length > 0)
	{
		var recipients = outlook_tobox$.text();
		recipients = recipients.replace(/\s+/g, '');//remove blank chars
		if(recipients.length > 0) //.cp_inputContainer
		{
			log( "tobox : recipient is   " + recipients );
			recipient_not_empty = true;
		}
		
	}
	return subject_has_RE && recipient_not_empty;	
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
			//log( "findoutlook_composer :  not found"   );
			return false;
		}
		//log( "findoutlook_composer :  found"   );
		return outlook_composer$;
	}
	catch(err)
	{
		log( "findoutlook_composer :  excpetion " +  err  );
	}
	return null;
	
}
///outlook composer part
/////////// subject part

function getSubjectBox(acomposer)
{
	return $(selector_outlook_composer_subject_input);
}

function getSubject(acomposer)
{
	var subject = getSubjectBox(acomposer).val();
	//remove 'Re:' if it has it.
	if(subject.indexOf(reply_token_in_subject) == 0)
	{
		subject = subject.substring(reply_token_in_subject.length -1);
	}	
	
	log( "outlook getSubject :  subject is:" +  subject  );
	return subject;
}

/////////// subject part
function log(msg)
{
	WEB_CMM.log( msg  );
}

//export
    //functions
	ns.findSendButton_from_composer = findSendButton_from_composer;
	ns.isForReply =  isForReply;
	ns.findoutlook_composer = findoutlook_composer;
	ns.get_latest_HJContentID = get_latest_HJContentID;
	ns.getSubject = getSubject;

})(fn_webpage_parser_outlook_ns);

