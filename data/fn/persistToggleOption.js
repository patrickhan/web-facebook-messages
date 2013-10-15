//logic: for persist the toggle options
//using web storage , window.localStorage   pref dom.storage.enabled must be true
;

"use strict";

var fn_web_common_persist_fn_toggle_option_ns  = (undefined === fn_web_common_persist_fn_toggle_option_ns) ? {}: fn_web_common_persist_fn_toggle_option_ns;
(function(ns) {
	
var  WEB_CMM = fn_web_common_ns;
	var _logic_enabled_flag =  false;
	var _persist_fn_toggle_option_name ="persist_fn_toggle_option";
	
	function start_logic(is_start)
	{
		_logic_enabled_flag =  is_start;
		WEB_CMM.log( "fn_web_common_persist_fn_toggle_option_ns : start_logic  _logic_enabled_flag is" +  _logic_enabled_flag  );
	}
	
	function persist(anEditor, data)
	{
		try{
		if(!_logic_enabled() )
		{
			return;
		}
		
		if(!anEditor)
		{
			return;
		}
		log( "fn_web_common_persist_fn_toggle_option_ns : persist : data:  " +data  );
	
		var persisted_value = get_persisted_value(anEditor,data );
		
		if(persisted_value)
		{
			set_fn_toogle_option(anEditor, persisted_value);
		}
		
		start_monitor_fn_toogle_options(anEditor, data);
		}
		catch(err)
		{
			log("persist exception: "+ err)
		}
		
	}
	function _logic_enabled()
	{
		return _logic_enabled_flag;
	}

	function on_editor_fn_toggle_options_modified_listener(anEditor,data)
	{ 
		try{
			log( 'on_editor_fn_toggle_options_modified_listener' );
			var val = $(anEditor).attr("fn-toggle-option");
			if(val && val.length > 0)
			{
				set_persisted_value(anEditor, val , data);
			}
		}catch(err)
		{
		}
	}
	function on_editor_fn_toggle_options_removed_listener(anEditor,data)
	{
		try{
			log( 'on_editor_fn_toggle_options_removed_listener' );
			remove_persisted_value(anEditor,data );
		}catch(err)
		{
		}
	}
	
	function start_monitor_fn_toogle_options(anEditor,data)
	{
		if(!_logic_enabled())
		{
			return;
		}	
		//in sand box, jqury has some problem to listen customized event using addEventListener instead
		anEditor.addEventListener("fn-toggle-option-changed", function(event){
				//sand box js code can not access parameter of customized event: //Error: Permission denied to access property 'xxxx'
					on_editor_fn_toggle_options_modified_listener(anEditor,data)
			},false);
		anEditor.addEventListener("fn-toggle-option-removed", function(event){
				//sand box js code can not access parameter of customized event: //Error: Permission denied to access property 'xxxx'
					on_editor_fn_toggle_options_removed_listener(anEditor,data)
			},false);
	}
	
	function stop_monitor_fn_toogle_options(anEditor)
	{
		//anEditor.removeEventListener("fn-toggle-option-changed", on_editor_fn_toggle_options_modified_listener,false);
		//anEditor.removeEventListener("fn-toggle-option-removed", on_editor_fn_toggle_options_removed_listener,false);
	}

	//////////////////remote store
	const c_msg_fn_toggle_options_persist_data_get = "fn-toggle-options-persist-data-get"; //  msg type
	const c_msg_fn_toggle_options_persist_data_get_callback = "fn-toggle-options-persist-data-get-callback"; //  msg type
	const c_msg_fn_toggle_options_persist_data_set = "fn-toggle-options-persist-data-set"; //  msg type
	const c_msg_fn_toggle_options_persist_data_remove = "fn-toggle-options-persist-data-remove"; //  msg type

	function get_persisted_value_remote(anEditor,data )//data: can be url_match_rule
	{
		if(!_logic_enabled())
		{
			return null;
		}
		var akey = _persist_fn_toggle_option_name+data;
		self.port.emit(c_msg_fn_toggle_options_persist_data_get, JSON.stringify({key:akey}) );
		
		self.port.on(c_msg_fn_toggle_options_persist_data_get_callback,  function(callback_data)
				{
					if(callback_data)
					{
						var callback_data_obj = JSON.parse(callback_data);//{key:_persist_fn_toggle_option_name+data,value:persist_val}
						log(" o n c_msg_fn_toggle_options_persist_data_get_callback" + callback_data );
						if(callback_data_obj.key === akey && callback_data_obj.value)
						{
							set_fn_toogle_option(anEditor, callback_data_obj.value);
						}
					}
				});
		return "can not get data here";
		
	}
	function set_persisted_value_remote(anEditor,persist_val,data )//data: can be url_match_rule
	{
		if(!_logic_enabled())
		{
			return;
		}
		self.port.emit(c_msg_fn_toggle_options_persist_data_set, JSON.stringify({key:_persist_fn_toggle_option_name+data, value:persist_val}) );
	}
	
	function remove_persisted_value_remote(anEditor,data )//data: can be url_match_rule
	{
		if(!_logic_enabled())
		{
			return;
		}
		self.port.emit(c_msg_fn_toggle_options_persist_data_remove, JSON.stringify({key:_persist_fn_toggle_option_name+data}));
	}
	//////////////////remote store]
	
	function get_persisted_value(anEditor,data )//data: can be url_match_rule
	{
		if(!_logic_enabled())
		{
			return null;
		}
		//window.localStorage can not persist in sandbox!!!
		//var val = window.localStorage.getItem(_persist_fn_toggle_option_name+data) ;
		//log( " get_persisted_value in :"  + data + " == key is:" + _persist_fn_toggle_option_name + ":val=" +  val);
		get_persisted_value_remote(anEditor,data );// data will be sent back in the callback message
		return null;
		
	}
	function set_persisted_value(anEditor,persist_val,data )//data: can be url_match_rule
	{
		if(!_logic_enabled())
		{
			return;
		}
		//window.localStorage can not persist in sandbox!!!
		//log( " set_persisted_value in :"  + data + " == key is:" + _persist_fn_toggle_option_name + ":val=" +  persist_val);
		//window.localStorage.setItem(_persist_fn_toggle_option_name+data, persist_val) ;
		set_persisted_value_remote(anEditor,persist_val,data );
	}
	
	function remove_persisted_value(anEditor,data )//data: can be url_match_rule
	{
		if(!_logic_enabled())
		{
			return;
		}
		//window.localStorage can not persist in sandbox!!!
		//log( " remove_persisted_value in :"  + data + " == key is:" + _persist_fn_toggle_option_name);
		//window.localStorage.removeItem(_persist_fn_toggle_option_name+data) ;
		remove_persisted_value_remote(anEditor,data );
	}
	
	function set_fn_toogle_option(anEditor, persisted_value)
	{
		log( " set_fn_toogle_option: persisted_value:"  + persisted_value );
		try{
			var option  = $(anEditor).attr("fn-toggle-option")
			if( !option  ||  option.length == 0)//set value only when the attr is empty
			{
				$(anEditor).attr("fn-toggle-option-persisted", persisted_value);//
				log( " set : fn-toggle-option-persisted:"  + persisted_value );
			}
		}
		catch(err){
			log( "set_fn_toogle_option : err :"  + err );
			}		
	}
	
	var c_msg_fn_toggle_options_persist = "fn-toggle-options-persist-msg"; //  msg type
	self.port.on(c_msg_fn_toggle_options_persist, function(is_start) {
		log( " on c_msg_fn_toggle_options_persist : is_start: "  + is_start );
		start_logic(is_start);
	});

	function log(msg)
	{
		WEB_CMM.log(msg);
	}
	//exports
	//ns.start_logic = start_logic;
	ns.persist = persist;

})(fn_web_common_persist_fn_toggle_option_ns);