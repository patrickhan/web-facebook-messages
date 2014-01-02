//exports.attach = attach;
//exports.detach = detach;
exports.save_Stream_topic = save_Stream_topic;
exports.get_BrowserWindow =  get_BrowserWindow;
exports.get_FnGlobalObject =  get_FnGlobalObject;// Raymon use 'FnGlobalObject' to store some global data
exports.get_recipients_from_fndocid = get_recipients_from_fndocid;

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
		return aBrowserWindow.FnGlobalObject;
	}
	return null;
}

function save_Stream_topic(aworker, msg )
{
	
}

//fndocid related 
function get_recipients_from_fndocid(afndocid, atask_callback)
{
	if(!afndocid || (typeof afndocid !== "string") || (afndocid.length == 0 ))
	{
		return null;
	}
	var aBrowserWindow = get_BrowserWindow();
	if(!aBrowserWindow)
	{
		return null;
	}
	var aDocServerObj = _create_FnFileBrowserSrv_DocServer(aBrowserWindow);
	if(!aDocServerObj)
	{
		return null;
	}
	var docids = _create_fndocid_object(afndocid);
	aDocServerObj.getKeysByDocId(docids, function(retKeys) {
            
            if(retKeys == null || retKeys == "") {
                return;
            }
            var aFnFileBrowserSrv_message = _create_FnFileBrowserSrv_message(aBrowserWindow);
            var keys = aFnFileBrowserSrv_message.parseKey(retKeys);
            /*  keys is formated as 'ret' as bellow
             *         var ret = {};
             *         var temp = {};
        	*			temp.docid = recipient.get("docguid");
        	*			temp.repid = recipient.get("recipientid");
        	*			temp.repkey = recipient.get("recipientkey");
        	*
        	*			ret[temp.docid+temp.repid] = temp
             * 
             */
            var data_recipients = [];
            for(var key in keys) {
            	data_recipients.push(keys[key].repid);
            }
            atask_callback(data_recipients);
        });
	
	return null;
}
//according to Raymon's definition 
//var docids = [{docGuid:adocid1, recipientId:ownerMe1},{docGuid:adocid2, recipientId:ownerMe2}];
function _create_fndocid_object(afndocid)
{
	var docids = [];
	docids.push({docGuid:afndocid, recipientId:null});
	return docids;
}
//refer extensions\fnwebService@federatednetworks.com\modules\fileBrowserSrv.js(551):FnFileBrowserSrv.DocServer.prototype.getKeysByDocId = function(data, func)
function _create_FnFileBrowserSrv_DocServer(aBrowserWindow)
{
	return  new aBrowserWindow.FnFileBrowserSrv.DocServer();
}
// refer : extensions\fnwebService@federatednetworks.com\modules\fileBrowserSrv.js(1523):FnFileBrowserSrv.Message.prototype.parseKey = function(keyData)
function _create_FnFileBrowserSrv_message(aBrowserWindow)
{
	return  new aBrowserWindow.FnFileBrowserSrv.message();
}
/*
 * 
 with fnRegistry:
            var versionMajor = _get_fnRegistry(aBrowserWindow).getMajorVersion();
            var versionMinor = _get_fnRegistry(aBrowserWindow).getMinorVersion();
*/
function _get_fnRegistry(aBrowserWindow)
{
	return  aBrowserWindow.fnRegistry;
}
;
