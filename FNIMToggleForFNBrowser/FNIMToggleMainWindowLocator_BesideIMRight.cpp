#include "FNIMToggleMainWindowLocator_BesideIMRight.h"


#include "nsIWindowWatcher.h"
//#include "nsIDOMWindowInternal.h"
#include "nsIDOMWindow.h" 
#include <nsServiceManagerUtils.h>
#include "nsComponentManagerUtils.h"
#include "nsStringAPI.h"


extern HWND getFNDesptopWidnow();
extern HWND getFNDesptopWidnowView();
//{
//    return 0;
//}

NS_IMPL_ISUPPORTS3(FNIMToggleMainWindowLocator_BesideIMRight, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMWindowLocator);


FNIMToggleMainWindowLocator_BesideIMRight::FNIMToggleMainWindowLocator_BesideIMRight()
{
   ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}
FNIMToggleMainWindowLocator_BesideIMRight::FNIMToggleMainWindowLocator_BesideIMRight(
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
 
FNIMToggleMainWindowLocator_BesideIMRight::~FNIMToggleMainWindowLocator_BesideIMRight()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 
}

////////////////////////////////////////////////////////////////
// the expected area should be the smae size as IM chat Session window and just beside the window's right
nsresult FNIMToggleMainWindowLocator_BesideIMRight::getPos_expected(RECT *rc)
{
    nsresult ret = NS_ERROR_FAILURE;
    if(rc == NULL)
        return ret;

    if(!readWindow_  || !inputWindow_ ||!mainWindow_)
    {
        return ret;
    }
    HWND win = 0;
    mainWindow_->GetM_hWnd((PRUint32*) &win);
    if(!::IsWindow(win))
    {
        return NS_ERROR_FAILURE;
    }
    RECT rc_sessionWindow = {0};
    ::GetWindowRect(win, &rc_sessionWindow);

    HWND parent = ::GetAncestor(win,GA_PARENT );
   if( ::GetDesktopWindow() != parent)
   {
       RECT rc_parent = {0};
       ::GetWindowRect(parent , &rc_parent);


       rc->top    = rc_sessionWindow.top - rc_parent.top  ;
       rc->left   = rc_sessionWindow.right - rc_parent.left  ;
       rc->right  = rc->left   + rc_sessionWindow.right - rc_sessionWindow.left;
       rc->bottom = rc->top    + rc_sessionWindow.bottom -rc_sessionWindow.top;

   }
   else
   {
       rc->left    = rc_sessionWindow.right ;
       rc->right   = rc_sessionWindow.right + (rc_sessionWindow.right - rc_sessionWindow.left) ;
       rc->top     = rc_sessionWindow.top ;
       rc->bottom  = rc_sessionWindow.bottom ;
   }
    return NS_OK;
}
nsresult FNIMToggleMainWindowLocator_BesideIMRight:: adjustLayout(const RECT* prc )
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

        HWND fndesktopwindow = getFNDesptopWidnowView();
        HWND myparent = ::GetParent( win );
        if(fndesktopwindow != myparent  && ::IsWindow(fndesktopwindow) )
        {
            ::SetParent(win,fndesktopwindow );
        }
        BOOL b  = ::MoveWindow(win, rc_ecpected_.left, rc_ecpected_.top, rc_ecpected_.right - rc_ecpected_.left, rc_ecpected_.bottom -rc_ecpected_.top, TRUE);
        if(b)
        {
            return NS_OK;
        }
        //return MoveWindow(rc_ecpected_.left, rc_ecpected_.top, rc_ecpected_.right - rc_ecpected_.left, rc_ecpected_.bottom -rc_ecpected_.top, TRUE);
    }
    return NS_ERROR_FAILURE;
}

nsresult FNIMToggleMainWindowLocator_BesideIMRight::SyncPosition()
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

nsresult FNIMToggleMainWindowLocator_BesideIMRight::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
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
nsresult FNIMToggleMainWindowLocator_BesideIMRight::Locate( )
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


nsresult FNIMToggleMainWindowLocator_BesideIMRight::Close()
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


