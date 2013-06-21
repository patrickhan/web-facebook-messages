#include "SkypeToggleChatFNInputWindow.h"

#include "nsEmbedString.h"

/* Implementation file */
NS_IMPL_ISUPPORTS2(SkypeToggleChatFNInputWindow, IFNIMToggleChatFNInputWindow, IFNIMWindowCreator)

SkypeToggleChatFNInputWindow::SkypeToggleChatFNInputWindow():refWindow_(0U),timerID_(0),windowclosed_(TRUE)
{
  /* member initializers and constructor code */
 }

SkypeToggleChatFNInputWindow::~SkypeToggleChatFNInputWindow()
{
  /* destructor code */
}

/* attribute long m_hWnd; */
NS_IMETHODIMP SkypeToggleChatFNInputWindow::GetM_hWnd(PRUint32 *aM_hWnd)
{
    if(aM_hWnd)
    {
        *aM_hWnd = (PRUint32)m_hWnd;
    }
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatFNInputWindow::SetM_hWnd(PRUint32 aM_hWnd)
{
    m_hWnd = (HWND)aM_hWnd;

    return NS_OK;
}

/* attribute long parentWindow; */
NS_IMETHODIMP SkypeToggleChatFNInputWindow::GetParentWindow(PRUint32 *aParentWindow)
{
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatFNInputWindow::SetParentWindow(PRUint32 aParentWindow)
{
    return NS_OK;
}

/* attribute IFNIMToggleChatInputWindow origianlInputWindow; */
NS_IMETHODIMP SkypeToggleChatFNInputWindow::GetOrigianlInputWindow(IFNIMToggleChatInputWindow * *aOrigianlInputWindow)
{
    if( inputWindow_ )
    {
        inputWindow_->QueryInterface(NS_GET_IID(IFNIMToggleChatInputWindow), (void**)aOrigianlInputWindow );
    }
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatFNInputWindow::SetOrigianlInputWindow(IFNIMToggleChatInputWindow * aOrigianlInputWindow)
{
    inputWindow_= aOrigianlInputWindow;
    return NS_OK;
}

/* void submit (); */
NS_IMETHODIMP SkypeToggleChatFNInputWindow::Submit()
{
    return NS_OK;
}

/* void submit (); */
NS_IMETHODIMP SkypeToggleChatFNInputWindow::Close()
{
    if(timerID_ != 0)
    {
        KillTimer(timerID_ );
        timerID_ = 0;
    }

    if(inputWindow_)
    {
        inputWindow_ = nsnull;//.forget();
    }
    if(! windowclosed_ )
    {
        windowclosed_ = TRUE;
        DestroyWindow();
    }   

    return NS_OK;
}


/* void showWindow (in boolean show); */
NS_IMETHODIMP SkypeToggleChatFNInputWindow::Show(PRBool show)
{
    ShowWindow(show ? SW_SHOW : SW_HIDE);
    return NS_OK;
}



LRESULT SkypeToggleChatFNInputWindow::OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    if(! windowclosed_)
    {
        windowclosed_ = TRUE;
        Close();
    }
    
    return 0;
}


LRESULT SkypeToggleChatFNInputWindow::onTimer(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    if(!::IsWindow((HWND)refWindow_))
    {
        Close();
        return 0;
    }
    if(!this->IsWindowVisible() )
    {
        return 0;
    }
    if(inputWindow_ )
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
       (void)MoveWindow( &rc_desired, TRUE);

    }
    return 0;
}

PRBool SkypeToggleChatFNInputWindow::getCurrentWindowRect( RECT *prc)
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
    prc->left   = rc.left - rc_parent.left;
    prc->right  = prc->left   + rc.right - rc.left;
    prc->bottom = prc->top    + rc.bottom -rc.top;


    return PR_TRUE;
}
PRBool SkypeToggleChatFNInputWindow::getDesiredWindowRect( RECT *prc)
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
 
LRESULT SkypeToggleChatFNInputWindow::OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    timerID_ = SetTimer(100, 1000U);
    windowclosed_ = FALSE;
    return 0;
}

 

NS_IMETHODIMP SkypeToggleChatFNInputWindow::Focus()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP SkypeToggleChatFNInputWindow::CreateNew(PRUint32 parent, PRInt32 left, 
                                                 PRInt32 top, PRUint32 w, 
                                                 PRUint32 h, PRUint32 style, PRUint32 exStyle,
                                                 PRBool* _ret)
{
    return NS_OK;
}

//
//#include "nsIDOMDocument.h"
//#ifndef _SHUCAI_ADD_CODE_
//#define _SHUCAI_ADD_CODE_  // SetAllRecipientsList
//#include "nsIEditor.h" 
//#endif //_SHUCAI_ADD_CODE_
//
//#include "nsIDOMWindowInternal.h"
//#include "nsIDOMDocumentView.h"
//#include "nsIDOMAbstractView.h"
//

 
#include "FNRichTextEditorWapper.h"
#include "nsIDOMElement.h"
#include "nsIEditor.h"
#include "nsIObserverService.h"
#include "nsServiceManagerUtils.h"
#include "nsIDOMHTMLTextAreaElement.h"
////////////////////////////////////////////////////////////////////
NS_IMPL_ISUPPORTS1(SkypeToggleChatFNInput , IFNIMToggleChatFNInput)
SkypeToggleChatFNInput::SkypeToggleChatFNInput()
{
}
SkypeToggleChatFNInput::SkypeToggleChatFNInput( nsISupports * ele)
{
    fnInput_element_ = ele;
}
SkypeToggleChatFNInput::~SkypeToggleChatFNInput()
{
}

extern nsString htmlEscape(const nsAString& str);
/* void setContent (in AString content); */
NS_IMETHODIMP SkypeToggleChatFNInput::SetContent(const nsAString & content)
{
    //nsCOMPtr<nsIEditor> editor =  do_QueryInterface(fnInput_element_);
    //if(!editor)
    //    return NS_ERROR_NO_INTERFACE;

    ///*nsString input = htmlEscape(content );
    //PRInt32 ret = 0;
    //nsresult rv = FNRichTextEditorWapper::SetValue(editor, (const nsString&)input , &ret);
    //*/
    //nsString input = htmlEscape(content );
    //PRInt32 ret = 0;
    //nsresult rv = FNRichTextEditorWapper::SetValue(editor, (const nsString&)content , &ret);
   

    //nsCOMPtr<nsIObserverService> svc =
    //    do_GetService("@mozilla.org/observer-service;1", &rv);

    //if( svc )
    //{
    //    svc->NotifyObservers(editor, "sync fn readers", L"set") ;
    //}
    //if(ret == 0)
    //{
    //    return NS_OK;
    //}

    nsCOMPtr<nsIDOMHTMLTextAreaElement >  ansIDOMHTMLTextAreaElement  = do_QueryInterface(fnInput_element_);
    if(ansIDOMHTMLTextAreaElement  )
    {
        ansIDOMHTMLTextAreaElement->SetValue(content);
        return 0;
    }

    return NS_ERROR_FAILURE;
}


/* void getContent (out AString content); */
NS_IMETHODIMP SkypeToggleChatFNInput::GetContent(nsAString & content)
{
    //nsCOMPtr<nsIEditor> editor =  do_QueryInterface(fnInput_element_);
    //if(!editor)
    //    return NS_ERROR_NO_INTERFACE;

    //nsresult rv;
    //nsCOMPtr<nsIObserverService> svc =
    //    do_GetService("@mozilla.org/observer-service;1", &rv);

    //if( svc  && rv == NS_OK)
    //{
    //    svc->NotifyObservers(editor, "sync fn readers", L"get") ;
    //}


    //nsString  notFoundRecipient ;
    //rv = FNRichTextEditorWapper::GetValue(   editor, 
    //                                                  nsString(L""), //default using text/plaint 
    //                                                  (nsString&)content, //out
    //                                                  nsString(L""),  //in
    //                                                  notFoundRecipient //out
    //                                                  ); 

    nsCOMPtr<nsIDOMHTMLTextAreaElement >  ansIDOMHTMLTextAreaElement  = do_QueryInterface(fnInput_element_);
    if(ansIDOMHTMLTextAreaElement  )
    {
        ansIDOMHTMLTextAreaElement->GetValue(content);
    }else
    {

    
    }
    return 0;
}

/* attribute nsIWebBrowser webBrowser; */
NS_IMETHODIMP SkypeToggleChatFNInput::GetWebBrowser(nsIWebBrowser * *aWebBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP SkypeToggleChatFNInput::SetWebBrowser(nsIWebBrowser * aWebBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isFocused (); */
NS_IMETHODIMP SkypeToggleChatFNInput::IsFocused(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setFocus (); */
NS_IMETHODIMP SkypeToggleChatFNInput::SetFocus()
{
    nsCOMPtr<nsIEditor> editor =  do_QueryInterface(fnInput_element_);
    if(!editor)
        return NS_ERROR_NO_INTERFACE;

    nsresult rv = 0 ;// FNRichTextEditorWapper::Focus(editor );
    return rv;
}

 