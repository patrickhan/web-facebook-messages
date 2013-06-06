// in this module , we are going to keep a array for the editors in the webpage

/*
(function() {
    jQuery.noConflict();
    $ = function(selector,context) { 
        return new jQuery.fn.init(selector,context||example.doc); 
    };
    $.fn = $.prototype = jQuery.fn;

    example = new function(){};
    example.log = function() { 
        Firebug.Console.logFormatted(arguments,null,"log"); 
    };
    example.run = function(doc,aEvent) {
        // Check for website
        if (!doc.location.href.match(/^http:\/\/(.*\.)?stackoverflow\.com(\/.*)?$/i))  
            return;

        // Check if already loaded
        if (doc.getElementById("plugin-example")) return;

        // Setup
        this.win = aEvent.target.defaultView.wrappedJSObject;
        this.doc = doc;

        // Hello World
        this.main = main = $('<div id="plugin-example">').appendTo(doc.body).html('Example Loaded!');
        main.css({ 
            background:'#FFF',color:'#000',position:'absolute',top:0,left:0,padding:8
        });
        main.html(main.html() + ' - jQuery <b>' + $.fn.jquery + '</b>');
    };

    // Bind Plugin
    var delay = function(aEvent) { 
        var doc = aEvent.originalTarget; setTimeout(function() { 
            example.run(doc,aEvent); 
        }, 1); 
     };
    var load = function() { 
        gBrowser.addEventListener("DOMContentLoaded", delay, true); 
    };
    window.addEventListener("pageshow", load, false);

})();
*/

const PROJECT_NAME_PREFIX   = "FBM";
const INTEGRATING_ROLE_NAME = "_integerating_role_";
const ROLE_NAME_TO_BOX   = "to_box_";
const ROLE_NAME_EDIT_BOX = "edit_box_";
const ROLE_NAME_SEND_BOX = "send_box_";
const ROLE_NAME_SEND_BY_KEYPRESS_ENTER = "keypress_enter";
const ROLE_NAME_SEND_BY_MOUSE_CLICK = "mouse_click";
const FN_INTEGRATING_ATTR_NAME = "fn-integrating";
const FN_INTEGRATING_ATTR_VALUE = "emailbody";
//new_message_editor_group.editor.removeAttr("fn-integrating") == "emailbody";

// config:
//1 facebook message new 
// div id="pagelet_web_messenger" -- a good starting point
//editor : textarea : name="message_body", 
//send button : input value="Send" type="submit"
//tobox : td #text="To:" this element's next sibling element

var selector_editor = 'textarea[name="message_body"]';
var selector_sendbox = 'input[value="Send"][type="submit"]';
var selector_tobox = "//td[contains(.,'To:')]";

var charstoformid = '_0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz'.split('');
function uniqID(idlength) {
    //var charstoformid = '_0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz'.split('');
    if (! idlength) {
        idlength = Math.floor(Math.random() * charstoformid.length);
    }
    var uniqid = '';
    for (var i = 0; i < length; i++) {
        uniqid += charstoformid[Math.floor(Math.random() * charstoformid.length)];
    }
    return uniqid;
}


var new_message_editor_group = 
{
	"id":null,
	"editor": null, 
	"sendbox": null, 
	"tobox": null, 
};

function find_Editor_group()
{
  var a_id = uniqID(20);
  var role_name = PROJECT_NAME_PREFIX + INTEGRATING_ROLE_NAME + a_id;
 // find editor
  if(!new_message_editor_group.editor)
  {
	  var editors$ = $(selector_editor);
  
	  var log_str = "find edtiors count is : " ;
	  log_str += editors$.length;
	  self.port.emit("getEditor", log_str + " " +a_id );
  
	  if(editors$.length == 1)//shoult there is only one
	  {
		  editors$.attr(role_name, ROLE_NAME_EDIT_BOX);
		  editors$.attr(FN_INTEGRATING_ATTR_NAME,FN_INTEGRATING_ATTR_VALUE);
		  new_message_editor_group.editor = editors$;

		  new_message_editor_group.id = a_id;
	  }
  }
  
  //find send button
  if(!new_message_editor_group.sendbox)
  {
	  var send_boxes$ = $(selector_sendbox);
  
	  var log_str = "find sendbox count is : " ;
	  log_str += send_boxes$.length;
	  self.port.emit("getEditor", log_str + " " +a_id );
  
	  if(send_boxes$.length == 1)//shoult there is only one
	  {
		  send_boxes$.attr(role_name, ROLE_NAME_SEND_BOX);
		  new_message_editor_group.sendbox = send_boxes$;
		  hook_Send_box();
	  }
  }
  
  //recepient box
  if(!new_message_editor_group.tobox)
  {
	  var to_boxes$ =  $.xpath(selector_tobox).next("td");
	  var log_str = "find to_boxe count is : " ;
	  log_str += to_boxes$.length;
	  self.port.emit("getEditor", log_str + " " +a_id );
  
	  if(to_boxes$.length == 1)//shoult there is only one
	  {
		  to_boxes$.attr(role_name, ROLE_NAME_TO_BOX);
		  new_message_editor_group.tobox = to_boxes$;
	  }
  }

  
  find_Editor_group_test(a_id);
}

function clean_Editor_group()
{
  // editor
	var role_name = PROJECT_NAME_PREFIX + INTEGRATING_ROLE_NAME + new_message_editor_group.id;
	if( new_message_editor_group.editor)
	{
		self.port.emit("getEditor- clean_Editor_group ", "editor_group.editor  " + new_message_editor_group.editor);
		new_message_editor_group.editor.removeAttr(role_name);
		new_message_editor_group.editor.removeAttr(FN_INTEGRATING_ATTR_NAME)

	    self.port.emit("getEditor", "editors$ removeAttr +  " + role_name);
		new_message_editor_group.editor = null;
	}

	if( new_message_editor_group.sendbox)
	{
		unhook_Send_box();
		new_message_editor_group.sendbox.removeAttr(role_name);
	   self.port.emit("getEditor", "sendbox$ removeAttr +  " + role_name);
	   new_message_editor_group.sendbox =  null;
	}

	if( new_message_editor_group.tobox)
	{
		new_message_editor_group.tobox.removeAttr(role_name);
	   self.port.emit("getEditor", "tobox$ removeAttr +  " + role_name);
	   new_message_editor_group.tobox =  null;
	}
	
	clean_Editor_group_test();
}


function call_simulate_mouse_click( box_obj, timeout)
{
	if(!box_obj)
		return;
	setTimeout(function(){
			var getX = function( obj ) {
				if( obj == null ) {
				  return 0;
				} else {
				  return obj.offsetLeft + getX( obj.offsetParent );
				}
			  }
			  var getY = function( obj ) {
				if( obj == null ) {
				  return 0;
				} else {
				  return obj.offsetTop + getY( obj.offsetParent );
				}
			  }
			  var evt = document.createEvent("MouseEvents");
			  evt.initMouseEvent("mousedown", true, true, window,
				0, 0, 0, 0, 0, false, false, false, false, 0, null);
			  box_obj.dispatchEvent(evt);
			  
			//top : it is window object
			try{
				var x = getX( box_obj );//getX( top ) - getX( box_obj ), 
				var y = getY( box_obj );//getY( top ) - getY( box_obj ),
				evt = document.createEvent("MouseEvents");
				evt.initMouseEvent("mousemove", true, true, window,
					0, 0, 0, x,y, 
					false, false, false, false, 0, null);
				box_obj.dispatchEvent(evt);
			  }
			  catch(err)
			  {
			  //alert(err)
			  }

			var evt = document.createEvent("MouseEvents");
			evt.initMouseEvent("mouseup", true, true, window,
				  0, 0, 0, 0, 0, false, false, false, false, 0, null);
				box_obj.dispatchEvent(evt);
		}	, timeout);
}
	
function on_mousedown(evt)
{
			
	if(!evt.target.hj_cocntrol || evt.target.hj_cocntrol == 0)
	{
		evt.target.hj_cocntrol = 1;
	}
	else
	{
		evt.target.hj_cocntrol = 0;
		return;
	}
					
	//onmouseup attribute is insert by other part of code, remove it , we call the insertInvitationFooter directly
	var onmouseup_val = evt.target.getAttribute("onmouseup");
					
	if(onmouseup_val === "try{fnInvitationSenderNamespace.insertInvitationFooter();}catch(err){alert(err);}")
	{
		evt.target.removeAttribute("onmouseup");
	}
	evt.stopPropagation();
					
	try{
		//alert('will call insertInvitationFooter');//fnInvitationSenderNamespace.insertInvitationFooter();
	}
	catch(err){
		alert(err);
		}
					
	//simulate a mosue click
	call_simulate_mouse_click(evt.target,10);
}

function hook_Send_box()
{
	if( new_message_editor_group.sendbox)
	{
		var send_obj = new_message_editor_group.sendbox;

		if(send_obj)
		{
			//intercept the event in caputuring phase
			//intercept the parent node of the div, because when user clicks the parent node, the message is send out too.
			//send_obj.parentNode
			send_obj.get(0).addEventListener('mousedown' , on_mousedown,true);
			//$(document).on("click", send_obj, on_mousedown);
			//console.log("** send_obj.addEventListener('mousedown' , on_mousedown,true)***"  );
		}
	}
}

function unhook_Send_box()
{
	if( new_message_editor_group.sendbox)
	{
		var send_obj = new_message_editor_group.sendbox;

		if(send_obj)
		{
			//intercept the event in caputuring phase
			//intercept the parent node of the div, because when user clicks the parent node, the message is send out too.
			//send_obj.parentNode
			send_obj.get(0).removeEventListener('mousedown' , on_mousedown, true);
			//$(document).off("click", send_obj, on_mousedown);
			console.log("** send_obj.removeEventListener('mousedown' , on_mousedown,true)***"  );
		}
	}
}

function find_Editor_group_test(a_id)
{
	//to do : plan to open a panel or  frame to tell the manager the page status with QUint
}

function clean_Editor_group_test()
{
	//to do : plan to  tell the manager the page status in a panel or a frame  with QUint
}

self.port.on("getEditors", function(url_spec) {

	//"https://www.facebook.com/messages/"  "https://www.facebook.com/messages" , "https://www.facebook.com/messages/new , "https://www.facebook.com/messages/new/: not match
	//"https://www.facebook.com/messages/xxxxxx"  match
	var reg_URL = /^https:\/\/www.facebook.com\/messages\/new(\/?)/ ;
	var match = reg_URL.test( url_spec );
	if(match)
	{
		if(document.URL == url_spec)
		{
			//self.port.emit("getEditor", "url_spec == https://www.facebook.com/messages/new");
			//self.port.emit("getEditor", "document url:" + document.URL);
			//self.port.emit("getEditor", "window url:" + window.location.pathname);
			find_Editor_group();
			//self.port.emit("getEditor", "url_spec == https://www.facebook.com/messages/new");
		}
	}
	else
	{
		clean_Editor_group();
	}
	
	/*var log = " this == ";
	for(var b in this)
	{
		log += b;
		log += "\n";
	}


	alert( "this type " + log)*/
	
	/*var log = " self == ";
	for(var b in self)
	{
		log += b;
		log += "\n";
	}


	alert( "self type " + log)
	self property : port
	postMessage
	on
	once
	removeListener
	so it is a worker
	*/

    /*if ("onhashchange" in window) {
         self.port.emit("getEditor", "The browser supports the hashchange event!");
    }
 
    function locationHashChanged() {
    if (location.hash === "#somecoolfeature") {
        somecoolfeature();
        }
    }
     window.onhashchange = locationHashChanged;

	$(window).bind( 'popstate', 
        function(e) { 
            alert("ssss")
            self.port.emit("getEditor", e);
            }
        );
    
    $(document).bind( 'DOMContentLoaded', 
        function(e) { 
            alert("ssss")
            self.port.emit("getEditor", e);
            }
        );
  */
});



//li class="fbTimelineUnit lastCapsule fbTimelineTwoColumn clearfix fbTimelineComposerCapsule"
//-- div class="timelineUnitContainer fbTimelineComposerUnit"
//----div data-referrer="timeline_composer"
//------ ... div class="uiMentionsInput _11a"
// ------- ...  textarea class="uiTextareaAutogrow input autofocus mentionsTextarea textInput DOMControl_placeholder" name="xhpc_message_text"

/*

form rel="async" action="/ajax/updatestatus.php" method="post" onsubmit="return window.Event &amp;&amp; Event.__inlineSubmit &amp;&amp; Event.__inlineSubmit(this,event)" 
id="u_0_1g"><input type="hidden" name="fb_dtsg" value="AQAqKbtk" autocomplete="off">

*/


///for comment reply:
///textarea class="textInput mentionsTextarea uiTextareaAutogrow uiTextareaNoResize UFIAddCommentInput"  name="add_comment_text_text"