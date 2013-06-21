#include "SkypeToggleChatSessionMainWindow.h"


#include "nsIObserverService.h"
#include "nsServiceManagerUtils.h"
 #include "nsComponentManagerUtils.h"

#define   SKYPE_MAINWINDOW_CLASSNAME "tSkMainForm"
#define   SKYPE_SUBSESSIONWINDOW_CLASSNAME "TConversationForm"

HWND getFNDesptopWidnow()
{
 return ::FindWindow(nsnull, L"fn-desktop-main-116959D9-260E-46d3-84B5-C45705E8CFD4"); //top level;
}

HWND getFNDesptopWidnowView()
{
    HWND fndesktopMainWnd = ::FindWindow(nsnull, L"fn-desktop-main-116959D9-260E-46d3-84B5-C45705E8CFD4"); //top level;
    if(::IsWindow(fndesktopMainWnd))
    {
        HWND fndesktopMainWnd_child  = GetWindow(fndesktopMainWnd, GW_CHILD);
        if(::IsWindow(fndesktopMainWnd_child) )
        {
            return ::FindWindowEx(fndesktopMainWnd_child, nsnull , nsnull, L"fn-desktop-view-116959D9-260E-46d3-84B5-C45705E8CFD4"); //top level;
        }
    }
    return nsnull;
}



/* Implementation file */
NS_IMPL_ISUPPORTS1(SkypeToggleChatSessionMainWindow, IFNIMToggleChatSessionMainWindow)

SkypeToggleChatSessionMainWindow::SkypeToggleChatSessionMainWindow(): m_hWnd(0U)
{
  /* member initializers and constructor code */
    //window_caption_
    window_classname_.AppendLiteral( SKYPE_MAINWINDOW_CLASSNAME ); 
    subSessionWindow_classname_.AppendLiteral( SKYPE_SUBSESSIONWINDOW_CLASSNAME ); 
}

SkypeToggleChatSessionMainWindow::~SkypeToggleChatSessionMainWindow()
{
  /* destructor code */
}

/* attribute long m_hWnd; */
NS_IMETHODIMP SkypeToggleChatSessionMainWindow::GetM_hWnd(PRUint32 *aM_hWnd)
{
    if( nsnull != aM_hWnd)
    {
        *aM_hWnd = m_hWnd;
    }
    
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatSessionMainWindow::SetM_hWnd(PRUint32 aM_hWnd)
{

    m_hWnd = aM_hWnd ;
    return NS_OK;
}

/* attribute AString classname; */
NS_IMETHODIMP SkypeToggleChatSessionMainWindow::GetClassname(nsAString & aClassname)
{
    aClassname = window_classname_;
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatSessionMainWindow::SetClassname(const nsAString & aClassname)
{
    window_classname_ = aClassname;
    return NS_OK;
}

/* attribute AString caption; */
NS_IMETHODIMP SkypeToggleChatSessionMainWindow::GetCaption(nsAString & aCaption)
{
    aCaption = window_caption_ ;
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatSessionMainWindow::SetCaption(const nsAString & aCaption)
{
    window_caption_ = aCaption;
    return NS_OK;
}


void SkypeToggleChatSessionMainWindow::getSubSesssionWindowClassName(nsEmbedString  &className)
{
    className = subSessionWindow_classname_ ;
}

NS_IMETHODIMP SkypeToggleChatSessionMainWindow::FindoutWindow(nsIArray **_retval) 
{
    return NS_ERROR_NOT_IMPLEMENTED;//obsolete
}


////////////////////////////////////////////////////////////////////
//SkypeChatSessionMainWindowLocator 

NS_IMPL_ISUPPORTS1(SkypeChatSessionMainWindowLocator, 
                   IFNIMToggleChatSessionMainWindowLocator);

#include "nsIMutableArray.h"
#include "nsIVariant.h"
#include "nsComponentManagerUtils.h"
#include "nsServiceManagerUtils.h"




#include "Windows.h"


static BOOL CALLBACK my_EnumWindowsProc( HWND hwnd,    LPARAM lParam)
{
  SkypeChatSessionMainWindowLocator* aMainWindow = reinterpret_cast <SkypeChatSessionMainWindowLocator*>(lParam);
  if(aMainWindow != nsnull)
  {
      char name[256] ;
      memset(name, 0, sizeof(name));
      nsEmbedString classname( NS_LITERAL_STRING( SKYPE_MAINWINDOW_CLASSNAME ) );
      nsEmbedString sunSession_classname(NS_LITERAL_STRING(SKYPE_SUBSESSIONWINDOW_CLASSNAME));

      ::GetClassNameA(hwnd, name, 255);
      if( classname.EqualsLiteral(name) && ::GetParent(hwnd) ==0 )//top level window 
      {
          HWND seesion_window = ::FindWindowEx(hwnd, 0, sunSession_classname.get(), nsnull);
          if(::IsWindow( seesion_window) )
          {
              aMainWindow->addWindow( (PRUint32)seesion_window );
          }
      }
      else if(sunSession_classname.EqualsLiteral(name)  && ::GetParent(hwnd) ==0 )//top level window : it is the seperated windo mode
      {
          aMainWindow->addWindow( (PRUint32)hwnd );
      }
  }
  return TRUE;
}

NS_IMETHODIMP SkypeChatSessionMainWindowLocator::Find(nsIArray **_retval) 
{
    
    hWnds_.clear();    

    nsCOMPtr<nsIMutableArray > foundWindows = do_CreateInstance(NS_ARRAY_CONTRACTID);
    

    if(foundWindows)
    {
        foundWindows->QueryInterface(NS_GET_IID(nsIArray ), (void**) _retval);
    }
    else
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }

    //1top level window finding
    BOOL  ok  = EnumWindows(      my_EnumWindowsProc,    (LPARAM)(this) );

    std::list<PRUint32>::iterator itor;
    for(itor = hWnds_.begin() ; itor != hWnds_.end() ; itor++)
    {
        nsCOMPtr<nsIWritableVariant>  ele = do_CreateInstance(NS_VARIANT_CONTRACTID);
        ele->SetAsInt32( (PRInt32)(*itor));
        foundWindows->AppendElement(ele, PR_FALSE);
    }
    return NS_OK;
 
}
SkypeChatSessionMainWindowLocator::SkypeChatSessionMainWindowLocator()
{
}
SkypeChatSessionMainWindowLocator::~SkypeChatSessionMainWindowLocator()
{
}
void SkypeChatSessionMainWindowLocator::addWindow( PRUint32 wnd)
{
    hWnds_.push_back(wnd);
}


nsresult SkypeChatSessionMainWindowLocator::Close( )
{
    return NS_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//class FNIMToggleChatFNMainWindowLocator
 
NS_IMPL_ISUPPORTS3(FNIMToggleChatFNMainWindowLocator, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMWindowLocator);


FNIMToggleChatFNMainWindowLocator::FNIMToggleChatFNMainWindowLocator()
{
   ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}
FNIMToggleChatFNMainWindowLocator::FNIMToggleChatFNMainWindowLocator(
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

FNIMToggleChatFNMainWindowLocator::~FNIMToggleChatFNMainWindowLocator()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 
}

////////////////////////////////////////////////////////////////
nsresult FNIMToggleChatFNMainWindowLocator::getPos_expected(RECT *rc)
{
    nsresult ret = NS_ERROR_FAILURE;
    if(rc == NULL)
        return ret;

    if(!readWindow_  || !inputWindow_)
    {
        return ret;
    }

    HWND readWindow_handle = 0;
    readWindow_ ->GetM_hWnd((PRUint32*)&readWindow_handle);



    HWND inputWindow_handle = 0;
    inputWindow_ ->GetM_hWnd((PRUint32*)&inputWindow_handle);

    if(!::IsWindow(inputWindow_handle) || !::IsWindow(readWindow_handle))
    {
        return ret;
    }


    HWND parent_readWindow = ::GetParent(readWindow_handle );

    RECT input_RC = {0};
    RECT read_RC = {0};
    BOOL b1 = ::GetWindowRect(readWindow_handle,  &read_RC );
    BOOL b2 = ::GetWindowRect(inputWindow_handle, &input_RC);

    POINT pt= {0};
    ::ClientToScreen(parent_readWindow , &pt);

    if(b1 && b2)
    {
        if( ::UnionRect(rc, &read_RC,  &input_RC) )
        {
            OffsetRect( rc, -pt.x, -pt.y);

        }
    }

    return NS_OK;
}
nsresult FNIMToggleChatFNMainWindowLocator:: adjustLayout(const RECT* prc )
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

        BOOL b  = ::MoveWindow(win, 
            rc_ecpected_.left, 
            rc_ecpected_.top, 
            rc_ecpected_.right - rc_ecpected_.left, 
            rc_ecpected_.bottom -rc_ecpected_.top, TRUE);
        if(b)
        {
            return NS_OK;
        }
    }
    return NS_ERROR_FAILURE;
}

nsresult FNIMToggleChatFNMainWindowLocator::SyncPosition()
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

nsresult FNIMToggleChatFNMainWindowLocator::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
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
nsresult FNIMToggleChatFNMainWindowLocator::Locate( )
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
        HWND parent = ::GetParent((HWND) refWindow);  //skype special

        PRBool bret = PR_FALSE;
        fnMainWindow_->CreateNew((PRUint32)parent, 
            (PRInt32)rc.left, (PRInt32) rc.top, (PRUint32)(rc.right-rc.left), (PRUint32)(rc.bottom-rc.top),
            WS_CHILD  | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0U, &bret);
        if(bret == PR_TRUE)
        {
            
            fnMainWindow_->GetWindowHandle((PRUint32*)&fnMainWindow_handle);
            if(::IsWindow(fnMainWindow_handle) )
            {
                ::SetWindowPos(fnMainWindow_handle, HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);

                LONG_PTR  styles = ::GetWindowLongPtr((HWND)refWindow, GWL_STYLE );
                ::SetWindowLongPtr( refWindow, GWL_STYLE ,styles |WS_CLIPSIBLINGS);
            }
        }

    }

    return 0;
}


nsresult FNIMToggleChatFNMainWindowLocator::Close()
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



///////////////////////////////////////////////////////////////////////////////////////
//class FNIMToggleButtonLocator


 
 
NS_IMPL_ISUPPORTS3(FNIMToggleButtonLocator, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMWindowLocator);


FNIMToggleButtonLocator::FNIMToggleButtonLocator()
{
   ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}
FNIMToggleButtonLocator::FNIMToggleButtonLocator(
    IFNIMToggleButton * button,
    IFNIMToggleChatReadWindow *inw)
{

    readWindow_ = inw;
    button_ = button;
    ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}

FNIMToggleButtonLocator::~FNIMToggleButtonLocator()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 
}


#define FN_TOOGLE_BUTTON_HEIGHT 32 
#define FN_TOOGLE_BUTTON_WIDTH  32 

////////////////////////////////////////////////////////////////
nsresult FNIMToggleButtonLocator::getPos_expected(RECT *prc)
{
    nsresult ret = NS_ERROR_FAILURE;
    if(prc == nsnull)
        return ret;

    if(! button_||  !readWindow_ )
    {
        return ret;
    }

    HWND refWindow = 0;
    readWindow_ ->GetM_hWnd((PRUint32*)&refWindow);

    if(!::IsWindow(refWindow)  )
    {
        return ret;
    }
 

    HWND parent = ::GetParent(refWindow );

    RECT rc = {0};
    ::GetWindowRect( refWindow, &rc);

    POINT pt= {0};
    ::ClientToScreen(parent , &pt);



    prc->bottom    = rc.top - pt.y  ;
    prc->right   = rc.right - pt.x;
    prc->left  = prc->right   - FN_TOOGLE_BUTTON_WIDTH;
    prc->top = prc->bottom    - FN_TOOGLE_BUTTON_HEIGHT;


    return NS_OK;
}
nsresult FNIMToggleButtonLocator:: adjustLayout(const RECT* prc )
{

    HWND win = 0;
    button_->GetM_hWnd((PRUint32*) &win);
    if(!::IsWindow(win))
    {
        return NS_ERROR_FAILURE;
    }
    if(!IsRectEmpty(prc) &&!::EqualRect(&rc_ecpected_, prc))
    {
        ::CopyRect(&rc_ecpected_, prc);

        BOOL b =  MoveWindow(win, rc_ecpected_.left, rc_ecpected_.top, rc_ecpected_.right - rc_ecpected_.left, rc_ecpected_.bottom -rc_ecpected_.top, TRUE);
        if(b)
        {
            return NS_OK;
        }
    }
    return NS_ERROR_FAILURE;
}

nsresult FNIMToggleButtonLocator::SyncPosition()
{
    if(! button_||  !readWindow_ )
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

nsresult FNIMToggleButtonLocator::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{
    if(0 == CaseInsensitiveCompare(aTopic, "timer-callback", 14U)  && button_)
    {
        HWND button_handle = 0;
        button_->GetM_hWnd((PRUint32*)&button_handle);
        if(!::IsWindow(button_handle) )
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
nsresult FNIMToggleButtonLocator::Locate( )
{

    if(! button_||  !readWindow_ )
        return NS_ERROR_FAILURE;

    HWND refWindow = 0;
    readWindow_->GetM_hWnd( (PRUint32 *)&refWindow);
    if(! ::IsWindow( refWindow) )
        return NS_ERROR_FAILURE;

    RECT rc ={0};
    nsresult rv =  getPos_expected( &rc );
    if(rv!= NS_OK || ::IsRectEmpty(&rc))
        return NS_ERROR_FAILURE;


    HWND parent = ::GetParent((HWND) refWindow);
 

    PRBool created = PR_FALSE;
    rv = button_->CreateNew((PRUint32 )parent, 
        (PRInt32)rc.left, (PRInt32)rc.top, 
        (PRUint32)(rc.right-rc.left), PRUint32(rc.bottom-rc.top), 
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0U, &created);
    HWND buttonWindow = 0;
    button_->GetM_hWnd( (PRUint32 *)&buttonWindow);
    if(!::IsWindow(buttonWindow))
    {
        return NS_ERROR_FAILURE;
    }

    ::SetWindowPos(buttonWindow, HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);

    //HWND send  = ::FindWindowEx(parent   ,nsnull,  L"NMGenWindowClass" , L"NMButton");
    //HWND send1  = ::FindWindowEx(send   ,nsnull,  L"Button" , nsnull);
    //LONG_PTR  styles = ::GetWindowLongPtr((HWND)send, GWL_STYLE );
    //::SetWindowLongPtr((HWND)send, GWL_STYLE ,styles |WS_CLIPSIBLINGS);

    // styles = ::GetWindowLongPtr((HWND)send1, GWL_STYLE );
    //::SetWindowLongPtr((HWND)send1, GWL_STYLE ,styles |WS_CLIPSIBLINGS);


    return NS_OK;
}

nsresult FNIMToggleButtonLocator::Close()
{
    button_ = nsnull;
    readWindow_ =  nsnull;

    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    }
    return NS_OK;
}






//class SkypeFNIMToggleChatFNInputWindowLocator : public IFNIMToggleChatFNInputWindowLocator

NS_IMPL_ISUPPORTS3(SkypeFNIMToggleChatFNInputWindowLocator, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMWindowLocator );
SkypeFNIMToggleChatFNInputWindowLocator::SkypeFNIMToggleChatFNInputWindowLocator()
{
    inputWindow_ = nsnull;
    ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}

SkypeFNIMToggleChatFNInputWindowLocator::SkypeFNIMToggleChatFNInputWindowLocator(
        IFNIMToggleChatInputWindow *inw   ,
        IFNIMToggleChatFNInputWindow* fninw)
{
    fninputWindow_ =  fninw;
    inputWindow_ = inw;
    ::SetRectEmpty((LPRECT)(&rc_ecpected_));
    refWindow_ = 0;

}
SkypeFNIMToggleChatFNInputWindowLocator::~SkypeFNIMToggleChatFNInputWindowLocator()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 
}

NS_IMETHODIMP SkypeFNIMToggleChatFNInputWindowLocator::Close()
{
    inputWindow_ =  nsnull;
    fninputWindow_ = nsnull;

    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    }
    return NS_OK;
}

NS_IMETHODIMP SkypeFNIMToggleChatFNInputWindowLocator::Locate()
{
    
    if(!inputWindow_ || !fninputWindow_)
        return NS_ERROR_FAILURE;

    HWND refWindow = 0;
    inputWindow_->GetM_hWnd( (PRUint32 *)&refWindow);
    if(! ::IsWindow( refWindow) )
        return NS_ERROR_FAILURE;
    refWindow_ = refWindow;

    RECT rc ={0};
    PRBool got =  getDesiredWindowRect( &rc );
    if(got == PR_FALSE|| ::IsRectEmpty(&rc))
        return NS_ERROR_FAILURE;

    HWND parent = ::GetParent((HWND) refWindow);

    nsresult rv = NS_OK;
    PRBool ret_ok = PR_FALSE;
    nsCOMPtr<IFNIMWindowCreator> aIFNIMWindowCreator =  do_QueryInterface(fninputWindow_);
    if(aIFNIMWindowCreator )
    {
        rv = aIFNIMWindowCreator->CreateNew((PRUint32 )parent, 
            (PRInt32)rc.left, (PRInt32)rc.top, 
            (PRUint32)(rc.right-rc.left), PRUint32(rc.bottom-rc.top), 
            WS_CHILD  | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0U, &ret_ok);
        HWND afninputWindowWindow = 0;
        fninputWindow_->GetM_hWnd( (PRUint32 *)&afninputWindowWindow);
        if(!::IsWindow(afninputWindowWindow))
        {
            return NS_ERROR_FAILURE;
        }
    

        ::SetWindowPos(afninputWindowWindow, HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);
    }
    /*HWND send  = ::FindWindowEx(parent   ,nsnull,  L"NMGenWindowClass" , L"NMButton");
    HWND send1  = ::FindWindowEx(send   ,nsnull,  L"Button" , nsnull);
    LONG_PTR  styles = ::GetWindowLongPtr((HWND)send, GWL_STYLE );
    ::SetWindowLongPtr((HWND)send, GWL_STYLE ,styles |WS_CLIPSIBLINGS);

     styles = ::GetWindowLongPtr((HWND)send1, GWL_STYLE );
    ::SetWindowLongPtr((HWND)send1, GWL_STYLE ,styles |WS_CLIPSIBLINGS);*/


    return NS_OK;
}

NS_IMETHODIMP SkypeFNIMToggleChatFNInputWindowLocator::SyncPosition()
{
    if(!inputWindow_ || !fninputWindow_)
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

PRBool SkypeFNIMToggleChatFNInputWindowLocator::getCurrentWindowRect( RECT *prc)
{
    if(prc == nsnull || !fninputWindow_)
        return PR_FALSE;
    if(! ::IsWindow((HWND) refWindow_) )
        return PR_FALSE;


    PRUint32 fninputWindow_hWnd = 0U;
    fninputWindow_->GetM_hWnd(&fninputWindow_hWnd );
    if(! ::IsWindow((HWND) fninputWindow_hWnd) )
        return PR_FALSE;

    HWND parent = ::GetParent((HWND)fninputWindow_hWnd);

    RECT rc = {0};
    ::GetWindowRect((HWND)fninputWindow_hWnd, &rc);
    RECT rc_parent = {0};
    ::GetWindowRect(parent, &rc_parent);


    prc->top    = rc.top - rc_parent.top  ;
    prc->left   = rc.left - rc_parent.left;
    prc->right  = prc->left   + rc.right - rc.left;
    prc->bottom = prc->top    + rc.bottom -rc.top;


    return PR_TRUE;
}
PRBool SkypeFNIMToggleChatFNInputWindowLocator::getDesiredWindowRect( RECT *prc)
{
    if(prc == nsnull)
        return PR_FALSE;
    if(! ::IsWindow((HWND) refWindow_) )
        return PR_FALSE;
 

    HWND parent = ::GetParent((HWND) refWindow_);

    RECT rc = {0};
    ::GetWindowRect((HWND) refWindow_, &rc);
    RECT rc_parent = {0};
    ::GetWindowRect(parent , &rc_parent);

 
    prc->top    = rc.top - rc_parent.top  ;
    prc->left   = rc.left - rc_parent.left;
    prc->right  = prc->left   + rc.right - rc.left;
    prc->bottom = prc->top    + rc.bottom -rc.top;

    return PR_TRUE;
}

nsresult SkypeFNIMToggleChatFNInputWindowLocator:: adjustLayout(const RECT* prc )
{
    if(!inputWindow_ || !fninputWindow_)
    {//not have the needed data
        return NS_ERROR_FAILURE;
    }
    HWND win = 0;
    fninputWindow_->GetM_hWnd((PRUint32*) &win);
    if(!::IsWindow(win))
    {
        return NS_ERROR_FAILURE;
    }
    RECT rc_desired ={0};
    if( ! getDesiredWindowRect( &rc_desired))
        return 0;

    RECT rc_current ={0};
    if( ! getCurrentWindowRect( &rc_current))
        return 0;

    if( EqualRect (&rc_current ,&rc_desired ) )
    {
        return 0;
    }
    BOOL b  = ::MoveWindow(win, rc_desired.left, rc_desired.top, rc_desired.right - rc_desired.left, rc_desired.bottom -rc_desired.top, TRUE);
    if(b)
    {
        return NS_OK;
    }
    return NS_ERROR_FAILURE;
}
nsresult SkypeFNIMToggleChatFNInputWindowLocator::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{

    if(!fninputWindow_)
    {
        return NS_OK;
    }
    HWND aWindow_handle = 0;
    fninputWindow_->GetM_hWnd((PRUint32*)&aWindow_handle);


    if(0 == CaseInsensitiveCompare(aTopic, "timer-callback", 14U) )
    {
        if(!::IsWindow(aWindow_handle) )
        {
            if(aNSTimer_)
            {
                aNSTimer_->Cancel();
                aNSTimer_.forget();
            }
            return NS_OK;
        }
        if(IsWindowVisible(aWindow_handle) )
        {
            RECT rc ={0};
            adjustLayout(&rc );
        }
    }
    return NS_OK;
}


//////////////////////////////////////////////////////////////
///class SkypeFNIMToggleChatFNReadWindowLocator : public IFNIMWindowLocator
NS_IMPL_ISUPPORTS3(SkypeFNIMToggleChatFNReadWindowLocator, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMWindowLocator);


SkypeFNIMToggleChatFNReadWindowLocator::SkypeFNIMToggleChatFNReadWindowLocator()
{
}
 
SkypeFNIMToggleChatFNReadWindowLocator::SkypeFNIMToggleChatFNReadWindowLocator( 
    IFNIMToggleChatReadWindow *readw   ,
    IFNIMToggleChatFNReadWindow *fnreadw   )
{
    readWindow_ = readw ;
    fnreadWindow_ = fnreadw ;
    ::SetRectEmpty((LPRECT)(&rc_ecpected_));
    refWindow_ = 0;
}

SkypeFNIMToggleChatFNReadWindowLocator:: ~SkypeFNIMToggleChatFNReadWindowLocator()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 
}

NS_IMETHODIMP SkypeFNIMToggleChatFNReadWindowLocator::Close()
{
    readWindow_ =  nsnull;
    fnreadWindow_ = nsnull;

    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    }
    return NS_OK;
}

NS_IMETHODIMP SkypeFNIMToggleChatFNReadWindowLocator::Locate()
{
    if(!readWindow_ || !fnreadWindow_)
        return NS_ERROR_FAILURE;

    HWND refWindow = 0;
    readWindow_->GetM_hWnd( (PRUint32 *)&refWindow);
    if(! ::IsWindow( refWindow) )
        return NS_ERROR_FAILURE;
    refWindow_ = refWindow;

    RECT rc ={0};
    PRBool got =  getDesiredWindowRect( &rc );
    if(got == PR_FALSE|| ::IsRectEmpty(&rc))
        return NS_ERROR_FAILURE;

    nsresult rv = NS_OK;
    HWND parent = ::GetParent((HWND) refWindow);
    nsCOMPtr<IFNIMWindowCreator> aIFNIMWindowCreator =  do_QueryInterface(fnreadWindow_);
    if(aIFNIMWindowCreator )
    {
        PRBool ret_ok = PR_FALSE;
        rv = aIFNIMWindowCreator->CreateNew((PRUint32 )parent, 
            (PRInt32)rc.left, (PRInt32)rc.top, 
            (PRUint32)(rc.right-rc.left), PRUint32(rc.bottom-rc.top), 
            WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0U, &ret_ok);
        HWND buttonWindow = 0;
        fnreadWindow_->GetM_hWnd( (PRUint32 *)&buttonWindow);
        if(!::IsWindow(buttonWindow))
        {
            return NS_ERROR_FAILURE;
        }


        ::SetWindowPos(buttonWindow, HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);

    }
    /*HWND send  = ::FindWindowEx(parent   ,nsnull,  L"NMGenWindowClass" , L"NMButton");
    HWND send1  = ::FindWindowEx(send   ,nsnull,  L"Button" , nsnull);
    LONG_PTR  styles = ::GetWindowLongPtr((HWND)send, GWL_STYLE );
    ::SetWindowLongPtr((HWND)send, GWL_STYLE ,styles |WS_CLIPSIBLINGS);

     styles = ::GetWindowLongPtr((HWND)send1, GWL_STYLE );
    ::SetWindowLongPtr((HWND)send1, GWL_STYLE ,styles |WS_CLIPSIBLINGS);*/


    return NS_OK;
}

NS_IMETHODIMP SkypeFNIMToggleChatFNReadWindowLocator::SyncPosition()
{
     if(!readWindow_ || !fnreadWindow_)
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

PRBool SkypeFNIMToggleChatFNReadWindowLocator::getCurrentWindowRect( RECT *prc)
{
    if(prc == nsnull)
        return PR_FALSE;
    if(! ::IsWindow((HWND) refWindow_) )
        return PR_FALSE;
    PRUint32 afnreadWindow_hWnd = 0U;
    fnreadWindow_->GetM_hWnd(&afnreadWindow_hWnd );
    if(! ::IsWindow((HWND) afnreadWindow_hWnd) )
        return PR_FALSE;


    HWND parent = ::GetParent((HWND)afnreadWindow_hWnd);

    RECT rc = {0};
    ::GetWindowRect((HWND)afnreadWindow_hWnd, &rc);
    RECT rc_parent = {0};
    ::GetWindowRect(parent, &rc_parent);


    prc->top    = rc.top - rc_parent.top  ;
    prc->left   = rc.left - rc_parent.left;
    prc->right  = prc->left   + rc.right - rc.left;
    prc->bottom = prc->top    + rc.bottom -rc.top;



    return PR_TRUE;
}
PRBool SkypeFNIMToggleChatFNReadWindowLocator::getDesiredWindowRect( RECT *prc)
{
    if(prc == nsnull)
        return PR_FALSE;
    if(! ::IsWindow((HWND) refWindow_) )
        return PR_FALSE;
 

    HWND parent = ::GetParent((HWND) refWindow_);

    RECT rc = {0};
    ::GetWindowRect((HWND) refWindow_, &rc);
    RECT rc_parent = {0};
    ::GetWindowRect(parent , &rc_parent);

 
    prc->top    = rc.top - rc_parent.top  ;
    prc->left   = rc.left - rc_parent.left;
    prc->right  = prc->left   + rc.right - rc.left;
    prc->bottom = prc->top    + rc.bottom -rc.top;

    return PR_TRUE;

}

nsresult SkypeFNIMToggleChatFNReadWindowLocator:: adjustLayout(const RECT* prc )
{
    if(!readWindow_ || !fnreadWindow_)
    {//not have the needed data
        return NS_ERROR_FAILURE;
    }
    HWND win = 0;
    fnreadWindow_->GetM_hWnd((PRUint32*) &win);
    if(!::IsWindow(win))
    {
        return NS_ERROR_FAILURE;
    }

    RECT rc_desired ={0};
    if( ! getDesiredWindowRect( &rc_desired))
        return 0;

    RECT rc_current ={0};
    if( ! getCurrentWindowRect( &rc_current))
        return 0;

    if( EqualRect (&rc_current ,&rc_desired ) )
    {
        return 0;
    }
    BOOL b  = ::MoveWindow(win, rc_desired.left, rc_desired.top, rc_desired.right - rc_desired.left, rc_desired.bottom -rc_desired.top, TRUE);
    if(b)
    {
        return NS_OK;
    }


    return NS_ERROR_FAILURE;
}
nsresult SkypeFNIMToggleChatFNReadWindowLocator::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{


    if(!fnreadWindow_)
    {
        return NS_OK;
    }
    HWND aWindow_handle = 0;
    fnreadWindow_->GetM_hWnd((PRUint32*)&aWindow_handle);

    if(0 == CaseInsensitiveCompare(aTopic, "timer-callback", 14U) )
    {
        if(!::IsWindow(aWindow_handle) )
        {
            if(aNSTimer_)
            {
                aNSTimer_->Cancel();
                aNSTimer_.forget();
            }
            return NS_OK;
        }
        if(::IsWindowVisible(aWindow_handle)  )
        {
            RECT rc ={0};
            adjustLayout(&rc );
        }
    }
    return NS_OK;
}
