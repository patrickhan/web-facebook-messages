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
		var theeditor$ = $(editor).is(selector_googleplus_wall_share_group_editor);
		if(!theeditor$)
		{
			return false;
		}
		if(!theeditor$.length == 0)
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
		
	ns.is_wall_share_editor = is_wall_share_editor;
	ns.get_sendbox =  get_sendbox;
	ns.get_tobox = get_tobox;

         
})(fn_webpage_parser_googleplus_wall_ns); // end of (function(){


