exports.attach = attach;
exports.detach = detach;
//exports.add_pafemod = add_pafemod;



var {Cc, Ci, Cm, Cr, Cu} = require("chrome");

const windowMediator = Cc['@mozilla.org/appshell/window-mediator;1'].getService(Ci.nsIWindowMediator);
let XPCOMUtils = Cu.import("resource://gre/modules/XPCOMUtils.jsm").XPCOMUtils;
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var addon_pref = require("sdk/simple-prefs");
var browserWindowListen = require("./browserWindowListener");

//pref :
//  "fn-facebook-pages-enable" bool

//local 
var page_mod_workers = [];
var facebook_pagemode = null;
//for facebook 
function add_pafemod()
{  
	if(!addon_pref.prefs["fn-facebook-pages-enable"])
	{
		return null;
	}
	
	if(facebook_pagemode)
	{
		return facebook_pagemode;
	}
		
	                                  
	let facebook_pagemode = new   pageMod.PageMod({
      include: "*.facebook.com",
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
			page_mod_workers.push(worker);
			worker.port.emit("getEditors", worker.url);
			log("^^^^^^^^^^^ worker onAttach page_mod_workers len = " + page_mod_workers.length + " >url:" + worker.url);
			
			worker.on('detach', function() {
				var index = page_mod_workers.indexOf(worker);
				//Then remove it with splice:
				page_mod_workers.splice(index, 1);

				log("^^^^^^^^^^^ worker detached  and removed from the array : page_mod_workers len = " + page_mod_workers.length  + " >url:" + worker.url);
			});//worker.on]

			  //worker.port.emit("getEditors", worker.url);
			  worker.port.on("getEditor", function(elementContent) {
			      log(" --- on getEditor" + elementContent);
			  });//worker.port.on
        }
		catch(ee)
		{
			log("onAttach : " + e);
		}
	  }
    });
  
    return facebook_pagemode;
	
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
}

function detach()
{
	browserWindowListen.detach();
}





function enable_facebook_pages( enable)//bool
{
	if(enable)
	{
		if(!facebook_pagemode)
		{
			add_pafemod(); 
		}
	}
	else
	{
		if(facebook_pagemode)
		{
			facebook_pagemode.destroy();
			facebook_pagemode = null;
			log("facebook_pagemode is destroied")
		}
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
addon_pref.on("fn-facebook-pages-enable", onAddon_PrefChange);


function log(msg)
{
	console.error(msg);
}
