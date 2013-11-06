

/************************************************************************/
/*                                                                      */
/************************************************************************/
Components.utils.import("resource://browsercontent/DbOperator.jsm");
Components.utils.import("resource://browsercontent/FnGlobalObject.jsm");
/**
 * FNfacebook
 * the interface of FNfacebook
 *
 * @param	
 * @param   
 * @return	none
 * @access	none-static
 * @author  Raymond FuXing
 * @date    2013-09-2
 */

function FNfacebook(doc, msg)
{
    this.doc = doc;
    
    try {
        processMsg(msg);
    } catch(err) {
        console.error("FNfacebook error:"+err);
    }
    
    function processMsg(msg)
    {
        eval(getMsgType(msg.detail))(msg.detail);
    }
    
    function getMsgType(msg)
    {
        return new FNfacebookImp().getMsgType(msg);
    }
    
    function testLucky(msg)
    {
        new FNfacebookImp().testLucky(this.doc, msg);
    }
    
    function passDataFromRTE(msg)
    {
        new FNfacebookImp().passDataFromRTE(this.doc, msg);
    }
    
    function passDataToRTE(msg)
    {
        new FNfacebookImp().passDataToRTE(this.doc, msg);
    }
	
	function showInvitationWindow(msg)
	{
		new FNfacebookImp().showInvitationWindow(this.doc, msg);
	}
    
    
}

/**
 * FNfacebookImp
 * the interface of file facebook implmentation
 *
 * @param	
 * @param   
 * @return	none
 * @access	static
 * @author  Raymond FuXing
 * @date    not sure
 */
function FNfacebookImp()
{

}

FNfacebookImp.prototype.getMsgType = function(msg)
{
	console.log("facebook:"+msg.msgheader+"\n"+JSON.stringify(msg.message));
    return msg.msgheader;
}

FNfacebookImp.prototype.sendMsg = function(doc, data)
{
    new FnFileBrowserSrv.MsgServer().sendMsg(doc, new FnFileBrowserSrv.MsgServer().newMsg(MessageObj.html, data, doc));

}

/**
 * testLucky
 * to test
 *
 * @param   doc
 * @param   msg
 * @return	none
 * @access	static
 * @author  Raymond FuXing
 * @date    not sure
 */
FNfacebookImp.prototype.testLucky = function (doc, msg)
{
    try {

		var param = msg.message.data;
		console.log("testLucky:"+JSON.stringify(param));
		if(msg.message.finish) {
			msg.message.finish("facebook:"+JSON.stringify(param));
		}

    } catch (err) {
        console.log("error::testLucky::"+err);
    }
}
   
FNfacebookImp.prototype.showInvitationWindow = function(doc, msg)
{
	try {
		var dataInv = msg.message;
		console.log("==========dataInv>"+dataInv);
		var ownerId = dataInv.match(/(\()(\d{5})(\))/g);
		if(ownerId) {
			ownerId = ownerId[0].match(/(\d{5})/g);
			if(ownerId) {
				ownerId = ownerId[0];
			}
		}
		if(ownerId == null || ownerId == undefined) {
			return;
		}
		if(this.isExistOwner(ownerId)) {
			return;
		}
		var path = "file://" + DirSrvObj.currentWorkingPath() + "/localWebApp/";
		var url = path + "dojo/FnInvitation.html?invitation=" + dataInv;
		var ww = Components.classes["@mozilla.org/embedcomp/window-watcher;1"].getService(Components.interfaces.nsIWindowWatcher);
		var winTemp = ww.openWindow(
			null,
			url,
			"FN Invitation",
			"menubar=yes,modal=no,chrome=no,centerscreen,width=480,resizable=no,scrollbars=no,status=no,titlebar=yes,toolbar=no,height=250",
			null
		);
		
		if(winTemp) {
			var win = winTemp.open(url, "", "menubar=yes,modal=no,chrome=no,centerscreen,width=480,resizable=no,scrollbars=no,status=no,titlebar=yes,toolbar=no,height=250");
			winTemp.close();
		}
		
	} catch(err) {
		console.error("showInvitationWindow:"+err);
	}
}

/**
 * passDataFromRTE
 * to get data from RTE element
 *
 * @param   doc
 * @param   msg
 * @return	none
 * @access	static
 * @author  Raymond FuXing
 * @date    Sep 06, 2013
 */
FNfacebookImp.prototype.passDataFromRTE = function (doc, msg)
{
    try {
		var self = this;
		var receivers = msg.message.data[0].receiver;
		console.log("receivers:"+receivers);
		this.getOwnerId(doc, receivers, function(ownerIds) {
		
			this.params.docids = {"HJContentID":null, "HJInvitationID":"0ca45fe1-1d4b-4879-bf08-dc8e2f582120(60863)"};
		
			if(ownerIds == null) {
				//need to add invitation
				var emails = "noemails@fn.com";
				var FNJSAPICaller = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
								createInstance(Components.interfaces.IFNWebSvrJSHelper);
				FNJSAPICaller.sendInvitation(emails,
					//this is a async function
					{call_withString:function(idInvitation ){
						var id = idInvitation.split(":")[1];
						console.log("got invitation id:" + id);
						this.params.docids.HJInvitationID = id;
						self.preprocessMsg(self, doc, this.msg, this.params, ownerIds);
					}.bind({msg: this.msg, params: this.params, ownerIds: ownerIds})} );
				
			} else {
				self.preprocessMsg(self, doc, this.msg, this.params, ownerIds);
			}
			
		}.bind({msg: msg, params: msg.message}));
		

    } catch (err) {
        console.log("error::passDataFromRTE::"+err);
    }
}
   
FNfacebookImp.prototype.preprocessMsg = function(self, doc, msg, params, ownerIds)
{
	try {
		var eleRteS = msg.eleRteS || "RichTextEditorS";
		var objRTE = doc.defaultView.wrappedJSObject.document.getElementById(eleRteS);
		var rteContent = objRTE.GetFNRTEContent();
		console.log("rteContent:"+rteContent);
		
		var reader = fbone.utils.json.toJson(objRTE.GetSendData(new FnIm.Common().getMsgDataContent(rteContent)));
		
		var data = new FnIm.Common().parseRTE(reader, objRTE.GetFneBinaryData());

		if(ownerIds) {
			if(new FnFileBrowserSrv.MsgServer().hasProperty(ownerIds)) {
				data = new FnIm.Common().addOwnerIdToRTE(data, ownerIds);
			}
		}

		objRTE.ShowPlainTextMsg("", "", "") ;  

		data.message = data.msg;
		console.log(JSON.stringify(data));
		
		var param = params.data;
		var finish = params.finish;
		param[0].message = data.docid;
		params.docids.HJContentID = data.docid;
		
		console.log("DOCIDS:"+JSON.stringify(params.docids)+"\nownerIds:"+JSON.stringify(ownerIds));
		
		self.processMsg(doc, data, function (ret, keyObjs) {
			console.log("upload RTE done.");
			
			if(this.finish) {
				this.finish(JSON.stringify(this.docid), doc);
			}
			
		}.bind({param: param, finish: finish, docid: params.docids}));
	} catch(err) {
		console.log("preprocessMsg error:" + err);
	}

}

/**
 * passDataToRTE
 * to send data to RTE element
 *
 * @param   doc
 * @param   msg
 * @return	none
 * @access	static
 * @author  Raymond FuXing
 * @date    Sep 04, 2013
 */
FNfacebookImp.prototype.passDataToRTE = function (doc, msg)
{
    try {
		var param = msg.message.data;
		var finish = msg.finish;
		
		new MsgService.MsgProcesser().receiveRTEmsg(null, doc, "", fbone.utils.json.fromJson(param), function(id) {
			var data = {"imtype":"facebook", "serviceName":"getDocidType", "message":id,"sender":"", "receiver":"","datetime":new Date().valueOf()};
			if(this.finish) {
				this.finish("facebook:"+JSON.stringify(data));
			}
		
		}.bind({finish: this.finish}));

    } catch (err) {
        console.log("error::passDataToRTE::"+err);
    }
}


FNfacebookImp.prototype.processMsg = function(doc, msg, func)
{
//1, use key that get from RTE, (encrypted key using me public key)
//2, decrypt key using me ownerid, decryptPublicEncKey = function(publickey, ownerid)
//3, encrypt new owner key using decrypted key
    try {
		var params = msg;
        var keyObjs = [];
		var randKey = "";
		var mePkey = "";
		
        for(var i=0;i<params.reader.length;++i) {
			if(params.reader[i].isme == true) {
				var repId = params.reader[i].ownerid.match(/\d{5}/g);
				var key = params.reader[i].pkey;
				mePkey = key;
				randKey = ECHelperNS.decryptPublicEncKey(key, repId);
				
			} 
            
        }
		
        for(var i=0;i<params.reader.length;++i) {
            if (params.reader[i].isme == true) {
                continue;
            } else {
                addInvitationFndoc(params.docid, mePkey);
			} 
            
        }
		
		for(var j=0;j<params.reader.length;++j) {
			if(params.reader[j].isme == true) continue;
			console.log(randKey+"\n"+params.reader[j].pkey);
			if(randKey && params.reader[j].pkey) {
				params.reader[j].pkey = ECHelperNS.encryptRealKey(randKey, params.reader[j].pkey);
			}
		}
   
		new MsgService.MsgProcesser().sendDataToServer(doc, params, function (ret, keyObjs) {
		    if (func) {
		        func(ret, keyObjs);
		    }
		});
        
    } catch(err) {
        console.error("FNskypeImp.processMsg:"+err);
    }    

}


/************************************************************************/
/* getOwnerId: to get ownerid and key from db using handle id
/* @param msg: [handle ids]
/* note: after getting ownerid and key from db, 
/*       1, decrypt using me key
/*       2, encrypt using new ownerid public key
/************************************************************************/

FNfacebookImp.prototype.getOwnerId = function(doc, msg, func)
{
    var handleIds = msg;

    var params = [];
    for(var i=0;i<handleIds.length;++i) {
		var param = {};
        param.imHandle = handleIds[i];
        param.imName = "facebookName";
		
		params.push(param);
    }
    var ownerMe = {ownerid:"", publickey:"", ramdkey:""};
    ownerMe = new FnFileBrowserSrv.DbServer().getMe();
    if(ownerMe == null) {
        return;
    }
    console.log("meeeeeeeeee facebook ownerid:"+ownerMe.ownerid+"\npublickey:"+ownerMe.publickey+"\nramdkey:"+ownerMe.ramdkey);

    new FnFileBrowserSrv.DbServer().getOwnerIdByImHandle(params, function (data) {
    
        var dataSend = {};
		if(data == null || data.length == 0) {
			console.log("getOwnerIdByImHandle returns null");
			
			return;
		}
        for(var i=0;i<data.length; ++i) {
            var ownerid = data[i].ownerid;
            var pkey = data[i].publickey;
			var isme = false;
            if(ownerid == ownerMe.ownerid) {
                isme = true;
            }
			if((ownerid == "" && pkey == "") || (ownerid == null && pkey == null)) {
				dataSend = null;
			} else {
				dataSend[ownerid] = {isme: isme, pkey: pkey};
			}
			console.log("returned ownerid:"+ownerid+"\nisme:"+isme+"\npkey:"+pkey);
        }
        
		if(func) {
			func(dataSend);
		}

    });

}

FNfacebookImp.prototype.isExistOwner = function(ownerId)
{
	return new FnFileBrowserSrv.DbServer().isExistOwner(ownerid);
}

