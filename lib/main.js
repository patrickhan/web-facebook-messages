// This is an active module of the facebook message Add-on


/*
 * Adds a page modification for Facebook
 * Copyright (c) 2013
 */


var { Class } = require("api-utils/heritage"); //sdk v1.10
//var { Class } = require('sdk/core/heritage');//sdk v1.14

var { Unknown } = require('api-utils/xpcom');//sdk v1.10
//var { Unknown } = require('sdk/platform/xpcom');//sdk v1.14

var data = require("self").data;
var { Cc, Ci } = require('chrome')
var observerService = Cc["@mozilla.org/observer-service;1"].
                        getService(Ci.nsIObserverService);
                        
var TriggerObserver = Class({
  extends:  Unknown,
  interfaces: [ 'nsIObserver' ],
  topic: 'EndDocumentLoad',  // "EndDocumentLoad" is only in firefox 12
  //ref : 'browser:purge-session-history',  in firefox 21 
  //'http-on-examine-response' EndDocumentLoad
  
  register: function () {
    observerService.addObserver(this, this.topic, false);
  },
  unregister: function() {
    observerService.removeObserver(this, this.topic, false);
  },
  
  observe: function(subject, topic, data)
  {
	//for test
     console.error('observe - EndDocumentLoad - mesg: ', subject, topic, data); 
  }
});



var aTriggerObserver = TriggerObserver();


const PROJECT_NAME_PREFIX = "FBM";

var browserWindowListen = require("./browserWindowListener");



exports.main = function() {

	console.error("exports.main");
	//onstart logic
	aTriggerObserver.register();
	browserWindowListen.attach(callback_in);
	add_pageMod();
};


exports.onUnload = function (reason) 
{
    //stop logic
	aTriggerObserver.unregister();
	browserWindowListen.detach();
	
    console.error("exports.onUnload");
};


/*
////////////////////
//Page location change
var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
let XPCOMUtils = Cu.import("resource://gre/modules/XPCOMUtils.jsm").XPCOMUtils;
//Cu.import("resource://gre/modules/XPCOMUtils.jsm");

const STATE_START = Ci.nsIWebProgressListener.STATE_START;
const STATE_STOP = Ci.nsIWebProgressListener.STATE_STOP;
var myListener = {
    QueryInterface: XPCOMUtils.generateQI(["nsIWebProgressListener",
                                           "nsISupportsWeakReference"]),

    onLocationChange: function(aProgress, aRequest, aURI) {
        // This fires when the location bar changes; that is load event is confirmed
        // or when the user switches tabs. If you use myListener for more than one tab/window,
        // use aProgress.DOMWindow to obtain the tab/window which triggered the change.
        
       //do something
       console.log("---" + aURI.spec);

    },
 
    // For definitions of the remaining functions see related documentation
    onStateChange: function(aWebProgress, aRequest, aFlag, aStatus) { },
    onProgressChange: function(aWebProgress, aRequest, curSelf, maxSelf, curTot, maxTot) {},
    onStatusChange: function(aWebProgress, aRequest, aStatus, aMessage) {},
    onSecurityChange: function(aWebProgress, aRequest, aState) {}
}

function add_listener()
{
	const windowMediator = Cc['@mozilla.org/appshell/window-mediator;1'].getService(Ci.nsIWindowMediator);
	var enumerator = windowMediator.getEnumerator("navigator:browser");
	while(enumerator.hasMoreElements()) {
		var window = enumerator.getNext();
		var gBrowser = window.gBrowser;
		gBrowser.addProgressListener(myListener);
	}
}

// exports.onUnload is called when Firefox starts and when the extension is disabled or uninstalled
function remove_listener() {
    //reason is a string : uninstall, disable, shutdown, upgrade, downgrade
            
    const windowMediator = Cc['@mozilla.org/appshell/window-mediator;1'].getService(Ci.nsIWindowMediator);
    var enumerator = windowMediator.getEnumerator("navigator:browser");
    while(enumerator.hasMoreElements()) {
        var window = enumerator.getNext();
        var gBrowser = window.gBrowser;
        gBrowser.removeProgressListener(myListener);
    }
};

*/

var page_mod_workers = [];
function add_pageMod()
{
	//pageMod 
	var pageMod = require("page-mod");
    pageMod.PageMod({
      //include: "https://www.facebook.com/messages/new",
      include: "*.facebook.com",
	  attachTo: ["existing", "top"],
      contentScriptFile: [data.url("jquery2.js") , data.url("jquery_xpath.js") , data.url("findeditors.js"),  data.url("message.js")],
	  
	  onAttach: function(worker) {
		page_mod_workers.push(worker);
		
		worker.port.emit("getEditors", worker.url);
		
		console.log("^^^^^^^^^^^ worker onAttach page_mod_workers len = " + page_mod_workers.length + " >url:" + worker.url);
		
		worker.on('detach', function() {

			var index = page_mod_workers.indexOf(worker);
			//Then remove it with splice:
			page_mod_workers.splice(index, 1);

            console.log("^^^^^^^^^^^ worker detached  and removed from the array : page_mod_workers len = " + page_mod_workers.length + + " >url:" + worker.url);
        });

		

        //worker.port.emit("getEditors", worker.url);
        worker.port.on("getEditor", function(elementContent) {
          console.error(elementContent);
        });
      }
      
    });

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
	
	  //var windows = require("windows").browserWindows;
	/*
	let utils = require('api-utils/window/utils');
	let active = utils.activeBrowserWindow;

	//active instanceof Ci.nsIXULWindow // => false
	let  aIXULWindow  = utils.getXULWindow(active);// instanceof Ci.nsIXULWindow // => true

	console.log("^^^^^^^^^^^ aIXULWindow.gBrowser  " + aIXULWindow.gBrowser);
	console.log("^^^^^^^^^^^ aIXULWindow.gBrowser.selectedTab  " + aIXULWindow.gBrowser.selectedTab);

	  */

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