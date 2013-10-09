//exports.attach = attach;
//exports.detach = detach;
exports.save_Stream_topic = save_Stream_topic;


var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
var utils = require('sdk/window/utils');

function get_BrowserWindow()
{


	var active = utils.getMostRecentBrowserWindow();
	//active instanceof Ci.nsIXULWindow // => false
	//utils.getXULWindow(active) instanceof Ci.nsIXULWindow // => true
	
	//console.error("active.document.location : "  + active.document.location);
	//console.error("active.gBrowser : " + active.gBrowser);
	return active;
}

function get_FnGlobalObject()
{
	var aBrowserWindow = get_BrowserWindow();
	if(aBrowserWindow)
	{
		return aBrowserWindow.FnGlobalObject
	}
	return null;
}

function save_Stream_topic(aworker, msg )
{
	
}

