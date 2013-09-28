
//exports
exports.attach = attach;
exports.detach = detach;
//exports.add_pafemod = add_pafemod;

//include
var {Cc, Ci, Cm, Cr, Cu} = require("chrome");

//const windowMediator = Cc['@mozilla.org/appshell/window-mediator;1'].getService(Ci.nsIWindowMediator);
//let XPCOMUtils = Cu.import("resource://gre/modules/XPCOMUtils.jsm").XPCOMUtils;
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var addon_pref = require("sdk/simple-prefs");

//pref :
//  "fn-conversation-gmail-enable" bool
var pagmode_gmail = null;
var worker_pagmode_gmail = null;
function add_pafemod()
{
	if(!get_settings_enable() )
	{
		return null;
	}
	if(pagmode_gmail)
	{
		return pagmode_gmail;
	}
	
	
	pagmode_gmail = new   pageMod.PageMod(
	  {
	  include: "https://mail.google.com/*",
	  attachTo: ["existing", "top"],
	  contentStyleFile: [
			 //for test
			 data.url("facebook/test-panel.css"),
			 data.url("facebook/chat.css")
			// data.url("chat.css")
			 ],
	
	  contentScriptFile: [data.url("jquery2.js") ,
			  data.url("jquery_xpath.js") ,
			  //for test
			  //data.url("jquery.mobile-1.3.1.js") ,
			  //data.url("qunit-1.11.0.js") ,
			  //fn special
			  data.url("fn/fncommon.js"),
			  data.url("fn/mock_test.js"),
			  data.url("fn/addReadersToDoc.js"),
			  //facebook
			  data.url("gmail/gmail.js")
			  ],
	  
	  onAttach: function(worker) {
			log(" in onAttach : " +  worker.url);
			try
			{
				worker_pagmode_gmail = worker;
				worker.port.emit("get-gmail-composer", worker.url);
				
				worker.on('detach', function() {
			
					worker_pagmode_gmail = null;
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
  return pagmode_gmail;
}

function attach()
{
	add_pafemod();
}

function detach()
{
	if(pagmode_gmail)
	{
		pagmode_gmail.destroy();
		delete pagmode_gmail;
	}
}


function enable_gmail_conversation( enable)//bool
{
	if(enable)
	{
		if(!pagmode_gmail)
		{
			add_pafemod(); 
		}
		if(worker_pagmode_gmail)
		{
			worker_pagmode_gmail.port.emit("status-gmail-action", "start");
		}
	}
	else
	{
		if(pagmode_gmail)
		{
			if(worker_pagmode_gmail)
			{
				worker_pagmode_gmail.port.emit("status-gmail-action", "stop");
			}
			
			pagmode_gmail.destroy();
			pagmode_gmail = null;
			log("pagmode_gmail is destroied")
		}
	}
}
function get_settings_enable()
{
	return addon_pref.prefs["fn-conversation-gmail-enable"];
}

///addon preference callback
function onAddon_PrefChange(prefName) {
   
	log("The " + prefName + " preference changed." + addon_pref.prefs[prefName])
    if(prefName == "fn-conversation-gmail-enable")
    {
    	enable_gmail_conversation( addon_pref.prefs[prefName]);
    }
}
 
// `""` listens to all changes in the extension's branch
addon_pref.on("fn-conversation-gmail-enable", onAddon_PrefChange);

function log(msg)
{
	console.error(msg);
}


