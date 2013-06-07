// these functions respond the InFocus event of an input box. An RTE is popped up to
// fill the input box
Components.utils.import("resource://webpagesvrmoudleLoader/webpgjs/origianlEditorToggleManager.jsm");
Components.utils.import("resource://browsercontent/FnGlobalObject.jsm");
let CONTENTATTACHMENT = {};
(function(NP){
    //Add Event listener to FnInputEleFocus
    document.addEventListener("FnInputEleFocus", function(evt){
        //setTimeout(function(evt){
		let inputobj = evt.target;
		if(showContentAttachmentOrNot(inputobj) == true)
		{
		    if(inputobj.lastpopContentAttachmentTime === undefined)
			{
			    showContentAttachment(inputobj);
				inputobj.lastpopContentAttachmentTime = (new Date()).getTime();
			}
			else
			{
			    let curTime = (new Date()).getTime();
				if(curTime - inputobj.lastpopContentAttachmentTime < 300)
				{
					return;
				}
				showContentAttachment(inputobj);
				inputobj.lastpopContentAttachmentTime = curTime;
			}
			
		}
		//},10000,evt)
    },false);
    
    // this function is called when "submit" is clicked on the content-attachment page
    NP.afterSubmit = function(doc, params, callback)
    {
        let inputobj = doc.fntoggledPlg;
	    inputobj.focusBySubmit= true;
    };

    function showContentAttachmentOrNot(inputobj) {
        let doc = inputobj.ownerDocument;
        //Local file, no need to show
        if(doc.domain === undefined || doc.domain == "")
        {
            return false;
        }
        
        let coveredBrowser = ECHelperNS.getCurrentTabBrowserFromHTMLDoc(inputobj.ownerDocument);
		let tempPropmt = coveredBrowser.parentNode.firstChild.nextSibling;
		while(tempPropmt != null)
		{
			if(tempPropmt.getAttribute("FnToggledPrompt") == "true")
			{
			    return false;
			}
			tempPropmt = tempPropmt.nextSibling;
		}
		
        if (inputobj.getAttribute("fn-toggle-option") != "FNRTE") {
            return false;
        }
        // content attachment page is not shown if the focus is caused by
        // the fill-back of content-attachment page
        // because when a "submit" on the page is clicked the focus is
        // regained by the widget but in this case the RTE should not be
        // popped again
		//if (inputobj.focusBySubmit !== undefined && inputobj.focusBySubmit == true) {
		//	inputobj.focusBySubmit = false;
		//	return false;
		//}

        if(inputobj.currentContAtta === undefined)
        {
            return true;   
        }            
        return false;         
    };

    function showContentAttachment(inputobj)
    {
        //inputobj.setAttribute("fn-toggle-option", "FNRTE");
	if (g_OETManager.is_fn_integrating_Editor(inputobj)  ||  (inputobj.wrappedJSObject.fnhookedFlag !== undefined) ) {
	    inputobj.setAttribute("fntoggledURL", "toggle_withWebPageHavingReceipts.html");
	    inputobj.setAttribute("fntoggledStyles",JSON.stringify({frameWidth:"448px", frameHeight:"395px"}));
        } else {
            inputobj.setAttribute("fntoggledURL", "toggle_withWebPageNoReceipts.html");
            inputobj.setAttribute("fntoggledStyles",JSON.stringify({frameWidth:"448px", frameHeight:"433px"}));
        }
        let toggleBussinessobj = Components.classes["@fntechnologies.com/webpgjsCOM/toggleBussiness;1"].
	                                          createInstance(Components.interfaces.nsIToggleBussiness);
		
		if(inputobj.ownerDocument.m_FN_receiptsObj === undefined)
		{
		    toggleBussinessobj.toggledPlg = inputobj;
		    toggleBussinessobj.toggle(inputobj);
			return;
		}
        // set the value or innerHTML back so they can be handled by
        // the following popped up RTE correctely
        var outstr="";
        var docids = "";
        var RTEContentObj = FnGlobalObject.getObject("RTEContent", inputobj);
		if(inputobj.nodeName == "IFRAME") {
			var fileCom = Components.classes["@fntechnologies.com/fileExplorer/fileSelectorCom;1"].getService().wrappedJSObject;
			if(fileCom) {
				var inputobjTmp = fileCom.getToBox(inputobj.ownerDocument);
				RTEContentObj = FnGlobalObject.getObject("RTEContent", inputobjTmp);
			}
		
		}

        if (RTEContentObj) {
            docids = RTEContentObj[0].name;
        }
        for(var counter = 0; counter < docids.length; ++counter) {
            outstr += "HJContentID:" + docids[counter] + " ";
        }

        if(outstr.length > 0)
        {
           outstr = "HackJacket Protected #spliter Start communicating securely (its free!) #spliter Go To: http://download.HacketJacket.com #spliter "+outstr;
        }

        if(inputobj.nodeName == 'TEXTAREA' || inputobj.nodeName == 'INPUT') {
            outstr = outstr.replace(/#spliter /gm, "");
            inputobj.value = outstr;
        } else if(inputobj.nodeName == 'IFRAME') {
            outstr = outstr.replace(/#spliter /gm, "");
            inputobj.contentDocument.body.innerHTML = outstr;
        }
		else if(inputobj.nodeName == 'DIV') {
            outstr = outstr.replace(/#spliter /gm, "");
            inputobj.innerHTML = outstr;
        }

        toggleBussinessobj.toggledPlg = inputobj;
        toggleBussinessobj.toggle(inputobj);
    }

    NP.setContAttaForWebpage = function(doc, params, callback)
    {
        let contentAttach = params;
        if(doc.fntoggledPlg != null)
        {
            let inputobj = doc.fntoggledPlg;
            inputobj.removeAttribute("fn-toggle-option");
            inputobj.removeAttribute("fntoggledURL");
            inputobj.removeAttribute("fntoggledStyles");

            inputobj.currentContAtta = contentAttach;
        }
    }
}(CONTENTATTACHMENT));

