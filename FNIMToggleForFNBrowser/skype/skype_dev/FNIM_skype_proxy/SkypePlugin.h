#ifndef SKYPE_PLUGIN_H_ 
#define SKYPE_PLUGIN_H_

#include "FNIM_skype_proxy.h"
#include "TEventHandler.h"
#include <map>

//using namespace std;
using namespace SKYPE4COMLib;

//typedef TEventHandler<SkypePlugin, ISkype, _ISkypeEvents> ISkypeEventHandler;
#include <atlcom.h>
class SkypePlugin  : public CComObjectRoot,
	public IDispatchImpl<SKYPE4COMLib::_ISkypeEvents>
{
public:

BEGIN_COM_MAP(SkypePlugin)
	COM_INTERFACE_ENTRY(SKYPE4COMLib::_ISkypeEvents)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

		SkypePlugin();
		~SkypePlugin();


		void quit();

		DWORD register_IFNIMChat(SkypeAPI_IFNIMChat *aSkypeAPI_IFNIMChat, LPCTSTR shakehandMsg);

		void  unregister_IFNIMChat(DWORD cookie);

		bool init(); 
		void adviseSkype(bool isAdvise);

		bool shake_hand_smg_check (	IChatMessage * pMessage,	TChatMessageStatus Status );
		void dispatch_Received_msg(	IChatMessage * pMessage,	TChatMessageStatus Status );

    bool Chat2ForSeamSession( IChat* aIChat1 , IChat* aIChata2 );
		void firstTimeDumpMessages();


		enum
		{
			DISP_ISkypeEvents_Command  = 1,
			DISP_ISkypeEvents_Reply ,
			DISP_ISkypeEvents_Error ,
			DISP_ISkypeEvents_AttachmentStatus ,
			DISP_ISkypeEvents_ConnectionStatus ,
			DISP_ISkypeEvents_UserStatus ,
			DISP_ISkypeEvents_OnlineStatus, 
			DISP_ISkypeEvents_CallStatus ,
			DISP_ISkypeEvents_CallHistory ,
			DISP_ISkypeEvents_Mute ,
			DISP_ISkypeEvents_MessageStatus ,
			DISP_ISkypeEvents_MessageHistory ,
			DISP_ISkypeEvents_AutoAway,
			DISP_ISkypeEvents_CallDtmfReceived ,
			DISP_ISkypeEvents_VoicemailStatus ,
			DISP_ISkypeEvents_ApplicationConnecting ,
			DISP_ISkypeEvents_ApplicationStreams ,
			DISP_ISkypeEvents_ApplicationDatagram ,
			DISP_ISkypeEvents_ApplicationSending ,
			DISP_ISkypeEvents_ApplicationReceiving, 
			DISP_ISkypeEvents_ContactsFocused,
			DISP_ISkypeEvents_GroupVisible ,
			DISP_ISkypeEvents_GroupExpanded ,
			DISP_ISkypeEvents_GroupUsers ,
			DISP_ISkypeEvents_GroupDeleted,
			DISP_ISkypeEvents_UserMood ,
			DISP_ISkypeEvents_SmsMessageStatusChanged ,
			DISP_ISkypeEvents_SmsTargetStatusChanged ,
			DISP_ISkypeEvents_CallInputStatusChanged ,
			DISP_ISkypeEvents_AsyncSearchUsersFinished, 
			DISP_ISkypeEvents_CallSeenStatusChanged ,
			DISP_ISkypeEvents_PluginEventClicked ,
			DISP_ISkypeEvents_PluginMenuItemClicked, 
			DISP_ISkypeEvents_WallpaperChanged ,
			DISP_ISkypeEvents_FileTransferStatusChanged ,
			DISP_ISkypeEvents_CallTransferStatusChanged ,
			DISP_ISkypeEvents_ChatMembersChanged ,
			DISP_ISkypeEvents_ChatMemberRoleChanged ,
			DISP_ISkypeEvents_CallVideoStatusChanged ,
			DISP_ISkypeEvents_CallVideoSendStatusChanged ,
			DISP_ISkypeEvents_CallVideoReceiveStatusChanged ,
			DISP_ISkypeEvents_SilentModeStatusChanged ,
			DISP_ISkypeEvents_UserAuthorizationRequestReceived 
		};

		
    HRESULT Command (
        ICommand * pCommand );
    HRESULT Reply (
        ICommand * pCommand );
    HRESULT Error (
        ICommand * pCommand,
        long Number,
        _bstr_t Description );
    HRESULT AttachmentStatus (
        TAttachmentStatus Status );
    HRESULT ConnectionStatus (
        TConnectionStatus Status );
    HRESULT UserStatus (
        TUserStatus Status );
    HRESULT OnlineStatus (
        IUser * pUser,
        TOnlineStatus Status );
    HRESULT CallStatus (
        ICall * pCall,
        TCallStatus Status );
    HRESULT CallHistory ( );
    HRESULT Mute (
        VARIANT_BOOL Mute );
    HRESULT MessageStatus (
        struct IChatMessage * pMessage,
         TChatMessageStatus Status );
    HRESULT MessageHistory (
        _bstr_t Username );
    HRESULT AutoAway (
        VARIANT_BOOL Automatic );
    HRESULT CallDtmfReceived (
         ICall * pCall,
        _bstr_t code );
    HRESULT VoicemailStatus (
         IVoicemail * pMail,
         TVoicemailStatus Status );
    HRESULT ApplicationConnecting (
         IApplication * pApp,
         IUserCollection * pUsers );
    HRESULT ApplicationStreams (
         IApplication * pApp,
         IApplicationStreamCollection * pStreams );
    HRESULT ApplicationDatagram (
         IApplication * pApp,
         IApplicationStream * pStream,
        _bstr_t Text );
    HRESULT ApplicationSending (
         IApplication * pApp,
         IApplicationStreamCollection * pStreams );
    HRESULT ApplicationReceiving (
         IApplication * pApp,
         IApplicationStreamCollection * pStreams );
    HRESULT ContactsFocused (
        _bstr_t Username );
    HRESULT GroupVisible (
         IGroup * pGroup,
        VARIANT_BOOL Visible );
    HRESULT GroupExpanded (
         IGroup * pGroup,
        VARIANT_BOOL Expanded );
    HRESULT GroupUsers (
         IGroup * pGroup,
         IUserCollection * pUsers );
    HRESULT GroupDeleted (
        long GroupId );
    HRESULT UserMood (
         IUser * pUser,
        _bstr_t MoodText );
    HRESULT SmsMessageStatusChanged (
         ISmsMessage * pMessage,
         TSmsMessageStatus Status );
    HRESULT SmsTargetStatusChanged (
         ISmsTarget * pTarget,
         TSmsTargetStatus Status );
    HRESULT CallInputStatusChanged (
         ICall * pCall,
        VARIANT_BOOL Status );
    HRESULT AsyncSearchUsersFinished (
        long Cookie,
         IUserCollection * pUsers );
    HRESULT CallSeenStatusChanged (
         ICall * pCall,
        VARIANT_BOOL Status );
    HRESULT PluginEventClicked (
         IPluginEvent * pEvent );
    HRESULT PluginMenuItemClicked (
         IPluginMenuItem * pMenuItem,
         IUserCollection * pUsers,
         TPluginContext PluginContext,
        _bstr_t ContextId );
    HRESULT WallpaperChanged (
        _bstr_t Path );
    HRESULT FileTransferStatusChanged (
         IFileTransfer * pTransfer,
         TFileTransferStatus Status );
    HRESULT CallTransferStatusChanged (
         ICall * pCall,
         TCallStatus Status );
    HRESULT ChatMembersChanged (
         IChat * pChat,
         IUserCollection * pMembers );
    HRESULT ChatMemberRoleChanged (
         IChatMember * pMember,
         TChatMemberRole Role );
    HRESULT CallVideoStatusChanged (
         ICall * pCall,
         TCallVideoStatus Status );
    HRESULT CallVideoSendStatusChanged (
         ICall * pCall,
         TCallVideoSendStatus Status );
    HRESULT CallVideoReceiveStatusChanged (
         ICall * pCall,
         TCallVideoSendStatus Status );
    HRESULT SilentModeStatusChanged (
        VARIANT_BOOL Silent );
    HRESULT UILanguageChanged (
        _bstr_t code );
    HRESULT UserAuthorizationRequestReceived (
         IUser * pUser );
		


		////IDispatch
		STDMETHOD(Invoke)( 
			/* [in] */ DISPID dispIdMember,
			/* [in] */ REFIID riid,
			/* [in] */ LCID lcid,
			/* [in] */ WORD wFlags,
			/* [out][in] */ DISPPARAMS *pDispParams,
			/* [out] */ VARIANT *pVarResult,
			/* [out] */ EXCEPINFO *pExcepInfo,
			/* [out] */ UINT *puArgErr);
		
	private:
		//long m_cRef;
		DWORD _Skype_EventListener_Cookie;

		DWORD  _IFNIMChat_Cookie;

		SKYPE4COMLib::ISkypePtr _pSkype;
		SKYPE4COMLib::ICallChannelManagerPtr _pCallChannelManager;

		std::map<DWORD,SkypeAPI_IFNIMChat*> _SkypeAPI_IFNIMChat_map;
		std::map<DWORD,wstring> _SkypeAPI_IFNIMChat_shakehandMsg_map;
		std::map<DWORD,IChat*> _SkypeAPI_IFNIMChat_chat_map;

    bool connected_skype_;
};

#endif