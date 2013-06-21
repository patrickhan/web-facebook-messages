#include "SkypeToggleChatReadWindow.h"
#include "windows.h"
#include "clipBoardUtil.h"
#include "keyStrokeUtil.h"
//#include "WINABLE.H" // for blockInput 
/* Implementation file */
NS_IMPL_ISUPPORTS1(SkypeToggleChatReadWindow, IFNIMToggleChatReadWindow)

SkypeToggleChatReadWindow::SkypeToggleChatReadWindow()
{
  /* member initializers and constructor code */
    window_classname_.AssignLiteral("TChatContentControl");
}

SkypeToggleChatReadWindow::~SkypeToggleChatReadWindow()
{
  /* destructor code */
}

/* attribute long m_hWnd; */
NS_IMETHODIMP SkypeToggleChatReadWindow::GetM_hWnd(PRUint32 *aM_hWnd)
{
    *aM_hWnd     =  m_hWnd;
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP SkypeToggleChatReadWindow::SetM_hWnd(PRUint32 aM_hWnd)
{
    m_hWnd = aM_hWnd;
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long parentWindow; */
NS_IMETHODIMP SkypeToggleChatReadWindow::GetParentWindow(PRUint32 *aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP SkypeToggleChatReadWindow::SetParentWindow(PRUint32 aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString content; */
NS_IMETHODIMP SkypeToggleChatReadWindow::GetContent(nsAString & aContent)
{    
    HWND wnd =(HWND) m_hWnd ;

    FN_Browser_Help::FN_ClipboardBackup cb;
    if (! cb.Backup(NULL)) {
        return NS_ERROR_FAILURE;
    }
    // clear for previous clipbourdcontent interfere

    FN_Browser_Help::ClearClipboardText( wnd ) ;


    FN_Browser_Help::pressCTRLKey();
    try
    {
        ::SendMessage( wnd, WM_LBUTTONDBLCLK,0, MAKELPARAM(10,10) );

        FN_Browser_Help::SendMessage_CTRL_A( wnd );
        FN_Browser_Help::SendMessage_CTRL_C( wnd );
    }
    catch(...){}
    FN_Browser_Help::releaseCTRLKey();

    wstring clipboard_data;
    if( ! FN_Browser_Help::GetClipboardTextEx( wnd, clipboard_data ) )
    {
        cb.Restore(NULL);
        return NS_ERROR_FAILURE;
    }

    aContent.Assign(clipboard_data .c_str() );

    // clear for our clipbourdcontent interferes others
 
    FN_Browser_Help::ClearClipboardText( wnd ) ;

    cb.Restore(NULL);

    return NS_OK;
}
/* attribute AString classname; */
NS_IMETHODIMP SkypeToggleChatReadWindow::GetClassname(nsAString & aClassname)
{
    aClassname = window_classname_;
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatReadWindow::SetClassname(const nsAString & aClassname)
{
    window_classname_ = aClassname;
    return NS_OK;
}

/* attribute AString caption; */
NS_IMETHODIMP SkypeToggleChatReadWindow::GetCaption(nsAString & aCaption)
{
    aCaption = window_caption_ ;
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatReadWindow::SetCaption(const nsAString & aCaption)
{
    window_caption_ = aCaption;
    return NS_OK;
}



////SkypeChatReadWindowLocator
NS_IMPL_ISUPPORTS1(SkypeChatReadWindowLocator, IFNIMToggleChatReadWindowLocator)
/////////////////////////////////////////////////////////////////////////////////
nsresult SkypeChatReadWindowLocator::Find(PRUint32 *hWnd_out) 
{

    if(!mainWindow_ || hWnd_out == nsnull)
    {
        return NS_ERROR_FAILURE;
    }   
    PRUint32 mainWnd = 0U;
    mainWindow_->GetM_hWnd(&mainWnd );

    HWND hwnd = ::FindWindowExW((HWND)mainWnd, 0, L"TChatContentControl" ,  nsnull) ;
    if(::IsWindow(hwnd  ) )
    {
        *hWnd_out = (PRUint32)hwnd;
        return NS_OK;
    }
    return NS_ERROR_FAILURE;
}
 nsresult SkypeChatReadWindowLocator::Close()
{
     
    mainWindow_= nsnull;
 
    return NS_OK;
}
