// in this module , we are going to parse the reply editor in yahoo mail




;
"use strict";
var fn_webpage_parser_yahoo_ns  = (undefined === fn_webpage_parser_yahoo_ns) ? {}: fn_webpage_parser_yahoo_ns;

(function(ns) {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;

const selector_yahoo_composer = "div[id='rtetext'][contenteditable='true'][aria-label='Message Body']"   //"//div[contains(@class, 'Am') and contains(@class, 'Al') and contains(@class, 'editable')]/iframe";
const selector_yahoo_composer_tobox = "div[id='to']";

//title="Show message history"
const selector_table = "table";
const selector_yahoo_composer_reply_Show_message_history_element = "span.qtd-expansion-text:contentIs('Show message history')";
const selector_yahoo_composer_sendbox = "a:contentIs('Send')"; //using plugin in jquery_xpath.js  "span[data-action='send']:contentIs('Send')";
const selector_yahoo_composer_threadpane = "div.threadpane";
const selector_yahoo_composer_subjectbox = "span.thread-subject";   //maybe use this: input:id=subject-field
//div . class="threadpane "    span .class="thread-subject"

function get_latest_HJContentID(acomposer)
{
	var content  = $(acomposer).text();
	log( "$(acomposer).contents() :  + "  +   content );
	var results = content.match( WEB_CMM.HJContentIDRegEx );
	if(results)
	{
		var docid = results[0];
		docid =  docid.substring( docid.indexOf(":") + 1 );// remove the prefix 
		
		log( "get_latest_HJContentID :  + "  +   docid );
		return docid;
	}
	return null;
}

////////////////send box part[
function findSendButton_from_composer(acomposer)
{
	log( "hookSendButton :  + "  +  acomposer );
	//we want to find out the 'table' element of acomposer's closest ansestor
	var parent_table$ =  $(acomposer).closest(selector_table);
	if(parent_table$ && parent_table$.length > 0)
	{	//there is a div whose content is 'Send'
		log( "hookSendButton :  + parent_table$ found"  );
		var sendbox$ = $(selector_yahoo_composer_sendbox, parent_table$).parent();
		
		if(sendbox$ && sendbox$.length > 0)
		{
			log( "sendbox$ : found  " );
			return sendbox$[0];
		}
	}
	return null;	
}

///////////////send box part]


///////////////tobox box part]
//tobox
//find to box from composer
//tobox :   textarea name=to -- table - form - td
//composer: iframe-table-table-td
function find_tobox(acomposer)
{
	log( "find_tobox  from :  + "  +  acomposer );
	//we want to find out the 'table' element of acomposer's closest ansestor
	var parent_table$ =  $(acomposer).closest(selector_table);
	if(parent_table$ && parent_table$.length > 0)
	{	
		log( "parent_table$ : found  " );
		var tobxo$ = parent_table$.find(selector_yahoo_composer_tobox);
		if(tobxo$ && tobxo$.length > 0)
		{
			log( "tobxo$ : found  " + tobxo$.length);
			return tobxo$;
		}
	}
	return null;	
}

function toBoxIsFilled(acomposer)
{
	var tobxo$ = find_tobox(acomposer);
	var recipients = tobxo$.text();
	recipients = recipients.replace(/\s+/g, '');//remove blank chars
	if(recipients.length > 0) 
	{
		log( "tobox : recipient is   " + recipients );
		return true;
	}
	return false;
}
//tobox/]

///////////////reply token part[

/*function isForReply(acomposer)
{// check the to box is filled or not, if it is filled then it is  for reply
	var toboxhasrecipients = toBoxIsFilled(acomposer);
	if(!toboxhasrecipients)
	{
		return false;
	}
	find_reply_token(acomposer)
	return !!reply;
}*/

//please note , if the same account is logined in diferent computers and open the save email, yahoo will sync the status, there will not be a token like this function, so bad!!
function find_reply_token(acomposer)
{
	//we want to find out the 'table' element of acomposer's closest ansestor
	var parent_table$ =  $(acomposer).closest(selector_table);
	if(parent_table$ && parent_table$.length > 0)
	{
		log( "find_reply_token :  parent_table$  ok"  );
		//there is  an div which has : 'Show message history'
		var show_trimmed_content_element$ = parent_table$.find( selector_yahoo_composer_reply_Show_message_history_element );
		if(show_trimmed_content_element$ && show_trimmed_content_element$.length > 0)
		{
			log( "findyahoo_composer :  show_trimmed_content  found"   );
			return show_trimmed_content_element$[0];
		}
	}
	return null;	
}

function expand_show_trimmed_content(reply_token)
{
	log( "expand_show_trimmed_content : reply_tokenis  "   + reply_token );
	$(reply_token).mouseover();
	$(reply_token).click();
}
///reply token part]


///yahoo composer part
function findyahoo_composer()
{
	try
	{
		var yahoo_composer$ = $(selector_yahoo_composer);
		if(!yahoo_composer$ || yahoo_composer$.length == 0)
		{
			//log( "findyahoo_composer :  not found"   );
			return false;
		}
		//log( "findyahoo_composer :  found "  +  yahoo_composer$.length);
		return yahoo_composer$;
	}
	catch(err)
	{
		log( "findyahoo_composer :  excpetion " +  err  );
	}
	return null;
	
}
///yahoo composer part
/////////// subject part

function getSubjectBox(acomposer)
{
	var threadpane$ = $(acomposer).closest(selector_yahoo_composer_threadpane);
	return threadpane$.find(selector_yahoo_composer_subjectbox);
}

function getSubject(acomposer)
{
	var subject = getSubjectBox(acomposer).text();
	log( "yahoo getSubject :  subject is:" +  subject  );
	return subject;
}
function log(msg)
{
	WEB_CMM.log( msg  );
}
/////////// subject part
//export
    //functions
	ns.findSendButton_from_composer = findSendButton_from_composer;
	ns.toBoxIsFilled =  toBoxIsFilled;
	ns.findyahoo_composer = findyahoo_composer;
	ns.find_reply_token = find_reply_token;
	ns.get_latest_HJContentID = get_latest_HJContentID;
	ns.expand_show_trimmed_content = expand_show_trimmed_content;
	ns.getSubject = getSubject;
	ns.find_tobox = find_tobox;

})(fn_webpage_parser_yahoo_ns);

