#include "FNIMToggleButton.h"

#include "FNToggleImage.h"

#define FN_TOOGLE_BUTTON_HEIGHT 32 
#define FN_TOOGLE_BUTTON_WIDTH  32 
/* Implementation file */
NS_IMPL_ISUPPORTS1(FNIMToggleButton, IFNIMToggleButton)

FNIMToggleButton::FNIMToggleButton()
:shownFnWindow_(FALSE),
refWindow_(0U),
timerID_(0),
windowclosed_(TRUE)
{
    /* member initializers and constructor code */
}

FNIMToggleButton::~FNIMToggleButton()
{
    /* destructor code */
}

/* readonly attribute long m_hWnd; */
NS_IMETHODIMP FNIMToggleButton::GetM_hWnd(PRUint32 *aM_hWnd)
{

    if(aM_hWnd)
    {
        *aM_hWnd =(PRUint32) m_hWnd;
    }

    return NS_OK;
}

/* readonly attribute long m_hWnd; */
NS_IMETHODIMP FNIMToggleButton::Close()
{

    if(timerID_ != 0)
    {
        KillTimer(timerID_ );
        timerID_ = 0;
    }

    if(chat_session_ )
    {
        //chat_session_->Quit();
        chat_session_ = nsnull;
    }

    if(! windowclosed_ )
    {
        windowclosed_ = TRUE; 
        DestroyWindow();
    }   
    return NS_OK;
}


PRBool FNIMToggleButton::getCurrentWindowRect( RECT *prc)
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
PRBool FNIMToggleButton::getDesiredWindowRect( RECT *prc)
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

    ::OffsetRect( prc, 0,  -50);

    return PR_TRUE;

}

PRBool FNIMToggleButton::createButton( PRUint32 refWindow)
{
    if(! ::IsWindow((HWND) refWindow) )
        return PR_FALSE;

    refWindow_ = refWindow;

    HWND parent = ::GetParent((HWND) refWindow);

    RECT rc = {0};
    getDesiredWindowRect( &rc );

    Create(parent, &rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN );

    SetWindowPos(HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);

    HWND send  = ::FindWindowEx(parent   ,nsnull,  L"NMGenWindowClass" , L"NMButton");
    HWND send1  = ::FindWindowEx(send   ,nsnull,  L"Button" , nsnull);
    LONG_PTR  styles = ::GetWindowLongPtr((HWND)send, GWL_STYLE );
    ::SetWindowLongPtr((HWND)send, GWL_STYLE ,styles |WS_CLIPSIBLINGS);

     styles = ::GetWindowLongPtr((HWND)send1, GWL_STYLE );
    ::SetWindowLongPtr((HWND)send1, GWL_STYLE ,styles |WS_CLIPSIBLINGS);

    return PR_TRUE;
    //chat_session_->
}




LRESULT FNIMToggleButton::onPaint(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(&ps); 

    RECT rc = {0};
    GetClientRect( &rc);
    FNToggleImageDraw::draw(hdc, &rc);

    EndPaint(&ps); 

    return 0;
}

LRESULT FNIMToggleButton::onClick(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    shownFnWindow_ = shownFnWindow_? PR_FALSE : PR_TRUE; 

    if(chat_session_)
    {
        chat_session_->ShowFNWidnows(shownFnWindow_);
    }
    return 0;
}

LRESULT FNIMToggleButton::OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    if(! windowclosed_)
    {
        windowclosed_ = TRUE;
        Close();
    }



    return 0;
}

LRESULT FNIMToggleButton::OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    timerID_ = SetTimer(100, 1000U);
    windowclosed_ = FALSE;
    return 0;
}

LRESULT FNIMToggleButton::onTimer(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
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