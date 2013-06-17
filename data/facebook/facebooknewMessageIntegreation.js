(function(){
    getNodesByXpath = function(doc, aExpr)
	{
	   var nodesSnapshot = doc.evaluate(aExpr, doc.documentElement, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null);
	   var found = [];
	   for(var i=0; i < nodesSnapshot.snapshotLength; i++)
	   {
		  found.push(nodesSnapshot.snapshotItem(i));
	   }
	   return found;
	};
	
    var docurl = document.URL;
	var restoreCallback = null;
	function locateTheButton()
	{
	    if(restoreCallback)
		{
			restoreCallback();
			restoreCallback = null;
		}
        if(docurl == "https://www.facebook.com/messages/new")
		{
			var butobjs = getNodesByXpath(document, '//input[@value="Send" and @type="submit"]')
			if(butobjs.length > 0)
			{
			    //alert("dfsdf");
			    var butobj = butobjs[0];				
				//try{
				butobj.parentNode.addEventListener("mouseup", function(evt){				    
					var editobjs = getNodesByXpath(document, '//textarea[@fn-integrating="emailbody" and @name="message_body"]');					
					for(var i=0; i<editobjs.length ;++i)
					{
					    var aeditobj = editobjs[i];	                        
						var orioption = aeditobj.getAttribute("fn-toggle-option");
						if(orioption != null)
						{
						    aeditobj.removeAttribute("fn-toggle-option");	
						    restoreCallback = function()
							{
								try
								{
									aeditobj.setAttribute("fn-toggle-option", orioption);
								}								
								catch(r)
								{
									alert("r  " + aeditobj);
								}									
								
							};
						}
						//alert("dfsdf111111");
					}
				}, true);
				//}
				//catch(e){alert(e)}
			}
			else
			{
			    setTimeout(locateTheButton, 1000);
			}
		}		
	}
	locateTheButton();
	setInterval(function(){
	    if(docurl != document.URL)
		{		    
			docurl = document.URL;
			locateTheButton();
		}
	}, 1000);	
	
	function locateTipDiv()
	{
	    try
	    {
	        var tooltipSS = document.body.lastChild;
	        var classAttr = tooltipSS.getAttribute("class");	    
	        for(var counter = 0; counter < 10; ++counter)
	        {
	            classAttr = tooltipSS.getAttribute("class");	        
	            if(classAttr != null && classAttr == "uiContextualLayerPositioner uiLayer uiContextualLayerPositionerFixed hidden_elem")	                                                  
	            {
	                return tooltipSS;
	            }
	            tooltipSS = tooltipSS.previousSibling;
	            if(tooltipSS == null)
	            {
	                return null;
	            }
	        }	    
	        return null;
	     }
	     catch(err)
	     {
	        return null;
	     }
	}
	
	function fillRecipientsTo_fnrecipients(the_A_Node)
	{
	    var target = the_A_Node.m_fnEditObject;
	    if(the_A_Node.getAttribute("aria-label") == null)
        {   
            target.m_fnrecipients.push(the_A_Node.innerHTML);
            //alert( target.m_fnrecipients.length);
            return;
        }
        else
        {	 
            
            setTimeout(function(){
                var funobj = null;
                document.body.addEventListener("DOMNodeInserted", funobj = function(evt){	                                        
                    document.body.removeEventListener("DOMNodeInserted", funobj, false);	                                                      
                    //alert(evt.target.textContent);
                    var nameTextNodes = document.evaluate('.//i/following-sibling::div/text()', 
                        evt.target, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null);
                    
                    for(var counter = 0; counter < nameTextNodes.snapshotLength; ++counter)
                    {   
                        target.m_fnrecipients.push(nameTextNodes.snapshotItem(counter).nodeValue);
                    }
                    //alert( target.m_fnrecipients.length);
                }, false)
                var evObj = document.createEvent('MouseEvents');
                evObj.initEvent( 'mouseenter', true, false );
                the_A_Node.dispatchEvent(evObj);	  
                var evObj = document.createEvent('MouseEvents');
                evObj.initEvent( 'mouseover', true, false );
                the_A_Node.dispatchEvent(evObj);	                                                                   
            }, 300);	
        }
	}
	
	function afterSendInvitationHandle(editobj)
	{
	    this.m_editobj = editobj;
	    this.handleEvent = function(evt)
	    {
	        var bodyObj = evt.target;	        
	        if(evt.attrName=="fnremotehtmlreq-event-param" && (evt.newValue == "true" || evt.newValue == "false"))
	        {
	            //bodyObj.removeEventListener("DOMAttrModified", this, false);
	            bodyObj.removeAttribute("fnremotehtmlreq-event-param");
	            if(evt.newValue == "true")
	            {
	                var untrustEmailes = bodyObj.getAttribute("fnremotehtmlreq-event-param-subvalue");
	                bodyObj.removeAttribute("fnremotehtmlreq-event-param-subvalue");
    	            {
    	                var transobj = {funname:"AppenddInvitation_ForWebPage", param:untrustEmailes};
                        this.m_editobj.setAttribute("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                  
                        var evtobj = document.createEvent("HTMLEvents");        
                        evtobj.initEvent("fnRemoteHtmlReq-event", true, false);                          
                        this.m_editobj.dispatchEvent(evtobj);
                    }
	            }
	            
	            this.m_editobj.setAttribute("id", "fneditorforfbchat");
	            setTimeout(function(){
	                try
	                {   
	                    var inEditobj = document.getElementById("fneditorforfbchat");
	                    if(inEditobj)
	                    {
	                        inEditobj.removeAttribute("id");
	                        inEditobj.m_isRealSendout = true
	                        var keyEvt = document.createEvent("KeyboardEvent");
		                    keyEvt.initKeyEvent("keypress", true, true, null, false, false, false, false, 13, 13);			            		                   		                
		                    inEditobj.dispatchEvent(keyEvt);
		                    var faketoobj = document.getElementById("facktofnobject");
		                    if(faketoobj)
		                    {
		                        faketoobj.parentNode.removeChild(faketoobj);
		                    }
		                }
		            }
		            catch(err){alert(err)};
		        }, 1300);
	        }	        
	     }
	}
	
	function chattabDOMAttrModifiedHandle(evt)
	{
	    var temptg = evt.target;	                                	                
        if(evt.attrName == "getemailsofanobject_facebook_forremotewebpage_res")
        {   
            temptg.removeEventListener("DOMAttrModified", chattabDOMAttrModifiedHandle, false);
            temptg.removeAttribute("getemailsofanobject_facebook_forremotewebpage_res");     
            var recipientEmails = JSON.parse(evt.newValue);
            var hiddenTextArea = document.createElement("TEXTAREA");
            hiddenTextArea.style.display = "none";
            hiddenTextArea.setAttribute("id", "facktofnobject");
            hiddenTextArea.value = recipientEmails.join(";");            
            
            temptg.parentNode.appendChild(hiddenTextArea);
            
            {
                var transobj = {funname:"setEditorobjForInivitation_forRemoteWebpage", param:null};
                temptg.setAttribute("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                  
                var evtobj = document.createEvent("HTMLEvents");        
                evtobj.initEvent("fnRemoteHtmlReq-event", true, false);                
                temptg.dispatchEvent(evtobj);
            }
            
            {
                var transobj = {funname:"setReceiptobjForInivitation_forRemoteWebpage", param:null};
                hiddenTextArea.setAttribute("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                  
                var evtobj = document.createEvent("HTMLEvents");        
                evtobj.initEvent("fnRemoteHtmlReq-event", true, false);                
                hiddenTextArea.dispatchEvent(evtobj);
            }
            
            {
                for(var counter = 0; counter < recipientEmails.length; ++counter)
                {
                    var theEmail = recipientEmails[counter];
                    var transobj = {funname:"addReceiptsToAnInput_ForWebPage", param:theEmail};    	        
                    temptg.setAttribute("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                
                    var event = document.createEvent("HTMLEvents");        
                    event.initEvent("fnRemoteHtmlReq-event", true, false);            
                    temptg.dispatchEvent(event);
                }           
            }
            
            document.body.addEventListener("DOMAttrModified", new afterSendInvitationHandle(temptg), false);
            {
                var transobj = {funname:"SendInvitation_ForWebPage", param:null};
                temptg.setAttribute("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                  
                var evtobj = document.createEvent("HTMLEvents");        
                evtobj.initEvent("fnRemoteHtmlReq-event", true, false);                
                temptg.dispatchEvent(evtobj);
            }
        }
	}
	
	function hookEnterEventOfEditObject(aEvent)
	{
	    var target = aEvent.target;	
	    var fntoggleoption = target.getAttribute("fn-toggle-option");
	    if(aEvent.which == 13 && aEvent.shiftKey == false && fntoggleoption != null)
	    {        
	        if(target.m_fnrecipients !== undefined && target.m_fnrecipients.length > 0 && target.m_isRealSendout === undefined)
	        {
	            target.m_ItsToObject.addEventListener("DOMAttrModified", chattabDOMAttrModifiedHandle, false);
	            
	            var transobj = {funname:"getEmailsOfAnObject_facebook_forRemoteWebpage", param:target.m_fnrecipients};    	   	                                 
                target.setAttribute("fnRemoteHtmlReq-event-param", JSON.stringify(transobj));                  
                var evtobj = document.createEvent("HTMLEvents");        
                evtobj.initEvent("fnRemoteHtmlReq-event", true, false);                
                target.dispatchEvent(evtobj);
            }
            if(target.m_isRealSendout === undefined)
            {
	            aEvent.preventDefault();
		        aEvent.stopPropagation();
		    }
		    else
		    {
		        delete target.m_isRealSendout;
		    }
		}
	}
	
	function hookedToggleBackFunctionHandle(evt)
	{
	    var target = evt.target;
	    var keyEvt = document.createEvent("KeyboardEvent");
        keyEvt.initKeyEvent("keypress", true, true, null, false, false, false, false, 13, 13);
        target.dispatchEvent(keyEvt);       
	}
	
	document.addEventListener("fnRemoteHtmlReq-event", function(evt){
	    var target = evt.target;
	    var paramobjJsonstring = target.getAttribute("fnRemoteHtmlReq-event-param");
	    if(paramobjJsonstring)
	    {
	         var paramobj = JSON.parse(paramobjJsonstring);
	         if(paramobj.funname == "userFireClickOnInputElementForWebpage")
	         {  
	            if(target.m_ItsToObject === undefined)
	            {
	                
	                if(target.tagName == "TEXTAREA" && target.getAttribute("onkeydown") != null &&
	                   target.getAttribute("onkeydown").indexOf("window") == 0)
	                {
	                    var prNode = target.parentNode;
	                    for(var count = 0; count < 6; ++count)
	                    {
	                        var clsAttr = prNode.getAttribute("class");
	                        if(clsAttr != null && clsAttr == "fbNubFlyout fbDockChatTabFlyout")
	                        {
	                            target.m_ItsToObject = prNode;
	                            break;
	                        }
	                        prNode = prNode.parentNode;
	                    }
	                    if(target.m_ItsToObject !== undefined)
	                    {   
	                        target.fnhookedFlag = true;
	                        target.parentNode.addEventListener("keypress", hookEnterEventOfEditObject, true);	                        
	                        target.addEventListener("fn_togglebackfinished", hookedToggleBackFunctionHandle, false);
	                        
	                        var nodesSnapshot = document.evaluate('.//a[contains(@class,"titlebarText") and @role="button"]', 
	                                            target.m_ItsToObject, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null);
	                        if(nodesSnapshot.snapshotLength > 0)
	                        {	                            
	                            var the_A_Node = nodesSnapshot.snapshotItem(0);	
	                            the_A_Node.m_fnEditObject = target;
	                            the_A_Node.addEventListener("DOMAttrModified", function(evt){
	                                var tempANode = evt.target;
	                                tempANode.m_fnEditObject.m_fnrecipients = [];
	                                fillRecipientsTo_fnrecipients(tempANode);
	                            }, false);
	                            the_A_Node.m_fnEditObject.m_fnrecipients = [];	                           
	                            fillRecipientsTo_fnrecipients(the_A_Node);
	                        }
	                    }
	                }
	            }
	         }
	    }
	}, true);
}());
