/* In this js file, we do the following thing(s) for fn box in html page:
 * 1 If there is a css tranform is set for any fn box's parent element, 
 * the window based fn box will not be shown, 
 * so this file will remove the 'css tranform' in any fn box's parent element. 
 * Think about the js in iframe it can not access the parent elements of iframe ,
 * we are going to add listener for any dom window.
 * 
 * refer : fnbox_guard.js
 */

 //fnbox.ownerDocument.defaultView.postMessage("fn-box-help" , srcElement.ownerDocument.defaultView.location);

"use strict";

var fnbox_pagecontent_ns  = (undefined === fnbox_pagecontent_ns) ? {}: fnbox_pagecontent_ns;

(function(ns)
{
	
var msg_fn_box_help =  "fn-box-help";
var msg_fn_box_help_to_addons =  "fn-box-help-to-addons";
var msg_fn_box_help_to_content =  "fn-box-help-to-content";

	function log(msg)
	{
		console.error("*****" + msg  );
	}

	function sendMessage_to_addons( obj1)
	{
		//log( "self.port.emit(msg_fn_box_help_to_addons, alocation);obj1: "+obj1);	
		self.port.emit(msg_fn_box_help_to_addons, obj1);
		
		
	}
	
	function listener_func(event)
	{
		try{
		if( event.data !==  msg_fn_box_help )
			return;
		//log( " on "  + event.data  + " -- source:" + event.source + "--origin:"+ event.origin);	
		event.source.postMessage("fn-box-help-received" , event.origin);
		sendMessage_to_addons(event.source.location);
		//sendMessage_to_addons( event.source);//event.origin);
		//if (event.origin !== "http://example.org:8080")//srcElement.ownerDocument.defaultView.location
		//	return;
	    // event.source is window.opener? 
	    // event.data is "hello there!"
	  // ...
	  }catch(e)
	  {
		log( " listener_func : error :  " + e);
	  }
	}
	
	function add_listener()
	{	
		window.addEventListener("message", listener_func, false);
		
		document.addEventListener(msg_fn_box_help_to_content, on_msg_fn_box_help_to_content, false);
	}
	
	function remove_css_transform(srcElement)
	{
		try
		{	
		  var  parentnd = srcElement;
		
		  while(parentnd)//.nodeName != "HTML" )
		  {
			if(parentnd == parentnd.parentElement)
			{
				break;
			}
			parentnd = parentnd.parentElement;
			if(parentnd == null)
			{
				break;
			}
			var transformVal = parentnd.ownerDocument.defaultView.getComputedStyle(parentnd, "").transform;
			if(transformVal && transformVal !="none")
			{
				parentnd.style.transform='none';
			}
		  }
	  }
	  catch(e)
	  {
		  log("remove_css_transform: error : " + e);
	  
	  }		
	}

	function on_msg_fn_box_help_to_content(event)
	{	
		
		var srcElement = event.target;

		remove_css_transform(srcElement);

		sendMessage_to_addons(null);//tell parent window  to do so : remove_css_transform
	 }
	  
	add_listener();
    
})(fnbox_pagecontent_ns);
