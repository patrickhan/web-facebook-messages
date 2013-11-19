/*
 * This js is for the 'wall' page in face book.
 * It will scratch the 'What do you mind' post message editor/recepients/submit
 */


"use strict";
var fn_webpage_parser_googleplus_wall_ns  = (undefined === fn_webpage_parser_googleplus_wall_ns) ? {}: fn_webpage_parser_googleplus_wall_ns;

(function(ns){

var  WEB_CMM = fn_web_common_ns;

const selector_googleplus_wall_share_group = "div[guidedhelpid='sharebox']:visible"  ;
const selector_googleplus_wall_share_group_editor_parent = "div[guidedhelpid='sharebox_editor']:visible"  ;

const selector_googleplus_wall_share_group_editor = "div[contenteditable='true'][g_editable='true'][role='textbox']:visible";


const selector_googleplus_wall_share_group_sendbox = "div[guidedhelpid='sharebutton']:visible";
const selector_googleplus_wall_share_group_tobox = "div[guidedhelpid='sharebox_chips_div']:visible";
//reply
const selector_googleplus_wall_reply_group_editor = selector_googleplus_wall_share_group_editor;
const selector_googleplus_wall_reply_group_parent = "div[role='article']:visible";
const selector_googleplus_wall_reply_group_reply  = "div[role='button']:visible:contains('Post comment')";
const selector_googleplus_wall_HJContentID_container = "div[hjcontentid-container]";
const attr_googleplus_wall_HJContentID_container = "hjcontentid-container";
	/*
group:
div: "guidedhelpid" ="sharebox"

editor :
div: "guidedhelpid" = "sharebox_editor"  > div contenteditable=true , g_editable=true, role=textbox"

recipient 
div : guidedhelpid=sharebox_chips_div

sendbox:
div guidedhelpid = shareboxcontrols > guidedhelpid=sharebutton :text=share
*/


	function is_wall_share_editor(editor)
	{
		var is_theeditor = $(editor).is(selector_googleplus_wall_share_group_editor);
		if(!is_theeditor)
		{
			return false;
		}
		var ashare_group$ = find_googleplus_wall_share_group_from_editor(editor);
		if(ashare_group$ && ashare_group$.length > 0)
		{
			return true;
		}
		//maybe more restrict
		return false;
	}
	
	function get_sendbox(editor)
	{
		var sendbox =  null;
		var ashare_group$ = find_googleplus_wall_share_group_from_editor(editor);
		if(!ashare_group$ || ashare_group$.length == 0)
		{
			return sendbox;
		}
		var sendbox$ = find_googleplus_wall_share_group_sendbox_from_group(ashare_group$ );
		if(sendbox$ && sendbox$.length > 0)
		{
			sendbox = sendbox$[0];
		}
		return sendbox;
	}
	
	function get_tobox(editor)
	{
		var tobox= null;
		var ashare_group$ = find_googleplus_wall_share_group_from_editor(editor);
		if(!ashare_group$ || ashare_group$.length == 0)
		{
			return tobox;
		}
		var tobox$ = find_googleplus_wall_share_group_tobox_from_group(ashare_group$);
		if(tobox$ && tobox$.length > 0)
		{
			tobox = tobox$[0];
		}
		
		return tobox;
	}
	
	function find_googleplus_wall_share_group_from_editor(editor)
	{
		if(!editor)
			return null;
		var ashare_group$  = $(editor).closest(selector_googleplus_wall_share_group);
		return ashare_group$;
	}
	
	function find_googleplus_wall_share_group_sendbox_from_group(ashare_group$)
	{
		return ashare_group$.find(selector_googleplus_wall_share_group_sendbox);
	}
	
	function find_googleplus_wall_share_group_tobox_from_group(ashare_group$)
	{
		return ashare_group$.find(selector_googleplus_wall_share_group_tobox);
	}
	
	// reply
	function is_wall_reply_editor(editor)
	{
		var is_theeditor = $(editor).is(selector_googleplus_wall_share_group_editor);
		if(!is_theeditor)
		{
			return false;
		}
		var theeditor$ = $(editor);
		var areply_group$  = theeditor$.closest(selector_googleplus_wall_reply_group_parent);
		if(areply_group$ && areply_group$.length > 0)
		{
			return true;
		}
		return false;
	}
	
	function findReplyButton_from_composer(editor)
	{
		var theeditor$ = $(editor);
		var areply_group$  = theeditor$.closest(selector_googleplus_wall_reply_group_parent);
		if(areply_group$ && areply_group$.length > 0)
		{
			var reply_button$ = areply_group$.find(selector_googleplus_wall_reply_group_reply);
			return reply_button$;
		}
		return null;
	}
	function get_Reply_latest_HJContentID(editor)
	{
		var theeditor$ = $(editor);
		var areply_group$  = theeditor$.closest(selector_googleplus_wall_reply_group_parent);
		if(areply_group$ && areply_group$.length > 0)
		{
			var content  = areply_group$.contents().find("div").text();
			log( "$(acomposer).contents() :  + "  +   content );
			var results = content.match( WEB_CMM.HJContentIDRegEx );
			if(results)
			{
				var docid = results[0];
				docid =  docid.substring( docid.indexOf(":") + 1 );// remove the prefix 
				
				log( "get_latest_HJContentID :  + "  +   docid );
				return docid;
			}
		}
		return null;
	}
	function get_Reply_latest_HJContentID_v2(editor)
	{
		var theeditor$ = $(editor);
		var areply_group$  = theeditor$.closest(selector_googleplus_wall_reply_group_parent);
		if(areply_group$ && areply_group$.length > 0)
		{ 
			var HJContentID_container$  = areply_group$.find(selector_googleplus_wall_HJContentID_container)
			if(HJContentID_container$ && HJContentID_container$.length > 0)
			{				
				var attr_val = HJContentID_container$.attr(attr_googleplus_wall_HJContentID_container);
				var attr_val_array = JSON.parse(attr_val);
				var fnDocId = "";
				if(typeof attr_val_array === "string")
				{
					fnDocId = attr_val_array;
				}
				else if(Array.isArray(attr_val_array))
				{
					fnDocId = attr_val_array[attr_val_array.length-1];
				}
				return fnDocId;				
			}
		}
		return null;
	}
	function log(msg)
	{
		WEB_CMM.log( msg  );
	}	
	ns.is_wall_share_editor = is_wall_share_editor;
	ns.get_sendbox =  get_sendbox;
	ns.get_tobox = get_tobox;
	
	//reply
	ns.is_wall_reply_editor = is_wall_reply_editor;
	ns.findReplyButton_from_composer = findReplyButton_from_composer
	ns.get_Reply_latest_HJContentID = get_Reply_latest_HJContentID
	ns.get_Reply_latest_HJContentID_v2 =  get_Reply_latest_HJContentID_v2;

         
})(fn_webpage_parser_googleplus_wall_ns); // end of (function(){


