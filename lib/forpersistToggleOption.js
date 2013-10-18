
//include
//var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
//var data = require("sdk/self").data;
//var pageMod = require("sdk/page-mod");
var { on, once, off, emit } = require('sdk/event/core');
var addon_pref = require("sdk/simple-prefs");
var sStorage = require("sdk/simple-storage");
var pageMod = require("sdk/page-mod");//for worker define
//exports
exports.attach = attach;
exports.detach = detach;
exports.fn_toggle_options_persist_data_get = fn_toggle_options_persist_data_get;
exports.fn_toggle_options_persist_data_set = fn_toggle_options_persist_data_set;
exports.fn_toggle_options_persist_data_remove = fn_toggle_options_persist_data_remove;
exports.start_listen_localStorage = start_listen_localStorage;
exports.notify_page_fn_toggle_options_persist_data_get_callback = notify_page_fn_toggle_options_persist_data_get_callback;
exports.notify_page_start_persist_composer_toggle_options =  notify_page_start_persist_composer_toggle_options;
//exports.add_fn_toggle_options_persist_messages_listeners  = add_fn_toggle_options_persist_messages_listeners;
//exports.remove_fn_toggle_options_persist_messages_listeners = remove_fn_toggle_options_persist_messages_listeners;

exports.get_settings_enable = get_settings_enable;
exports.on = on.bind(null, exports); // for event 
exports.off = off.bind(null, exports); // for event 
//exports.once = once.bind(null, exports);
//exports.removeListener = function removeListener(type, listener) {
//  off(exports, type, listener);

exports.c_pref_fn_toggle_options_persist = c_pref_fn_toggle_options_persist;
exports.c_msg_fn_toggle_options_persist = c_msg_fn_toggle_options_persist;
exports.c_msg_fn_toggle_options_persist_data_get_callback = c_msg_fn_toggle_options_persist_data_get_callback
//}
//const 
const c_pref_fn_toggle_options_persist = "fn-toggle-options-persist"; // pref , boolean
const c_msg_fn_toggle_options_persist = "fn-toggle-options-persist-msg"; //  msg type
const c_msg_fn_toggle_options_persist_data_get_callback = "fn-toggle-options-persist-data-get-callback"; //  msg type
const c_msg_fn_toggle_options_persist_data_get = "fn-toggle-options-persist-data-get"; //  msg type 
const c_msg_fn_toggle_options_persist_data_set = "fn-toggle-options-persist-data-set"; //  msg type
const c_msg_fn_toggle_options_persist_data_remove = "fn-toggle-options-persist-data-remove"; //  msg type

function attach()//called when the addons is enabled
{
	fn_toggle_options_persist_start();
}

function detach()//called when the addons is disabled
{
	fn_toggle_options_persist_stop();
}

function fn_toggle_options_persist_start()//called when the addons is enabled
{
	try
	{
		var enable = get_settings_enable();
		log(" fn_toggle_options_persist_start run: emit(exports,enable)."  );
		emit(exports,c_msg_fn_toggle_options_persist, enable);//tell gmail magemod objects to start the 'fn toggle options persist' logic
	}
	catch(err)
	{
		log(" fn_toggle_options_persist_start exception." +  err );
	}
	
	
}
function fn_toggle_options_persist_stop()//called when the addons is disabled
{
	//todo: if something needs to clean.
}



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


//message page=pagemod
function start_listen_localStorage(aworker)
{
	aworker.port.on(c_msg_fn_toggle_options_persist_data_set, function(data){
		log(c_msg_fn_toggle_options_persist_data_set + " : " + data);
			try{
				fn_toggle_options_persist_data_set(data);
			}
			catch(err){
				log("fn_toggle_options_persist_data_set : err" + err)
				}
		} );
	
	aworker.port.on(c_msg_fn_toggle_options_persist_data_get, function(data){
		log(c_msg_fn_toggle_options_persist_data_get + " : " + data);
			try{
				fn_toggle_options_persist_data_get(data);
			}
			catch(err){
				log("fn_toggle_options_persist_data_get : err" + err)
				}
		} ); 
	
	aworker.port.on(c_msg_fn_toggle_options_persist_data_remove, function(data){
		log(c_msg_fn_toggle_options_persist_data_remove + " : " + data);
			try{
				fn_toggle_options_persist_data_remove(data);
			}
			catch(err)
			{
				log("fn_toggle_options_persist_data_remove : err" + err)
				}
		} );  
}

function notify_page_fn_toggle_options_persist_data_get_callback(aworker, data)	
{
	aworker.port.emit(c_msg_fn_toggle_options_persist_data_get_callback, data);
}
function notify_page_start_persist_composer_toggle_options(aworker, is_start)
{
	log("aworker.port.emit(c_msg_fn_toggle_options_persist : " + is_start);
	aworker.port.emit(c_msg_fn_toggle_options_persist, is_start);
}

/*function add_fn_toggle_options_persist_messages_listeners(on_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist_data_get_callback )
{
	on(c_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist);
	on(c_msg_fn_toggle_options_persist_data_get_callback, on_msg_fn_toggle_options_persist_data_get_callback);
}


function remove_fn_toggle_options_persist_messages_listeners(on_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist_data_get_callback )
{
	off(c_msg_fn_toggle_options_persist, on_msg_fn_toggle_options_persist);
	off(c_msg_fn_toggle_options_persist_data_get_callback, on_msg_fn_toggle_options_persist_data_get_callback);
}*/
	
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
