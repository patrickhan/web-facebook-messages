// This is an active module of the facebook message Add-on
/*
 * Adds a page modification for Facebook
 * Copyright (c) 2013
 */


//var { Class } = require("api-utils/heritage"); //sdk v1.10
var { Class } = require('sdk/core/heritage');//sdk v1.14

//var { Unknown } = require('api-utils/xpcom');//sdk v1.10
var { Unknown } = require('sdk/platform/xpcom');//sdk v1.14

//var data = require("self").data;
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var tabs = require("sdk/tabs");

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
   
    //onstart logic
    aTriggerObserver.register();
    browserWindowListen.attach(callback_in);
    add_pageMod(); 
	console.error("exports.main ======");
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
    //var pageMod = require("page-mod");
	
    pageMod.PageMod({
      include: "*.facebook.com",
      attachTo: ["existing", "top"],
      contentStyleFile: [
			 //for test
			 data.url("facebook/test-panel.css"),
			 data.url("facebook/chat.css")
			// data.url("chat.css")
			 ],
	  /*contentStyle: [ 
".fn-facebook-chat{  top:-261px;  width:262px;  height:261px;  overflow:hidden;  position:relative;  z-index:1000;} " ,
".fn-facebook-chat-uppart{	border-color:#CCCCCC;	border-style:solid;	border-width:1px;	overflow:hidden;    width:260px;    height:232px;}",
".fn-facebook-chat-downpart{	border-color:#CCCCCC;	border-style:solid;	border-width:1px;	margin-top:-1px;	overflow:hidden;    width:260px;    height:25px;}",
".RichTextEditorR{    width:258px;    height:232px;	}",
".RichTextEditorS{	margin-left:-4px;	margin-top:-28px;	width:263px;    height:55px;	}"
],*/
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
		console.error(" in onAttach : " +  worker.url);
		try
		{
			page_mod_workers.push(worker);
			worker.port.emit("getEditors", worker.url);
			console.error("^^^^^^^^^^^ worker onAttach page_mod_workers len = " + page_mod_workers.length + " >url:" + worker.url);
			
			worker.on('detach', function() {
				var index = page_mod_workers.indexOf(worker);
				//Then remove it with splice:
				page_mod_workers.splice(index, 1);

				console.error("^^^^^^^^^^^ worker detached  and removed from the array : page_mod_workers len = " + page_mod_workers.length  + " >url:" + worker.url);
			});//worker.on]

			  //worker.port.emit("getEditors", worker.url);
			  worker.port.on("getEditor", function(elementContent) {
			      console.error(" --- on getEditor" + elementContent);
			  });//worker.port.on
        }
		catch(ee)
		{
			console.error("onAttach : " + e);
		}
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