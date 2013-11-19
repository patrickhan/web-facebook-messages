(function(NP){
    function Processor_HackJacket ()
	{
	    this.superclass("Processor_HackJacket");
	}	
	Processor_HackJacket.prototype = new NP.Processor_Base("Processor_HackJacket");	
	Processor_HackJacket.prototype.superclass = NP.Processor_Base;
    Processor_HackJacketProto = Processor_HackJacket.prototype;     
        
    Processor_HackJacketProto.processBusiness = function(self, doc)
    {
        //Filter out the text node having HackJacket Protectedd flag.
        let res = ECHelperNS.getNodesByXpath(doc, "//text()[contains(.,'HJContentID:')]"); 
        let prNode = null;
        for(let counter = 0; counter < res.length; ++counter)
        {
            let txtnode = res[counter];
            if(txtnode.HJ_processed == true || ECHelperNS.nodeIsEditable(txtnode))
            {
               continue; 
            }            
            txtnode.HJ_processed = true;
            if(prNode == txtnode.parentNode)
            {
               continue;
            }
            prNode = NP.trainProcess(txtnode);
            if(prNode == false)
            {
                prNode = txtnode.parentNode;    
            }
            let prNodeTextContent = prNode.textContent;
            //prNodeTextContent = ECHelperNS.removeNonSenseChars(prNodeTextContent);
            let hackJacketPre = ECHelperNS.matchHackJacketFromString(prNodeTextContent);
            let JContentIDs = ECHelperNS.matchHJContentIDFromString(prNodeTextContent);            
            let hackJackettail = ECHelperNS.matchHackJacketTailFromString(prNodeTextContent);
            if(JContentIDs != null)
            {   
                prNode.fnDocIdVals = [];
			
                for(let i = 0; i < JContentIDs.length; i++)
                {
					let fnDocIdVal = JContentIDs[i].substring('HJContentID:'.length);
                    prNode.fnDocIdVals.push(fnDocIdVal);
                    prNodeTextContent = prNodeTextContent.replace(JContentIDs[i], "#fnDocIdVal"+i);
                }
				if(prNode.fnDocIdVals.length > 0)
				{
					prNode.setAttribute("hjcontentid-container", JSON.stringify(prNode.fnDocIdVals));
				}
            }

            if(hackJacketPre != null)
            {  
                for(let i = 0; i < hackJacketPre.length; i++)
                {
                    prNodeTextContent = prNodeTextContent.replace(hackJacketPre, "");
                }

            }

            if(hackJackettail != null)
            {  
                for(let i = 0; i < hackJackettail.length; i++)
                {
                    let fnDocIdVal = hackJackettail[i].substring('HJInvitationID:'.length);                    
                    prNodeTextContent = prNodeTextContent.replace(hackJackettail[i], " #FNHackJackettail ");
                }
                prNode.invitationGuid = hackJackettail[0].substring('HJInvitationID:'.length);
                //Use timer to get invitation
				prNodeTextContent = prNodeTextContent.replace(/#fnDocIdVal\d/gm, "")
                setTimeout(addInvitaionDiv, 1, prNode, prNodeTextContent);                
            }
            
            if(prNode.invitationGuid === undefined && JContentIDs.length > 0)
            {
                for(let i = 0; i < prNode.fnDocIdVals.length; ++i)
                {
                    let fnDocIdVal = prNode.fnDocIdVals[i];
                    prNodeTextContent = prNodeTextContent.replace("#fnDocIdVal"+i, "fndocid:"+fnDocIdVal +"!!##Thie should be on the page, if this lien is on the page, then maybe fnclient is not running,");
                }
                prNode.innerHTML = "";
                let newNode = doc.createTextNode(prNodeTextContent);
                prNode.appendChild(newNode);
            }
            
        }        
    }

    function switchToFnDocid(prNode)
    {
        prNode.innerHTML = "fndocid:"+ prNode.fnDocIdVals.join(' fndocid:');
    }

    function addInvitaionDiv_V2(prNode, prNodeTextContent)
    {
        let isReplaceHTMLofPrNode = false;
        let invitationDIVTemplate = 
                "<div style='width:400px ; text-align: center; line-height: normal; margin-bottom: 0pt' >\
                <p><span style='text-align: center; font-family: Calibri sans-serif; color: #7f7f7f;  font-weight: bold; font-size: 18pt;'>HackJacket Protected Content</span></p>\
                <p><span style='text-align: center;font-family: Calibri; color: #595959;  font-weight: bold; font-size: 12pt;'>#username has HackJacket protected content for you.</span></p>\
                <p><span fnId='ChangeKeyButton' style='cursor: pointer; background-color:#ff6600; color: white; font-size: 16pt;  font-family: Calibri; padding-left:10px; padding-right:10px'>View Content</span></p>\
                <p><span style='text-align: center; font-family: Calibri; color: #7f7f7f;  font-weight: bold; font-size: 10pt;'>#username will automatically be added to your Hack Jacket Secure Friends List</span></p>\
                </div>"
        let name = prNode.m_invitationInfoQuerier.m_username;        
        let invitationDIVText = invitationDIVTemplate.replace("#username", name);//first "#username"
        invitationDIVText = invitationDIVText.replace("#username", name);//second "#username"
        prNodeTextContent = prNodeTextContent.replace("#FNHackJackettail", invitationDIVText)
        prNode.innerHTML = prNodeTextContent;
        isReplaceHTMLofPrNode = true;
        
        if(isReplaceHTMLofPrNode == true)
        {
            let selectedEles = ECHelperNS.getNodesByXpath2(prNode.ownerDocument, prNode, ".//span[@fnId='ChangeKeyButton']");
            if(selectedEles != null && selectedEles.length > 0)
            {
                let button = selectedEles[0];
                button.addEventListener('click', function(evt){
                    //Accept the invitation
                    try
                    {
                        var serviceName = {serviceProviderName:"", handleName:"", guid: ""};
                        var fileCom = Components.classes["@fntechnologies.com/fileExplorer/fileSelectorCom;1"].getService().wrappedJSObject;
                        if(fileCom) {
                            var temp = fileCom.getServiceProviderAndHandle(prNode.ownerDocument);
                            serviceName.serviceProviderName = temp.serviceProviderName; //fu "facebookName"
                            serviceName.handleName = temp.handleName;   //"John Smith";
                            var guids = fileCom.getGuid(prNode.invitationGuid);
                            if(guids.length > 0) {
                                serviceName.guid = guids[0];
                            }
                        }
//                        alert("serviceProviderName:"+serviceName.serviceProviderName+"\nhandleName:"+serviceName.handleName+"\nguid:"+serviceName.guid);
                        var FNJSAPICaller = Components.classes["@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1"].
								                createInstance(Components.interfaces.IFNWebSvrJSHelper);
                            //send command to client
                            //invitation id, service provider name, handle name                            
							FNJSAPICaller.acceptInvitationEx("HJInvitationID:" + prNode.invitationGuid, serviceName.serviceProviderName, serviceName.handleName, serviceName.guid);        
                    }
					catch(Err)	           
					{
						alert(Err);
					}
									  
									  
					prNode.innerHTML = "fndocid:"+ prNode.fnDocIdVals.join(' fndocid:');

                }, false);
            }
        }
    }
    
/*"<div>\
<span>HackJacket Protected Content</span>\
<span>#username has HackJacket protected content for you.</span>\
<div style='background-Color:orange' fnId='ChangeKeyButton'>View Content</div>\
<span>#username will automatically  be added to your Hack Jacket Secure Friends List</span>\
</div>";*/
    function addInvitaionDiv(prNode, prNodeTextContent)
    {
        let nameFinder = new RegExp('\\(([0-9]*)\\)', 'g');
        let result = nameFinder.exec(prNode.invitationGuid);        
        if(result != null)
        {
            let ownerid = parseInt(result[1]);
            if(prNode.fnDocIdVals === undefined || prNode.fnDocIdVals.length == 0)
            {
                return;
            }
            
            function invitationInfoQuerier(prNode, ownerid)
            {
                this.m_prNode = prNode;
                this.m_fnDocid = prNode.fnDocIdVals[0];
                this.m_ownerid = ownerid;
                
                this.m_prNodeTextContent = prNodeTextContent;
                this.start = function()
                {
                    this.docProcessorObj = new processAFnDoc_Gneral(this.m_fnDocid, ECHelperNS.getOwnerId())
                    let self = this;
                    this.docProcessorObj.on("getKeyByDocId", function(gotkeyResult){                          
                        switchToFnDocid(self.m_prNode);
                    })
                    this.docProcessorObj.on("error", function(errorMsg){                        
                        //Check local database   
                        ContactModule.getPublicKeyByOwnerId(self.m_ownerid, function(res){
                            if(res != null && res.length > 0)
                            {                                
                                switchToFnDocid(self.m_prNode);
                            }
                            else
                            {                                
                                self.m_userInfoQuerier = new UserInfoRTOper_Gneral(self.m_ownerid);
                                self.m_userInfoQuerier.on("getUserInfo", function(res){
                                    if(res.length > 0)
                                    {
                                        self.m_username = res[0].firstName + "  " + res[0].lastName;
                                        let email = res[0].emailAddress;
                                        
                                        self.m_prNode.invitationGuid = self.m_prNode.invitationGuid.replace("(" + self.m_ownerid.toString() +")", 
                                                                             "(" + btoa(email) + "," 
                                                                              + btoa(self.m_username) +")");
                                        addInvitaionDiv_V2(self.m_prNode, self.m_prNodeTextContent);
                                    }
                                })
                                self.m_userInfoQuerier.on("error", function(error){
                                    alert(error.msg)
                                })
                                self.m_userInfoQuerier.getUserInfo();
                            }
                        })
                        
                    })
                    this.docProcessorObj.getKeyByDocId(true);
                    setTimeout(function(thenode){
                        delete thenode.m_invitationInfoQuerier;
                    }, 10000, this.m_prNode)
                }
            }
            prNode.m_invitationInfoQuerier = new invitationInfoQuerier(prNode, ownerid);
            prNode.m_invitationInfoQuerier.start();
        }
        
    }
    
    Processor_HackJacketProto.process = function(doc)
    {
        if(this.preEnter(doc) == false)
        {
       	  return;
        }
        let self = this;
        setTimeout(function()
                   {
                     try
                     {
                       self.processBusiness(self, doc)
                     }
                     catch(err)
                     {
                       console.log("Processor_HackJacketProto error:" + err);
                     }
                     self.preQuit(doc);
                   }, 
        1);      
    }  
    NP.RegistProcessorToSys(new Processor_HackJacket());
}(ECProcessorNS));
