exports.attach = attach;
exports.detach = detach;


//var { Class } = require("api-utils/heritage"); //sdk v1.10
var { Class } = require('sdk/core/heritage');//sdk v1.14
//var { Unknown } = require('api-utils/xpcom');//sdk v1.10
var { Unknown } = require('sdk/platform/xpcom');//sdk v1.14

var {Cc, Ci, Cm, Cr, Cu} = require("chrome");

const windowMediator = Cc['@mozilla.org/appshell/window-mediator;1'].getService(Ci.nsIWindowMediator);
let XPCOMUtils = Cu.import("resource://gre/modules/XPCOMUtils.jsm").XPCOMUtils;
var data = require("sdk/self").data;
var pageMod = require("sdk/page-mod");
var addon_pref = require("sdk/simple-prefs");



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


var  aTriggerObserver = TriggerObserver();

function attach()
{
	aTriggerObserver.register();
}

function detach()
{
	 aTriggerObserver.unregister();
}