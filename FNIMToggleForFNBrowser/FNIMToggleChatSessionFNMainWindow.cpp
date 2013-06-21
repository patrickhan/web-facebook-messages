#include "FNIMToggleChatSessionFNMainWindow.h"

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

#include "nsIXULWindow.h"
// NON-FROZEN APIs!
#include "nsIBaseWindow.h"
#include "nsIWebNavigation.h"


std::string  getIMUIFilePath()
{
    char pathFile[1024] ={0};
    ::GetModuleFileNameA(NULL, pathFile, 1023U);
    std::string path (pathFile);
    std::string::size_type pos = path.find_last_of("\\");
    path.replace(pos+1, path.length()-pos, "fnwebim\\fnskype.html");

    return path  ;
}


/* Implementation file */
NS_IMPL_ISUPPORTS1(FNIMToggleChatSessionFNMainWindowUI, IFNIMToggleChatFNMainWindow)

FNIMToggleChatSessionFNMainWindowUI::FNIMToggleChatSessionFNMainWindowUI() : windowclosed_(FALSE), eventHooked_(FALSE),theMainDOMWindow_HWND_(0)
{
    
}

FNIMToggleChatSessionFNMainWindowUI::~FNIMToggleChatSessionFNMainWindowUI()
{
  /* destructor code */
}



LRESULT FNIMToggleChatSessionFNMainWindowUI::OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */)
{

    if(theMainDOMWindow_)
    {
        theMainDOMWindow_ = nsnull;
    }
    if(ansIWebBrowser_ )
    {
         DestoryBrowser();
         ansIWebBrowser_.forget();
    }

    if(! windowclosed_)
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

LRESULT FNIMToggleChatSessionFNMainWindowUI::OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */)
{
    CreateBrowser( );

    return 0;
}

LRESULT FNIMToggleChatSessionFNMainWindowUI::onPosChanged(UINT message, WPARAM wParam , LPARAM lParam , BOOL&  bHandled )
{
    if(theMainDOMWindow_)
    {
        RECT rect;
        GetClientRect(&rect);

        // Make sure the browser is visible and sized
        ::MoveWindow( 
            GetWindow(GW_CHILD),
            0,0,
            rect.right - rect.left, 
            rect.bottom - rect.top,
            PR_TRUE);
    }

    if(ansIWebBrowser_)
    {
        nsCOMPtr<nsIWebBrowserChrome> ansIWebBrowserChrome ;
        nsresult rv = ansIWebBrowser_->GetContainerWindow(getter_AddRefs(ansIWebBrowserChrome));
        if(rv == NS_OK && ansIWebBrowserChrome)
        {
            FNIMWebBrowserChromeUI::ResizeEmbedding(ansIWebBrowserChrome);
        }
    }
    return 0;
}

LRESULT FNIMToggleChatSessionFNMainWindowUI:: onMOUSEACTIVATE(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* bHandled */)
{

    SetFocusBrowser();
    return 0;
}
PRBool FNIMToggleChatSessionFNMainWindowUI:: CreateNew( const LPRECT  prc)
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

#include "nsIDOMDocument.h"
#include "nsIDOMElement.h"
#include "nsIDOMEventTarget.h"
void FNIMToggleChatSessionFNMainWindowUI:: hookDOMEvent()
{
    if(!theMainDOMWindow_  || eventHooked_)
        return ;

    nsCOMPtr<nsIDOMDocument> theMainDOMDocument_;
    theMainDOMWindow_->GetDocument(getter_AddRefs(theMainDOMDocument_));
    if(!theMainDOMDocument_)
        return ;

    //PRUint32 win  = 0;
    //GetWindowHandle( &win);
    //Hide();// make sure not show the popup rte now

    //if(!_title.IsEmpty() )
    //{
    //    nsCOMPtr<nsIDOMElement> title;
    //    theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("sub-title"), getter_AddRefs(title));
    //    if(title)
    //    {
    //        title->SetAttribute(NS_LITERAL_STRING("value"), _title);
    //    }
    //}
    //FNIMSendButton 
    if(_listener_FNIMSendButton)
    {
        nsCOMPtr<nsIDOMElement> button;
        theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("FNIMSendButton"), getter_AddRefs(button));
        nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(button);
        if(eventTarget)
        {
            eventTarget->AddEventListener(NS_LITERAL_STRING("click"), _listener_FNIMSendButton, PR_FALSE);
            eventHooked_ = TRUE;
        }
    }
    //closebutton
    if(_listener_closebutton)
    {
        nsCOMPtr<nsIDOMElement> button;
        theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("closebutton"), getter_AddRefs(button));
        nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(button);
        if(eventTarget)
        {
            eventTarget->AddEventListener(NS_LITERAL_STRING("click"), _listener_closebutton, PR_FALSE);
            eventHooked_ = TRUE;
        }
    }
    if(_listener_invitationbutton)
    {
        nsCOMPtr<nsIDOMElement> button;
        theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("FNInviteButton"), getter_AddRefs(button));
        nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(button);
        if(eventTarget)
        {
            eventTarget->AddEventListener(NS_LITERAL_STRING("click"), _listener_invitationbutton, PR_FALSE);
            eventHooked_ = TRUE;
        }        
    }


    if(_documentReadyObserver)// notify listener
    {
        _documentReadyObserver->Observe(nsnull,  "FNIMWebBrowserChrome_Ready", nsnull) ;
    }
    eventHooked_ = TRUE;
}

PRBool  FNIMToggleChatSessionFNMainWindowUI:: Show( )
{

    if(theMainDOMWindow_  &&!eventHooked_)
    {
        hookDOMEvent();

        ::SetParent(theMainDOMWindow_HWND_, m_hWnd);
        ::MoveWindow(theMainDOMWindow_HWND_,0, 0, 100,100, FALSE);
        //::MoveWindow(theMainDOMWindow_HWND_,0, 0, w+1,h+1, TRUE);
        //::SetWindowLong(theMainDOMWindow_HWND_, GWL_STYLE, WS_CHILDWINDOW|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN);	
    }

    ShowWindow(SW_SHOW);
    //::ShowWindow(theMainDOMWindow_HWND_, SW_SHOW);

    
    ::ShowWindow(GetWindow(GW_CHILD),SW_SHOW );
    return PR_TRUE;
}

PRBool  FNIMToggleChatSessionFNMainWindowUI:: Hide( )
{
    ShowWindow(SW_HIDE);
    //::ShowWindow(GetWindow(GW_CHILD),SW_SHOW );
    return PR_TRUE;
}

//BOOL FNIMToggleChatSessionFNMainWindowUI:: adjustLayout(const LPRECT prc )
//{
//    //if(!IsRectEmpty(prc) &&!::EqualRect(&rc_ecpected_, prc))
//    //{
//    //    ::CopyRect(&rc_ecpected_, prc);
//
//    //    return SetWindowPos(HWND_TOP, 
//    //        rc_ecpected_.left, rc_ecpected_.top, rc_ecpected_.right - rc_ecpected_.left, rc_ecpected_.bottom -rc_ecpected_.top,
//    //        0U);
//    //    //return MoveWindow(rc_ecpected_.left, rc_ecpected_.top, rc_ecpected_.right - rc_ecpected_.left, rc_ecpected_.bottom -rc_ecpected_.top, TRUE);
//    //}
//    return FALSE;
//}
 
extern NS_IMETHODIMP getDOMWindowParentNativeWindow(nsIDOMWindow *domwin, void** outHWnd);
extern NS_IMETHODIMP getDOMWindowParentNativeWindow2(nsIDOMWindow *domwin, void** outHWnd, void** topmostDOMWindow);
extern BOOL getDOMWindowTopmost(nsIDOMWindow *aDOMWindow, nsIDOMWindow ** topmost);
extern std::string getIMUIFilePath();
//lint -e{1762,831,774,948}

#include "nsIWindowMediator.h"
#include "nsISimpleEnumerator.h"
BOOL  FNIMToggleChatSessionFNMainWindowUI::CreateBrowser()
{
    ::MessageBox(0, L"FNIMToggleChatSessionFNMainWindowUI::CreateBrowser(",L"",0);
    RECT rc ={0};
    ::GetWindowRect(m_hWnd,&rc);
    LONG w = rc.right- rc.left;
    LONG h = rc.bottom-rc.top ;
    



    nsresult rv;

  nsCOMPtr<nsIWindowWatcher> windowWatcher =  do_GetService("@mozilla.org/embedcomp/window-watcher;1", &rv);
  if(!windowWatcher )
      return rv ;

  nsCOMPtr<nsIDOMWindow> activeParent;
  
 
  //nsCString window_feature ( "chrome,modal=no,dependent=yes,resizable=yes," );
  nsCString window_feature ( "chrome=no,dependent=yes,titlebar=no,modal=no,resizable=yes," );

  window_feature +="screenY=";
  window_feature.AppendInt( rc.top );
  window_feature +=",";

  window_feature +="screenX=";
  window_feature.AppendInt(  rc.left);
  window_feature +=",";


  window_feature +="width=";
  window_feature.AppendInt(  w);
  window_feature +=",";

  
  window_feature +="height=";
  window_feature.AppendInt(  h);
  window_feature +=",";

  long init_size_w_ = (w);
  long init_size_h_ = (h);
	//this->AddRef();

  static int kkk = 0l;
  std::string filepath = getIMUIFilePath();
  nsCString window_uri("file:///" );

   window_uri +=filepath.c_str();
  window_uri +="?nothing=";
  window_uri.AppendInt(kkk++ ); 
  

  //nsCOMPtr<nsISupports> ansSupport;
  //this->QueryInterface(NS_GET_IID(nsISupports), getter_AddRefs(ansSupport) );
  //this->AddRef();

  nsCOMPtr<nsIDOMWindow> theMainDOMWindow_new;
	rv = windowWatcher->OpenWindow(activeParent,
		window_uri.get(),
    "", ///Please note : here should not be a valid name, or there will be "close old, open new result".
    window_feature.get() ,
    nsnull,//ansSupport,
		getter_AddRefs(theMainDOMWindow_new));

    if(!theMainDOMWindow_new  )
    {
        return  FALSE;
    }
  

    nsString window_uri_ws =     NS_ConvertASCIItoUTF16(window_uri);
    nsString name (L"skypewindow");
    nsString options(L"");
    theMainDOMWindow_new->Open(window_uri_ws,name,options,getter_AddRefs(theMainDOMWindow_) );


    theMainDOMWindow_new->Close();


    if(rv == NS_OK)
    {
        if(theMainDOMWindow_)
        {


            HWND win  = 0;
            nsCOMPtr<nsIDOMWindow>topmost_DomWindow; // this is not mosttop window !!
            getDOMWindowParentNativeWindow2(theMainDOMWindow_, (void**) &win,  getter_AddRefs(topmost_DomWindow));
            if(::IsWindow(win))
            {
                theMainDOMWindow_HWND_ = win;
                ::ShowWindow(win, SW_HIDE);
                //::SetParent(win, m_hWnd);
                ::SetWindowLong(win, GWL_STYLE, (::GetWindowLong(win,GWL_STYLE) ) & ~(WS_THICKFRAME|WS_CAPTION));
                //::SetWindowLong(win, GWL_EXSTYLE, (::GetWindowLong(win,GWL_EXSTYLE)|WS_EX_TOOLWINDOW) & ~WS_EX_APPWINDOW);
                ::MoveWindow(win,0, 0, w,h, FALSE);
                if(topmost_DomWindow)
                {
                    /*nsCOMPtr<nsIWindowMediator> windowMediator =  do_GetService("@mozilla.org/appshell/window-mediator;1", &rv);
                   nsCOMPtr<nsISimpleEnumerator> aSimpleEnumerator ;
                    windowMediator->GetXULWindowEnumerator(L"navigator:browser", getter_AddRefs(aSimpleEnumerator )) ;
                    topmost_DomWindow = nsnull;
                    while(aSimpleEnumerator->HasMoreElements()) 
                    {
                        nsCOMPtr<nsISupport> asupport;
                        aSimpleEnumerator->GetNext(getter_AddRefs(asupport));
                        if(asupport)
                        {
                           nsCOMPtr<nsIDOMWidnow> domw = do_QueryInterface(asupport);
                           if(domw )
                           {
                               topmost_DomWindow  = nsnull;
                               HWND win_domw  = 0;
                               getDOMWindowParentNativeWindow2(domw, (void**) &win_domw,  getter_AddRefs(topmost_DomWindow));
                               if(::IsWindow(win) && win_domw == win)
                               {
                                   break;
                               }
                           }
                        }
                    }
                    */

                    //nsCOMPtr<nsIWindowMediator> windowMediator =  do_GetService("@mozilla.org/appshell/window-mediator;1", &rv);
                    //
                    //nsCOMPtr<nsIXULWindow> ansIXULWindow = do_QueryInterface(topmost_DomWindow);
                    //if(ansIXULWindow )
                    //{
                    //    windowMediator->UnregisterWindow(ansIXULWindow );//do not do this, it will close the window
                    //}
                    

                    nsCOMPtr<nsIDOMDocument>topmst_nsIDOMDocument;
                    topmost_DomWindow->GetDocument(getter_AddRefs(topmst_nsIDOMDocument));
                    if(topmst_nsIDOMDocument)
                    {
                        //'navigator-toolbox';
                        //'titlenbar-1'
                        nsString url_top;
                        topmst_nsIDOMDocument->GetDocumentURI(url_top);
                        nsCOMPtr<nsIDOMElement> navigator_toolbox;
                        nsCOMPtr<nsIDOMElement> titlenbar_1;
                        nsCOMPtr<nsIDOMElement> window_element;
                        topmst_nsIDOMDocument->GetElementById(nsString(L"main-window"), getter_AddRefs(window_element));
                        if(window_element)
                        {
                            //windowtype="navigator:browser" -->  //windowtype="navigator:browser-in-skype"
                            window_element->SetAttribute( nsString(L"windowtype") , nsString(L"navigator:browser-in-skype"));// this does not work
                            //some program will Enumeratr the window which is windowtype="navigator:browser" , and show them, but it was nt we want 
                        }
                        topmst_nsIDOMDocument->GetElementById(nsString(L"navigator-toolbox"), getter_AddRefs(navigator_toolbox));
                        topmst_nsIDOMDocument->GetElementById(nsString(L"titlebar-1"), getter_AddRefs(titlenbar_1));
                        if(titlenbar_1)
                        {
                            titlenbar_1->SetAttribute(nsString(L"hidden"), nsString(L"true"));
                        }
                        if(navigator_toolbox)
                        {
                            navigator_toolbox->SetAttribute(nsString(L"hidden"), nsString(L"true"));
                        }

                    }
                }
            }
        }
    }

    return TRUE;

}
//lint -e{529,438,952}
void FNIMToggleChatSessionFNMainWindowUI::DestoryBrowser()
{

    if(ansIWebBrowser_)
    {
        nsCOMPtr<nsIWebBrowserChrome> aBrowserChrome;
        nsresult rv = ansIWebBrowser_->GetContainerWindow(getter_AddRefs(aBrowserChrome) );

        if(NS_SUCCEEDED(rv) && aBrowserChrome )
        {
            aBrowserChrome->DestroyBrowserWindow();
        }
        ansIWebBrowser_ = nsnull;
    }
}

void FNIMToggleChatSessionFNMainWindowUI::SetFocusBrowser(  )
{
    nsCOMPtr<nsIBaseWindow> browserBaseWindow = do_QueryInterface(ansIWebBrowser_);

    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(ansIWebBrowser_);
    if (browserAsFocus && browserBaseWindow)
    {
        browserBaseWindow->SetFocus();
        browserAsFocus->Activate();
    }
}
void FNIMToggleChatSessionFNMainWindowUI::KillFocusBrowser(  )
{
    nsCOMPtr<nsIBaseWindow> browserBaseWindow = do_QueryInterface(ansIWebBrowser_);

    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(ansIWebBrowser_);
    if (browserAsFocus && browserBaseWindow)
    {
        browserAsFocus->Deactivate();
    }
}

#include "nsIDOMDocument.h"
#include "nsIDOMXULElement.h"
#include "nsIEditor.h"
#include "nsIBoxObject.h"
#include "nsIContainerBoxObject.h"
#include "nsIDocShell.h"
#include "nsIInterfaceRequestor.h"
#include "nsIDOMWindow.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMElementCSSInlineStyle.h"
//#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMCSSStyleDeclaration.h"

//#include "FNRichTextEditorWapper.h"

/* readonly attribute nsIDOMElement fnInput; */
NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::GetFnInput(nsISupports * *aFnInput)
{//to do for new UI
     if(!ansIWebBrowser_)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIDOMWindow> aWindow_out;
     ansIWebBrowser_->GetContentDOMWindow( getter_AddRefs(aWindow_out));
     if(!aWindow_out)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIDOMDocument> docu_out; 
     aWindow_out->GetDocument( getter_AddRefs(docu_out));
     if(!docu_out)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIDOMElement> readerBrowser;
     docu_out->GetElementById(NS_LITERAL_STRING("fnimeditorBrowser"), getter_AddRefs(readerBrowser));
     if(!readerBrowser)
     {
         return NS_ERROR_FAILURE;
     }

     return readerBrowser->QueryInterface(NS_GET_IID(nsISupports), (void**)aFnInput);

     /*nsCOMPtr<nsIDOMXULElement> frameRTE_XUL(do_QueryInterface(readerBrowser));
     if(!frameRTE_XUL)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIBoxObject> boxObject;
     nsresult rv = frameRTE_XUL->GetBoxObject(getter_AddRefs(boxObject));
     if(!boxObject)
     {
         return NS_ERROR_FAILURE;
     }

     nsCOMPtr<nsIContainerBoxObject> frameRTE_IContainerBoxObject(do_QueryInterface(boxObject));
     if(!frameRTE_IContainerBoxObject)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIDocShell> browser_nsIDocShell;
     frameRTE_IContainerBoxObject->GetDocShell( getter_AddRefs(browser_nsIDocShell)) ;

     if(!browser_nsIDocShell)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIInterfaceRequestor> pInterfaceRequestor = do_QueryInterface(browser_nsIDocShell);

     if(!pInterfaceRequestor )
     { 
         return NS_ERROR_FAILURE;
     }


     nsCOMPtr<nsIDOMDocument> spDoc;
     nsCOMPtr<nsIDOMWindow> aContentDOMWindow ;
     pInterfaceRequestor ->GetInterface(NS_GET_IID(nsIDOMWindow), getter_AddRefs( aContentDOMWindow) ) ;

     if(!aContentDOMWindow)
     {
         return NS_ERROR_FAILURE;
     }

     if(NS_SUCCEEDED(rv) && aContentDOMWindow)
     {
         aContentDOMWindow->GetDocument(getter_AddRefs(spDoc) );
         if(spDoc)
         {
             nsCOMPtr<nsIEditor> pEditor;
             rv = FNRichTextEditorWapper::GetEditor(spDoc , getter_AddRefs(pEditor) );
             if(pEditor)
             {
                 pEditor->QueryInterface(NS_GET_IID(nsISupports), (void**)aFnInput);
             }
         }
     }*/

    ///todo
    nsresult rv = 0;
     return rv;
 
}

/* readonly attribute nsIDOMElement fnReader; */
NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::GetFnReader(nsISupports * *aFnReader)
{//to do for new UI
    if(!ansIWebBrowser_)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIDOMWindow> aWindow_out;
     ansIWebBrowser_->GetContentDOMWindow( getter_AddRefs(aWindow_out));
     if(!aWindow_out)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIDOMDocument> docu_out; 
     aWindow_out->GetDocument( getter_AddRefs(docu_out));
     if(!docu_out)
     {
         return NS_ERROR_FAILURE;
     }
     nsCOMPtr<nsIDOMElement> readerBrowser;
     docu_out->GetElementById(NS_LITERAL_STRING("fnimreaderBrowser"), getter_AddRefs(readerBrowser));
     if(!readerBrowser)
     {
         return NS_ERROR_FAILURE;
     }

    return readerBrowser->QueryInterface(NS_GET_IID(nsISupports), (void**)aFnReader);
     
      

    //todo
    nsresult rv = 0;
     return rv;
}

/* void addUIListener_Close (in nsIDOMEventListener aListener); */
NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::AddUIListener_Close(nsIDOMEventListener *aListener)
{

    _listener_closebutton = aListener;
    return NS_OK;
}

/* void addUIListener_Submit (in nsIDOMEventListener aListener); */
NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::AddUIListener_Submit(nsIDOMEventListener *aListener)
{
    _listener_FNIMSendButton = aListener;
    return NS_OK;
}
NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::AddUIListener_Invitation(nsIDOMEventListener *aListener)
{

    _listener_invitationbutton = aListener;
    return NS_OK;
}


NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::Show(PRBool show)
{
    if(show)
    {
        Show( );
    }
    else 
    {
        Hide( );
    }

    return NS_OK;
}

NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::Close()
{

    if(! windowclosed_)
    {
        windowclosed_ = TRUE;
        if(::IsWindow(m_hWnd) )
        {
            DestroyWindow();
        }
    }

    ansIWebBrowser_ =  nsnull;
    theMainDOMWindow_ = nsnull;

    _listener_FNIMSendButton    =   nsnull;
    _listener_closebutton       =   nsnull;
    _documentReadyObserver      =   nsnull;
    aDestroyEvnetListener_      =   nsnull;

    return  NS_OK;
}

NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::WindowVisible(PRBool *_retval)
{
    if(_retval == nsnull)
        return NS_ERROR_INVALID_ARG;

    *_retval = PR_FALSE;


    if(!::IsWindowVisible( m_hWnd ))
        return NS_OK;

    HWND root2 = ::GetAncestor(m_hWnd, GA_ROOT);
    //HWND root2 = ::GetAncestor((HWND)(win), GA_ROOT);
    if( ::IsIconic(root2) )
    {
        return NS_OK;
    }
    if( !::IsWindowVisible(root2))
    {
        return NS_OK;
    }

    *_retval = PR_TRUE;

    return  NS_OK;
}

NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::GetWindowHandle( PRUint32 *win)
{

    if(win != nsnull)
    {
        *win =(PRUint32) m_hWnd;
    }
    return 0;

}

NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, 
                                                             PRUint32 w, PRUint32 h, 
                                                             PRUint32 style,  PRUint32 exStyle , PRBool* ret  )
{

     if(ret) 
     {
         *ret   = PR_FALSE;
     }
    RECT rc;
    rc.top      = (LONG)top;
    rc.left     = (LONG)left ;
    rc.right    = (LONG)left + (LONG)w;
    rc.bottom   = (LONG)top  + (LONG)h ;
    HWND newWin = Create((HWND)parent, &rc, NULL, style , exStyle);
    if(::IsWindow(newWin )  && ret)
    {
        *ret   = PR_TRUE;
    }
    return NS_OK;
}

NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::GetTitle(nsAString & aTitle)
{
    aTitle = _title;
    return 0;
}
NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::SetTitle(const nsAString & aTitle)
{
    _title  = aTitle;
    return 0;
}


NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::AddDocumentReadyObserver(nsIObserver *aObserver)
{
    _documentReadyObserver = aObserver;
    return NS_OK;
}
NS_IMETHODIMP FNIMToggleChatSessionFNMainWindowUI::AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener)
{
    aDestroyEvnetListener_ = listener;
    return NS_OK;//has registered
}


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

nsresult runjavascript_receriveRTEmsg(nsIDOMWindow* pDOMWindow,const nsString & cmd)
{
    nsresult rv = NS_OK;

    if(pDOMWindow == nsnull  )
        return NS_ERROR_INVALID_ARG;

    try{

        nsCOMPtr<nsIXPConnect> xpconnect = do_GetService(nsIXPConnect::GetCID(), &rv);
        if(NS_FAILED(rv) || !xpconnect)
        {
            return rv;
        }


        nsCOMPtr<nsIDOMWindow>  ansIDOMWindow = pDOMWindow;
        if(!ansIDOMWindow )
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

        jsParams[paramsCount++] = STRING_TO_JSVAL(JS_NewUCStringCopyZ(domWindow_context, (const jschar *)(cmd.get() ))  );//lint !e929 !e923

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


nsresult runjavascript_changeHandShake_status(nsIDOMWindow* pDOMWindow, bool handShaked)
{
    nsresult rv = NS_OK;

    if(pDOMWindow == nsnull  )
        return NS_ERROR_INVALID_ARG;

    try{

        nsCOMPtr<nsIXPConnect> xpconnect = do_GetService(nsIXPConnect::GetCID(), &rv);
        if(NS_FAILED(rv) || !xpconnect)
        {
            return rv;
        }


        nsCOMPtr<nsIDOMWindow>  ansIDOMWindow = pDOMWindow;
        if(!ansIDOMWindow )
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

        jsParams[paramsCount++] = BOOLEAN_TO_JSVAL( handShaked ? JS_TRUE : JS_FALSE);//lint !e929 !e923

        suc = JS_CallFunctionName(domWindow_context, window_obj, "set_handshake_status", 
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



void FNIMToggleChatSessionFNMainWindowUI::on_chat_message_received( const nsString &data)
{

    runjavascript_receriveRTEmsg(theMainDOMWindow_,  data);
     
}