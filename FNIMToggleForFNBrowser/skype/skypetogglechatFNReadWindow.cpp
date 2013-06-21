#include "SkypeToggleChatFNReadWindow.h"
#include "clipBoardUtil.h"

/* Implementation file */
NS_IMPL_ISUPPORTS2(SkypeToggleChatFNReadWindow, IFNIMToggleChatFNReadWindow, IFNIMWindowCreator)

SkypeToggleChatFNReadWindow::SkypeToggleChatFNReadWindow():refWindow_(0U),timerID_(0),windowclosed_(TRUE),reaadOnlyFalg_(FALSE)
{
  /* member initializers and constructor code */
    
}

SkypeToggleChatFNReadWindow::~SkypeToggleChatFNReadWindow()
{
  /* destructor code */
}

/* attribute long m_hWnd; */
NS_IMETHODIMP SkypeToggleChatFNReadWindow::GetM_hWnd(PRUint32 *aM_hWnd)
{
    if(aM_hWnd)
    {
        *aM_hWnd = (PRUint32)m_hWnd;
    }
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatFNReadWindow::SetM_hWnd(PRUint32 aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long parentWindow; */
NS_IMETHODIMP SkypeToggleChatFNReadWindow::GetParentWindow(PRUint32 *aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP SkypeToggleChatFNReadWindow::SetParentWindow(PRUint32 aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatReadWindow origianlReadWindow; */
NS_IMETHODIMP SkypeToggleChatFNReadWindow::GetOrigianlReadWindow(IFNIMToggleChatReadWindow * *aOrigianlReadWindow)
{
    if( readWindow_ )
    {
        readWindow_->QueryInterface(NS_GET_IID(IFNIMToggleChatReadWindow), (void**)aOrigianlReadWindow );
    }
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatFNReadWindow::SetOrigianlReadWindow(IFNIMToggleChatReadWindow * aOrigianlReadWindow)
{
    readWindow_= aOrigianlReadWindow;
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString content; */
NS_IMETHODIMP SkypeToggleChatFNReadWindow::GetContent(nsAString & aContent)
{
 
    return NS_ERROR_NOT_IMPLEMENTED;
}

//
//#pragma warning(disable:4100) //unreferenced formal parameter
//#pragma warning(disable:4189) //local variable is initialized but not referenced
//#pragma warning(disable:4101) //unreferenced local variable
//#pragma warning(disable:4244) //return' : conversion from 'int' to 'char', possible loss of data
//#pragma warning(disable:4245) //warning C4245: '=' : conversion from 'int' to 'DWORD', signed/unsigned mismatch
//#pragma warning(disable:4996) //warning C4996: 'localtime' was declared deprecated in workspace\fn360\src\include\common\iplog.h(118)
//
//#include "svcwrap.h"
//
//#pragma warning(default:4100) //unreferenced formal parameter
//#pragma warning(default:4189) //local variable is initialized but not referenced
//#pragma warning(default:4101) //unreferenced local variable
//#pragma warning(default:4244) //return' : conversion from 'int' to 'char', possible loss of data
//#pragma warning(default:4245) //warning C4245: '=' : conversion from 'int' to 'DWORD', signed/unsigned mismatch
//#pragma warning(default:4996) //warning C4996: 'localtime' was declared deprecated

//#include "nsIDOMDocument.h"
//#ifndef _SHUCAI_ADD_CODE_
//#define _SHUCAI_ADD_CODE_  // SetAllRecipientsList
//#include "nsIEditor.h" 
//#endif //_SHUCAI_ADD_CODE_

//#include "nsIDOMNSHTMLDocument.h"





//nsresult runjavascript_receriveRTEmsg(nsISupports* htmlelement,const nsString & cmd);
 

NS_IMETHODIMP SkypeToggleChatFNReadWindow::SetContent(const nsAString & aContent)
{
    //if(aContent.IsEmpty() ) is not a good pre-condition : justa temp work around
    //if(aContent.IsEmpty() )
    //{
    //    return NS_OK;
    //}
    //if(fnRTEService_)
    //{
    //    fnstring content_fn =  L"";
    //    if(aContent.Length()  > 0)
    //    {
    //        content_fn  = aContent.BeginReading();
    //        /////////////////////////////////////////
    //        fnstring strReturn;
    //        try
    //        {
    //            CDecryptHtmlLocal decryptHtml;

    //            strReturn = decryptHtml.DecryptHTML(content_fn, fnstring(L""));
    //            //content_fn = strReturn;
    //        }
    //        catch(...)
    //        {
    //            strReturn.clear();
    //        }
    //        if(!strReturn.empty())
    //        {
    //            content_fn = strReturn;
    //        }
    //        /////////////////////////////////////
    //    }

    //    fnRTEService_->PutContent(m_hWnd, fnstring(L""), content_fn );

    //}
    return NS_OK;
}

/* void showWindow (in boolean show); */
NS_IMETHODIMP SkypeToggleChatFNReadWindow::Show(PRBool show)
{
    /*if(show )
    {

        nsEmbedString content;
        if(readWindow_)
        {
            readWindow_->GetContent(content);
        }
        if(! content_cache_.Equals(content) )
        {
            content_cache_ = content;
            SetContent(content_cache_);
            FN_Browser_Help::ClearClipboardText( (HWND) refWindow_ ) ;
        }
        ShowWindow(SW_SHOW );
    }
    else
    {
        ShowWindow(SW_HIDE);
    }*/
    return NS_OK;
}

/* void showWindow (in boolean show); */
NS_IMETHODIMP SkypeToggleChatFNReadWindow::Close()
{

    if(timerID_ != 0)
    {
        KillTimer(timerID_ );
        timerID_ = 0;
    }

    //if(fnRTEService_)
    //{
    //    fnRTEService_->DestoryBrowser(m_hWnd);
    //    fnRTEService_->shutDown();
    //    fnRTEService_ = nsnull;
    //}
    if(readWindow_)
    {
        readWindow_ = nsnull;
    }

    if(! windowclosed_ )
    {
        windowclosed_ = TRUE;
        DestroyWindow();
    }   
    
    return NS_OK;
}



LRESULT SkypeToggleChatFNReadWindow::OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    if(! windowclosed_)
    {
        windowclosed_ = TRUE;
        Close();
    }
    
    return 0;
}

BOOL SkypeToggleChatFNReadWindow::isWidnowVisibleOnCreeen()
{

    RECT rc = {0};
    GetWindowRect( &rc);
    POINT point1 ={rc.left+3, rc.top+3 };
    POINT point2 ={rc.right-13 , rc.bottom-13};
    HWND wnd1   = WindowFromPoint(point1 );
    HWND wnd2   = WindowFromPoint(point2 );
    if( 1
        //(wnd1   == m_hWnd &&  wnd2   == m_hWnd ) || 
        //( this->IsChild( wnd1 ) && this->IsChild( wnd2 ) )
        )
    {
        return TRUE;
    }

    return FALSE;
}

LRESULT SkypeToggleChatFNReadWindow::onTimer(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
   // if(!::IsWindow((HWND)refWindow_))
   // {
   //     Close();
   //     return 0;
   // }
   // if(!this->IsWindowVisible())
   //     return 0;
   // HWND root2 = ::GetAncestor((HWND)(refWindow_), GA_ROOT);
   // if( ::IsIconic(root2))
   // {
   //     return 0;
   // }
   // if(!::IsWindowVisible(root2 ))
   //     return 0;

   // //if(!isWidnowVisibleOnCreeen() )
   // //{
   // //    return 0;
   // //}
   // 
   ////HWND active  = ::GetActiveWindow();
   ////HWND root1 = ::GetAncestor(active, GA_ROOT);
   ////HWND root2 = ::GetAncestor((HWND)(refWindow_), GA_ROOT);
   ////if(root2 == root1)
   //////reflresh the content
   //{
   //    nsEmbedString content;
   //    readWindow_->GetContent(content);
   //    if(! content_cache_.Equals(content) )
   //    {
   //        content_cache_ = content;
   //        SetContent(content_cache_);
   //        FN_Browser_Help::ClearClipboardText((HWND) refWindow_ ) ;
   //    }
   //}

   ////move the window to cover the window refWindow_

   //RECT rc_desired ={0};
   //if( ! getDesiredWindowRect( &rc_desired))
   //    return 0;

   //RECT rc_current ={0};
   //if( ! getCurrentWindowRect( &rc_current))
   //    return 0;

   //if( EqualRect (&rc_current ,&rc_desired ) )
   //{
   //    Invalidate();
   //    return 0;
   //}

   //BOOL ok = MoveWindow( &rc_desired, TRUE);

   // 
   ////Invalidate();

   // //



    return 0;
}



PRBool SkypeToggleChatFNReadWindow::getCurrentWindowRect( RECT *prc)
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
PRBool SkypeToggleChatFNReadWindow::getDesiredWindowRect( RECT *prc)
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


    //::OffsetRect( prc, -3,  -50);
    //::OffsetRect( prc, -3,  -50);
    //::OffsetRect( prc, 103,  -50);
    //prc->left    = prc->left - 2;
    return PR_TRUE;

}

PRBool SkypeToggleChatFNReadWindow::createFNWidnow( PRUint32 refWindow)
{
    if(! ::IsWindow((HWND) refWindow) )
        return PR_FALSE;

    refWindow_ = refWindow;

    HWND parent = ::GetParent((HWND) refWindow);

    RECT rc = {0};
    getDesiredWindowRect( &rc );
    Create(parent, &rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN );

    SetWindowPos(HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);

    LONG_PTR  styles = ::GetWindowLongPtr((HWND)refWindow, GWL_STYLE );
    ::SetWindowLongPtr((HWND)refWindow, GWL_STYLE ,styles |WS_CLIPSIBLINGS);

    return PR_TRUE;
}


 LRESULT SkypeToggleChatFNReadWindow::onSize(UINT uMsg , WPARAM  wParam , LPARAM lParam , BOOL& /* lResult */)
{
    HWND childWnd = GetWindow(GW_CHILD);
    if(::IsWindow( childWnd ))
    {
        ::SendMessage(childWnd,  uMsg , wParam , lParam );
    }
    return 0;
}

//#include "FNRichTextEditor_Service.h"

LRESULT SkypeToggleChatFNReadWindow::OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    //if(!fnRTEService_)
    //{
    //    fnRTEService_ =  new FNRichTextEditor_Service();
    //    fnRTEService_->initialize();
    //    fnRTEService_->CreateRichEditor(m_hWnd, L"&toolbarconfig=showShort", PR_TRUE); //readonly one
    //    
    //}
    if(timerID_ == 0)
    {
       // timerID_ = SetTimer(100, 3000U);
    }

    windowclosed_ = FALSE;

    return 0;
}
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMHTMLElement.h"
//#include "nsIDOMNSHTMLElement.h"

nsString htmlEscape(const nsAString& str)
{
  // this is naive, but it'll work
  nsString s;
  //for (PRUint32 i = 0; i < str.Length(); i++)
  //{
  //    s += L"&#";
  //    s.AppendInt( str[i]);
  //    s += L";";
  //}
  return s;
}

//static const std::wstring FNENCRYPTED_CONST_HTML_TAG = L"<input readonly=readonly value = 'FN Encrypted Content'  style=' background-color:black; width:auto; color:#F65A26; font-size: 1em; border-top-style: none; border-right-style: none; border-left-style: none; border-bottom-style: none; text-align: center;'/>" ;
static const std::wstring FNENCRYPTED_CONST_HTML_TAG = L"<input readonly=readonly value = 'FN Encrypted Content'  style=' background-color:black; width:auto; color:#F65A26; font-size: 1em; border-top-style: none; border-right-style: none; border-left-style: none; border-bottom-style: none; text-align: center;'/>" ;
static const std::wstring FNENCRYPTED_CONST_PLAINT_TAG = L"****FN Encrypted Content****" ;

nsresult SkypeToggleChatFNReadWindow::AppendContent(const nsAString   &aContent)
{

    return NS_OK;

}
NS_IMETHODIMP SkypeToggleChatFNReadWindow::CreateNew(PRUint32 parent, PRInt32 left, 
                                                 PRInt32 top, PRUint32 w, 
                                                 PRUint32 h, PRUint32 style, PRUint32 exStyle,
                                                 PRBool* _ret)
{
    return NS_OK;
}

//////////////////////////////////////////////////////////////
//SkypeToggleChatFNReader

/* Implementation file */
NS_IMPL_ISUPPORTS1(SkypeToggleChatFNReader, IFNIMToggleChatFNReader)

SkypeToggleChatFNReader::SkypeToggleChatFNReader()
{
  /* member initializers and constructor code */
}

SkypeToggleChatFNReader::SkypeToggleChatFNReader(nsISupports* ele)
{
    fnreader_element_ = ele;
}

SkypeToggleChatFNReader::~SkypeToggleChatFNReader()
{
  /* destructor code */
}

#include "nsIDOMHTMLTextAreaElement.h"
/* void appendContent1 (in AString content); */
NS_IMETHODIMP SkypeToggleChatFNReader::AppendContent1(const nsAString & content)
{
    //nsCOMPtr<nsIEditor>  spEditor =  do_QueryInterface(fnreader_element_);
    //if(!spEditor )
    //{
    //    return NS_ERROR_FAILURE;
    //}
    //if(aContent.Length() == 0)
    //    return NS_OK; 
    //fnstring content_fn =  L"";
    //if(aContent.Length()  > 0)
    //{
    //    const wchar_t * pText  = nsnull;
    //    NS_StringGetData(aContent, &pText);
    //    if(pText != nsnull)
    //        content_fn  = pText;
    //    /////////////////////////////////////////
    //    fnstring strReturn;
    //    try
    //    {
    //        CDecryptHtmlLocal decryptHtml;

    //        strReturn = decryptHtml.DecryptHTML(content_fn, fnstring(L""));
    //        /*if(fnstring::npos != strReturn.find(L"FN Encrypted Content"))
    //        {
    //        strReturn = L"*****FN Encrypted Content****";// FNRTE can not handle the output html with back ground color
    //        }*/

    //        //content_fn = strReturn;
    //    }
    //    catch(...)
    //    {
    //        strReturn.clear();
    //    }
    //    if(!strReturn.empty())
    //    {
    //        content_fn = strReturn;
    //    }
    //    /////////////////////////////////////
    //}



    //nsCOMPtr<nsIDOMDocument> dom_document;
    //nsresult rv  = spEditor->GetDocument(getter_AddRefs(dom_document) );
    //nsCOMPtr<nsIDOMHTMLDocument> html_document = do_QueryInterface(dom_document);
    //if(html_document )
    //{

    //    nsCOMPtr<nsIDOMHTMLElement> body;
    //    rv = html_document->GetBody(getter_AddRefs(body) );
    //    if(body)
    //    {

    //        nsCOMPtr<nsIDOMNode > nsIDOMNode_new;
    //        rv = spEditor->CreateNode(nsString(L"span"),  body, 0x0FFFFFFF, getter_AddRefs(nsIDOMNode_new) ); //append
    //        if(nsIDOMNode_new )
    //        {
    //            nsCOMPtr<nsIDOMHTMLElement> elementHTML = do_QueryInterface(nsIDOMNode_new);
    //            if (elementHTML)
    //            {
    //                wstring input_ws = content_fn.c_str();
    //                basic::replace_all_ws( input_ws, FNENCRYPTED_CONST_HTML_TAG,		FNENCRYPTED_CONST_PLAINT_TAG);
    //                nsString input = htmlEscape(nsString(input_ws.c_str()));
    //                input_ws.clear();

    //                rv = elementHTML->SetInnerHTML( input   );        
    //                rv = elementHTML->ScrollIntoView(PR_FALSE,0);
    //                input.Truncate();
    //            }
    //        }
    //    }
    //}
    //

    nsCOMPtr<nsIDOMHTMLTextAreaElement >  ansIDOMHTMLTextAreaElement  = do_QueryInterface(fnreader_element_);
    if(ansIDOMHTMLTextAreaElement  )
    {
        nsString oldData;
        ansIDOMHTMLTextAreaElement->GetValue(oldData);
        oldData.Append(L"\n");
        oldData.Append(content);
        ansIDOMHTMLTextAreaElement->SetValue(oldData);
    }
    else
    {
        /*nsString oldData(content);
        runjavascript_receriveRTEmsg(fnreader_element_,  oldData);*/
    }

    return NS_OK;
}

/* void setContent1 (in AString content); */
NS_IMETHODIMP SkypeToggleChatFNReader::SetContent1(const nsAString & content)
{
    // nsCOMPtr<nsIEditor>  spEditor = do_QueryInterface(fnreader_element_);;
    //if(!spEditor )
    //{
    //    return NS_ERROR_FAILURE;
    //}
    //fnstring content_fn =  L"";
    //if(aContent.Length()  > 0)
    //{
    //    const wchar_t * pText  = nsnull;
    //    NS_StringGetData(aContent, &pText);
    //    if(pText != nsnull)
    //        content_fn  = pText;
    //    
    //    /////////////////////////////////////////
    //    fnstring strReturn;
    //    try
    //    {
    //        CDecryptHtmlLocal decryptHtml;

    //        strReturn = decryptHtml.DecryptHTML(content_fn, fnstring(L""));
    //    }
    //    catch(...)
    //    {
    //        strReturn.clear();
    //    }
    //    if(!strReturn.empty())
    //    {
    //        content_fn = strReturn;
    //    }
    //    /////////////////////////////////////
    //}
    //
    //{        
    //    nsString input(L"") ;
    //    if(content_fn.length()> 0)
    //    {
    //        wstring input_ws = content_fn.c_str();
    //        basic::replace_all_ws( input_ws, FNENCRYPTED_CONST_HTML_TAG,		FNENCRYPTED_CONST_PLAINT_TAG);
    //        input = htmlEscape(nsString(input_ws.c_str()));
    //        input_ws.clear();
    //    }
    //    PRInt32 retval = 0;
    //    //FNRichTextEditorWapper::SetValue(spEditor, input, &retval);
    //}
    nsCOMPtr<nsIDOMHTMLTextAreaElement >  ansIDOMHTMLTextAreaElement  = do_QueryInterface(fnreader_element_);
    if(ansIDOMHTMLTextAreaElement  )
    {
        ansIDOMHTMLTextAreaElement->SetValue(content);
        return 0;
    }
    return NS_OK;
}

/* attribute nsIWebBrowser webBrowser; */
NS_IMETHODIMP SkypeToggleChatFNReader::GetWebBrowser(nsIWebBrowser * *aWebBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP SkypeToggleChatFNReader::SetWebBrowser(nsIWebBrowser * aWebBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
 

#if 0


#pragma warning(disable:4800 4273) //forcing value to bool 'true' or 'false' (performance warning) //warning C4273: 'js_DeclEnvClass' : inconsistent dll linkage in firefox 5

#include "nsIDocument.h"
#include "nsPIDOMWindow.h"

#include "jsapi.h"

#include "nsIScriptGlobalObject.h"
#include "nsIScriptContext.h"
#include "nsIXPConnect.h"
#include "nsServiceManagerUtils.h"
#include "xpccomponents.h"
#include "nsComponentManagerUtils.h"
#include "nsIInterfaceRequestorUtils.h"

nsresult runjavascript_receriveRTEmsg(nsISupports* htmlelement,const nsString & cmd)
{
    nsresult rv = NS_OK;

    if(htmlelement = nsnull  )
        return NS_ERROR_INVALID_ARG;

    try{

        nsCOMPtr<nsIDOMHTMLElement >  ansIDOMHTMLElement  = do_QueryInterface(htmlelement);

        if(!ansIDOMHTMLElement  )
        {
            return NS_ERROR_INVALID_ARG;
        }
        nsCOMPtr<nsIDOMDocument> aDOMHTMLDocument ;
        ansIDOMHTMLElement->GetOwnerDocument( getter_AddRefs(aDOMHTMLDocument ) );
        // We need a document to evaluate scripts.
        if (!aDOMHTMLDocument) {
            return NS_ERROR_INVALID_ARG;
        }

        JSObject* out_JSObject = nsnull;
        JSContext* out_JSContext = nsnull;

        nsCOMPtr<nsIXPConnect> xpconnect = do_GetService(nsIXPConnect::GetCID(), &rv);
        if(NS_FAILED(rv) || !xpconnect)
        {
            return rv;
        }


        nsCOMPtr<nsIDOMWindow>  ansIDOMWindow;
        rv = aDOMHTMLDocument->GetDefaultView( getter_AddRefs(ansIDOMWindow) );
        if(NS_FAILED(rv) ||!ansIDOMWindow )
        {
            return rv;
        }

        nsCOMPtr<nsIScriptGlobalObject> sgo = do_GetInterface(ansIDOMWindow, &rv);
        if(NS_FAILED(rv) ||!sgo)
        {
            return rv;
        }
        nsIScriptContext* jscontext = sgo->GetContext();
        if(jscontext == NULL)
        {
            return NS_ERROR_FAILURE;
        }

        JSContext* domWindow_context = reinterpret_cast<JSContext*>(jscontext->GetNativeContext());	
        if(domWindow_context == NULL)
        {
            return NS_ERROR_FAILURE;
        }
        JSObject* window_obj = JS_GetGlobalForScopeChain(domWindow_context);
        if(window_obj == NULL)
        {
            return NS_ERROR_FAILURE;
        }

        PRInt32		  paramsCount;	
        jsval       jsParams[1];	
        PRBool		  suc;	
        jsval       jsRet;	
        paramsCount = 0;	

        jsParams[paramsCount++] = STRING_TO_JSVAL(JS_NewUCStringCopyZ(out_JSContext, (const jschar *)(cmd.get() ))  );//lint !e929 !e923

        suc = JS_CallFunctionName(domWindow_context, window_obj, "passDataToRte", 
            paramsCount, jsParams, &jsRet);		//lint !e732
        if(!JSVAL_IS_BOOLEAN(jsRet) )
        {
            return NS_ERROR_FAILURE;
        }
        JSBool jsbool =  JSVAL_TO_BOOLEAN(jsRet);//lint !e704 !e1960
        if(JS_FALSE == jsbool)
        {
            return NS_ERROR_FAILURE;
        }

    }
    catch(...)
    {
    }
    return rv;
}
#endif 