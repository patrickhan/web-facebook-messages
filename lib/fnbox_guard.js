
/* In this js file, we do the following thing(s) for fn box in html page:
 * 1 If there is a css tranform is set for any fn box's parent element, 
 * the window based fn box will not be shown, 
 * so this file will remove the 'css tranform' in any fn box's parent element. 
 * Think about the js in iframe it can not access the parent elements of iframe ,
 * we are going to add listener for any dom window.
 * refer :fnboxhelper.js
 */
	
 

exports.attach = attach;
exports.detach = detach;

var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var addon_pref = require("sdk/simple-prefs");

//pref :
var pref_fn_box_page_guard_enable = "fn-box-page-guard-enable" ; // bool
//messages
var msg_fn_box_help_to_addons =  "fn-box-help-to-addons";
var msg_fn_box_help_to_content =  "fn-box-help-to-content";

//local 
var g_pagmode = null;
var page_mod_workers = [];

function addWorker(aworker)
{
	var index = page_mod_workers.indexOf(aworker);
	/*if(index == -1)
	{
		page_mod_workers.push(aworker);
	};*/
	(index == -1) && (page_mod_workers.push(aworker) );
}

function removeWorker(aworker)
{
	var index = page_mod_workers.indexOf(aworker);
	/*if(index != -1)
	{
		page_mod_workers.splice(index, 1);
	}*/
	(index != -1) && (page_mod_workers.splice(index, 1));
}
function  addWorkerListeners(aworker)
{
	
	try
	{
		addWorker(aworker);
		
		aworker.on('detach', function() {
			removeWorker(aworker);
		}); 
	
		aworker.port.on(msg_fn_box_help_to_addons,  on_msg_fn_box_help_to_addons.bind(aworker));
	}
	catch(e)
	{
		log("addWorkerListeners : " + e);
	}
		
}
function find_iframe_byworkers(aworker, worker_parent)
{
	var awindow  = aworker.host_window;
	var awindow_parent = worker_parent.host_window;
	var the_iframe = null;
	var iframes = awindow_parent.document.getElementsByTagName('IFRAME');
	for(var i = 0; i < iframes.length; i++)
	{// using iframe.src is not a good idea, becuase the sub-window may do redirection.
		var afrm1 = iframes[i];
		if(afrm1.contentWindow == awindow)
		{
			log(" found iframe from contentWindow: " +  afrm1.contentWindow); 
			the_iframe = afrm1;
			break;
		}
	}
	return the_iframe;
}

function find_worker_parent(aworker)
{
	try
	{
		var awindow  = aworker.host_window;
		var awindow_parent = awindow.parent;
		if(!awindow)
		{
			return null;
		}
		if(awindow_parent == awindow)
		{
			return null;
		}
		var index = page_mod_workers.indexOf(aworker);
		if(index == -1)
		{
			return;
		}
		var out_worker = null;
		page_mod_workers.some( function(element, index, array) {
			var the_worker = element;
			if(the_worker.host_window == awindow_parent)
			{
				out_worker = the_worker;
				return true;// break the loop;
			}
			return false;
		});
		return out_worker;
	}
	catch(e)
	{
		log("find_worker_parent : error : " + e);
	}
	return null;
}

function notify_iframe_fn_box_help(the_iframe)
{//invoke the event to let the page know where to start from
	var event = the_iframe.ownerDocument.createEvent("HTMLEvents");
	event.initEvent(msg_fn_box_help_to_content, true, false);
	the_iframe.dispatchEvent(event);
}

function on_msg_fn_box_help_to_addons(obj1)
{// aworker is binded as ''this' 
	var aworker = this;
	try
	{
		
		var worker_parent = find_worker_parent(aworker);
		if(worker_parent)
		{
			var the_iframe = find_iframe_byworkers(aworker, worker_parent);
			if(the_iframe)
			{
				notify_iframe_fn_box_help(the_iframe);
			}
			worker_parent.port.emit( msg_fn_box_help_to_content, the_iframe);
		}
		
	}
	catch(e)
	{
		log("on_msg_fn_box_help_to_addons : err:"+e );
	}
}


function add_pafemod()
{  
	if(!get_settings_enable() )
	{
		return null;
	}
	
	if(g_pagmode)
	{
		return g_pagmode;
	}
		
	                                  
	g_pagmode = new   pageMod.PageMod({
      include: "*",
      attachTo: ["existing", "top","frame"],
      contentStyleFile: [
			 //for test
			 ],

      contentScriptFile: [
			  data.url("fn/fnboxhelper.js"),
			  ],
	  contentScriptWhen: "start",
      onAttach: function(worker) {
			addWorkerListeners(worker);
	  }
    });
  
    return g_pagmode;
	
}

function start_pages_logic(   ) 
{
	 
	if(!g_pagmode)
	{
		add_pafemod(); 
	}
	/*page_mod_workers.forEach( function(aworker, index, array)
		{
			enable_action_in_page(aworker,  true)
		});
		*/
}
function stop_pages_logic() 
{
	 
	//todo: detach_persistToggleOption();
	if(g_pagmode)
	{
		/*page_mod_workers.forEach( function(aworker, index, array)
		{
			enable_action_in_page(aworker,  false)
		});
		
		page_mod_workers = [];
		*/
		g_pagmode.destroy();
		g_pagmode = null;
	}
}


function attach()
{
	add_pafemod();
	if(g_pagmode)
	{
		//todo :attach_persistToggleOption();
	}
}

function detach()
{
	stop_pages_logic();
}

function get_settings_enable()
{
	return addon_pref.prefs[pref_fn_box_page_guard_enable];
}

function enable_fnbox_gaurd( enable)//bool
{
	if(enable)
	{
		start_pages_logic();
	}
	else
	{
		stop_pages_logic();
	}
}

///addon preference callback
function onAddon_PrefChange(prefName) {
    if(prefName == pref_fn_box_page_guard_enable)
    {
    	enable_fnbox_gaurd( addon_pref.prefs[prefName]);
    }
}
 
// `""` listens to all changes in the extension's branch
addon_pref.on( pref_fn_box_page_guard_enable,  onAddon_PrefChange);


function log(msg)
{
	console.error(msg);
}
