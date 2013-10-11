
//include
//var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
//var data = require("sdk/self").data;
//var pageMod = require("sdk/page-mod");
var { on, once, off, emit } = require('sdk/event/core');
var addon_pref = require("sdk/simple-prefs");
var sStorage = require("sdk/simple-storage");
//exports
exports.attach = attach;
exports.detach = detach;
exports.fn_toggle_options_persist_data_get = fn_toggle_options_persist_data_get;
exports.fn_toggle_options_persist_data_set = fn_toggle_options_persist_data_set;
exports.fn_toggle_options_persist_data_remove = fn_toggle_options_persist_data_remove;

exports.get_settings_enable = get_settings_enable;
exports.on = on.bind(null, exports);
//exports.once = once.bind(null, exports);
//exports.removeListener = function removeListener(type, listener) {
//  off(exports, type, listener);

//}
//const 
const c_pref_fn_toggle_options_persist = "fn-toggle-options-persist"; // pref , boolean

const c_msg_fn_toggle_options_persist = "fn-toggle-options-persist-msg"; //  msg type
const c_msg_fn_toggle_options_persist_data_get_callback = "fn-toggle-options-persist-data-get-callback"; //  msg type

function attach()
{
	fn_toggle_options_persist_start();
}

function detach()
{
	//fn_toggle_options_persist_stop();
}

function fn_toggle_options_persist_start()
{
	try
	{
		var enable = get_settings_enable();
		log(" fn_toggle_options_persist_start run: emit(exports,enable)."  );
		emit(exports,c_msg_fn_toggle_options_persist, enable)
	}
	catch(err)
	{
		log(" fn_toggle_options_persist_start exception." +  err );
	}
	
	
}


/*function notify_pageMode_workers(pageMode_workers , data)
{
	emit(null,c_pref_fn_toggle_options_persist_msg_start, c_pref_fn_toggle_options_persist_msg_stop)
}
*/
if (!sStorage.storage.fn_toggle_option)
  sStorage.storage.fn_toggle_option = {};
	
function fn_toggle_options_persist_data_get(data)
{
	try{
		var data_obj = JSON.parse(data);//{key:_persist_fn_toggle_option_name+data}
		var val = sStorage.storage.fn_toggle_option[data_obj.key]; 
		log("fn_toggle_options_persist_data_get" + data  + "\nresult=" + val);
		if(val && val.length > 0)
		{
			data_obj["value"] = val
			emit(exports,c_msg_fn_toggle_options_persist_data_get_callback, JSON.stringify(data_obj));
		}
	}	
	catch(err)
	{
		log("fn_toggle_options_persist_data_get err:" + err);
	}
	
}

function fn_toggle_options_persist_data_set(data)
{
	try{
		var data_obj = JSON.parse(data);//{key:_persist_fn_toggle_option_name+data, value:persist_val}
	
	log("fn_toggle_options_persist_data_set" + data );
	sStorage.storage.fn_toggle_option[data_obj.key ] = data_obj.value;
	log("fn_toggle_options_persist_data_set then get:" + sStorage.storage.fn_toggle_option[data_obj.key ] );
	}
	catch(err)
	{
		log("fn_toggle_options_persist_data_set err:" + err);
	}
}

function fn_toggle_options_persist_data_remove(data)
{
	try{	var data_obj = JSON.parse(data);//{key:_persist_fn_toggle_option_name+data}
	log("fn_toggle_options_persist_data_set" + data );	
	delete sStorage.storage.fn_toggle_option[data_obj.key ];
	log("fn_toggle_options_persist_data_remove then get:" + sStorage.storage.fn_toggle_option[data_obj.key ] );
	}
	catch(err)
	{
		log("fn_toggle_options_persist_data_remove err:" + err);
	}
}


//monite the preference

function get_settings_enable()
{
	return addon_pref.prefs[c_pref_fn_toggle_options_persist];
}

///addon preference callback
function onAddon_PrefChange(prefName) {
   
	log("The " + prefName + " preference changed." + addon_pref.prefs[prefName])
    if(prefName === c_pref_fn_toggle_options_persist)
    {
    	fn_toggle_options_persist_start(  );
    }
}
 
// `""` listens to all changes in the extension's branch
addon_pref.on(c_pref_fn_toggle_options_persist, onAddon_PrefChange);

function log(msg)
{
	console.error(msg);
}
