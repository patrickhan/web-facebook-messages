var ECHelperNS = {};

(function(NP){
	NP.getNodesByXpath = function(doc, aExpr)
	{
		 var nodesSnapshot = doc.evaluate(aExpr, doc.documentElement, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null);
	   var found = [];
	   for(var i=0; i < nodesSnapshot.snapshotLength; i++)
	   {
	      found.push(nodesSnapshot.snapshotItem(i));
	   }
	   return found;
	};

    NP.getNodesByXpath2 = function(doc, searchNode, aExpr)
	{
		 var nodesSnapshot = doc.evaluate(aExpr, searchNode, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null);
	   var found = [];
	   for(var i=0; i < nodesSnapshot.snapshotLength; i++)
	   {
	      found.push(nodesSnapshot.snapshotItem(i));
	   }
	   return found;
	};

    NP.removeSomeNodesUnderParentByTagName = function(prNode, tagName)
	{
        var wbrnodes =  prNode.getElementsByTagName(tagName);       
        for(var cnt = wbrnodes.length - 1; cnt >= 0; cnt--)
        {
            wbrnodes[cnt].parentNode.removeChild(wbrnodes[cnt]);                    
        }        
	};
	
	NP.removeNonSenseChars = function(instr)
	{
        return instr.replace(/[^\x20-\x7E]/gm,'');
	};

    NP.removeNonSenseChars_keepReturn = function(instr)
	{
	    return instr.replace(/[\x00-\x09]|[\x0B-\x0C]|[\x0E-\x1F]|[\x7F-\xFF]/gm,'');
        //return instr.replace(/[\x0-\x9]|[\xB-\xC]|[\xE-\x1F]|[\x7F-\xFF]/gm,'');
	};

    NP.mergeCountiueTextNodeIntoOne = function(firstTxtNode)
    {
        var nexttxtnode = firstTxtNode.nextSibling;
        while(nexttxtnode != null && nexttxtnode.nodeType == 3)
        {
            firstTxtNode.nodeValue += nexttxtnode.nodeValue;
            var lastnextnode = nexttxtnode;
            nexttxtnode = nexttxtnode.nextSibling;
            lastnextnode.FnDocId_processed = true; //Make this node don't process any more
            lastnextnode.parentNode.removeChild(lastnextnode);             
        }
    };
    
    NP.markDealedTxtNodes = function(prNode, txtnodes)
	{
	    for(var counter = 0; counter < txtnodes.length; ++counter)
	    {   
	        var anele = txtnodes[counter];
	        while(anele != prNode && anele != prNode.ownerDocument.body)
	        {	        
	            if(anele.parentNode == null)
	            {
	                txtnodes[counter].FnDocId_processed = true;
	                break;
	            }
	            anele = anele.parentNode;
	        }	        
	        if(anele == prNode)
	        {
	            txtnodes[counter].FnDocId_processed = true;
	        }
	    }
	};


    NP.matchFnDocIdFromString = function(theString)
    {
        var fnidFinder = new RegExp('fndocid:([a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12})', 'gm');        	    
     	var match = theString.match(fnidFinder);
        return match;
    };

    NP.matchHackJacketFromString = function(theString)
    {
        var fnidFinder = new RegExp('HackJacket Protected[.\\n \\r]{0,6}Start communicating securely \\(its free!\\)[.\\n \\r]{0,6}Go To: http://download\\.HacketJacket\\.com', 'gm');        	    
     	var match = theString.match(fnidFinder);
        return match;
    };

    NP.removeHackJacketFromString = function(theString)
    {
        let results = NP.matchHackJacketFromString(theString);
        if(results != null)
        {
            for(let i = 0; i < results.length; ++i)
            {
               theString = theString.replace(results[i], "");
            }
        }
        return theString;
    };

    NP.matchHJContentIDFromString = function(theString)
    {
        var fnidFinder = new RegExp('HJContentID:([a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12})', 'gm');        	    
     	var match = theString.match(fnidFinder);
        return match;
    };

    NP.matchHackJacketTailFromString = function(theString)
    {
        var fnidFinder = new RegExp('HJInvitationID:([a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12})\\([0-9]*\\)', 'gm');        	    
        //var fnidFinder = new RegExp('HJInvitationID:([a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12})', 'gm');        	    
     	var match = theString.match(fnidFinder);
        return match;
    };

    NP.removeJacketTailFromString = function(theString)
    {
        let results = NP.matchHackJacketTailFromString(theString);
        if(results != null)
        {
            for(let i = 0; i < results.length; ++i)
            {
               theString = theString.replace(results[i], "");
            }
        }
        return theString;
    };

    NP.getFnDocIdLength = function()
    {
        return 44;
    }

    NP.getHJContentIDLength = function()
    {
        return 48;
    }
    
    NP.matchEmailFromString = function(theString)
    {
        var fnidFinder = new RegExp('(\\w+\\.)*\\w+@(\\w+\\.)+[A-Za-z]+', 'gm');        	    
     	var match = theString.match(fnidFinder);
        return match;
    };

    NP.matchFnDocidFromNode = function(anode)
    {
        let tempstring = '';
        if(anode.nodeName != "TEXT")
        {
            tempstring = NP.removeNonSenseChars(anode.textContent);
        }
        else
        {
            tempstring = NP.removeNonSenseChars(anode.nodeValue);
        }
        let matchRes = NP.matchFnDocIdFromString(tempstring);
        return matchRes;        
    };
    
	NP.nodeIsEditable = function(node)
	{
		 if(!node)
     {
      	return false;
     }
	   if(node.ownerDocument.designMode == "on")
	   {
	       return true;
	   }
	   while( node.isContentEditable === undefined || node.isContentEditable == false)
	   {
	      if(node.tagName == "TEXTAREA")
	      {
	          return true;
	      }	      
          if(node.nodeName=="BODY")
          {
              return false;
          }
          if(node.isContentEditable !== undefined && node.isContentEditable == true)
          {
              return true;
          }
          node = node.parentNode; 
          if(!node)
          {
          	return false;
          }
	   }	   
	   return node.isContentEditable;
	};

    NP.elementInDOM = function(aElement)
    {
    	if(aElement)
    	{
    		if(aElement.ownerDocument)
    		{
    			if(aElement == aElement.ownerDocument.body)
    			{
    				return true;
    			}
    			else if(aElement == aElement.ownerDocument.documentElement)
    			{
    				return true;
    			}
    			else
    			{
    				let parent =  aElement.parentNode;
    				while(parent)
    				{
    					
    					if(parent == aElement.ownerDocument.body)
    					{
    						return true;
    					}
    					parent =  parent.parentNode;
    					
    					if(parent && parent ==  parent.parentNode)//dead loop
    					{
    						return false;
    					}
    					
    				}
    			}
    		}
    	}
    	return false;
    }

    NP.getAncestorNodeByTagName = function(tname, curnode)
    {
        let parentnd = curnode.parentNode;
        let body = curnode.ownerDocument.body;
        while(parentnd.nodeName != tname || parentnd != body)
        {
            parentnd = parentnd.parentNode;
            if(parentnd == null)
            {
                break;
            }
            if(parentnd.tagName == tname)
            {
                return parentnd;
            }
        }
        throw "Fn Error getAncestorNodeByTagName happen error";
    }

	NP.getAncestorNodeByTagName_className = function(atagname, aclassname, curnode)
    {
		try{
        let parentnd = curnode.parentElement;
        let body = curnode.ownerDocument.body;
        while(parentnd && parentnd != body)
        {
            parentnd = parentnd.parentElement;
            if(!parentnd)
            {
                break;
            }
            if(parentnd.tagName == atagname)
            {
				var index = parentnd.className.indexOf(aclassname);
				if(index != -1)//contain the class name
				{
					return parentnd;
				}
            }
        }
		}catch(e){}
        return false;
    }
	
	var g_ownerid = 0;
	NP.getOwnerId = function()
	{
		 if(g_ownerid == 0)
		 {
		     var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
		                      createInstance(Components.interfaces.IFNWebSvrJSHelper);
		     g_ownerid = FnComHelper.getMyOwnerId();
		 }
		 return g_ownerid;
	};	
	
	NP.getFnDocIdFromInStream = function(instream, cbfun)
	{
		var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
        createInstance(Components.interfaces.IFNWebSvrJSHelper);
		if(FnComHelper)
		{
			FnComHelper.tryToGetFnDocIdFromInStream(instream, cbfun);
		}		   
	};
	
	NP.getFnDocIdFromInBlob = function(blob, cbfun)
	{
		var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
        createInstance(Components.interfaces.IFNWebSvrJSHelper);
		if(FnComHelper)
		{
			//Get internalstream of blob
			var instream = FnComHelper.exportInternalInputStreamBlob(blob);			
			NP.getFnDocIdFromInStream(instream, cbfun);
		}		   
	};
	
	NP.exportInternalInputStreamBlob = function(blob)
	{
		var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
        createInstance(Components.interfaces.IFNWebSvrJSHelper);
		if(FnComHelper)
		{
			//Get internalstream of blob
			var instream = FnComHelper.exportInternalInputStreamBlob(blob);			
			return instream;
		}		   
	};

    NP.decryptPublicEncKey = function(publickey, ownerid)
    {
        var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
        createInstance(Components.interfaces.IFNWebSvrJSHelper);
        if(FnComHelper)
		{
			//Get internalstream of blob
			try
            {                         
			    var outrealkey = FnComHelper.decryptPublicEncKey(publickey, ownerid);			
                return outrealkey;
            }
            catch(err)
            {
                return null;
            }
		}	
    };

    NP.encryptRealKey = function(realkey, publickey)
    {
        var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
        createInstance(Components.interfaces.IFNWebSvrJSHelper);
        if(FnComHelper)
		{
			//Get internalstream of blob
			try
            {                        
			    var outrealkey = FnComHelper.encryptRealkey(realkey, publickey);			
                return outrealkey;
            }
            catch(err)
            {
                return null;
            }
		}	
    };

    

    NP.dataDBOper = function(sqltemplate, inparams, callback)
    {
        alert("ECHelperNS.dataDBOper don't use anymore");
        throw ("ECHelperNS.dataDBOper don't use anymore");
        
        /*try
        {
            Components.utils.import("resource://webpagesvrmoudleLoader/webpgjs/dataOper.jsm"); 
            dataDBOper(sqltemplate, inparams, callback);            
        }
        catch(err)
        {
            alert("dataDBOper error: " + err);
            callback(null);
        }*/
        
    };

    NP.dataDBOper_v2 = function(sqltemplate, inparams, callback, isAddedIntoStatementsMap, selectDBIndex, isAsync)
    {
        try
        {
            Components.utils.import("resource://webpagesvrmoudleLoader/webpgjs/dataOper.jsm");             
            dataDBOper(sqltemplate, inparams, callback, isAddedIntoStatementsMap, selectDBIndex, isAsync);            
        }
        catch(err)
        {
            alert("dataDBOper error: " + err);
            callback(null);
        }
        
    };

    NP.dumpBlobTopTempFile = function(blob)
	{
		var file = Components.classes["@mozilla.org/file/directory_service;1"].
		   getService(Components.interfaces.nsIProperties).
		   get("TmpD", Components.interfaces.nsIFile);
		file.append("FnImage.fne");
		file.createUnique(Components.interfaces.nsIFile.NORMAL_FILE_TYPE, 0666);
		
		var foStream = Components.classes["@mozilla.org/network/file-output-stream;1"].
					   createInstance(Components.interfaces.nsIFileOutputStream);
		foStream.init(file, 0x02 | 0x08 | 0x20, 0666, 0);
		var outputStream = Cc["@mozilla.org/network/buffered-output-stream;1"].
                       createInstance(Ci.nsIBufferedOutputStream);
		outputStream.init(foStream, 8192);
		
		var instream = ECHelperNS.exportInternalInputStreamBlob(blob);		
		outputStream.writeFrom(instream, blob.size);
		outputStream.close();
		return file.path;
	};

    NP.loadAJsFile = function(jsfileName)
    {
        var loader = Components.classes["@mozilla.org/moz/jssubscript-loader;1"]
                               .getService(Components.interfaces.mozIJSSubScriptLoader);
        var fulljsfile = "chrome://webpagesvr/content/webpgjs/" + jsfileName;
        loader.loadSubScript(fulljsfile, EcselfDefineGlobalScope);
    };

    NP.getCurrentTabBrowserFromHTMLDoc = function(doc)
    {
        var mainWindow = doc.defaultView.QueryInterface(Components.interfaces.nsIInterfaceRequestor).
                           getInterface(Components.interfaces.nsIWebNavigation).
                           QueryInterface(Components.interfaces.nsIDocShellTreeItem).
                           rootTreeItem.
                           QueryInterface(Components.interfaces.nsIInterfaceRequestor).
                           getInterface(Components.interfaces.nsIDOMWindow);
          
        var curGBrowser = mainWindow.gBrowser;
        return curGBrowser.selectedTab.linkedBrowser;
    };

    NP.sendError = function(msg, fileName, linenum)
    {
        let outmsg = "";
        if(msg !== undefined)
        {
            outmsg += msg;
        }
        if(fileName !== undefined)
        {
            if(outmsg.length > 0)
            {
               outmsg += "  " + fileName; 
            }
            else
            {
               outmsg += fileName;  
            }
        }
        if(linenum !== undefined)
        {
            if(outmsg.length > 0)
            {
               outmsg += "  " + linenum; 
            }
            else
            {
               outmsg += linenum;  
            }
        }
        console.log("FnErrorMessage: " + outmsg);
    };

    NP.getFileExtensionByFileName = function(fileName)
    {
        let n = fileName.lastIndexOf(".");
        if(n != -1)
        {
            return fileName.substr(n+1);
        }
        return "";
    };

    NP.getImagePathByExtName = function(extName, callback)
    {
        var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
        createInstance(Components.interfaces.IFNWebSvrJSHelper);
        if(FnComHelper)		{
			
			try
            {                         
			    FnComHelper.getIconByExtensionName(extName, {call_withString:function(imgPath){                    
                    callback(imgPath);
                }});               
            }
            catch(err)
            {
                
            }
		}	
    };

    NP.showTextInRTEWithMixFormater = function(retobj, mixFormater)
    {
        var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
                          createInstance(Components.interfaces.IFNWebSvrJSHelper);
        FnComHelper.showTextInRTEWithMixFormater(retobj, mixFormater);
    };

    NP.generateDataURI = function(file, contentType)
    {
        /*let contentType = Components.classes["@mozilla.org/mime;1"]
                                    .getService(Components.interfaces.nsIMIMEService)
                                    .getTypeFromFile(file);*/
        let inputStream = Components.classes["@mozilla.org/network/file-input-stream;1"]
                                    .createInstance(Components.interfaces.nsIFileInputStream);
        inputStream.init(file, 0x01, 0600, 0);
        let stream = Components.classes["@mozilla.org/binaryinputstream;1"]
                               .createInstance(Components.interfaces.nsIBinaryInputStream);
        stream.setInputStream(inputStream);
        let encoded =btoa(stream.readBytes(stream.available()));
        return "data:" + contentType + ";base64," + encoded;
    };

    NP.getFilePathOfChromeUrl = function(chromeurl)
    {
        let ioService = Components.classes["@mozilla.org/network/io-service;1"]
                                  .getService(Components.interfaces.nsIIOService);
        var uri = ioService.newURI(chromeurl, null, null);
        let nsChannel = ioService.newChannelFromURI(uri);
        let nsFileChnnel = nsChannel.QueryInterface(Components.interfaces.nsIFileChannel);
        return nsFileChnnel.file.path;
    };

    NP.generateDataURIByFileName = function(file, contentType)
    {
        let localFile = Components.classes["@mozilla.org/file/local;1"]
                                  .createInstance(Components.interfaces.nsILocalFile);
        localFile.initWithPath(file);
        return NP.generateDataURI(localFile, contentType);
    };

    NP.adjustEleOutterToDisplay = function(plg, tempnode, wantWidth, wantHeight)
    {
        if(plg.tagName == "BODY")
        {
            return;
        }
        let tempnode = tempnode.parentNode;
        let cliplgWidth = tempnode.clientWidth;
        let cliplgHeight = tempnode.clientHeight;
               
        let isAdjustNext = false;
        
        if(cliplgWidth < wantWidth)
        {
            tempnode.style.width = wantWidth + "px";
            tempnode.style.maxWidth = wantWidth + "px";
            isAdjustNext = true;
        }

        if(cliplgHeight < wantHeight)
        {            
            tempnode.style.height = wantHeight + "px";
            tempnode.style.maxHeight = wantWidth + "px";
            isAdjustNext = true;
        }

        if(isAdjustNext)
        {    
            setTimeout(NP.adjustEleOutterToDisplay, 10,
                   plg, tempnode, wantWidth, wantHeight);
        }        
        
    }    
    
    NP.postMsgToWindow = function(winHandle, msg, lparam)
    {
        const ctypes = Components.utils.import("resource://gre/modules/ctypes.jsm").ctypes;
        const libs = {};
        libs.user32 = ctypes.open("user32.dll");

        const INT = ctypes.int;
        const WORD = ctypes.unsigned_short;
        const UINT = ctypes.unsigned_int;
        const WINAPI = ctypes.winapi_abi;
        const HWND = ctypes.voidptr_t;
        const DWORD = UINT;//ctypes.unsigned_long;

        const LRESULT = INT;//ctypes.long;
        const LPARAM = UINT;//INT;//ctypes.long;
        const WPARAM = UINT;//UINT.ptr;

        var PostMessage = libs.user32.declare("PostMessageW",/* function name */
                         WINAPI,			/* ABI type */
                         LRESULT,				/* return type */  
						 HWND,				/*hWnd,*/
						 UINT,
						 WPARAM,
						 LPARAM
                         );
        function PostMessage_JS(hWnd, msg , wParam, lParam)
        {


        	var hWnd_in = HWND(hWnd); 
        	var Msg_in = UINT(msg); 

        	
        	var lParam_in = LPARAM(lParam); 
        	 

        	
        	var wParam_in = WPARAM(wParam);             
        	var ret	= PostMessage( hWnd_in, Msg_in, wParam_in, lParam_in );
        	return ret;	

        }
        PostMessage_JS(winHandle, msg, 0, lparam);
    }

    NP.sendemailbyoutlook = function(sendParams)
    {
        var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
        createInstance(Components.interfaces.IFNWebSvrJSHelper);
        if(FnComHelper)		{
			
			try
            {   
                let array = Components.classes["@mozilla.org/array;1"]
                                     .createInstance(Components.interfaces.nsIMutableArray);
                
                let newstring = Components.classes["@mozilla.org/supports-string;1"]
                                    .createInstance(Components.interfaces.nsISupportsString);
                
                newstring.data = JSON.stringify(sendParams);                
                array.appendElement(newstring, false);                
			    var res = FnComHelper.callMSJSScriptFunction("sendemail", array);
            }
            catch(err)
            {
                alert(err);
            }
		}	
    };

    NP.getInstallationDirectory = function()
    {
      	 var fileinf = Components.classes["@mozilla.org/file/directory_service;1"].
      	            getService(Components.interfaces.nsIProperties).
      	            get("CurProcD", Components.interfaces.nsIFile);
      	 return fileinf.path;
    };

    NP.getElementRectToOutmostWin = function(theElement)
    {
        
        var eleRectOri = theElement.getBoundingClientRect();  
        var retele = {};          
        let outmostpg = NP.getCurrentTabBrowserFromHTMLDoc(theElement.ownerDocument);
        retele.left = theElement.ownerDocument.defaultView.mozInnerScreenX - outmostpg.contentWindow.mozInnerScreenX + eleRectOri.left;
        retele.top = theElement.ownerDocument.defaultView.mozInnerScreenY - outmostpg.contentWindow.mozInnerScreenY + eleRectOri.top;        
        retele.right = theElement.ownerDocument.defaultView.mozInnerScreenX - outmostpg.contentWindow.mozInnerScreenX + eleRectOri.right;
        retele.bottom = theElement.ownerDocument.defaultView.mozInnerScreenY - outmostpg.contentWindow.mozInnerScreenY + eleRectOri.bottom;    
        if(theElement.ownerDocument.defaultView != outmostpg.contentWindow)
        {
            //alert(theElement.tagName + "  " + theElement.ownerDocument.defaultView.mozInnerScreenY + "  " +
                  //outmostpg.contentWindow.mozInnerScreenY + " " + retele.top);
        }         
        return retele;
    };

    NP.getValueWithZoom = function(orival, win)
    {
        var domWinUtils = win.QueryInterface(Components.interfaces.nsIInterfaceRequestor).
                          getInterface(Components.interfaces.nsIDOMWindowUtils);        
        return orival * domWinUtils.screenPixelsPerCSSPixel;
    };

    NP.getElementRectToOutmostWin_Zoom = function(theElement)
    {
        let eleRectOri = NP.getElementRectToOutmostWin(theElement);
        let eleRect = {left:NP.getValueWithZoom(eleRectOri.left, theElement.ownerDocument.defaultView),
                       right:NP.getValueWithZoom(eleRectOri.right, theElement.ownerDocument.defaultView),
                       bottom:NP.getValueWithZoom(eleRectOri.bottom, theElement.ownerDocument.defaultView),
                       top:NP.getValueWithZoom(eleRectOri.top, theElement.ownerDocument.defaultView)};
        return eleRect;
    };
    
    NP.callXulService = function(svrName, svrParam, callback)
    {
        var FnComHelper = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
                          createInstance(Components.interfaces.IFNWebSvrJSHelper);
        function callbackFromcallXulrunnerService(retstring)
        {
            if(callback != null)
            {
            	 callback(retstring);
            }
        }
        FnComHelper.callXulrunnerService(svrName, svrParam, callbackFromcallXulrunnerService);
    };

    NP.swapObject = function(obj1, obj2)
    {
        var tempbox = window.document.createElement("box");
        obj1.parentNode.insertBefore(tempbox, obj1);
        var obj1 = obj1.parentNode.removeChild(obj1);
        obj2.parentNode.insertBefore(obj1, obj2);
        var obj2 = obj2.parentNode.removeChild(obj2);
        tempbox.parentNode.insertBefore(obj2,tempbox);
        tempbox.parentNode.removeChild(tempbox);
    }
        
}(ECHelperNS));
