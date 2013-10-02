
#include "stdafx.h"
#include "SkypePlugin.h"

#include <ctime>
#include <xstring>
#include <list>

#include "atltime.h"

SkypePlugin::SkypePlugin(): //m_cRef(0L),
_Skype_EventListener_Cookie (0u),
_IFNIMChat_Cookie(0u),
connected_skype_(false)
{
    CoInitialize(NULL);
}

SkypePlugin::~SkypePlugin()
{
    // Cleanup
    CTime aTime;
    quit();
    CoUninitialize();
}

void SkypePlugin::quit()
{
    if(_pSkype)
    {
        if(_Skype_EventListener_Cookie!= 0)
        {
            adviseSkype(false);
            _Skype_EventListener_Cookie =  0;
        }
        _pSkype = NULL;

        _SkypeAPI_IFNIMChat_map.clear();
        _SkypeAPI_IFNIMChat_shakehandMsg_map.clear();
    }
}



/***helper methdos**/


bool SkypePlugin::init()
{

    if(connected_skype_)
        return  true;
    // Initialize COM
    if(!_pSkype)
    {
        // Create Skype object
        _pSkype.CreateInstance(__uuidof(SKYPE4COMLib::Skype) );
        _pCallChannelManager.CreateInstance(__uuidof(SKYPE4COMLib::ICallChannelManager) );
    }
    // Connect to API
    if(_pSkype)
    {
        try
        {
            if(!_pSkype->Client->IsRunning)
            {
                return false; // we do not start skype 
                //_pSkype->Client->Start(VARIANT_TRUE,VARIANT_TRUE);
            }

            long lProtocol = 0;
            if(S_OK != _pSkype->get_Protocol(&lProtocol))
            {
                return false;
            }
            if(S_OK != _pSkype->Attach(lProtocol, VARIANT_FALSE))
            {
                return false; //can not attach 
            }
        }
        catch(...)
        {
            return false;
        }
        if(_pCallChannelManager)
        {
            _pCallChannelManager->Connect( _pSkype);
        }

        adviseSkype(true);

        return true;
    }

    return false;
}

void SkypePlugin::adviseSkype(bool isAdvise)
{
    if(isAdvise)
    {
        if(_Skype_EventListener_Cookie == 0u)
        {
            CComPtr<SKYPE4COMLib::ISkype> aISkype = (SKYPE4COMLib::ISkype*)_pSkype;
            aISkype.Advise(this, __uuidof(SKYPE4COMLib::_ISkypeEvents), &_Skype_EventListener_Cookie);
            ::Sleep(500);
        }
    }
    else
    {
        if(_Skype_EventListener_Cookie != 0u)
        {
            CComPtr<SKYPE4COMLib::ISkype> aISkype = (SKYPE4COMLib::ISkype*)_pSkype;
            AtlUnadvise(this,  __uuidof(SKYPE4COMLib::_ISkypeEvents), _Skype_EventListener_Cookie);
        }
    }
}

DWORD SkypePlugin::register_IFNIMChat(SkypeAPI_IFNIMChat *aSkypeAPI_IFNIMChat, LPCTSTR shakehandMsg)
{
    // todo check the aSkypeAPI_IFNIMChat si existed or not
    if(aSkypeAPI_IFNIMChat)
    {
        ++_IFNIMChat_Cookie;
        _SkypeAPI_IFNIMChat_map[_IFNIMChat_Cookie] = aSkypeAPI_IFNIMChat;
        _SkypeAPI_IFNIMChat_shakehandMsg_map[_IFNIMChat_Cookie] = wstring(shakehandMsg);

        return _IFNIMChat_Cookie;
    }

    return 0;
}

void  SkypePlugin::unregister_IFNIMChat(DWORD cookie)
{
    std::map<DWORD,SkypeAPI_IFNIMChat*>::iterator itor = _SkypeAPI_IFNIMChat_map.find(cookie);
    if(itor!= _SkypeAPI_IFNIMChat_map.end() )
    {
        _SkypeAPI_IFNIMChat_map.erase(itor);
    }

    std::map<DWORD,wstring>::iterator itor2 = _SkypeAPI_IFNIMChat_shakehandMsg_map.find(cookie);
    if(itor2!= _SkypeAPI_IFNIMChat_shakehandMsg_map.end() )
    {
        _SkypeAPI_IFNIMChat_shakehandMsg_map.erase(itor2);
    }
}

bool SkypePlugin::MessageCanSendout( IChatMessage * pMessage)
{
    if(NULL == pMessage)
    {
        return false;
    }

    IChatPtr aIChat = pMessage->Chat;
    if(!aIChat)
    {
        return false;
    }
    IUserCollectionPtr mc  =  aIChat->Members;
    long count =  mc->Count;

     _bstr_t fromSkypeHandle = pMessage->FromHandle;

    // if there is a user is not online , then the message is sending , not been sent
    if(count >= 2)
    {
        for(long i = 1L; i<= count ; i++ ) //skype is based on 1 
        {
            IUserPtr amember = mc->Item[i];
            if( !amember )
            {
                continue;
            }
            _bstr_t ahandle1_bstr = amember->Handle;
            if(fromSkypeHandle  == ahandle1_bstr)
            {   
                continue;
            }
            
            if(amember->OnlineStatus == olsOffline)
            {
                return false;
            }
        }
    }
    return true;
}

bool SkypePlugin::Chat2ForSeamSession( IChat* aIChat1 , IChat* aIChat2 )
{
    bool isSeam =  false;
    if(aIChat1 == NULL || aIChat2 == NULL)
    {
        return false;
    }

    //condition 1 pair chat 
    _bstr_t name1 = aIChat1->DialogPartner;
    _bstr_t name2 = aIChat2->DialogPartner;
    UINT len1 = name1.length();// - 16U;
    UINT len2 = name2.length();// - 16U;
    if(len1 > 0  &&  len2 > 0)
    {
        BSTR pname1 = name1.GetBSTR();
        BSTR pname2 = name2.GetBSTR();
        if( 0 == wcsncmp(pname1, pname2, len1) )
        {
            return true;
        }
    }

    //condition2 group
    IChatMemberCollectionPtr mc1  =  aIChat1->MemberObjects;
    IChatMemberCollectionPtr mc2  =  aIChat2->MemberObjects;
    long count1 =  mc1->Count;
    long count2 =  mc2->Count;

    if(mc1 && mc2 && count1 > 2  && count2 > 2)
    {
        bool seam = true;
        if(count2  != count1 )
        {
            seam = false;
        }
        else
        {
            std::list<std::wstring> mlist1;
            std::list<std::wstring> mlist2;
            bool seam = true;
            for(long i = 1L; i<= count1 ; i++ ) //skype is based on 1 
            {
                IChatMemberPtr amember1 = mc1->Item[i];
                IChatMemberPtr amember2 = mc2->Item[i];
                if( !amember2 || !amember1 )
                {
                    seam = false;
                    break;
                }
                _bstr_t ahandle1_bstr = amember1->Handle;
                _bstr_t ahandle2_bstr = amember2->Handle;
                UINT len1 = ahandle1_bstr.length();
                UINT len2 = ahandle2_bstr.length();
                if(len1  != len2)
                {
                    seam = false;
                    break;
                }

                BSTR ahandle1 = ahandle1_bstr.GetBSTR();
                BSTR ahandle2 = ahandle2_bstr.GetBSTR();
                if( 0 != wcsncmp(ahandle2, ahandle1, len1) )
                {
                    seam = false;
                    break;
                }

            }
        }//else
        return seam;
    }

    return false;

}


BOOL timeConvert(DATE time_stamp, __time32_t &out__time32_t)
{
    SYSTEMTIME asystemTime ={0};
    BOOL ok =  VariantTimeToSystemTime(time_stamp,  &asystemTime);
    if(!ok)
    {
        return FALSE;
    }
    //COleDateTime is in local timezone, DateTime is in UTC, so we need to convert
    SYSTEMTIME st_utc;
    TzSpecificLocalTimeToSystemTime(NULL, &asystemTime, &st_utc);
    /*
    The range of the _mkgmtime32 function is from midnight, January 1, 1970, UTC to January 19, 3:14:07, 2038, UTC. 
    The range of _mkgmtime64 is from midnight, January 1, 1970, UTC to 23:59:59, December 31, 3000, UTC. 
    An out-of-range date results in a return value of –1. The range of _mkgmtime depends on whether _USE_32BIT_TIME_T is defined. 
    If not defined (the default) the range is that of _mkgmtime64; otherwise, the range is limited to the 32-bit range of _mkgmtime32.
    */
    tm aTM = {0};
    aTM.tm_year = (int)st_utc.wYear - 1900;
    aTM.tm_mon = (int)st_utc.wMonth;
    aTM.tm_mday = st_utc.wDay;
    aTM.tm_hour = st_utc.wHour;
    aTM.tm_min = st_utc.wMinute;
    aTM.tm_sec = st_utc.wSecond;
    out__time32_t = _mkgmtime32(&aTM);
    return TRUE;
}

//give a DATE time_stamp, calculate the timespan from Now
int timeSpanFromNow(DATE time_stamp)
{
    __time64_t now ={0};
    _time64(  &now );
    CTime tmp(now);

    SYSTEMTIME st;
    tmp.GetAsSystemTime(st); 

    double nowtime_stamp;
    AtlConvertSystemTimeToVariantTime(st, &nowtime_stamp);
    //ConvertSystemTimeToVariantTime(st) 

    __time32_t now_new;
    timeConvert( nowtime_stamp, now_new);


    __time32_t then;
    timeConvert( time_stamp, then);

    return  (int)(now_new - then);
}

void  SkypePlugin::dispatch_Received_msg(IChatMessage * pMessage,	TChatMessageStatus Status)
{//TChatMessageStatus::cmsRead
    if(pMessage ==  NULL)
        return;
    //when a user is not online the Status should be  SKYPE4COMLib::cmsSending
    //to take this into account , we change the condition of Status

    bool status_passed =  false;
 

    if(Status==SKYPE4COMLib::cmsReceived )
    {
        status_passed  =  true;
    }
    if(Status==SKYPE4COMLib::cmsSent)
    {
        int span  = timeSpanFromNow(pMessage->Timestamp);
        if(span >  10)
        {// the message has shown due to sendings
            //so , do not pass it to FNRTE
            status_passed  =  false;
        }
        else
        {
            status_passed  =  true;
        }
    }

    _bstr_t FromHandle_bstr = pMessage->FromHandle;


    if(Status==SKYPE4COMLib::cmsSending)
    {


        long count = pMessage->Chat->ActiveMembers->Count;

        _variant_t v(count) ;// we use _bstr_t(_variant_t) constructor to create _bstr_t instance
        _bstr_t date_str(v );

        if(count == 1)
        {
            status_passed  =  true;
        }
        else if(count >  1)
        {
            bool cansent = MessageCanSendout(pMessage);
            if(!cansent)
            {
                status_passed  =  true;
            }
            else
            {
                status_passed  =  false;
            }
        }
    }

    if(status_passed  )
    {
        IChatPtr aIChatPtr = pMessage->GetChat();

        DATE time_stamp = pMessage->Timestamp ;
        //_bstr_t FromDisplayName = pMessage->FromDisplayName;
        _bstr_t FromDisplayName = pMessage->FromHandle;

        _bstr_t msgBody =  pMessage->Body;

        std::map<DWORD,SkypeAPI_IFNIMChat*>::const_iterator itor;
        for(itor =  _SkypeAPI_IFNIMChat_map.begin(); itor != _SkypeAPI_IFNIMChat_map.end(); itor++)
        {
            SkypeAPI_IFNIMChat* aSkypeAPI_IFNIMChat = itor->second;
            if(aSkypeAPI_IFNIMChat)
            {
                IChat* aIChat = aSkypeAPI_IFNIMChat->get_Skype_chat_obj();
                if(aIChat == NULL)
                {
                    continue;
                }

                IChat* msgChat = aIChatPtr.GetInterfacePtr();
                if(msgChat == NULL)
                {
                    continue;
                }
                if (Chat2ForSeamSession(msgChat,aIChat ) )
                {

                    __time32_t   aTime_t ;
                    timeConvert( time_stamp, aTime_t);
                    _variant_t v(aTime_t) ;// we use _bstr_t(_variant_t) constructor to create _bstr_t instance
                    _bstr_t date_str(v );
                    date_str += _bstr_t(L"000");// we do not care about ms
                    aSkypeAPI_IFNIMChat->on_chat_message_received(FromDisplayName.GetBSTR(), msgBody.GetBSTR(), date_str.GetBSTR() );
                }
            }

        }
    }
}

bool  SkypePlugin::shake_hand_smg_check(IChatMessage * pMessage,	TChatMessageStatus Status)
{
    if(Status ==SKYPE4COMLib::cmsSending )
    {
        if(_SkypeAPI_IFNIMChat_shakehandMsg_map.size() == 0)
        {
            return false;
        }
        _bstr_t msg;
        pMessage->get_Body(msg.GetAddress());
        _bstr_t guid1 = pMessage->Guid;
        map <DWORD,wstring> :: reverse_iterator m1_rIter;
        m1_rIter = _SkypeAPI_IFNIMChat_shakehandMsg_map.rbegin(); // we only care abouthe last SkypeAPI_IFNIMChat_shakehandMsg
        //m1_rIter--;
        if(m1_rIter != _SkypeAPI_IFNIMChat_shakehandMsg_map.rend() )
        {
            DWORD id = m1_rIter->first;
            _bstr_t handshakemsg = m1_rIter->second.c_str();

            if(handshakemsg ==  msg)
            {
                //pMessage->PutSeen(VARIANT_FALSE);
                std::map<DWORD,SkypeAPI_IFNIMChat*>::iterator itor  = _SkypeAPI_IFNIMChat_map.find(m1_rIter->first);
                SkypeAPI_IFNIMChat* aSkypeAPI_IFNIMChat = itor->second;
                if(aSkypeAPI_IFNIMChat)
                {
                    //pMessage.Chat.Members  is the participants
                    _bstr_t FromDisplayName = pMessage->FromDisplayName;
                    aSkypeAPI_IFNIMChat->set_Chat_OwnerMe(FromDisplayName.GetBSTR() );

                    IChatPtr aIChatPtr = pMessage->GetChat();
                    IChat * pIChat = aIChatPtr.GetInterfacePtr();
                    if(pIChat != NULL)
                    {
                        _bstr_t FromSkypeHandle = pMessage->FromHandle;

                        aSkypeAPI_IFNIMChat->set_Skype_chat_obj(pIChat );
                        aSkypeAPI_IFNIMChat->set_handshaked2(FromSkypeHandle.GetBSTR(),  true);


                    }

                    _SkypeAPI_IFNIMChat_chat_map[itor->first] = (IChat*)pMessage->GetChat();
                    return true;
                }
            }//if(handshakemsg ==  msg)
        }
    }

    return false;
}

HRESULT SkypePlugin::Invoke( 
                            /* [in] */ DISPID dispIdMember,
                            /* [in] */ REFIID riid,
                            /* [in] */ LCID lcid,
                            /* [in] */ WORD wFlags,
                            /* [out][in] */ DISPPARAMS *pDispParams,
                            /* [out] */ VARIANT *pVarResult,
                            /* [out] */ EXCEPINFO *pExcepInfo,
                            /* [out] */ UINT *puArgErr)
{
    switch(dispIdMember)
    {
    case DISP_ISkypeEvents_Command  :
        {

            VARIANT varlValue1 ;
            ICommand *pICommand;

            VariantInit(&varlValue1);
            VariantClear(&varlValue1);
            varlValue1 = (pDispParams -> rgvarg)[0];
            pICommand = (ICommand*) V_UNKNOWN(&varlValue1);

            Command(pICommand);
        }
        break;
    case 		DISP_ISkypeEvents_Reply  :
        {

            VARIANT varlValue1 ;
            ICommand *pICommand;

            VariantInit(&varlValue1);
            VariantClear(&varlValue1);
            varlValue1 = (pDispParams -> rgvarg)[0];
            pICommand = (ICommand*) V_UNKNOWN(&varlValue1);

            Reply (pICommand );
        }
        break;
    case 		DISP_ISkypeEvents_Error  :
        break;
    case 	DISP_ISkypeEvents_AttachmentStatus  :
        {

            VARIANT varlValue1 ;
            TAttachmentStatus aTAttachmentStatus;

            VariantInit(&varlValue1);
            VariantClear(&varlValue1);
            varlValue1 = (pDispParams -> rgvarg)[0];
            aTAttachmentStatus = (TAttachmentStatus) V_I4(&varlValue1);

            AttachmentStatus (aTAttachmentStatus );
        }
        break;
    case DISP_ISkypeEvents_ConnectionStatus  :
        break;
    case 		DISP_ISkypeEvents_UserStatus  :
        {
            // 1st param : [in] TUserStatus Status
            VARIANT varlValue;
            TUserStatus skypeUserStatus;
            VariantInit(&varlValue);
            VariantClear(&varlValue);
            varlValue = (pDispParams -> rgvarg)[0];
            skypeUserStatus = (TUserStatus) V_I4(&varlValue);

            UserStatus(skypeUserStatus);
        }
        break;
    case 		DISP_ISkypeEvents_OnlineStatus :
        break; 
    case 		DISP_ISkypeEvents_CallStatus  :
        break;
    case 		DISP_ISkypeEvents_CallHistory  :
        break;
    case 		DISP_ISkypeEvents_Mute  :
        break;
    case 		DISP_ISkypeEvents_MessageStatus  :
        {
            VARIANT varlValue1 , varlValue2;
            IChatMessage *pIChatMessage;
            TChatMessageStatus skypeChatStatus;

            VariantInit(&varlValue1);
            VariantClear(&varlValue1);
            VariantInit(&varlValue2);
            VariantClear(&varlValue2);

            varlValue1 = (pDispParams -> rgvarg)[1];
            varlValue2 = (pDispParams -> rgvarg)[0];
            pIChatMessage = (IChatMessage*) V_UNKNOWN(&varlValue1);
            skypeChatStatus = (TChatMessageStatus) V_I4(&varlValue2);

            MessageStatus(pIChatMessage , skypeChatStatus);
        }
        break;
    case 		DISP_ISkypeEvents_MessageHistory  :
        break;
    case 		DISP_ISkypeEvents_AutoAway :
        break;
    case 		DISP_ISkypeEvents_CallDtmfReceived  :
        break;
    case 		DISP_ISkypeEvents_VoicemailStatus  :
        break;
    case 		DISP_ISkypeEvents_ApplicationConnecting  :
        break;
    case 		DISP_ISkypeEvents_ApplicationStreams  :
        break;
    case 		DISP_ISkypeEvents_ApplicationDatagram  :
        break;
    case 		DISP_ISkypeEvents_ApplicationSending  :
        break;
    case 		DISP_ISkypeEvents_ApplicationReceiving :
        break; 
    case 		DISP_ISkypeEvents_ContactsFocused :
        break;
    case 		DISP_ISkypeEvents_GroupVisible  :
        break;
    case 		DISP_ISkypeEvents_GroupExpanded  :
        break;
    case 		DISP_ISkypeEvents_GroupUsers  :
        break;
    case 		DISP_ISkypeEvents_GroupDeleted :
        break;
    case 		DISP_ISkypeEvents_UserMood  :
        break;
    case 		DISP_ISkypeEvents_SmsMessageStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_SmsTargetStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_CallInputStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_AsyncSearchUsersFinished :
        break; 
    case 		DISP_ISkypeEvents_CallSeenStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_PluginEventClicked  :
        break;
    case 		DISP_ISkypeEvents_PluginMenuItemClicked :
        break; 
    case 		DISP_ISkypeEvents_WallpaperChanged  :
        break;
    case 		DISP_ISkypeEvents_FileTransferStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_CallTransferStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_ChatMembersChanged  :
        {
            VARIANT varlValue1 , varlValue2;

            IChat * pChat = 0;
            IUserCollection * pMembers = 0;

            VariantInit(&varlValue1);
            VariantClear(&varlValue1);
            VariantInit(&varlValue2);
            VariantClear(&varlValue2);

            varlValue1 = (pDispParams -> rgvarg)[1];
            varlValue2 = (pDispParams -> rgvarg)[0];
            pChat = (IChat*) V_UNKNOWN(&varlValue1);
            pMembers = (IUserCollection*) V_I4(&varlValue2);

            ChatMembersChanged(pChat , pMembers);
        }
        break;
    case 		DISP_ISkypeEvents_ChatMemberRoleChanged  :
        {
        }
        break;
    case 		DISP_ISkypeEvents_CallVideoStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_CallVideoSendStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_CallVideoReceiveStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_SilentModeStatusChanged  :
        break;
    case 		DISP_ISkypeEvents_UserAuthorizationRequestReceived  :
        break;
    }

    return S_OK;
}

///SKYPE4COMLib::_ISkypeEvents
HRESULT SkypePlugin::Command (
                              ICommand * pCommand )
{
    _bstr_t aCommand  = pCommand->Command;
    _bstr_t aReply = pCommand->Reply;
    return 0;
}
HRESULT SkypePlugin:: Reply (
                             ICommand * pCommand )
{
    _bstr_t aReply = pCommand->Reply;
    return 0;
}
HRESULT SkypePlugin::Error (
                            ICommand * pCommand,
                            long Number,
                            _bstr_t Description )
{
    return 0;
}
HRESULT SkypePlugin::AttachmentStatus (
                                       TAttachmentStatus Status )
{
    if (Status == SKYPE4COMLib::apiAttachAvailable)
    {
        _pSkype->Attach(8, true);
    }


    if( Status == SKYPE4COMLib::apiAttachSuccess )
    {
        //this.textBox_log.Text += "Current user is " + oSkype.CurrentUserHandle;
    }
    return 0;
}
HRESULT SkypePlugin::ConnectionStatus (
                                       TConnectionStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::UserStatus (
                                 TUserStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::OnlineStatus (
                                   IUser * pUser,
                                   TOnlineStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::CallStatus (
                                 ICall * pCall,
                                 TCallStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::CallHistory ( )
{
    return 0;
}
HRESULT SkypePlugin::Mute (
                           VARIANT_BOOL Mute )
{
    return 0;
}
HRESULT SkypePlugin::MessageStatus (
                                    IChatMessage * pMessage,
                                    TChatMessageStatus Status )
{

    bool ishand_shake  = shake_hand_smg_check(pMessage, Status);
    if(!ishand_shake)
    {
        dispatch_Received_msg(pMessage,Status );
    }

    return 0;
}
HRESULT SkypePlugin::MessageHistory (
                                     _bstr_t Username )
{
    return 0;
}
HRESULT SkypePlugin::AutoAway (
                               VARIANT_BOOL Automatic )
{
    return 0;
}
HRESULT SkypePlugin::CallDtmfReceived (
                                       ICall * pCall,
                                       _bstr_t code )
{
    return 0;
}
HRESULT SkypePlugin::VoicemailStatus (
                                      IVoicemail * pMail,
                                      TVoicemailStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::ApplicationConnecting (
    IApplication * pApp,
    IUserCollection * pUsers )
{


    return 0;
}
HRESULT SkypePlugin::ApplicationStreams (
    IApplication * pApp,
    IApplicationStreamCollection * pStreams )
{
    return 0;
}
HRESULT SkypePlugin::ApplicationDatagram (
    IApplication * pApp,
    IApplicationStream * pStream,
    _bstr_t Text )
{
    return 0;
}
HRESULT SkypePlugin::ApplicationSending (
    IApplication * pApp,
    IApplicationStreamCollection * pStreams )
{
    return 0;
}
HRESULT SkypePlugin::ApplicationReceiving (
    IApplication * pApp,
    IApplicationStreamCollection * pStreams )
{
    return 0;
}
HRESULT SkypePlugin::ContactsFocused (
                                      _bstr_t Username )
{
    return 0;
}
HRESULT SkypePlugin::GroupVisible (
                                   IGroup * pGroup,
                                   VARIANT_BOOL Visible )
{
    return 0;
}
HRESULT SkypePlugin::GroupExpanded (
                                    IGroup * pGroup,
                                    VARIANT_BOOL Expanded )
{
    return 0;
}
HRESULT SkypePlugin::GroupUsers (
                                 IGroup * pGroup,
                                 IUserCollection * pUsers )
{
    return 0;
}
HRESULT SkypePlugin::GroupDeleted (
                                   long GroupId )
{
    return 0;
}
HRESULT SkypePlugin::UserMood (
                               IUser * pUser,
                               _bstr_t MoodText )
{
    return 0;
}
HRESULT SkypePlugin::SmsMessageStatusChanged (
    ISmsMessage * pMessage,
    TSmsMessageStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::SmsTargetStatusChanged (
    ISmsTarget * pTarget,
    TSmsTargetStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::CallInputStatusChanged (
    ICall * pCall,
    VARIANT_BOOL Status )
{
    return 0;
}
HRESULT SkypePlugin::AsyncSearchUsersFinished (
    long Cookie,
    IUserCollection * pUsers )
{
    return 0;
}
HRESULT SkypePlugin::CallSeenStatusChanged (
    ICall * pCall,
    VARIANT_BOOL Status )
{
    return 0;
}
HRESULT SkypePlugin::PluginEventClicked (
    IPluginEvent * pEvent )
{
    return 0;
}
HRESULT SkypePlugin::PluginMenuItemClicked (
    IPluginMenuItem * pMenuItem,
    IUserCollection * pUsers,
    TPluginContext PluginContext,
    _bstr_t ContextId )
{
    return 0;
}
HRESULT SkypePlugin::WallpaperChanged (
                                       _bstr_t Path )
{
    return 0;
}
HRESULT SkypePlugin::FileTransferStatusChanged (
    IFileTransfer * pTransfer,
    TFileTransferStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::CallTransferStatusChanged (
    ICall * pCall,
    TCallStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::ChatMembersChanged (
    IChat * pChat,
    IUserCollection * pMembers )
{
    /*std::vector<wstring> chat_members;
    IUserCollectionPtr aIUserCollectionPtr = pChat->GetMembers();
    if(aIUserCollectionPtr)
    {

    long count  = aIUserCollectionPtr->GetCount();
    for (long i = 1L ; i<= count ; i++)
    {
    IUserPtr aIUserPtr = aIUserCollectionPtr->GetItem(i);
    if(aIUserPtr)
    {
    wstring amember(aIUserPtr->GetHandle().GetBSTR());
    chat_members.push_back(amember);
    }
    }
    }


    std::vector<wstring> chat_members1;
    if(pMembers)
    {

    long count  = pMembers->GetCount();
    for (long i = 1L ; i<= count ; i++)
    {
    IUserPtr aIUserPtr = pMembers->GetItem(i);
    if(aIUserPtr)
    {
    wstring amember(aIUserPtr->GetHandle().GetBSTR());
    chat_members1.push_back(amember);
    }
    }
    }*/


    std::map<DWORD,SkypeAPI_IFNIMChat*>::const_iterator itor;
    for(itor =  _SkypeAPI_IFNIMChat_map.begin(); itor != _SkypeAPI_IFNIMChat_map.end(); itor++)
    {
        SkypeAPI_IFNIMChat* aSkypeAPI_IFNIMChat = itor->second;
        if(aSkypeAPI_IFNIMChat)
        {
            IChat* aIChat = aSkypeAPI_IFNIMChat->get_Skype_chat_obj();
            _bstr_t name1 = aIChat->Name;
            _bstr_t name2 = pChat->Name;
            if(name1 == name2 )
            {
                aSkypeAPI_IFNIMChat->notify_chatMember_changed();
            }
        }

    }

    return 0;
}
HRESULT SkypePlugin::ChatMemberRoleChanged (
    IChatMember * pMember,
    TChatMemberRole Role )
{
    return 0;
}
HRESULT SkypePlugin::CallVideoStatusChanged (
    ICall * pCall,
    TCallVideoStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::CallVideoSendStatusChanged (
    ICall * pCall,
    TCallVideoSendStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::CallVideoReceiveStatusChanged (
    ICall * pCall,
    TCallVideoSendStatus Status )
{
    return 0;
}
HRESULT SkypePlugin::SilentModeStatusChanged (
    VARIANT_BOOL Silent )
{
    return 0;
}
HRESULT SkypePlugin:: UILanguageChanged (
    _bstr_t code )
{
    return 0;
}
HRESULT SkypePlugin::UserAuthorizationRequestReceived (
    IUser * pUser )
{
    return 0;
}
