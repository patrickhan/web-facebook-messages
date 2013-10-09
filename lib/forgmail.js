
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
const c_pref_fn_conversation_gmail_enable = "fn-conversation-gmail-enable";

//msgs
const c_msg_name_get_gmail_composer = "get-gmail-composer";// tell the page content js to start fn logic by starting scratching gmail composer
const c_msg_name_status_gmail_action = "status-gmail-action";// tell the page content js to start/stop  fn logic by 'status'
const c_msg_val_status_gmail_action_start = "start";
const c_msg_val_status_gmail_action_stop = "stop";

const c_pagemode_include_expression = "https://mail.google.com/*";

//local vars
var g_pagmode_gmail = null;
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
	if(g_pagmode_gmail)
	{
		return g_pagmode_gmail;
	}
	
	
	g_pagmode_gmail = new   pageMod.PageMod(
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
			  //gmail
			  data.url("gmail/gmail_page_parser.js"),
			  data.url("gmail/gmail_fn_logic.js")
			  ],
	  
	  onAttach: function(worker) {
			log(" in onAttach : " +  worker.url);
			try
			{
				addWorker(worker) ;
				worker.port.emit(c_msg_name_get_gmail_composer, worker.url);
				
				worker.on('detach', function() {
			
					removeWorker(worker) ;
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
  return g_pagmode_gmail;
}

function attach()
{
	add_pafemod();
}

function detach()
{
	if(g_pagmode_gmail)
	{
		g_pagmode_gmail.destroy();
		delete g_pagmode_gmail;
	}
}

function enable_gmail_action_in_page(aworker,  enabled)
{
	try{
	aworker.port.emit(c_msg_name_status_gmail_action, enabled?c_msg_val_status_gmail_action_start:c_msg_val_status_gmail_action_stop);
	}
	catch(err){}
}



function enable_gmail_conversation(  )//bool
{
	var enable = get_settings_enable();
	if(!!enable)
	{
		if(!g_pagmode_gmail)
		{
			add_pafemod(); 
		}
		page_mod_workers.forEach( function(aworker, index, array)
			{
				enable_gmail_action_in_page(aworker,  true)
			});
		
	}
	else
	{
		if(g_pagmode_gmail)
		{
			page_mod_workers.forEach( function(aworker, index, array)
			{
				enable_gmail_action_in_page(aworker,  false)
			});
			page_mod_workers = [];
			g_pagmode_gmail.destroy();
			g_pagmode_gmail = null;
			log("pagmode_gmail is destroied")
		}
	}
}
function get_settings_enable()
{
	return addon_pref.prefs[c_pref_fn_conversation_gmail_enable];
}

///addon preference callback
function onAddon_PrefChange(prefName) {
   
	log("The " + prefName + " preference changed." + addon_pref.prefs[prefName])
    if(prefName === c_pref_fn_conversation_gmail_enable)
    {
    	enable_gmail_conversation(  );
    }
}
 
// `""` listens to all changes in the extension's branch
addon_pref.on(c_pref_fn_conversation_gmail_enable, onAddon_PrefChange);

function log(msg)
{
	console.error(msg);
}


