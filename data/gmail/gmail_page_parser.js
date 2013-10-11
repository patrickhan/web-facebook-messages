// in this module , // in this module , we are going to parse the html page DOM in gmail




;
"use strict";
var fn_webpage_parser_gmail_ns  = (undefined === fn_webpage_parser_gmail_ns) ? {}: fn_webpage_parser_gmail_ns;

(function(ns) {

var  M_TEST =  fn_web_mocktest_ns;
var  WEB_CMM = fn_web_common_ns;

const selector_gmail_composer = "div[class='Am Al editable'] > iframe"   //"div.Am.Al.editable > iframe" "//div[contains(@class, 'Am') and contains(@class, 'Al') and contains(@class, 'editable')]/iframe";

const selector_form = "form";
const selector_table = "table"	;
const selector_td = "td"	;
const selector_gmail_composer_parent_table = selector_table;
const selector_gmail_composer_parent_table_td = selector_td;
const selector_gmail_composer_parent_td_Show_trimmed_content_element = "div[data-tooltip='Show trimmed content'] > div > img";
const selector_gmail_composer_sendbox = "div:contentIs('Send')"; //using plugin in jquery_xpath.js

const selector_gmail_composer_tobox_from_form = "form table textarea[name='to']";  //tobox :   form table textarea[name='to']

const selector_gmail_composer_subjectbox_from_form = "form  input[name='subject']"; 

const selector_gmail_composer_tobox_emial_spans = "span[email*='@']:visible";  
const gmail_reply_prefix = "Re: ";

function get_latest_HJContentID(acomposer)
{
	var content  = $(acomposer).contents().find("body").text();
	WEB_CMM.log( "$(acomposer).contents() :  + "  +   content );
	var results = content.match( WEB_CMM.HJContentIDRegEx );
	if(results)
	{
		var docid = results[0];
		docid =  docid.substring( docid.indexOf(":") + 1 );// remove the prefix 
		
		WEB_CMM.log( "get_latest_HJContentID :  + "  +   docid );
		return docid;
	}
	return null;
}

////////////////send box part[
function findSendButton_from_composer(acomposer)
{
	WEB_CMM.log( "hookSendButton :  + "  +  acomposer );
	//we want to find out the 'table' element of acomposer's closest ansestor
	var parent_table$ =  $(acomposer).closest(selector_gmail_composer_parent_table);
	//we want to find out the 'table' element of parent_table$ closest ansestor, using closest. will return itself
	var parent_table_table$ =  parent_table$.parent().closest(selector_gmail_composer_parent_table);
	if(parent_table_table$ && parent_table_table$.length > 0)
	{	//there is a div whose content is 'Send'
		var sendbox$ = $(selector_gmail_composer_sendbox, parent_table_table$);
		
		if(sendbox$ && sendbox$.length > 0)
		{
			WEB_CMM.log( "sendbox$ : found  " );
			return sendbox$[0];
		}
	}
	return null;	
}

///////////////tobox box part]
//tobox
//find to box from composer
//tobox :   textarea name=to -- table - form - td
//composer: iframe-table-table-td
function find_tobox(acomposer)
{
	WEB_CMM.log( "find_tobox  from :  + "  +  acomposer );
	//we want to find out the 'table' element of acomposer's closest ansestor
	var parent_table$ =  $(acomposer).closest(selector_table);
	//we want to find out the 'table' element of parent_table$ closest ansestor, using closest. will return itself
	var parent_table_table$ =  parent_table$.parent().closest(selector_table);
	if(parent_table_table$ && parent_table_table$.length > 0)
	{	
		WEB_CMM.log( "parent_table_table$ : found  " );
		//there is common td
		var parent_common_td$ =  parent_table_table$.closest(selector_td);
		if(parent_common_td$ && parent_common_td$.length > 0)
		{
			WEB_CMM.log( "parent_common_td$ : found  " );
			var tobxo$ = parent_common_td$.find(selector_gmail_composer_tobox_from_form);
			if(tobxo$ && tobxo$.length > 0)
			{
					WEB_CMM.log( "tobxo$ : found  " );
					return tobxo$;
			}
		}
	}
	return null;	
}

function toBoxIsFilled(acomposer)
{
	var tobxo$ = find_tobox(acomposer);
	if(tobxo$)
	{
		if(tobxo$.is(":visible")  )
		{
			/*WEB_CMM.log( "toBox Is  ="  + tobxo$[0] );
			var recipients = tobxo$.val();
			if(recipients.length > 0 )*/
			var offset = tobxo$.offset();
			if(offset.left >8 || offset.top >8)// if the tobxo$ is move to right or move down then there is recipient inserted
			{
				WEB_CMM.log( "toBoxIsFilled :  offset.left = "  + offset.left  );
				return true;
			}
		}
		else
		{//if the editor is invisible , check the content text 
			var recipients$  = tobxo$.closest(selector_table).closest(selector_td).find(selector_gmail_composer_tobox_emial_spans);
			if(recipients$ && recipients$.length > 0)
			{
				recipients$.each(function(index)
				{
					WEB_CMM.log( "toBoxIsFilled :  recipient = "  + $(this).attr('email')  );
				});
				return true;
			}	
		}
	}
	
	return false;
}
//tobox/]
///////////////reply token part[
//please note , if the same account is logined in diferent computers and open the save email, gmail will sync the status, there will not be a token like this function, so bad!!
function find_reply_token(acomposer)
{
	//we want to find out the 'table' element of acomposer's closest ansestor
	var parent_table$ =  $(acomposer).closest(selector_gmail_composer_parent_table);
	//we want to find out the 'td' element of parent_table$ closest ansestor
	var parent_table_td$ =  parent_table$.closest(selector_gmail_composer_parent_table_td);
	if(parent_table_td$ && parent_table_td$.length > 0)
	{
		WEB_CMM.log( "check_for_reply :  parent_table_td$  ok"  );
		//there is  an image which has tool tip : 'Show trimmed content'
		var show_trimmed_content_element$ = parent_table_td$.find( selector_gmail_composer_parent_td_Show_trimmed_content_element );
		if(show_trimmed_content_element$ && show_trimmed_content_element$.length > 0)
		{
			WEB_CMM.log( "findgmail_composer :  show_trimmed_content  found"   );
			return show_trimmed_content_element$[0];
		}
	}
	
	return null;	
}




function expand_show_trimmed_content(reply_token)
{
	WEB_CMM.log( "expand_show_trimmed_content : reply_tokenis  "   + reply_token );
	$(reply_token).click();
}
///reply token part]


///gmail composer part
function findgmail_composer()
{
	try
	{
		var gmail_composer$ = $(selector_gmail_composer);
		if(!gmail_composer$ || gmail_composer$.length == 0)
		{
			//WEB_CMM.log( "findgmail_composer :  not found"   );
			return false;
		}
		//WEB_CMM.log( "findgmail_composer :  found : "  + gmail_composer$.length );
		return gmail_composer$;
	}
	catch(err)
	{
		WEB_CMM.log( "findgmail_composer :  excpetion " +  err  );
	}
	return null;
	
}
///gmail composer part
/////////// subject part

function getSubjectBox(acomposer)
{
	
	WEB_CMM.log( "getSubjectBox  from :  + "  +  acomposer );
	//we want to find out the 'table' element of acomposer's closest ansestor
	var parent_table$ =  $(acomposer).closest(selector_table);
	//we want to find out the 'table' element of parent_table$ closest ansestor, using closest. will return itself
	var parent_table_table$ =  parent_table$.parent().closest(selector_table);
	if(parent_table_table$ && parent_table_table$.length > 0)
	{	
		WEB_CMM.log( " getSubjectBox parent_table_table$ : found  " );
		//there is common td
		var parent_common_td$ =  parent_table_table$.closest(selector_td);
		if(parent_common_td$ && parent_common_td$.length > 0)
		{
			WEB_CMM.log( "getSubjectBox parent_common_td$ : found  " );
			var subjectbxo$ = parent_common_td$.find(selector_gmail_composer_subjectbox_from_form);
			if(subjectbxo$ && subjectbxo$.length > 0)
			{
					WEB_CMM.log( "subjectbxo$ : found  " );
					return subjectbxo$;
			}
		}
	}
	return null;
}

function getSubject(acomposer)
{
	var subject = getSubjectBox(acomposer).val();
	//remove 'Re:' if it has it.
	if(subject.indexOf(gmail_reply_prefix) == 0)
	{
		subject = subject.substring(gmail_reply_prefix.length -1);
	}
	
	WEB_CMM.log( "gmail getSubject :  subject is:" +  subject  );
	return subject;//table: role="presentation" h1
}

/////////// subject part
//export
    //functions
	ns.findSendButton_from_composer = findSendButton_from_composer;
	ns.find_reply_token =  find_reply_token;
	ns.findgmail_composer = findgmail_composer;
	ns.get_latest_HJContentID = get_latest_HJContentID;
	ns.expand_show_trimmed_content = expand_show_trimmed_content;
	ns.toBoxIsFilled = toBoxIsFilled;
	ns.getSubject = getSubject;

})(fn_webpage_parser_gmail_ns);

