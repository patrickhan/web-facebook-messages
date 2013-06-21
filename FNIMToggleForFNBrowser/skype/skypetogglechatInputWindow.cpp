#include "SkypeToggleChatInputWindow.h"

/* Implementation file */
NS_IMPL_ISUPPORTS1(SkypeToggleChatInputWindow, IFNIMToggleChatInputWindow)

SkypeToggleChatInputWindow::SkypeToggleChatInputWindow()
{
  /* member initializers and constructor code */
     window_classname_.AssignLiteral("TChatRichEdit");
}

SkypeToggleChatInputWindow::~SkypeToggleChatInputWindow()
{
  /* destructor code */
}

/* attribute long m_hWnd; */
NS_IMETHODIMP SkypeToggleChatInputWindow::GetM_hWnd(PRUint32 *aM_hWnd)
{
    *aM_hWnd = m_hWnd;
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatInputWindow::SetM_hWnd(PRUint32 aM_hWnd)
{
    m_hWnd = aM_hWnd;
    return NS_OK;
}

/* attribute long parentWindow; */
NS_IMETHODIMP SkypeToggleChatInputWindow::GetParentWindow(PRUint32 *aParentWindow)
{
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatInputWindow::SetParentWindow(PRUint32 aParentWindow)
{
    return NS_OK;
}

/* attribute AString classname; */
NS_IMETHODIMP SkypeToggleChatInputWindow::GetClassname(nsAString & aClassname)
{
    aClassname = window_classname_;
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatInputWindow::SetClassname(const nsAString & aClassname)
{
    window_classname_ = aClassname;
    return NS_OK;
}

/* attribute AString caption; */
NS_IMETHODIMP SkypeToggleChatInputWindow::GetCaption(nsAString & aCaption)
{
    aCaption = window_caption_ ;
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatInputWindow::SetCaption(const nsAString & aCaption)
{
    window_caption_ = aCaption;
    return NS_OK;
}

#include "windows.h"

static BOOL  GetWindowTextW_my(HWND m_hWnd, nsAString  &txt) throw()
{
    int nLen = ::SendMessage(m_hWnd , WM_GETTEXTLENGTH, (WPARAM)0,(LPARAM)0 );
    if(nLen >0)
    {
        TCHAR *lpszText = new TCHAR[nLen + 1];
        if (lpszText == NULL)
        {
            return FALSE;
        }

        int nLen_Copied = ::SendMessage(m_hWnd , WM_GETTEXT, (WPARAM)(nLen+1),(LPARAM)(TCHAR*)lpszText );

        if(nLen_Copied > 0)
        {
            txt.Assign( lpszText );
        }
        delete[] lpszText; 
    }
    return TRUE;
}


/* attribute AString content; */
NS_IMETHODIMP SkypeToggleChatInputWindow::GetContent(nsAString & aContent)
{

    if(::IsWindow((HWND) m_hWnd) )
    {
        GetWindowTextW_my((HWND)m_hWnd, aContent);
    }

    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatInputWindow::SetContent(const nsAString & aContent)
{
    if(::IsWindow((HWND)m_hWnd) )
    {
        const wchar_t * pText  = nsnull;
        NS_StringGetData(aContent, &pText);
        ::SendMessage( (HWND)m_hWnd, WM_SETTEXT , (WPARAM)0,  (LPARAM)pText );
    }
    return NS_OK;
}

/* void submit (); */
NS_IMETHODIMP SkypeToggleChatInputWindow::Submit()
{
    ::PostMessage((HWND)m_hWnd, WM_KEYDOWN, 0x0D, 0x011C0001); //enter down
    ::PostMessage((HWND)m_hWnd, WM_KEYUP,   0x0D, 0xC11C0001); //enter up
    return NS_OK;
}

/* End of implementation class template. */


///////////////////////////////////////////////////////////////////////////
////SkypeChatInputWindowLocator

NS_IMPL_ISUPPORTS1(SkypeChatInputWindowLocator, IFNIMToggleChatInputWindowLocator)
/////////////////////////////////////////////////////////////////////////////////
nsresult SkypeChatInputWindowLocator::Find(PRUint32 *hWnd_out) 
{

    if(!mainWindow_ || hWnd_out == nsnull)
    {
        return NS_ERROR_FAILURE;
    }   
    PRUint32 mainWnd = 0U;
    mainWindow_->GetM_hWnd(&mainWnd );

    HWND inputParant = ::FindWindowExW((HWND)mainWnd, 0, L"TChatEntryControl",  nsnull ) ;
    if(::IsWindow(inputParant   ) )
    {
        HWND hwnd = ::FindWindowExW(inputParant , 0, L"TChatRichEdit" ,  nsnull) ;
        if(::IsWindow(hwnd  ) )
        {
            *hWnd_out = (PRUint32)hwnd;
            return NS_OK;
        }
    }
    return NS_ERROR_FAILURE;
}
 nsresult SkypeChatInputWindowLocator::Close()
{
     
    mainWindow_= nsnull;
 
    return NS_OK;
}
