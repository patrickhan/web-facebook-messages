
#ifndef FNIMCONTACTLISTUI_HEADER__
#define FNIMCONTACTLISTUI_HEADER__

#include "IFNIMToggle.h"

#include "nsITimer.h"
#include "nsIObserver.h"
#include "nsWeakReference.h"
#include "nsIWebBrowser.h"
#include "boost/shared_ptr.hpp"


//WTL

//#define WINVER		0x0500
//#define _WIN32_WINNT	0x0501
//#define _WIN32_IE	0x0501
//#define _RICHEDIT_VER	0x0200
#include <atlbase.h>
//#include <atlapp.h>
//#include "atlctrls.h"
#include <atlwin.h>

class FNIMContactListUI : public CWindowImpl<FNIMContactListUI >
        ,public nsIObserver
		,public nsSupportsWeakReference 
    
{
  
    NS_DECL_ISUPPORTS
    NS_DECL_NSIOBSERVER
  
public:
    
    FNIMContactListUI();
    ~FNIMContactListUI();

  BEGIN_MSG_MAP(FNIMContactListUI)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
  END_MSG_MAP()


  LRESULT OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);

  void Close();
  bool CreateNew(PRUint32 parent, 
      PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, 
      PRUint32 style, PRUint32 exStyle,PRBool *_retval);

  BOOL  CreateBrowser();
  nsresult onFNIMWebBrowserChrome_Ready();
private:
    BOOL windowclosed_;
    nsCOMPtr<nsIWebBrowser> ansIWebBrowser_;
    //nsCOMPtr<nsIDOMWindow> theMainDOMWindow_;
};


class FNIMContactListUI_Locator : public IFNIMWindowLocator
    ,public nsIObserver
    ,public nsSupportsWeakReference 
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOBSERVER
  NS_DECL_IFNIMWINDOWLOCATOR


  FNIMContactListUI_Locator();

  FNIMContactListUI_Locator(boost::shared_ptr<FNIMContactListUI> aFNIMContactListUI , IFNIMToggleChatSessionMainWindow* amainWindow);
   ~FNIMContactListUI_Locator();
  
protected:
    nsresult getPos_expected( RECT *rc);
    nsresult adjustLayout(const RECT* prc );

    nsCOMPtr<IFNIMToggleChatSessionMainWindow > mainWindow_;
    boost::shared_ptr<FNIMContactListUI> _FNIMContactListUI;

    RECT rc_ecpected_ ;

    nsCOMPtr<nsITimer>  aNSTimer_;

};

#endif //FNIMCONTACTLISTUI_HEADER__