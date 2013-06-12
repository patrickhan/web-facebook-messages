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
    aTriggerObserver.unregister();
    browserWindowListen.detach();
    console.error("exports.onUnload");
};

var page_mod_workers = [];
function add_pageMod()
{
    //pageMod 
    var pageMod = require("page-mod");
    pageMod.PageMod({
      include: "*.facebook.com",
      attachTo: ["existing", "top"],
      contentStyleFile: [
			 //for test
			 data.url("/facebook/test-panel.css"),
			 //data.url("jquery.mobile-1.3.1.css"),
			 //data.url("qunit-1.11.0.css"),
			 ],
      contentScriptFile: [data.url("jquery2.js") ,
			  data.url("jquery_xpath.js") ,
			  //for test
			  //data.url("jquery.mobile-1.3.1.js") , // will ruin the page
			  //data.url("qunit-1.11.0.js") ,
			  //fn special
			  data.url("/fn/fncommon.js"),
			  data.url("/fn/mock_test.js"),
			  //facebook
			  data.url("/facebook/facebook-common.js"),
			  data.url("/facebook/message-new.js"),
			  data.url("/facebook/message-reply.js"),
			  data.url("/facebook/wallpage.js"),
			  ],
	  
      onAttach: function(worker) {
		page_mod_workers.push(worker);
		worker.port.emit("getEditors", worker.url);
		console.log("^^^^^^^^^^^ worker onAttach page_mod_workers len = " + page_mod_workers.length + " >url:" + worker.url);
		
		worker.on('detach', function() {
			var index = page_mod_workers.indexOf(worker);
			//Then remove it with splice:
			page_mod_workers.splice(index, 1);

		    console.log("^^^^^^^^^^^ worker detached  and removed from the array : page_mod_workers len = " + page_mod_workers.length + + " >url:" + worker.url);
		});//worker.on]

	      //worker.port.emit("getEditors", worker.url);
	      worker.port.on("getEditor", function(elementContent) {
		console.error(elementContent);
	      });//worker.port.on
        }
    });//pageMod.PageMod]
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