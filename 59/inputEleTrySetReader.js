let SETREADERFORANINPUT = {};
(function(NP){
    //Add Event listener about FnInputEleFocus to know an input element is focused
    document.addEventListener("FnInputEleFocus", function(evt){
        let inputobj = evt.target;
        isShowAddReader(inputobj);
    },false);

    function isShowAddReader(inputobj)
    {
        let doc = inputobj.ownerDocument;
        //Local file don't toggle
        if(doc.domain === undefined || doc.domain == "")
        {
            return false;
        }
        
        Components.utils.import("resource://webpagesvrmoudleLoader/webpgjs/origianlEditorToggleManager.jsm");
        let anOETController = g_OETManager.find_editorHandler(inputobj);
	
        if(anOETController != null && 
           anOETController.initialized == true && 
		   !g_OETManager.is_fn_integrating_Editor(inputobj)&&
		   
           //doc.m_FN_receiptsObj === undefined 
           inputobj.currentReaders === undefined)
        {
	    inputobj.currentReaders = {};
            if(doc.wrappedJSObject.FnExtensionTrainedRemotePage == true)
            {
                if(inputobj.wrappedJSObject.fnhookedFlag === undefined)
                {
                    let evt = doc.createEvent("CustomEvent");
                    evt.initCustomEvent("FnExtensionNotifyTrainedRemotePage", true, false, null);
                    inputobj.setAttribute("FnExtensionNotifyTrainedRemotePage_Config", JSON.stringify(
                        {functionName:"hookKeyDownEvent", param:null}
                    ));
                    inputobj.dispatchEvent(evt);
                    anOETController.on("OETControllerRemove", function(arg){
                        if(inputobj.currentReaders)
                        {
                            delete inputobj.currentReaders;
                        }
                    });
                }
            }            

            setTimeout(function(){
                if(inputobj.wrappedJSObject.fnhookedFlag === undefined)
                {
				    delete inputobj.currentReaders;
                    anOETController.on("OETControllerRemove", function(arg){
                        if(inputobj.currentReaders)
                        {
                            delete inputobj.currentReaders;
                        }

                        FNCANVASOPERNP.removeAButtonOnFnDrawLayer_V2(inputobj, "fnEncButton");                        
                    });
                    toggleSetReaderUI(inputobj);
                    //Add a button on fndrawlayer
                    FNCANVASOPERNP.addAButtonOnFnDrawLayer_V2(inputobj, "fnEncButton");  
                }                
           }, 100);
        }
        return false;         
    };

    function toggleSetReaderUI(inputobj, oldReadersMapJsonString)
    {
        inputobj.setAttribute("fn-toggle-option", "SetReader");
        let URI = "toggle_SetReader.html";
        if(oldReadersMapJsonString !== undefined && oldReadersMapJsonString.length > 0)
        {
            URI += "?reqData=" + oldReadersMapJsonString;
        }
        inputobj.setAttribute("fntoggledURL", URI);
        inputobj.setAttribute("fntoggledStyles", JSON.stringify({
            frameWidth:'420px',frameHeight:'220px', aroundBk:'transparent'
        }));
        let toggleBussinessobj = Components.classes["@fntechnologies.com/webpgjsCOM/toggleBussiness;1"].
	                                          createInstance(Components.interfaces.nsIToggleBussiness);
        toggleBussinessobj.toggledPlg = inputobj;
	    toggleBussinessobj.toggle(inputobj);
    }

    NP.setReadersForWebpage = function(doc, params, callback)
    {
        //This object is the same as g_datas.receiptsEmail_OwnerId
        let settedReaders = params;
        if(doc.fntoggledPlg != null)
        {
            let inputobj = doc.fntoggledPlg;
            inputobj.removeAttribute("fn-toggle-option");
            inputobj.removeAttribute("fntoggledURL");
            inputobj.removeAttribute("fntoggledStyles");

            inputobj.currentReaders = settedReaders;
            setTimeout(function(){
                doc.fntoggledPlg.focus();
            }, 10);
        }
    }

    NP.toggleSetReaderUI = function(inputobj)
    {
        if(inputobj.currentReaders !== undefined)
        {
            let oldReadersMapJsonString = escape(JSON.stringify(inputobj.currentReaders));
            toggleSetReaderUI(inputobj, oldReadersMapJsonString);
        }
    }

    NP.removeEncButton = function(doc, params, callback)
    {
        if(doc.fntoggledPlg != null)
        {
            let inputobj = doc.fntoggledPlg;
            FNCANVASOPERNP.removeAButtonOnFnDrawLayer_V2(inputobj, "fnEncButton");
        }
    }
}(SETREADERFORANINPUT));

