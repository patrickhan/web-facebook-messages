
//exports
exports.attach = attach;
exports.detach = detach;

//include
var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var addon_pref = require("sdk/simple-prefs");

//const 
//pref :
const c_pref_fn_conversation_yahoo_enable = "fn-conversation-yahoo-enable";

//msgs
const c_msg_name_get_yahoo_composer = "get-yahoo-composer";// tell the page content js to start fn logic by starting scratching yahoo composer
const c_msg_name_status_yahoo_action = "status-yahoo-action";// tell the page content js to start/stop  fn logic by 'status'
const c_msg_val_status_yahoo_action_start = "start";
const c_msg_val_status_yahoo_action_stop = "stop";

const c_pagemode_include_expression = "*.mail.yahoo.com";//mail.yahoo.com  /http.*moz.*/

//local vars
var g_pagmode_yahoo = null;
var g_worker_pagmode_yahoo = null;

function add_pafemod()
{
	if(!get_settings_enable() )
	{
		return null;
	}
	if(g_pagmode_yahoo)
	{
		return g_pagmode_yahoo;
	}
	
	
	g_pagmode_yahoo = new   pageMod.PageMod(
	  {
	  include: c_pagemode_include_expression,
	  attachTo: ["existing", "top"],
	  contentStyleFile: [
			 //for test
			 //data.url("facebook/test-panel.css"),
			 //data.url("facebook/chat.css")
			// data.url("chat.css")
			 ],
	
	  contentScriptFile: [data.url("jquery2.js") ,
			  data.url("jquery_xpath.js") ,
			  //for test
			  //data.url("jquery.mobile-1.3.1.js") ,
			  //data.url("qunit-1.11.0.js") ,
			  //fn special common
			  data.url("fn/fncommon.js"),
			  data.url("fn/mock_test.js"),
			  data.url("fn/addReadersToDoc.js"),
			  //yahoo
			  data.url("yahoo/yahoo_page_parser.js"),
			  data.url("yahoo/yahoo_fn_logic.js")
			  ],
	  
	  onAttach: function(worker) {
			log(" in onAttach : " +  worker.url);
			try
			{
				g_worker_pagmode_yahoo = worker;
				worker.port.emit(c_msg_name_get_yahoo_composer, worker.url);
				
				worker.on('detach', function() {
			
					g_worker_pagmode_yahoo = null;
					log("^^^^^^^^^^^ worker detached   " +  worker.url);
				});//worker.on]
			
				  worker.port.on("getEditor===", function(elementContent) {
				      log(" --- on getEditor===" + elementContent);
				  });//worker.port.on
			}
			catch(ee)
			{
				log("onAttach : " + e);
			}
		  }//onAttach
	  }//pageMod
	  );
  return g_pagmode_yahoo;
}

function attach()
{
	add_pafemod();
}

function detach()
{
	if(g_pagmode_yahoo)
	{
		g_pagmode_yahoo.destroy();
		delete g_pagmode_yahoo;
	}
}


function enable_yahoo_conversation(  )//bool
{
	var enable = get_settings_enable();
	if(!!enable)
	{
		if(!g_pagmode_yahoo)
		{
			add_pafemod(); 
		}
		if(g_worker_pagmode_yahoo)
		{
			g_worker_pagmode_yahoo.port.emit(c_msg_name_status_yahoo_action, c_msg_val_status_yahoo_action_start);
		}
	}
	else
	{
		if(g_pagmode_yahoo)
		{
			if(g_worker_pagmode_yahoo)
			{
				g_worker_pagmode_yahoo.port.emit(c_msg_name_status_yahoo_action, c_msg_val_status_yahoo_action_stop);
			}
			
			g_pagmode_yahoo.destroy();
			g_pagmode_yahoo = null;
			log("pagmode_yahoo is destroied")
		}
	}
}
function get_settings_enable()
{
	return addon_pref.prefs[c_pref_fn_conversation_yahoo_enable];
}

///addon preference callback
function onAddon_PrefChange(prefName) {
   
	log("The " + prefName + " preference changed." + addon_pref.prefs[prefName])
    if(prefName === c_pref_fn_conversation_yahoo_enable)
    {
    	enable_yahoo_conversation(  );
    }
}
 
// `""` listens to all changes in the extension's branch
addon_pref.on(c_pref_fn_conversation_yahoo_enable, onAddon_PrefChange);

function log(msg)
{
	console.error(msg);
}


