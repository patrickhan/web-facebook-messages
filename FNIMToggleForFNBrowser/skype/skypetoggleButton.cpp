#include "SkypeToggleButton.h"

#include "FNToggleImage.h"

#define FN_TOOGLE_BUTTON_HEIGHT 32 
#define FN_TOOGLE_BUTTON_WIDTH  32 
/* Implementation file */
NS_IMPL_ISUPPORTS1(SkypeToggleButton, IFNIMToggleButton)

SkypeToggleButton::SkypeToggleButton()
:shownFnWindow_(FALSE),
refWindow_(0U),
timerID_(0),
windowclosed_(FALSE),
_aToggleState(PR_FALSE)
{
    /* member initializers and constructor code */
}

SkypeToggleButton::~SkypeToggleButton()
{
    /* destructor code */
}

/* readonly attribute long m_hWnd; */
NS_IMETHODIMP SkypeToggleButton::GetM_hWnd(PRUint32 *aM_hWnd)
{

    if(aM_hWnd)
    {
        *aM_hWnd =(PRUint32) m_hWnd;
    }

    return NS_OK;
}

/* readonly attribute long m_hWnd; */
NS_IMETHODIMP SkypeToggleButton::Close()
{

    buttonEvnetListener_.Clear();

    if(timerID_ != 0)
    {
        KillTimer(timerID_ );
        timerID_ = 0;
    }
 

    if(! windowclosed_ )
    {
        windowclosed_ = TRUE; 
        if(::IsWindow(m_hWnd) )
        {
            DestroyWindow();
        }
    }   

    return NS_OK;
}


PRBool SkypeToggleButton::getCurrentWindowRect( RECT *prc)
{
    if(prc == nsnull)
        return PR_FALSE;
    if(! ::IsWindow((HWND) refWindow_) )
        return PR_FALSE;


    CWindow parent = GetParent();

    RECT rc = {0};
    GetWindowRect(&rc);
    RECT rc_parent = {0};
    parent.GetWindowRect(&rc_parent);


    prc->top    = rc.top - rc_parent.top  ;
    prc->left   = rc.right - rc_parent.left;
    prc->right  = prc->left   + FN_TOOGLE_BUTTON_WIDTH;
    prc->bottom = prc->top    + FN_TOOGLE_BUTTON_HEIGHT;


    return PR_TRUE;
}
PRBool SkypeToggleButton::getDesiredWindowRect( RECT *prc)
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
    prc->left   = rc.right - rc_parent.left;
    prc->right  = prc->left   + FN_TOOGLE_BUTTON_WIDTH;
    prc->bottom = prc->top    + FN_TOOGLE_BUTTON_HEIGHT;

   // ::OffsetRect( prc, 0,  -50);

    return PR_TRUE;

}

PRBool SkypeToggleButton::createButton( PRUint32 refWindow)
{
    if(! ::IsWindow((HWND) refWindow) )
        return PR_FALSE;

    refWindow_ = refWindow;
    ::SendMessage(HWND(refWindow_), WM_LBUTTONDBLCLK, 0, 0);

    HWND parent = ::GetParent((HWND) refWindow);

    RECT rc = {0};
    getDesiredWindowRect( &rc );

    HWND newWindow = Create(parent, &rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    if(!::IsWindow( newWindow))
    {
        return PR_FALSE;

    }

    SetWindowPos(HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);

    HWND send  = ::FindWindowEx(parent   ,nsnull,  L"NMGenWindowClass" , L"NMButton");
    HWND send1  = ::FindWindowEx(send   ,nsnull,  L"Button" , nsnull);
    LONG_PTR  styles = ::GetWindowLongPtr((HWND)send, GWL_STYLE );
    ::SetWindowLongPtr((HWND)send, GWL_STYLE ,styles |WS_CLIPSIBLINGS);

     styles = ::GetWindowLongPtr((HWND)send1, GWL_STYLE );
    ::SetWindowLongPtr((HWND)send1, GWL_STYLE ,styles |WS_CLIPSIBLINGS);

    return PR_TRUE;
}




LRESULT SkypeToggleButton::onPaint(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(&ps); 

    RECT rc = {0};
    GetClientRect( &rc);
    FNToggleImageDraw::draw(hdc, &rc);

    EndPaint(&ps); 

    return 0;
}

LRESULT SkypeToggleButton::onClick(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    //shownFnWindow_ = shownFnWindow_? PR_FALSE : PR_TRUE; 
    _aToggleState = _aToggleState == PR_TRUE? PR_FALSE : PR_TRUE;  

    PRBool stop = PR_FALSE;
    PRInt32 len = buttonEvnetListener_.Count();
    for(PRInt32 index = 0; index < len; ++index)
    {

        nsCOMPtr<IFNIMToggleButtonEvnetListener> aListener = buttonEvnetListener_.ObjectAt( index );
        if(aListener )
        {
            aListener->OnToggle(_aToggleState,  &stop);
            if(stop == PR_TRUE)
            {
                break;
            }
        }
    }

    return 0;
}

LRESULT SkypeToggleButton::OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{

    
    if(! windowclosed_ )
    {
        windowclosed_ = TRUE;
        
        if(aDestroyEvnetListener_)
        {
            aDestroyEvnetListener_->OnDestroy((nsISupports*)this);
            aDestroyEvnetListener_ = nsnull;
        }
        Close();
    }
    return 0;
}

LRESULT SkypeToggleButton::OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    windowclosed_ = FALSE;
  
    return 0;
}

LRESULT SkypeToggleButton::onTimer(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{

    RECT rc_desired ={0};
    if( ! getDesiredWindowRect( &rc_desired))
        return 0;

    RECT rc_current ={0};
    if( ! getCurrentWindowRect( &rc_current))
        return 0;

    if( EqualRect (&rc_current ,&rc_desired ) )
    {
        Invalidate();
        return 0;
    }

    BOOL ok = MoveWindow( &rc_desired, TRUE);

    Invalidate();
    return 0;
}

NS_IMETHODIMP SkypeToggleButton::GetState(PRBool *aToggleState)
{
    if(aToggleState)
        *aToggleState = _aToggleState ;
    return 0;
}
NS_IMETHODIMP SkypeToggleButton::SetState(PRBool aToggleState)
{
    _aToggleState = aToggleState;

    return 0;
}

NS_IMETHODIMP SkypeToggleButton::AddToggleEventListener(IFNIMToggleButtonEvnetListener *listener)
{
    if(listener == nsnull)
    {
        return NS_ERROR_INVALID_ARG;
    }

    PRBool hadit = PR_FALSE;
    PRInt32 len = buttonEvnetListener_.Count();
    for(PRInt32 index = 0; index < len; ++index)
    {

        nsCOMPtr<IFNIMToggleButtonEvnetListener> aListener = buttonEvnetListener_.ObjectAt( index );
        if(aListener ==  listener)
        {
            hadit = PR_TRUE;
            break;
        }
    }
    if(hadit == PR_FALSE)
    {
        buttonEvnetListener_.AppendObject(listener);
    }
    return NS_OK;//has registered
} 

NS_IMETHODIMP SkypeToggleButton::AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener)
{
    aDestroyEvnetListener_ = listener;

    
    return NS_OK;//has registered
}


NS_IMETHODIMP SkypeToggleButton::CreateNew(PRUint32 parent, 
                                           PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, 
                                           PRUint32 style, PRUint32 exStyle,PRBool *_retval)
{

    RECT rc;
    rc.top =  (LONG)top;
    rc.left =  (LONG)left;
    rc.right=  rc.left + (LONG)w;
    rc.bottom = rc.top +  (LONG)h;

    HWND newW = Create(( HWND) parent, &rc, NULL, style, exStyle );
    if(::IsWindow(newW))
    {
        if(_retval)
        {
            *_retval = PR_TRUE;
        }
        return NS_OK;
    }
    return NS_ERROR_FAILURE;
}