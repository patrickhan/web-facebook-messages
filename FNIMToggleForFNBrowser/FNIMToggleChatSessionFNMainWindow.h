#ifndef FNIMToggleChatSessionFNMainWindow__HEADER__ 
#define FNIMToggleChatSessionFNMainWindow__HEADER__ 


#include "IFNIMToggle.h"
#include "nsEmbedString.h"
#include "nsIMutableArray.h"
#include "nsCOMPtr.h"

#include "nsIDOMWindow.h"

#include <list>


//WTL

//#define WINVER		0x0500
//#define _WIN32_WINNT	0x0501
//#define _WIN32_IE	0x0501
//#define _RICHEDIT_VER	0x0200
#include <atlbase.h>
//#include <atlapp.h>
//#include "atlctrls.h"
#include <atlwin.h>


#include "nsIDOMEventListener.h"
#include "nsIWebBrowser.h"
class FNIMToggleChatSessionFNMainWindowUI :
    public IFNIMToggleChatFNMainWindow,
    public CWindowImpl<FNIMToggleChatSessionFNMainWindowUI >
{
    NS_DECL_ISUPPORTS
    NS_DECL_IFNIMTOGGLECHATFNMAINWINDOW

public:

  FNIMToggleChatSessionFNMainWindowUI();
  ~FNIMToggleChatSessionFNMainWindowUI();


BEGIN_MSG_MAP(FNIMToggleChatSessionFNMainWindowUI)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, onPosChanged)
    MESSAGE_HANDLER(WM_MOUSEACTIVATE, onMOUSEACTIVATE)
END_MSG_MAP()
  LRESULT OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */);
  
  LRESULT OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */);
  LRESULT onPosChanged(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */);
  LRESULT onMOUSEACTIVATE(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */);


	static LPCTSTR GetWndCaption()
	{
		return L"FNLM";
	}

  PRBool  CreateNew( const LPRECT prc );
  PRBool  Show( );
  PRBool  Hide( );

  BOOL  CreateBrowser();
  void DestoryBrowser();
  void SetFocusBrowser();
  void KillFocusBrowser();

   nsCOMPtr<nsIWebBrowser>  getWebBrowser_()
   {
       return ansIWebBrowser_;
   }

   void on_chat_message_received(const nsString &);

protected:
  /* additional members */

    void hookDOMEvent();
    BOOL  windowclosed_;
    BOOL eventHooked_;
    HWND theMainDOMWindow_HWND_;

    nsCOMPtr<nsIWebBrowser> ansIWebBrowser_;
    nsCOMPtr<nsIDOMWindow> theMainDOMWindow_;
    

    nsCOMPtr<nsIDOMEventListener> _listener_FNIMSendButton;
    nsCOMPtr<nsIDOMEventListener> _listener_closebutton;
    nsCOMPtr<nsIDOMEventListener> _listener_invitationbutton;
    nsCOMPtr<nsIObserver> _documentReadyObserver;
    nsCOMPtr<IFNIMWindowDestroyEvnetListener> aDestroyEvnetListener_;

    nsString _title  ;
};

#endif //FNIMToggleChatSessionFNMainWindow__HEADER__


