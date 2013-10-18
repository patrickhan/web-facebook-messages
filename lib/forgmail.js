
//exports
exports.attach = attach;
exports.detach = detach;

//include
var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var addon_pref = require("sdk/simple-prefs");

var persistToggleOption = require("./forpersistToggleOption.js");

//const 
//pref :
const c_pref_fn_conversation_enable = "fn-conversation-gmail-enable";
//pagemod using 
const c_pagemode_include_expression = "https://mail.google.com/*";
//msgs
const c_msg_name_get_gmail_composer = "get-gmail-composer";// tell the page content js to start fn logic by starting scratching gmail composer
const c_msg_name_status_gmail_action = "status-gmail-action";// tell the page content js to start/stop  fn logic by 'status'


//messages beteewn work and this
//const c_msg_fn_toggle_options_persist_data_get = "fn-toggle-options-persist-data-get"; //  msg type 
//const c_msg_fn_toggle_options_persist_data_set = "fn-toggle-options-persist-data-set"; //  msg type
//const c_msg_fn_toggle_options_persist_data_remove = "fn-toggle-options-persist-data-remove"; //  msg type


//local vars
var g_pagmode = null;
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

//logics
function start_parse_composer(aworker)
{
	aworker.port.emit(c_msg_name_get_gmail_composer, aworker.url);
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
	
	
	g_pagmode = new   pageMod.PageMod(
	  {
	  include: c_pagemode_include_expression,
	  attachTo: ["existing", "top"],
	  contentStyleFile: [
			 ],
	
	  contentScriptFile: [data.url("jquery2.js") ,
			  data.url("jquery_xpath.js") ,
			  //fn special common
			  data.url("fn/fncommon.js"),
			  data.url("fn/mock_test.js"),
			  data.url("fn/addReadersToDoc.js"),
			  data.url("fn/persistToggleOption.js"),			  
			  //gmail
			  data.url("gmail/gmail_page_parser.js"),
			  data.url("gmail/gmail_fn_logic.js")
			  ],
	  
	  onAttach: function(worker) {
			log(" in onAttach : " +  worker.url);
			try
			{
				addWorker(worker) ;

				start_persist_composer_toggle_options(worker);
				start_parse_composer(worker);
				persistToggleOption.start_listen_localStorage(worker);
				
				worker.on('detach', function() {
			
					removeWorker(worker) ;
					log("^^^^^^^^^^^ worker detached   " +  worker.url);
				});//worker.on]
			
			}
			catch(ee)
			{
				log("onAttach : " + ee);
			}
		  }//onAttach
	  }//pageMod
	  );
  return g_pagmode;
}

function attach()
{
	add_pafemod();
	if(g_pagmode)
	{
		attach_persistToggleOption();
	}
}

function detach()
{
	 stop_conversation_logic();
}

function enable_action_in_page(aworker,  enabled)
{
	try{
		//send message to content js to start
	aworker.port.emit(c_msg_name_status_gmail_action, enabled );
	}
	catch(err){}
}

function start_conversation_logic()
{
	if(!g_pagmode)
	{
		add_pafemod(); 
	}
	page_mod_workers.forEach( function(aworker, index, array)
		{
			enable_action_in_page(aworker,  true)
		});
	attach_persistToggleOption();
}

function stop_conversation_logic()
{
	detach_persistToggleOption();
	if(g_pagmode)
	{
		page_mod_workers.forEach( function(aworker, index, array)
		{
			enable_action_in_page(aworker,  false)
		});
		page_mod_workers = [];
		g_pagmode.destroy();
		g_pagmode = null;
		log("pagmode_gmail is destroied")
	};
}
function enable_conversation( is_start )//bool
{
	 
	if(is_start)
	{
		start_conversation_logic()
		
	}
	else
	{
		stop_conversation_logic();
		
	}
}
function get_settings_enable()
{
	return addon_pref.prefs[c_pref_fn_conversation_enable];
}

///addon preference callback
function onAddon_PrefChange(prefName) {
   
	log("The " + prefName + " preference changed." + addon_pref.prefs[prefName])
    if(prefName === c_pref_fn_conversation_enable)
    {
    	enable_conversation( addon_pref.prefs[prefName] );
    }
}
 
// `""` listens to all changes in the extension's branch
addon_pref.on(c_pref_fn_conversation_enable, onAddon_PrefChange);


///////// for fn_toggle_options_persist[
function start_persist_composer_toggle_options(aworker) 
{
	var is_start = persistToggleOption.get_settings_enable();
	persistToggleOption.notify_page_start_persist_composer_toggle_options(aworker, is_start);
}
function on_msg_fn_toggle_options_persist(is_start)
{
	log("on_msg_fn_toggle_options_persist . gmail:" + is_start )
	var enable = get_settings_enable();
	if(!!enable)
	{
		if(g_pagmode)
		{
			page_mod_workers.forEach( function(aworker, index, array)
			{
				persistToggleOption.notify_page_start_persist_composer_toggle_options(aworker, is_start);
			});

		}
	}	
}
 

function on_msg_fn_toggle_options_persist_data_get_callback(data)
{
	log("on_msg_fn_toggle_options_persist_data_get_callback . gmail:" + data )
	var enable = get_settings_enable();
	if(!!enable)
	{
		if(g_pagmode)
		{
			page_mod_workers.forEach( function(aworker, index, array)
			{
				
				persistToggleOption.notify_page_fn_toggle_options_persist_data_get_callback(aworker, data)
			});

		}
	}
}

const c_msg_fn_toggle_options_persist = "fn-toggle-options-persist-msg"; //  msg type
const c_msg_fn_toggle_options_persist_data_get_callback = "fn-toggle-options-persist-data-get-callback"; //  msg type
function attach_persistToggleOption()
{
	//persistToggleOption.add_fn_toggle_options_persist_messages_listeners(on_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist_data_get_callback );
	persistToggleOption.on(c_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist);
	persistToggleOption.on(c_msg_fn_toggle_options_persist_data_get_callback, on_msg_fn_toggle_options_persist_data_get_callback);
}

function detach_persistToggleOption()
{
	//persistToggleOption.remove_fn_toggle_options_persist_messages_listeners(on_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist_data_get_callback );
	persistToggleOption.off(c_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist);
	persistToggleOption.off(c_msg_fn_toggle_options_persist_data_get_callback, on_msg_fn_toggle_options_persist_data_get_callback);
}
///////// for fn_toggle_options_persist]

function log(msg)
{
	console.error(msg);
}


