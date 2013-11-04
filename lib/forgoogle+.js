
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
const c_pref_fn_conversation_enable = "fn-googleplus-enable";
//pagemod using 
const c_pagemode_include_expression = "https://plus.google.com/u/0/*";
//msgs
const c_msg_name_get_composer = "get-googleplus_share-composer";// tell the page content js to start fn logic by starting scratching composer
const c_msg_name_status_fnlogic_action = "status-fnlogic-action";// tell the page content js to start/stop  fn logic by 'status'


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
	aworker.port.emit(c_msg_name_get_composer, aworker.url);
}

function on_apage_attached(worker)// on page loaded
{
	try
	{
		addWorker(worker) ;
	
		//addlisteners
		persistToggleOption.start_listen_localStorage(worker);
		
		worker.on('detach', function() {
	
			removeWorker(worker) ;
		});//worker.on]
		
		start_persist_composer_toggle_options(worker);
		//start the page  fn logic
		start_parse_composer(worker);
	
	}
	catch(ee)
	{
		log("onAttach : " + ee);
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
	
	g_pagmode = new   pageMod.PageMod(
	  {
	  include: c_pagemode_include_expression,
	  attachTo: ["existing", "top"],
	  contentStyleFile: [
			 ],
	
	  contentScriptFile: [data.url("jquery/jquery2.js") ,
			  data.url("jquery/jquery_xpath.js") ,
			  //fn special common
			  data.url("fn/fncommon.js"),
			  data.url("fn/mock_test.js"),
			  data.url("fn/addReadersToDoc.js"),
			  data.url("fn/persistToggleOption.js"),			  
			  //gmail
			  data.url("googleplus/wall_page_parser.js"),
			  data.url("googleplus/fn_logic_wall.js")
			  ],
	  
	  onAttach: function(worker) {
		  on_apage_attached(worker);
	  	}//onAttach
			
	  }//pageMod
	  );
  return g_pagmode;
}

function attach()
{
	start_fn_logic();
}

function detach()
{
	stop_fn_logic();
}

function enable_action_in_page(aworker,  enabled)
{
	try{
		//send message to content js to start
	aworker.port.emit(c_msg_name_status_fnlogic_action, enabled );
	}
	catch(err){}
}

function start_fn_logic()
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

function stop_fn_logic()
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
	};
}
function enable_fn_logic( is_start )//bool
{
	 
	if(is_start)
	{
		start_fn_logic();
	}
	else
	{
		stop_fn_logic();
		
	}
}
function get_settings_enable()
{
	return addon_pref.prefs[c_pref_fn_conversation_enable];
}

///addon preference callback
function onAddon_PrefChange(prefName) {
    if(prefName === c_pref_fn_conversation_enable)
    {
    	enable_fn_logic( addon_pref.prefs[prefName] );
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
	persistToggleOption.on(c_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist);
	persistToggleOption.on(c_msg_fn_toggle_options_persist_data_get_callback, on_msg_fn_toggle_options_persist_data_get_callback);
}

function detach_persistToggleOption()
{
	persistToggleOption.off(c_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist);
	persistToggleOption.off(c_msg_fn_toggle_options_persist_data_get_callback, on_msg_fn_toggle_options_persist_data_get_callback);
}
///////// for fn_toggle_options_persist]

function log(msg)
{
	console.error(msg);
}


