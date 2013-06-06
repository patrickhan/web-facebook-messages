


var {Cc, Ci, Cm, Cr, Cu} = require("chrome");

const windowMediator = Cc['@mozilla.org/appshell/window-mediator;1'].getService(Ci.nsIWindowMediator);
let XPCOMUtils = Cu.import("resource://gre/modules/XPCOMUtils.jsm").XPCOMUtils;

var g_browsr_windows = [];

const STATE_START = Ci.nsIWebProgressListener.STATE_START;
const STATE_STOP = Ci.nsIWebProgressListener.STATE_STOP;
var myProgressListener = {
	my_callback_func: null,

	QueryInterface: XPCOMUtils.generateQI(["nsIWebProgressListener",
											"nsISupportsWeakReference"]),

	onLocationChange: function(aProgress, aRequest, aURI) {
		// This fires when the location bar changes; that is load event is confirmed
		// or when the user switches tabs. If you use myListener for more than one tab/window,
		// use aProgress.DOMWindow to obtain the tab/window which triggered the change.
        
		//do something
		//console.log(" -- " + aURI.spec);

		if(this.my_callback_func)
		{
			this.my_callback_func(aURI.spec);

			
		}

	},
 
	// For definitions of the remaining functions see related documentation
	onStateChange: function(aWebProgress, aRequest, aFlag, aStatus) { },
	onProgressChange: function(aWebProgress, aRequest, curSelf, maxSelf, curTot, maxTot) {},
	onStatusChange: function(aWebProgress, aRequest, aStatus, aMessage) {},
	onSecurityChange: function(aWebProgress, aRequest, aState) {}
}

function add_a_browser()
{
	var enumerator = windowMediator.getEnumerator("navigator:browser");
	while(enumerator.hasMoreElements()) {
		var window = enumerator.getNext();
		var gBrowser = window.gBrowser;
		if( gBrowser)
		{
			if(-1 == g_browsr_windows.indexOf(gBrowser) )
			{
				g_browsr_windows.push(gBrowser);
				gBrowser.addProgressListener(myProgressListener);
				console.log(" === = = agBrowser1.addProgressListener(myProgressListener) ++ " );
			}
		}
		
	}
}

 
function remove_a_browser()
{
	let temp_gBrowsers = [];
	let enumerator = windowMediator.getEnumerator("navigator:browser");
	while(enumerator.hasMoreElements() ) {
		var window = enumerator.getNext();
		var gBrowser = window.gBrowser;
		if(gBrowser )
		{
			temp_gBrowsers.push(gBrowser);
		}
	}

	//find which is closed
	for(var i = 0;  i < g_browsr_windows.length; i++ )
	{
		let agBrowser1 = g_browsr_windows[i];
		if(-1 == temp_gBrowsers.indexOf(agBrowser1) )
		{
		   try {
			  console.log(" === = = agBrowser1.removeProgressListener(myProgressListener) -- " );
			  agBrowser1.removeProgressListener(myProgressListener);
		    } catch (ex) {}
			
		}
	}
	//copy the list to global
	g_browsr_windows = temp_gBrowsers.slice(0);
}

function init_ProgressListener(callback_func)
{
	add_a_browser();

	myProgressListener.my_callback_func = callback_func;
}


function attach_browserWindows(){
    var windows = require("windows").browserWindows;
 
	// add a listener to the 'open' event
	windows.on('open', function(window) {
	  //console.log("A window was open. :  " + window.location);
	  add_a_browser();
	  //myOpenWindows.push(window);
	});
 
	// add a listener to the 'close' event
	windows.on('close', function(window) {
	  //console.log("A window was closed.");
	  remove_a_browser();
	  //var gBrowser = window.gBrowser;
	  //gBrowser.removeProgressListener(myListener);
	});
 
	// add a listener to the 'activate' event
	windows.on('activate', function(window) {
	  //todo
	  //console.log("A window was activated.");
	});
 
	// add a listener to the 'deactivate' event
	windows.on('deactivate', function(window) {
	  //todo
	  //console.log("A window was deactivated.");
	});
}


function attach( callback_func)
{
	attach_browserWindows();
	init_ProgressListener(callback_func);
}
function detach()
{
	// not needed
}


exports.attach = attach;
exports.detach = detach;


/*
function sort_unique(arr) {
    arr = arr.sort(function (a, b) { return a*1 - b*1; });
    var ret = [arr[0]];
    for (var i = 1; i < arr.length; i++) { // start loop at 1 as element 0 can never be a duplicate
        if (arr[i-1] !== arr[i]) {
            ret.push(arr[i]);
        }
    }
    return ret;
}
console.log(sort_unique(['237','124','255','124','366','255']));
*/