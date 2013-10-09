
//exports
exports.attach = attach;
exports.detach = detach;

//include
var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var addon_pref = require("sdk/simple-prefs");
//var fnaddons_helper = = require("./fnaddon_com.js");
//const 
//pref :
const c_pref_fn_conversation_yahoo_enable = "fn-conversation-yahoo-enable";

//msgs
const c_msg_name_get_yahoo_composer = "get-yahoo-composer";// tell the page content js to start fn logic by starting scratching yahoo composer
const c_msg_name_status_yahoo_action = "status-yahoo-action";// tell the page content js to start/stop  fn logic by 'status'
const c_msg_val_status_yahoo_action_start = "start";
const c_msg_val_status_yahoo_action_stop = "stop";

const c_pagemode_include_expression = "*.mail.yahoo.com";//mail.yahoo.com  /http.*moz.*/
const c_save_Stream_topic_msg = "save-Stream-topic";
//local vars
var g_pagmode_yahoo = null;
////[manage the workers in pagemod
var page_mod_workers = [];
function addWorker(aworker)
{
	var index = page_mod_workers.indexOf(aworker);
	if(index == -1)
	{
		page_mod_workers.push(aworker)
	}
}
function removeWorker(aworker)
{
	var index = page_mod_workers.indexOf(aworker);
	if(index != -1)
	{
		page_mod_workers.splice(index, 1);
	}
}
////]

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
				addWorker(worker) ;
				worker.port.emit(c_msg_name_get_yahoo_composer, worker.url);
				
				worker.on('detach', function() {
			
					removeWorker(worker) ;
					log("^^^^^^^^^^^ worker detached   " +  worker.url);
				});//worker.on]
			
				  worker.port.on("getEditor===", function(elementContent) {
				      log(" --- on getEditor===" + elementContent);
				  });
				  worker.port.on(c_save_Stream_topic_msg, function(msg) {
				      
					  log(" --- on " + c_save_Stream_topic_msg + "=msg=" + msg 
						  + "--arguments is:"+ arguments + "--arguments len:"+arguments.length 
						  + "--arguments[1] should be htmlelemnt:"+arguments[1]);
				      //fnaddons_helper.save_Stream_topic(worker, msg );
				  });
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

function enable_yahoo_action_in_page(aworker,  enabled)
{
	try{
	aworker.port.emit(c_msg_name_status_yahoo_action, enabled?c_msg_val_status_yahoo_action_start:c_msg_val_status_yahoo_action_stop);
	}
	catch(err){}
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
		page_mod_workers.forEach( function(aworker, index, array)
			{
				enable_yahoo_action_in_page(aworker,  true)
		});
	}
	else
	{
		if(g_pagmode_yahoo)
		{
			page_mod_workers.forEach( function(aworker, index, array)
					{
					enable_yahoo_action_in_page(aworker,  false)
			});
			page_mod_workers =[];
			
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


