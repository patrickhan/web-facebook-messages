#ifndef FNIMToggleChatSessionFNMainWindow__HEADER__skype
#define FNIMToggleChatSessionFNMainWindow__HEADER__skype


#include "IFNIMToggle.h"
#include "nsEmbedString.h"
#include "nsIMutableArray.h"
#include "nsCOMPtr.h"


#include <list>


//WTL

#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200
#include <atlbase.h>
//#include <atlapp.h>
//#include "atlctrls.h"
#include <atlwin.h>

#include "FNRichTextEditor_Service.h"

/* Header file */
class SkypeToggleChatSessionFNMainWindow :
    public CWindowImpl<SkypeToggleChatSessionFNMainWindow >
{
public:
    //DECLARE_WND_CLASS(L"SkypeClass" )

  //NS_DECL_ISUPPORTS
  //NS_DECL_ISkypeTOGGLECHATSESSIONMAINWINDOW

  SkypeToggleChatSessionFNMainWindow();
  ~SkypeToggleChatSessionFNMainWindow();


BEGIN_MSG_MAP(SkypeToggleChatSessionFNMainWindow)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, onPosChanged)
END_MSG_MAP()
  LRESULT OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */);
  LRESULT OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */);
  LRESULT onPosChanged(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */);



	

	static LPCTSTR GetWndCaption()
	{
		return L"FNLM Skype";
	}

  PRBool  CreateNew( const LPRECT prc );
  PRBool  Show( );
  PRBool  Hide( );
  void  Close( );

  BOOL adjustLayout();


  HWND getFNReaderHost()
  {
      return readWindowParent_.m_hWnd;
  }
  HWND getFNInputHost()
  {
      return inputWindowParent_.m_hWnd;
  }

  void setReaderHWND( HWND h)
  {
        fn_readWindow_.Attach(h);
  }

  void setInputHWND( HWND h)
  {
      fn_inputWindow_.Attach(h);
  }


  BOOL  CreateBrowser();
  void DestoryBrowser();
  void SetFocusBrowser();
  void KillFocusBrowser();

   void setChatSession(IFNIMToggleChatSession* aChatSession)
   {
       chat_Session_ = aChatSession;
   }
   nsCOMPtr<nsIWebBrowser>  getWebBrowser_()
   {
       return ansIWebBrowser_;
   }
protected:
  /* additional members */
    CWindow hideButton_;
    CWindow readWindowParent_;
    CWindow inputWindowParent_;
    CWindow fn_inputWindow_;
    CWindow fn_readWindow_;


    nsCOMPtr<nsIWebBrowser> ansIWebBrowser_;


    nsCOMPtr<IFNIMToggleChatSession> chat_Session_;


};

#endif //

