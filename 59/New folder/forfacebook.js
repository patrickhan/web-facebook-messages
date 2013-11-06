exports.attach = attach;
exports.detach = detach;



var {Cc, Ci, Cm, Cr, Cu} = require("chrome");

const windowMediator = Cc['@mozilla.org/appshell/window-mediator;1'].getService(Ci.nsIWindowMediator);
let XPCOMUtils = Cu.import("resource://gre/modules/XPCOMUtils.jsm").XPCOMUtils;
let dataDBOper_Asyn_V2  = Cu.import("resource://webpagesvrmoudleLoader/webpgjs/dataOper.jsm").dataDBOper_Asyn_V2;
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var addon_pref = require("sdk/simple-prefs");
var browserWindowListen = require("./browserWindowListener.js");

const c_msg_name_facebook_prompt_import_contacts = "facebook_prompt_import_contacts";//to page content,  to prompt users to import the contact in facebook
const c_msg_name_facebook_after_fn_logic_excute = "facebook_after_fn_logic_excute";//from page content,  tell the addon, facebook_after_fn_logic_excute
const c_msg_name_status_facebook_action = "status-facebook-action";// tell the page content js to start/stop  fn logic by 'status'
const c_msg_name_getEditors_action = "getEditors";// tell the page content js to get Editors interested
const c_msg_name_get_recipient_for_reply_message_page = "get-recipient-for-reply-message-page";
const c_msg_name_get_recipient_for_reply_message_page_feedback = "get-recipient-for-reply-message-page-feedback";
//pref :
//  "fn-facebook-pages-enable" bool

//local 
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
function  addWorkerListeners(aworker)
{
	aworker.on('detach', function() {
		removeWorker(aworker);

		log("^^^^^^^^^^^ worker detached  and removed from the array : page_mod_workers len = " + page_mod_workers.length  + " >url:" + aworker.url);
	}); 

	aworker.port.on(c_msg_name_facebook_after_fn_logic_excute,  on_facebook_after_fn_logic_excute.bind(aworker));
	
	aworker.port.on(c_msg_name_get_recipient_for_reply_message_page, on_get_recipient_for_reply_message_page.bind(aworker));
}

function prompt_facebook_import_contacts(awroker)
{
	awroker.port.emit(c_msg_name_facebook_prompt_import_contacts, true);
	
	//show a panel		
	var panel = require("sdk/panel").Panel({
		  width: 180,
		  height: 180,
		contentURL: data.url("UI/importFacebookcContect.html"),
		});
	 
		panel.show();
}

function check_facebook_contacts_imported( callback_fun, callback_fun_param)
{
	var sqltemplate = "SELECT * FROM SecureKeyImHandleMap WHERE SecureKeyImHandleMap.imName=:imName";
	var selfworker = this;
	var params = [{imName:'facebookName'}]; 
	dataDBOper_Asyn_V2(sqltemplate,params ,
			 function(result){
				if(!result || result.length == 0)
		        {
		        	callback_fun(callback_fun_param);
		        }
			});	
}
var prompt_facebook_import_contacts_done_once =  false;
function on_facebook_after_fn_logic_excute()
{// aworker is binded as ''this' 
	//here we plan to prompt the user to do 'import' in fn contact ui

	//we query the table SecureKeyImHandleMap in fndata.db, if there is a row which has imName='facebookName' then
	//we can say the facebook contacts has been already imported once,
	//if there is not such a row , we are going to prompt user to do "Facebook Caontact imports"
	if(!prompt_facebook_import_contacts_done_once)
	{
		var selfworker = this;
		check_facebook_contacts_imported( prompt_facebook_import_contacts, selfworker);
		prompt_facebook_import_contacts_done_once =  true;
	}
}
//using Raymond's code to get recipient , refer data/facebook/message_reply.js 
function on_get_recipient_for_reply_message_page(data)//data : reserved to use it later
{
	// aworker is binded as ''this'
	try{
		var selfworker = this;
		var utils = require('sdk/window/utils');
		var active = utils.getMostRecentBrowserWindow();
		
		var awindow  = selfworker.host_window;
		
		var objName = "webMessageEmails"; 
		var node = awindow.document.getElementById("pagelet_web_messenger"); 
		var emailObj = active.FnGlobalObject.getObject(objName, node);
		emailObj = JSON.stringify(emailObj);
		log("on_get_recipient_for_reply_message_page : " + emailObj);
		selfworker.port.emit(c_msg_name_get_recipient_for_reply_message_page_feedback, emailObj);
	}
	catch(e)
	{
		log("on_get_recipient_for_reply_message_page :  error" + e);
	}
}
////]

//for facebook 
function add_pafemod()
{  
	if(!addon_pref.prefs["fn-facebook-pages-enable"])
	{
		return null;
	}
	
	if(g_pagmode)
	{
		return g_pagmode;
	}
		
	                                  
	g_pagmode = new   pageMod.PageMod({
      include: "*.facebook.com",
      attachTo: ["existing", "top"],
      contentStyleFile: [
			 //for test
			 data.url("facebook/test-panel.css"),
			 data.url("facebook/chat.css")
			// data.url("chat.css")
			 ],

      contentScriptFile: [data.url("jquery/jquery2.js") ,
			  data.url("jquery/jquery_xpath.js") ,
			  //fn special
			  data.url("fn/fncommon.js"),
			  data.url("fn/mock_test.js"),
			  data.url("fn/addReadersToDoc.js"),
			  data.url("fn/persistToggleOption.js"),  
			  //facebook
			  data.url("facebook/facebook-common.js"),
			  data.url("facebook/message-new.js"),
			  data.url("facebook/message-reply.js"),
			  data.url("facebook/wallpage.js"),
			  data.url("facebook/chat.js")
			  ],
	  
      onAttach: function(worker) {
		log(" in onAttach : " +  worker.url);
		try
		{
			addWorker(worker);
			start_parse_composer(worker);
			addWorkerListeners(worker);
        }
		catch(ee)
		{
			log("onAttach : " + e);
		}
	  }
    });
  
    return g_pagmode;
	
}


// if we use pageMod onAttach to trigger the 'getEditors' , then trigger it onactivate for tab is not neccessary 
var tabs = require("tabs");
tabs.on('activate', function(tab) {
 
    for( let i = 0; i < page_mod_workers.length; i++)
    {
	  let aworker = page_mod_workers[i];
	  if(aworker && aworker.tab == tab)
	  {
	    aworker.port.emit("getEditors", tab.url);
	    break;
	  }
    }
    console.log("^^^^^^^^^^^ tab on activate: tab url " + tab.url);

});


function callback_in( msg )
{
    let tabs = require('tabs');
    let activeTab = tabs.activeTab;
    if(activeTab.url != msg)
    {
	  return;
    }

    console.log("^^^^^^^^^^^ active tab url " + activeTab.url);

    for( let i = 0; i < page_mod_workers.length; i++)
    {
      let aworker = page_mod_workers[i];
      if(aworker && aworker.tab == activeTab)
      {
	     aworker.port.emit("getEditors", msg);
	     break;
      }
    }
    console.log("*****" + msg);
}


function attach()
{
	browserWindowListen.attach(callback_in);
	add_pafemod();
	if(g_pagmode)
	{
		//todo :attach_persistToggleOption();
	}
}

function detach()
{
	browserWindowListen.detach();
	stop_facebook_pages_logic();
}


//logics
function start_parse_composer(aworker)
{
	aworker.port.emit(c_msg_name_getEditors_action, aworker.url);
}

function enable_action_in_page(aworker,  enabled)
{
	try{
		//send message to content js to start
	aworker.port.emit(c_msg_name_status_facebook_action, enabled );
	}
	catch(err){}
}

function start_facebook_pages_logic(   ) 
{
	 
	if(!g_pagmode)
	{
		add_pafemod(); 
	}
	page_mod_workers.forEach( function(aworker, index, array)
		{
			enable_action_in_page(aworker,  true)
		});
	//to do: attach_persistToggleOption();
}
function stop_facebook_pages_logic(   ) 
{
	 
	//todo: detach_persistToggleOption();
	if(g_pagmode)
	{
		page_mod_workers.forEach( function(aworker, index, array)
		{
			enable_action_in_page(aworker,  false)
		});
		page_mod_workers = [];
		g_pagmode.destroy();
		g_pagmode = null;
	}
}


function enable_facebook_pages( enable)//bool
{
	if(enable)
	{
		start_facebook_pages_logic();
	}
	else
	{
		stop_facebook_pages_logic();
	}
}

///addon preference callback
function onAddon_PrefChange(prefName) {
   
	log("The " + prefName + " preference changed." + addon_pref.prefs[prefName])
    if(prefName == "fn-facebook-pages-enable")
    {
    	enable_facebook_pages( addon_pref.prefs[prefName]);
    }
}
 
// `""` listens to all changes in the extension's branch
addon_pref.on( "fn-facebook-pages-enable",  onAddon_PrefChange);


function log(msg)
{
	console.error(msg);
}
