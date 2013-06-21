#ifndef SKYPEAPI_IFNIMCHAT_HEADER_
#define SKYPEAPI_IFNIMCHAT_HEADER_

#include <vector>
#include <xstring>
using namespace std;

#import "..\Skype4COM.dll"
using namespace SKYPE4COMLib;
/// SkypeAPI_IFNIMChat is a interface 
class SkypeAPI_IFNIMChat
{
public :
	virtual void get_Chat_Members(/*out*/ vector<wstring>&) = 0;
	virtual void set_Chat_Members(/*in*/ vector<wstring>&) = 0;

	virtual const wstring get_Chat_OwnerMe() = 0;
	virtual void set_Chat_OwnerMe(LPCTSTR chat_owner) = 0;

	virtual void on_Message_received( const wstring & sender, const wstring & msg, vector<wstring>& chat_Members) = 0;
	virtual void on_chat_message_received(LPCTSTR sender ,LPCTSTR msg ,LPCTSTR timeinDouble ) = 0;
	virtual void send_Message( LPCTSTR msg) = 0;

	virtual void shakehand() = 0 ;
	virtual void set_handshaked( bool shaked) = 0 ;

	virtual DWORD get_cookie() = 0 ;
	virtual void  set_Skype_chat_obj(IChat *) = 0 ;
	virtual IChat* get_Skype_chat_obj( ) = 0 ;

	virtual void notify_chatMember_changed() = 0;

	virtual void stop() = 0;

  virtual void set_handshaked2( LPCTSTR sender, bool shaked) = 0 ;
};


FNIM_SKYPE_PROXY_API bool connect_skypePlugin();
FNIM_SKYPE_PROXY_API void quit_skypePlugin();
FNIM_SKYPE_PROXY_API DWORD register_SkypeAPI_IFNIMChat(SkypeAPI_IFNIMChat* aSkypeAPI_IFNIMChat, LPCTSTR shakehandMsg);
FNIM_SKYPE_PROXY_API void unregister_SkypeAPI_IFNIMChat(DWORD cookie);

#endif //SKYPEAPI_IFNIMCHAT_HEADER_
