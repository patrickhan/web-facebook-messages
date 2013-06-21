#ifndef SkypeToggleChatSession__HEADER__
#define SkypeToggleChatSession__HEADER__

#include "IFNIMToggle.h"
#include "nsCOMPtr.h"
#include "nsITimer.h"
#include "nsIObserver.h"
#include "nsWeakReference.h"
#include "nsEmbedString.h"
#include "nsIDOMEventListener.h"
#include "../FNIMToggleChatSessionFNMainWindow.h"

#include "skype_dev/FNIM_skype_proxy/FNIM_skype_proxy.h"

#include "boost/shared_ptr.hpp"

#include "FNIMContactListUI.h"

class SkypeToggleChatSession : 
     public IFNIMToggleChatSession
    ,public nsIObserver
		,public nsSupportsWeakReference 
    ,public IFNIMToggleButtonEvnetListener
    ,public nsIDOMEventListener
    ,public IFNIMWindowDestroyEvnetListener
    ,public IFNIMToggleChatSessionContactor
    ,public IFNIMSendInvitation
    ,public SkypeAPI_IFNIMChat
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOBSERVER
  NS_DECL_IFNIMTOGGLECHATSESSION
  NS_DECL_IFNIMTOGGLEBUTTONEVNETLISTENER
  NS_DECL_NSIDOMEVENTLISTENER
  NS_DECL_IFNIMWINDOWDESTROYEVNETLISTENER
  NS_DECL_IFNIMTOGGLECHATSESSIONCONTACTOR
  NS_DECL_IFNIMSENDINVITATION


  SkypeToggleChatSession();


  virtual void get_Chat_Members(/*out*/ vector<wstring>&);
  virtual void set_Chat_Members(/*in*/ vector<wstring>&) ;
  virtual const wstring get_Chat_OwnerMe() ;
  virtual void set_Chat_OwnerMe(LPCTSTR chat_owner) ;
  virtual void on_Message_received( const wstring & sender, const wstring & msg, vector<wstring>& chat_Members);
  virtual void on_chat_message_received(LPCTSTR sender , LPCTSTR msg , LPCTSTR timeInDouble) ;
  virtual void send_Message( LPCTSTR msg) ;
  virtual void shakehand()  ;
  virtual void set_handshaked( bool shaked);
  virtual DWORD get_cookie() ;
  virtual void  set_Skype_chat_obj(IChat *) ;
  virtual IChat* get_Skype_chat_obj( )  ;
  virtual void notify_chatMember_changed();
  virtual void stop();
  virtual void set_handshaked2( LPCTSTR sender, bool shaked) ;

  void FirstTimeDumpMessages();
private:
  ~SkypeToggleChatSession();

protected:
    nsresult findInputWindow( IFNIMToggleChatInputWindow ** window  );
    nsresult findReadWindow( IFNIMToggleChatReadWindow **window  );

    nsresult createToggleButton( IFNIMToggleButton** toggleButton );
    nsresult create_toggleButtonLocator(IFNIMWindowLocator ** aLocator);

    nsresult create_fnInput(IFNIMToggleChatFNInput ** fnInput);
    nsresult create_fnReader(IFNIMToggleChatFNReader ** fnRead);


    nsresult create_fnInputWindow(IFNIMToggleChatFNInputWindow ** fnInput);
    nsresult create_fnInputWindowLocator(IFNIMWindowLocator ** fnInputLocator);
    
    nsresult create_fnReaderWindow(IFNIMToggleChatFNReadWindow ** fnRead);
    nsresult create_fnReaderWindowLocator(IFNIMWindowLocator** fnReadLocator);

    nsresult create_fnMainWindow(IFNIMToggleChatFNMainWindow ** fnRead);
    nsresult create_fnMainWindowLocator(IFNIMWindowLocator ** aLocator);

    nsresult syncReaderContentOnIdel();
    nsresult syncReaderContent();
    nsresult syncInputContent();
    nsresult onFNIMWebBrowserChrome_Ready(); 

    nsresult retrieveChatContactorInfo(); 
    nsresult retrieveAccountInfo(); 
    void retriveHandeShakeInvitation(LPCTSTR sender , LPCTSTR msg , LPCTSTR timeInDouble);

    nsresult onSubmit(nsIDOMElement *);


    bool create_FNIMContactListUI();
    bool create_FNIMContactListUILocator(IFNIMWindowLocator ** aLocator);

  /* additional members */
    nsCOMPtr<IFNIMToggleApplication> application_;
    nsCOMPtr<IFNIMToggleChatSessionMainWindow >  mainWindow_;
    nsCOMPtr<IFNIMToggleChatInputWindow > inputWindow_;
    nsCOMPtr<IFNIMToggleChatReadWindow > readWindow_;
    nsCOMPtr<IFNIMToggleChatReadWindowLocator>  chatReadWindowLocator_;
    nsCOMPtr<IFNIMToggleChatInputWindowLocator>  chatInputWindowLocator_;
    
    nsCOMPtr<IFNIMToggleButton> toggleButton_;
    nsCOMPtr<IFNIMWindowLocator> toggleButtonLocator_;

    nsCOMPtr<IFNIMWindowLocator>  fnMainWindowLocator_;
    nsCOMPtr<IFNIMToggleChatFNMainWindow>   fnMainWindow_;

    nsCOMPtr<IFNIMToggleChatFNInput >  fnInput_;
    nsCOMPtr<IFNIMToggleChatFNReader>  fnReader_;

    nsCOMPtr<IFNIMToggleChatFNInputWindow>  fnInput_Window_;// act as  a cover
    nsCOMPtr<IFNIMWindowLocator>  fnInput_Window_Locator_;

    nsCOMPtr<IFNIMToggleChatFNReadWindow>   fnReader_Window_;// act as  a cover
    nsCOMPtr<IFNIMWindowLocator>  fnReader_Window_Locator_;

    nsCOMPtr<IFNIMWindowLocator> _FNIMContactListUILocator;
    boost::shared_ptr<FNIMContactListUI> _FNIMContactListUIPtr;



    nsCOMPtr<nsITimer>  aNSTimer_;
    nsString readerContent_cache_;
    nsString account_nickname_;
    nsString chatContactor_nickname_;
    nsString invitation_content_;

    IChatPtr aIChat_;
    DWORD listener_Cookie_;

    bool handshaked_;

};


#endif //FNIMToggleApplication__HEADER__
