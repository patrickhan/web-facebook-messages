#include "SkypeToggleChatSessionFNMainWindow.h"

#include "nsIWebNavigation.h"
#include "nsIWebBrowserChrome.h"
#include "FNIMWebBrowserChromeUI.h"


#include "nsIInterfaceRequestor.h"
#include "nsIObserverService.h"
#include "nsIObserver.h"
#include "nsIURI.h"
#include "nsIWebBrowserFocus.h"
#include "nsIWindowWatcher.h"
#include "nsComponentManagerUtils.h"
#include "nsServiceManagerUtils.h"


// NON-FROZEN APIs!
#include "nsIBaseWindow.h"
#include "nsIWebNavigation.h"


/* Implementation file */
//NS_IMPL_ISUPPORTS1(FNIMToggleChatSessionMainWindow, IFNIMToggleChatSessionMainWindow)

SkypeToggleChatSessionFNMainWindow::SkypeToggleChatSessionFNMainWindow()//: m_hWnd(0U)
{
  /* member initializers and constructor code */
    
}

SkypeToggleChatSessionFNMainWindow::~SkypeToggleChatSessionFNMainWindow()
{
  /* destructor code */
}



LRESULT SkypeToggleChatSessionFNMainWindow::OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */)
{
    if(ansIWebBrowser_ )
    {
         DestoryBrowser();
         ansIWebBrowser_.forget();
    }


  return 0;
}

LRESULT SkypeToggleChatSessionFNMainWindow::OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */)
{
    CreateBrowser( );

    return 0;
}

LRESULT SkypeToggleChatSessionFNMainWindow::onPosChanged(UINT message, WPARAM wParam , LPARAM lParam , BOOL&  bHandled )
{
    if(ansIWebBrowser_)
    {
        nsCOMPtr<nsIWebBrowserChrome> ansIWebBrowserChrome ;
        nsresult rv = ansIWebBrowser_->GetContainerWindow(getter_AddRefs(ansIWebBrowserChrome));
        if(rv == NS_OK && ansIWebBrowserChrome)
        {
            FNIMWebBrowserChromeUI::ResizeEmbedding(ansIWebBrowserChrome);
        }
    }
    return NS_OK;
}

PRBool SkypeToggleChatSessionFNMainWindow:: CreateNew( const LPRECT  prc)
{


    RECT rc = {0,0, 1000, 800};
    if(prc == NULL)
    {
        return PR_FALSE;
        //prc = &rc;

    }
    //getDesiredWindowRect( &rc );
    //HWND newWin = Create(0, &rc, NULL, WS_OVERLAPPEDWINDOW | WS_OVERLAPPED| WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_THICKFRAME, WS_EX_WINDOWEDGE);
    HWND newWin = Create(0, prc, NULL, WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN , WS_EX_TOOLWINDOW);
    if(::IsWindow(newWin ))
    {
        return PR_TRUE;
    }


    return PR_FALSE;
}
void  SkypeToggleChatSessionFNMainWindow::Close( )
{
    DestroyWindow();
    return  ;
}
PRBool  SkypeToggleChatSessionFNMainWindow:: Show( )
{
    ShowWindow(SW_SHOW);
    return PR_TRUE;
}
PRBool  SkypeToggleChatSessionFNMainWindow:: Hide( )
{
    ShowWindow(SW_HIDE);
    return PR_TRUE;
}

BOOL SkypeToggleChatSessionFNMainWindow:: adjustLayout()
{
    return FALSE;
}
 

//lint -e{1762,831,774,948}
BOOL  SkypeToggleChatSessionFNMainWindow::CreateBrowser()
{
    if( ansIWebBrowser_ )
        return TRUE;
    //Create browsersite widnow
    HWND browserSiteWidnow = m_hWnd;
    if(!::IsWindow(browserSiteWidnow))
        return FALSE;

    nsCOMPtr<nsIWebBrowser>  aWebBrowser = do_CreateInstance("@mozilla.org/embedding/browser/nsWebBrowser;1");
    if (!aWebBrowser)
        return FALSE;


    ansIWebBrowser_ = aWebBrowser ;

    FNIMWebBrowserChrome *aBrowserChrome = new FNIMWebBrowserChrome( aWebBrowser, browserSiteWidnow);
    if (aBrowserChrome == NULL)
    {
        return FALSE;
    }
    aBrowserChrome->AddRef();
    aBrowserChrome->SetChromeFlags(nsIWebBrowserChrome::CHROME_ALL );
    aBrowserChrome->SetParent(nsnull);
    aBrowserChrome->setChatSession( chat_Session_ );

    nsresult rv = aWebBrowser->SetContainerWindow(static_cast<nsIWebBrowserChrome*>(aBrowserChrome));
    if(NS_FAILED(rv) )
        return FALSE;
    nsCOMPtr<nsIBaseWindow> browserBaseWindow = do_QueryInterface(aWebBrowser);
    if(!browserBaseWindow )
        return FALSE;

    RECT rcLocation;
    ::GetWindowRect(browserSiteWidnow,//hparentWindow, 
        &rcLocation);

    rv  = browserBaseWindow->InitWindow( browserSiteWidnow,//hparentWindow,
        nsnull, 
        0, 0, 
        rcLocation.right - rcLocation.left, 
        rcLocation.bottom- rcLocation.top);
    if(NS_FAILED(rv) )
        return FALSE;

    rv = browserBaseWindow->Create();
    if(NS_FAILED(rv) )
        return FALSE;

    nsCOMPtr<nsIWebProgressListener> listener(static_cast<nsIWebProgressListener*>(aBrowserChrome));
    nsCOMPtr<nsIWeakReference> thisListener(do_GetWeakReference(listener));
    (void)aWebBrowser->AddWebBrowserListener(thisListener,  NS_GET_IID(nsIWebProgressListener));

    // Visible
    browserBaseWindow->SetVisibility(PR_TRUE);

    // Activated
    //nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(aWebBrowser);

    //if(browserAsFocus)
    //	browserAsFocus->Activate();

    nsCOMPtr<nsIWebNavigation> webNav(do_QueryInterface(aWebBrowser));
    if(!webNav)
        return  0;

    //[using the following surfix is to avoid the browser get url content from cache 
    //mozilla do cache to speed up, even though you set the parameter LOAD_FLAGS_BYPASS_CACHE
    nsEmbedString url ;

    url = NS_LITERAL_STRING("chrome://fnidguard/content/fnim.xul");
    rv  = webNav->LoadURI(url.get(),//NS_ConvertASCIItoUTF16(url).get(),
        nsIWebNavigation::LOAD_FLAGS_NONE | nsIWebNavigation::LOAD_FLAGS_BYPASS_CACHE,// not cache
        nsnull,
        nsnull,
        nsnull);

    return TRUE;

}
//lint -e{529,438,952}
void SkypeToggleChatSessionFNMainWindow::DestoryBrowser()
{

    if(ansIWebBrowser_)
    {
        nsCOMPtr<nsIWebBrowserChrome> aBrowserChrome;
        nsresult rv = ansIWebBrowser_->GetContainerWindow(getter_AddRefs(aBrowserChrome) );

        if(NS_SUCCEEDED(rv) )
        {
            aBrowserChrome->DestroyBrowserWindow();
        }
    }
}

void SkypeToggleChatSessionFNMainWindow::SetFocusBrowser(  )
{
    nsCOMPtr<nsIBaseWindow> browserBaseWindow = do_QueryInterface(ansIWebBrowser_);

    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(ansIWebBrowser_);
    if (browserAsFocus && browserBaseWindow)
    {
        browserBaseWindow->SetFocus();
        browserAsFocus->Activate();
    }
}
void SkypeToggleChatSessionFNMainWindow::KillFocusBrowser(  )
{
    nsCOMPtr<nsIBaseWindow> browserBaseWindow = do_QueryInterface(ansIWebBrowser_);

    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(ansIWebBrowser_);
    if (browserAsFocus && browserBaseWindow)
    {
        browserAsFocus->Deactivate();
    }
}