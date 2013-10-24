(function(NP){
  NP.trainProcess = function(txtnode)
  {
      var domainFilter = {
        "facebook.com": function(txtnode){
            for(var counter = 0; counter < 10; ++counter)
            {
				if(ECHelperNS.getAncestorNodeByTagName_className("TABLE", "conversationContainer", txtnode) )
				{//this is the facebook chat , decryption is not expected.
					return null;
				}
                if(txtnode.nodeName == "SPAN" && txtnode.getAttribute("class") == "userContent")
                {    
                    var innertextStr = txtnode.textContent;                    
                    txtnode.innerHTML = ECHelperNS.removeNonSenseChars(innertextStr);
                    return txtnode;
                }        
                if(txtnode.parentNode != null)
                {       
                    txtnode = txtnode.parentNode;
                }
                else
                {
                    return false;
                }
            }
            return false;
        },        
      };              
      if(txtnode.ownerDocument.domain in domainFilter)
      {  
         return domainFilter[txtnode.ownerDocument.domain](txtnode);
      }
      else
      {
         return false;
      }
  };
  
  function Processor_FnDocId ()
  {
     this.superclass("Processor_FnDocId");
  }	
  Processor_FnDocId.prototype = new NP.Processor_Base("Processor_FnDocId");	
  Processor_FnDocId.prototype.superclass = NP.Processor_Base;
  Processor_FnDocIdProto = Processor_FnDocId.prototype;  
  
  
  Processor_FnDocIdProto.processBusiness = function(self, doc)
  {
     //Filter out the text node having fndocid flag.
     var res = ECHelperNS.getNodesByXpath(doc, "//text()[contains(.,'fndocid:')]");      
        
     for(var counter = 0; counter < res.length; ++counter)
     {
        var txtnode = res[counter];  
        var prNode = txtnode.parentNode;        
        //To avoid process it for more than once
        if(txtnode.FnDocId_processed == true)
        {
            continue;
        }                
        txtnode.FnDocId_processed = true;         
        //prNode.isParsed_Level = 1;        
        try
        {
       
        if(ECHelperNS.nodeIsEditable(txtnode) == false)
        {
            var match = null;            
            var txtnode2 = NP.trainProcess(txtnode);
            var oriTxt = "";
            if(txtnode2 != false)
            {   
                txtnode = txtnode2;
                prNode = txtnode.parentNode;
                ECHelperNS.markDealedTxtNodes(prNode, res);
                //trained process                
                match = ECHelperNS.matchFnDocIdFromString(txtnode2.innerHTML);
                oriTxt = txtnode2.innerHTML;
            }
            else
            {
                //default process
                ECHelperNS.removeSomeNodesUnderParentByTagName(prNode, "WBR");
                ECHelperNS.mergeCountiueTextNodeIntoOne(txtnode);  
                txtnode.nodeValue = ECHelperNS.removeNonSenseChars(txtnode.nodeValue);
        	    //Extrace the fndocid
                match = ECHelperNS.matchFnDocIdFromString(txtnode.nodeValue);
        	    oriTxt = txtnode.nodeValue;
        	}
  			if(match != null && match.length > 0)
  			{
  			    var isReplaceOriText = true;
  			    
		        //var containerDiv = doc.createElement("div");
  			    for(var i = 0; i < match.length; i++)
  			    {  
  			       //Under some special page do some special process
            	   if(sepcialDecrypt_1(prNode, txtnode, match[i]) == false)
                   {   
      			       var fnDocIdVal = match[i].substring('fndocid:'.length);
      			       var splitPos = oriTxt.indexOf(match[i]);
      			       var beforeText = oriTxt.substring(0, splitPos);
      			       oriTxt = oriTxt.substring(splitPos +  match[i].length);
      			       var nextxtNode = doc.createTextNode(beforeText);
      			       prNode.appendChild(nextxtNode);
      			       var ownerid = ECHelperNS.getOwnerId();
                       let holdNode = doc.createElement("div");
                       prNode.appendChild(holdNode);                                          
      			       processAFnDoc_internal(doc, holdNode, fnDocIdVal, ownerid, null, replaceFndocid, function(errorMsg){
                            /*holdNode.style.color="#F65A26";
                            holdNode.style.fontSize="1em";
                            holdNode.style.backgroundColor="black";
                            holdNode.style.maxWidth="202px";
                            holdNode.style.fontFamily='"Open Sans",Sans-serif';
                            holdNode.style.fontSize="15px";                            
                            holdNode.innerHTML = "Hack Jakcet Protected Content";*/
                            holdNode.innerHTML = "<div style='width:380px;text-align: center;line-height: normal; padding-bottom: 3pt;'>\
<p><span style='text-align: center; font-family: Calibri Sans-serif; color: #7f7f7f;  font-weight: bold; font-size: 18pt;'>HackJacket Protected Content</span></p>\
<p style='text-align: center;font-family: Calibri Sans-serif; color: #595959;  font-weight: bold; font-size: 12pt;'><span>The author has <U>not</U> provided you with access permission.</span></p>\
</div>"
                       });                      
                   }
                   else
                   {
                       isReplaceOriText = false;
                   }
  			    };
  			    
  			    if(isReplaceOriText == true)
  			    {
  			        var nextxtNode = doc.createTextNode(oriTxt);
  			        prNode.appendChild(nextxtNode);  			    
                    prNode.removeChild(txtnode);
                }
                else
                {
                    prNode.removeChild(txtnode);
                }
               
  			}              			
            //prNode.appendChild(containerDiv);
            //__SetBorderOfParentNode(containerDiv);
        }}
        catch(err)     
        {
           alert(err);
        }
     }
     
     self.preQuit(doc);
  };

  function sepcialDecrypt_1(prNode, txtNode, fndocid)
  {
     var domainFilter = {
            "^https://mail\.google\.com/mail/.*(inbox|drafts|sent)$":function(prNode, txtNode, fndocid){            
            let trnode = null;
            try
            {
                trnode = ECHelperNS.getAncestorNodeByTagName("TD", prNode);               
            }
            catch(err)
            {
                //alert(err);
                return false;
            }
            let doc = prNode.ownerDocument;            
            let imgPrnode = trnode.nextSibling;
            if(imgPrnode.hasInsertedFnClipImage === undefined)
            {
                imgPrnode.hasInsertedFnClipImage = false;
            }
            else if(imgPrnode.hasInsertedFnClipImage == false)
            {
                imgPrnode.hasInsertedFnClipImage = true;
                let clipsImageFilePath = ECHelperNS.getFilePathOfChromeUrl("chrome://webpagesvr/content/images/clips.PNG");
                let clipsimageDataB64 =  ECHelperNS.generateDataURIByFileName(clipsImageFilePath, "image/png");  
                let imgNode = doc.createElement('img');                
                imgNode.setAttribute("src", clipsimageDataB64);
                if(imgPrnode.firstChild == null)
                {
                    imgPrnode.appendChild(imgNode);
                }
                else
                {
                    imgPrnode.insertBefore(imgNode, imgPrnode.firstChild);
                }
            }             
            return true;
        },
     };

     for(let key in domainFilter)
     {
        let regobj = new RegExp(key);
        if(regobj.test(prNode.ownerDocument.location))
        {
            return domainFilter[key](prNode, txtNode, fndocid);
        }
     }
     return false;
  }
  
  function __SetBorderOfParentNode(prNode)
  {
     prNode.style.borderWidth="2px";
     prNode.style.borderColor="orange";
     prNode.style.borderStyle="solid";
  }


  function creatinnerHTMLOfPrNode(imgFileIconData, docName, downLoadImgData, openAsWebImgData, popDocInfoImgData, docinfo)
  {
      let divInnerHTMLTemplate = "<div align='left' style='margin-top:2px;height:34px;width:216px;background-Color:white;border:2px solid #C4C4C4;border-Radius:5px'>\
                                <div style='height:27px;margin-top:7px;display:inline-block'>\
                         <img style='width:15px;height:15px' src='#imgData'>\
                       </div>\
                       <div style='display:inline-block;overflow:hidden;font-family:Arial;font-size:10px;color:#1E66EB; vertical-align:top;margin-top:10px; width:130px; max-width:130px'>\
                       <span style='width:90px; max-width:90px'>\
                          #docName\
                       </span>\
                       <span style='width:40px; max-width:40px; float:right; text-align:right'>\
                          #docSize\
                       </span>\
                       </div>\
                       <div style='height:27px;margin-top:7px;display:inline-block'>\
                          <img style='width:18px;height:18px' src='#downLoadImgData'>\
                       </div>\
                       <div style='height:27px;margin-top:7px;display:inline-block'>\
                          <img style='width:18px;height:18px' src='#openAsWebImgData'>\
                       </div>\
                       <div style='height:27px;margin-top:7px;display:inline-block'>\
                          <img style='width:18px;height:18px' src='#popDocInfoImgData'>\
                       </div>\
                       </div>";
      let divInnerHTML = divInnerHTMLTemplate.replace('#imgData', imgFileIconData);
      divInnerHTML = divInnerHTML.replace('#docName', docName);
      divInnerHTML = divInnerHTML.replace('#docSize', (function(docSize){
          if(docSize < 1024)
          {
              return docSize + "B"
          }
          else if(docSize < 0x100000)
          {
              return (docSize / 1024.0).toFixed(1) + "KB"
          }
          else
          {
              return (docSize / 1048576.0).toFixed(1) + "M"
          }
      }(docinfo[FNDOCINFO_E.docSize])));
      divInnerHTML = divInnerHTML.replace('#downLoadImgData', downLoadImgData);
      divInnerHTML = divInnerHTML.replace('#openAsWebImgData', openAsWebImgData);   
      divInnerHTML = divInnerHTML.replace('#popDocInfoImgData', popDocInfoImgData);
      return divInnerHTML;
  }

  function creatinnerHTMLOfInfomration(fnlogImgData)
  {
      let divInnerHTMLTemplate = 
        "<span style='display:inline-block;line-height:0px;padding:10px 0px 0px 10px;'>\
		    <span style='width:auto;overflow:hidden;height:20px;display:inline-block;padding:0px;margin:0px;'>\
	        	<img src='#fnlogImgData' style='height:20px'/>\
	        </span>\
	    	<span style='height:20px;display:inline-block;padding:0px;margin:0px;font-size:15px;font-weight:bold;color:#C4C4C4;font-family:helvetica;vertical-align:middle;'>FN Document Information</span>\
		</span>\
		<ul style='margin:0px 10px 0px 10px;width:260px;height:180px;background-color:white;list-style-type:none;overflow:auto'>\
		</ul>";
	  let divInnerHTML = divInnerHTMLTemplate.replace('#fnlogImgData', fnlogImgData);
      return divInnerHTML;
  }
  
  function __addFnDownloadHerf(prNode, downloadlink, fnDocId, docName, docinfo, isSDF)
  {
     getIconPathByFileName_ForWebPage(null, docName, function(imgFilePath){        
        let imageDataB64 =  ECHelperNS.generateDataURIByFileName(imgFilePath, "image/png");                
        let downloadImageFilePath = ECHelperNS.getFilePathOfChromeUrl("chrome://webpagesvr/content/images/download.PNG");
        let downloadimageDataB64 =  ECHelperNS.generateDataURIByFileName(downloadImageFilePath, "image/png");        
        let openAsWebImageFilePath = ECHelperNS.getFilePathOfChromeUrl("chrome://webpagesvr/content/images/openAsWeb.PNG");
        let openAsWebimageDataB64 =  ECHelperNS.generateDataURIByFileName(openAsWebImageFilePath, "image/png");        
        let popDocInfoimageFilePath = ECHelperNS.getFilePathOfChromeUrl("chrome://webpagesvr/content/images/information.PNG");
        let popDocInfoimageDataB64 =  ECHelperNS.generateDataURIByFileName(popDocInfoimageFilePath, "image/png");        

        
        let innhtmlString = creatinnerHTMLOfPrNode(imageDataB64, docName, downloadimageDataB64, openAsWebimageDataB64, popDocInfoimageDataB64, docinfo);
        prNode.addEventListener("DOMNodeInserted", function(evt){
            let doc = prNode.ownerDocument;
            let imgs = ECHelperNS.getNodesByXpath2(doc, prNode, ".//IMG");
            let downloadImg = imgs[1];
            let openImg = imgs[2];
            let popInfo = imgs[3];
            downloadImg.addEventListener("click", function(evt){                
                doc.defaultView.location.href=downloadlink;
            }, false);
            
            openImg.addEventListener("click", function(evt){
                if(prNode.imagelinke !== undefined && prNode.pkey !== undefined)
                {
                    //Downdata by ajax
                    var myid = ECHelperNS.getOwnerId();
                    var fndocProcessor = new processAFnDoc_Gneral(fnDocId, myid);
                    fndocProcessor.on("downloaded", function(gotBlob){
                        prNode.removeChild(prNode.firstChild);
                        if(docinfo[0] == "image")
                        {
                            __addprotectedimage(doc, prNode, prNode.pkey, gotBlob, isSDF, fnDocId);
                        }
                        else
                        {
                            __addoriginalimage(doc, prNode, prNode.pkey, gotBlob);
                        }
                    });
                    fndocProcessor.downloadFnDoc(prNode.imagelinke);
                }
                else
                {
                    var myid = ECHelperNS.getOwnerId();
                    new WebService.DocServer().openAsWeb(fnDocId, myid);
                }
            }, false);
            popInfo.addEventListener("click", function(evt){
                let divobj = doc.createElement("div");
                divobj.setAttribute("style", "position:absolute;width:320px;height:230px;border-radius:5px;border-width:0px;background-color:#3B3B3B;z-index:9999")
                let fnlogopath = ECHelperNS.getFilePathOfChromeUrl("chrome://webpagesvr/content/images/FNLogo.PNG");
                let fnlogoimageDataB64 =  ECHelperNS.generateDataURIByFileName(fnlogopath, "image/png");
                divobj.innerHTML = creatinnerHTMLOfInfomration(fnlogoimageDataB64);
                divobj.setAttribute("tabindex", "-1");//Make onblur can work
                divobj = doc.body.appendChild(divobj);   
                divobj.focus();                
                divobj.style.left = prNode.offsetLeft + prNode.scrollLeft + "px"; 
                divobj.style.top = prNode.offsetTop + prNode.clientHeight + prNode.scrollTop + "px";
                let ul = ECHelperNS.getNodesByXpath2(doc, divobj, ".//UL")[0];                
                divobj.addEventListener("blur", function(evt){
                    divobj.parentNode.removeChild(divobj);
                }, false);

                let docProc = new processAFnDoc_Gneral(fnDocId, ECHelperNS.getOwnerId());
                docProc.on("getDocInform", function(responseData){                    
                    for(let count = 0; count < responseData.length; ++count)
                    {
                        var name = responseData[count].firstName + " " + responseData[count].lastName + " (" + responseData[count].userName +")";
                        let liobj = doc.createElement("li");
                        liobj.innerHTML = name;                        
                        ul.appendChild(liobj);
                    }
                });
                docProc.getDocInform();
            },false);
        },false);
        prNode.innerHTML = innhtmlString;        
     });       
  }

  window.FN__addFnDownloadHerf_Extern = __addFnDownloadHerf;
    
  function __setFileImageTmOut(plg, pkey, tempfilename)
  {
        try
	    {
		    var FNJSAPICaller = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
	                            createInstance(Components.interfaces.IFNWebSvrJSHelper);
            var myid = ECHelperNS.getOwnerId();
	        FNJSAPICaller.setImageFile(plg, myid, pkey, tempfilename);        
	    }
	    catch(Err)	           
	    {
	        alert(Err);
            ECHelperNS.sendError(Err, (new Error()).fileName, (new Error()).lineNumber);
	    }
  }
  
  
  function __addprotectedimage(doc, prNode, pkey, blob, isSDF, fndocid)
  {
     //dump blob into a temporary files
    var tempfilename = ECHelperNS.dumpBlobTopTempFile(blob);

    //Insert an plugin and set fne into the plugin
    var plg = null;
    plg = doc.createElement("object");
	plg.setAttribute("type", "application/fn-protectedimage-proxy");	
	plg.setAttribute("width", "100");
	plg.setAttribute("height", "100");	
    plg.setAttribute("isStartTimer", "false");
    plg.setAttribute("id", Math.random() * 100000);

    var myid = ECHelperNS.getOwnerId();
    plg.setAttribute("ownerid", myid);
    plg.setAttribute("FnimageFileName", tempfilename);
    plg.setAttribute("Fnkey", pkey);
    plg.setAttribute("isSDF", isSDF.toString());
    plg.setAttribute("fnDocId", fndocid);

    plg.addEventListener("DOMAttrModified", function(evt){
        if(evt.attrName == "fnpluginwindow")
        {
            let winhandle = evt.newValue;            
            ECHelperNS.postMsgToWindow(parseInt(winhandle), 0x410, 0, 0);
        }
		
    }, false);
    
	prNode.appendChild(plg);		
  }
  
  NP.getPlainImageFile = function(pkey, blob)
  {
	 var tempfilename = ECHelperNS.dumpBlobTopTempFile(blob);
     let aPlainTextFNCipherCombiner = Cc["@fntechnologies.com/firefoxhelper/plaintextfnciphercombiner;1"].
                         createInstance(Ci.IPlainTextFNCipherCombiner);
     let sfile = Components.classes["@mozilla.org/file/directory_service;1"].
		   getService(Components.interfaces.nsIProperties).
		   get("Home", Components.interfaces.nsIFile);
     sfile.append("Application Data");
     sfile.append("EcExtensionTemp");

     //sfile.append("fnePlain.data");
     //sfile.createUnique(sfile.NORMAL_FILE_TYPE, 600);

     var outfilename = new Object();
     let isok = aPlainTextFNCipherCombiner.fneDecodeFileWithMe(tempfilename, pkey, sfile.path, outfilename);
     if(isok == true)
     {
        let sfileParentDir = sfile.parent;
        sfile.append(outfilename.value);
        sfileParentDir.append("fnePlain.data");
        sfileParentDir.createUnique(sfile.NORMAL_FILE_TYPE, 600);        
        sfile.copyTo(null, sfileParentDir.leafName);
        return "resource://webpagesvrtemp/" + sfileParentDir.leafName;
	 }
	 return "";
  }
  
  function __addoriginalimage(doc, prNode, pkey, blob)
  {
     //dump blob into a temporary files 
     let imgRscName = NP.getPlainImageFile(pkey, blob);	 
     if(imgRscName != "")
	 {
        imgobj = doc.createElement("img");
        imgobj.setAttribute("src", imgRscName);		
		prNode.appendChild(imgobj);    
     
     }
  }
  

  function setContentOfRTE_V2(prNode, RTEobj, ownerId, pkey, msgEncodedTxt)
  {
      RTEobj.setAttribute("ownerid", ownerId);
      RTEobj.setAttribute("FnEnMsg", msgEncodedTxt);
      RTEobj.setAttribute("Fnpkey",  pkey);

      RTEobj.addEventListener("DOMAttrModified", function(evt){
        if(evt.attrName == "fnpluginwindow")
        {
            let winhandle = evt.newValue;
            ECHelperNS.postMsgToWindow(parseInt(winhandle), 0x410, 0, 0);
        }
      }, false)

      prNode.appendChild(RTEobj);
  }
  
  const default_RTE_width = "500px";
  const default_RTE_height = "200px";
  
  function getTrainedFNRTESize(doc)
  {
  	var ret_val = {"width":default_RTE_width,"height":default_RTE_height};
    try
    {
	    if(doc.domain === undefined || doc.domain == null || doc.domain == "")
	    {
	        return ret_val;
	    }

	    
	    ECHelperNS.dataDBOper_v2("SELECT FNRTE_width, FNRTE_height FROM webpage_decrypt_FNRTE WHERE RegExp(webpageURL, :docdomain);",
	                             [{docdomain:doc.domain}],
	                             function(rowResult){
	                                
	                                if(rowResult != null)
	                                {
	                                		let araw = rowResult.getNextRow();
	                                		if(araw )
	                                		{
	                                    	ret_val.width  = araw.getResultByName("FNRTE_width");
	                                    	ret_val.height = araw.getResultByName("FNRTE_height");
	                                    }
	                                }
	                             },
	                             true,
	                             "webdata",
	                             false);	
	  }
	  catch(err)
	  {//log err
	  }
		return ret_val;                             
  }

  function replaceFndocid(doc, prNode, docType, ownerId, pkey, blob, fnDocIdVal, docName, downloadlink, docinfo, isSDF)
  {
     if(docType == 'text' || docType == 'text_plain')
     {
          oFReaader = new FileReader();
    	  oFReaader.onload = function(oFRevent)
    	  { 
    	    var msgEncodedTxt = oFRevent.target.result;	    	     

            if(docType == 'text_plain')
            {
                let aPlainTextFNCipherCombiner = Cc["@fntechnologies.com/firefoxhelper/plaintextfnciphercombiner;1"].
                         createInstance(Ci.IPlainTextFNCipherCombiner);
                let outstring = new Object();
                let isok = aPlainTextFNCipherCombiner.fneDecodeTextWithMe(msgEncodedTxt, pkey, outstring);
                if(isok == true)
                {
                    prNode.innerHTML = outstring.value;
                }
            }
            else
            {
                var RTEobj = doc.createElement("object");
        	    var aTrainedFNRTESize = getTrainedFNRTESize(doc);
                RTEobj.setAttribute("width", aTrainedFNRTESize.width );
                RTEobj.setAttribute("height", aTrainedFNRTESize.height);
               
                RTEobj.setAttribute("type", "application/fn-richeditor-proxy");	           
                var idv = "RTE_" + Math.floor(Math.random() * 10000);
                RTEobj.setAttribute("id", idv);                     
               
                var RTEParam_Readonly = doc.createElement("param");
                RTEParam_Readonly.setAttribute("name", "create_param");
                RTEParam_Readonly.setAttribute("value", "&winmode=readonly");
                RTEobj.appendChild(RTEParam_Readonly);
               
               
                msgEncodedTxt = btoa(msgEncodedTxt);	           	             
                msgEncodedTxt = "BEGIN_FN_SECURE_MESSAGE_" + msgEncodedTxt + "_END_FN_SECURE_MESSAGE";	           	           
                //setTimeout(setContentTmOut, 1000, RTEobj, ownerId, pkey, msgEncodedTxt);

                prNode.style.border="5px solid #cccccc";
                prNode.style.borderRadius="5px";
                prNode.style.width = aTrainedFNRTESize.width;                                
               
                setContentOfRTE_V2(prNode, RTEobj, ownerId, pkey, msgEncodedTxt);
            }
    	 }
    	 oFReaader.readAsBinaryString(blob);	 
        
     }   
     else if(docType == 'file')
     {        
        //Add file download to prNode
        __addFnDownloadHerf(prNode, blob, fnDocIdVal, docName, docinfo);
     }
     else if(docType == 'image' || docType == 'image_plain')
     {        
        __addFnDownloadHerf(prNode, downloadlink, fnDocIdVal, docName, docinfo, isSDF);
        prNode.imagelinke = downloadlink;        
        prNode.pkey = pkey;
     }
  }
  
  Processor_FnDocIdProto.process = function(doc)
  {
      if(this.preEnter(doc) == false)
      {
      	return;
      }
     
      setTimeout(this.processBusiness, 1, this, doc);      
      
      
  }  
  NP.RegistProcessorToSys(new Processor_FnDocId());

  
}(ECProcessorNS));

