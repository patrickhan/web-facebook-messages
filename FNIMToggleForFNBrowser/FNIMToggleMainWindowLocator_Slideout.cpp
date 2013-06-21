#include "FNIMToggleMainWindowLocator_Slideout.h"


#include "nsIWindowWatcher.h"
//#include "nsIDOMWindowInternal.h"
#include "nsIDOMWindow.h" 
#include <nsServiceManagerUtils.h>
#include "nsComponentManagerUtils.h"
#include "nsStringAPI.h"

NS_IMPL_ISUPPORTS3(FNIMToggleMainWindowLocator_Slideout, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMWindowLocator);


FNIMToggleMainWindowLocator_Slideout::FNIMToggleMainWindowLocator_Slideout()
{
   ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}
FNIMToggleMainWindowLocator_Slideout::FNIMToggleMainWindowLocator_Slideout(
    IFNIMToggleChatFNMainWindow * fnmw,
    IFNIMToggleChatSessionMainWindow *mw,
    IFNIMToggleChatInputWindow *inw,
    IFNIMToggleChatReadWindow* rw)
{
    mainWindow_ = mw;
    inputWindow_ = inw;
    readWindow_ = rw;
    fnMainWindow_ = fnmw;
    ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}
 
FNIMToggleMainWindowLocator_Slideout::~FNIMToggleMainWindowLocator_Slideout()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 
}

////////////////////////////////////////////////////////////////
nsresult FNIMToggleMainWindowLocator_Slideout::getPos_expected(RECT *rc)
{
    nsresult ret = NS_ERROR_FAILURE;
    if(rc == NULL)
        return ret;

    if(!readWindow_  || !inputWindow_)
    {
        return ret;
    }

    nsCOMPtr<nsIWindowWatcher> windowWatcher = do_GetService(NS_WINDOWWATCHER_CONTRACTID);

    nsCOMPtr<nsIDOMWindowInternal> saltelliteWindow;
    nsCOMPtr<nsIDOMWindow> active;
    windowWatcher->GetWindowByName(TEXT("satellite"),nsnull,getter_AddRefs(active));
    if (active) 
    {
        active->QueryInterface(NS_GET_IID(nsIDOMWindowInternal), getter_AddRefs(saltelliteWindow));
    }

    if(!saltelliteWindow)
        return ret;

    //get the size value of satellite
    PRInt32 outerHeight = 0;
    saltelliteWindow->GetOuterHeight(&outerHeight);
    PRInt32 outerWidth = 0;
    saltelliteWindow->GetOuterWidth(&outerWidth);
 
    PRInt32 screenX = 0;
    saltelliteWindow->GetScreenX(&screenX);
    PRInt32 screenY = 0;
    saltelliteWindow->GetScreenY(&screenY);

    //make the window a full screen size
    LONG lScrnWidth  = GetSystemMetrics ( SM_CXSCREEN );
    LONG lScrnHeight = GetSystemMetrics ( SM_CYSCREEN );

    //editro defaule size is 372X480
    //default sildeout size  is 1024xlScrnHeight 1024- 44 = 980 ; 44 is the 
    INT slideoutWidth = 1024-outerWidth;


    rc ->left   = lScrnWidth - slideoutWidth; 
    rc ->top    = screenY;
    rc ->right  = lScrnWidth - outerWidth;
    rc ->bottom = outerHeight;

    return NS_OK;
}
nsresult FNIMToggleMainWindowLocator_Slideout:: adjustLayout(const RECT* prc )
{

    HWND win = 0;
    fnMainWindow_->GetWindowHandle((PRUint32*) &win);
    if(!::IsWindow(win))
    {
        return NS_ERROR_FAILURE;
    }
    if(!IsRectEmpty(prc) &&!::EqualRect(&rc_ecpected_, prc))
    {
        ::CopyRect(&rc_ecpected_, prc);

        /*BOOL b =  ::SetWindowPos(win, HWND_TOP,
            rc_ecpected_.left, rc_ecpected_.top, 
            rc_ecpected_.right - rc_ecpected_.left, rc_ecpected_.bottom -rc_ecpected_.top,
            0U );*/
        BOOL b  = ::MoveWindow(win, rc_ecpected_.left, rc_ecpected_.top, rc_ecpected_.right - rc_ecpected_.left, rc_ecpected_.bottom -rc_ecpected_.top, TRUE);
        if(b)
        {
            return NS_OK;
        }
        //return MoveWindow(rc_ecpected_.left, rc_ecpected_.top, rc_ecpected_.right - rc_ecpected_.left, rc_ecpected_.bottom -rc_ecpected_.top, TRUE);
    }
    return NS_ERROR_FAILURE;
}

nsresult FNIMToggleMainWindowLocator_Slideout::SyncPosition()
{
    if(! mainWindow_||  !inputWindow_ || !readWindow_ || !fnMainWindow_)
    {//not have the needed data
        return NS_ERROR_FAILURE;
    }

    if(!aNSTimer_)
    {
        aNSTimer_ =  do_CreateInstance("@mozilla.org/timer;1");
        if(!aNSTimer_) 
        {
            return NS_ERROR_FAILURE;
        }

        nsCOMPtr<nsIObserver> abserver;
        this->QueryInterface(NS_GET_IID(nsIObserver), (void**)getter_AddRefs(abserver) );
        if(abserver)
        {
            aNSTimer_->Init(abserver, 500U, nsITimer::TYPE_REPEATING_SLACK);
        }
    }
    return NS_OK;
}

nsresult FNIMToggleMainWindowLocator_Slideout::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{

    if(0 == CaseInsensitiveCompare(aTopic, "timer-callback", 14U) )
    {
        HWND fnMainWindow_handle = 0;
        fnMainWindow_->GetWindowHandle((PRUint32*)&fnMainWindow_handle);
        if(!::IsWindow(fnMainWindow_handle) )
        {
            if(aNSTimer_)
            {
                aNSTimer_->Cancel();
                aNSTimer_.forget();
            }
            return NS_OK;
        }
        RECT rc ={0};
        getPos_expected(&rc);
        adjustLayout(&rc );
    }
    return NS_OK;
}
nsresult FNIMToggleMainWindowLocator_Slideout::Locate( )
{

    if(!fnMainWindow_ ||!readWindow_)
        return NS_ERROR_FAILURE;

    HWND refWindow = 0;
    readWindow_->GetM_hWnd( (PRUint32 *)&refWindow);
    if(! ::IsWindow( refWindow) )
        return NS_ERROR_FAILURE;


    RECT rc ={0};
    nsresult rv =  getPos_expected( &rc );
    if(rv!= NS_OK || ::IsRectEmpty(&rc))
        return NS_ERROR_FAILURE;

    HWND fnMainWindow_handle = 0;
    fnMainWindow_->GetWindowHandle((PRUint32*)&fnMainWindow_handle);
    if(!::IsWindow(fnMainWindow_handle) )
    {//create //skype special
        HWND parent = 0;//::GetParent((HWND) refWindow);  //skype special

        PRBool bret = PR_FALSE;
        fnMainWindow_->CreateNew((PRUint32)parent, 
            (PRInt32)rc.left, (PRInt32) rc.top, (PRUint32)(rc.right-rc.left), (PRUint32)(rc.bottom-rc.top),
            WS_POPUP  | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_TOOLWINDOW, &bret);

        /*if(bret == PR_TRUE)
        {
            
            fnMainWindow_->GetWindowHandle((PRUint32*)&fnMainWindow_handle);
            if(::IsWindow(fnMainWindow_handle) )
            {
                ::SetWindowPos(fnMainWindow_handle, HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);

                LONG_PTR  styles = ::GetWindowLongPtr((HWND)refWindow, GWL_STYLE );
                ::SetWindowLongPtr( refWindow, GWL_STYLE ,styles |WS_CLIPSIBLINGS);
            }
        }*/

    }

    return 0;
}


nsresult FNIMToggleMainWindowLocator_Slideout::Close()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    }
    mainWindow_= nsnull;
    inputWindow_= nsnull;
    readWindow_= nsnull;
    fnMainWindow_= nsnull;
    return NS_OK;
}
