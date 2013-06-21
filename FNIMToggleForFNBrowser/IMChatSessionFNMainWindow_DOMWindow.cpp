#include "IMChatSessionFNMainWindow_DOMWindow.h"


#include "nsIInterfaceRequestor.h"
#include "nsIObserverService.h"
#include "nsIObserver.h"

#include "nsIWindowWatcher.h"
#include "nsComponentManagerUtils.h"
#include "nsServiceManagerUtils.h"


#include "nsIDOMDocument.h"
#include "nsIDOMXULElement.h"
#include "nsIEditor.h"
#include "nsIBoxObject.h"
#include "nsIContainerBoxObject.h"
#include "nsIDocShell.h"
#include "nsIDOMWindow.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMElementCSSInlineStyle.h"
//#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMCSSStyleDeclaration.h"
#include "nsIDocument.h"
#include "nsIBaseWindow.h"
#include "nsPIDOMWindow.h"
#include "nsIWindowWatcher.h"
//#include "nsIDOMWindowInternal.h"
#include "nsIDOMEventTarget.h"

#include "FNRichTextEditorWapper.h"

//
//#define WINVER		0x0500
//#define _WIN32_WINNT	0x0501
//#define _WIN32_IE	0x0501
//#define _RICHEDIT_VER	0x0200
#include <atlbase.h>
//#include <atlapp.h>
//#include "atlctrls.h"
#include <atlwin.h>

//static 
#include "nsIDocShell.h"
#include "nsIInterfaceRequestor.h"
#include "nsIWebNavigation.h"
#include "nsIBaseWindow.h"
#include "nsIWidget.h"
#include "nsIDocShellTreeItem.h"
#include "nsIInterfaceRequestorUtils.h"

nsCOMPtr<nsIDocShell>  getDocShell(nsIDOMWindow * ansIDOMWindow)
{

    nsCOMPtr<nsIDocShell>   docShell;

    if(nsnull != ansIDOMWindow)
    {
        nsCOMPtr<nsIInterfaceRequestor> pInterfaceRequestor = do_QueryInterface(ansIDOMWindow);

        if(pInterfaceRequestor )
        {
            nsCOMPtr<nsIWebNavigation> ansIWebNavigation;
            pInterfaceRequestor ->GetInterface(NS_GET_IID(nsIWebNavigation), getter_AddRefs( ansIWebNavigation) ) ;

            if(ansIWebNavigation)
            {
                docShell = do_QueryInterface(ansIWebNavigation);
            }
        }
    }
    return docShell;

}
BOOL getDOMWindowTopmost(nsIDOMWindow *aDOMWindow, nsIDOMWindow ** topmost)
{
    nsCOMPtr<nsIInterfaceRequestor> pInterfaceRequestor = do_QueryInterface(aDOMWindow);

    if(pInterfaceRequestor )
    {
        nsCOMPtr<nsIWebNavigation> ansIWebNavigation;
        pInterfaceRequestor ->GetInterface(NS_GET_IID(nsIWebNavigation), getter_AddRefs( ansIWebNavigation) ) ;

        if(ansIWebNavigation)
        {

            nsCOMPtr<nsIDocShellTreeItem> navItem( do_QueryInterface( ansIWebNavigation ) );
            if ( navItem ) 
            {
                nsCOMPtr<nsIDocShellTreeItem> rootItem;
                navItem->GetRootTreeItem( getter_AddRefs( rootItem ) );
                nsCOMPtr<nsIDOMWindow> rootWin( do_QueryInterface( rootItem ) );
                rootWin->QueryInterface( NS_GET_IID(nsIDOMWindow) ,(void**) topmost);
                return TRUE ;
            }             
        }
    }

    return FALSE ;
}
//#include "nsIBrowserDOMWindow.h"
//#include "nsIDOMChromeWindow.h"
//nsCOMPtr<nsIBrowserDOMWindow> Get_BrowserDOMWindow(nsIWebNavigation* navNav)
//{
//
//  nsCOMPtr<nsIBrowserDOMWindow> bwin;
//  if(navNav != nsnull)
//  { // scope a bunch of temporary cruft used to generate bwin
//    nsCOMPtr<nsIDocShellTreeItem> navItem( do_QueryInterface( navNav ) );
//    if ( navItem ) 
//    {
//      nsCOMPtr<nsIDocShellTreeItem> rootItem;
//      navItem->GetRootTreeItem( getter_AddRefs( rootItem ) );
//      nsCOMPtr<nsIDOMWindow> rootWin( do_QueryInterface( rootItem ) );
//
//      nsCOMPtr<nsIDOMChromeWindow> chromeWin(do_QueryInterface(rootWin));
//      if ( chromeWin )
//        chromeWin->GetBrowserDOMWindow( getter_AddRefs ( bwin ) );
//    }
//  }
//  return bwin;
//}


NS_IMETHODIMP getDOMWindowParentNativeWindow2(nsIDOMWindow *domwin, void** outHWnd, void** topmostDOMWindow)
{
    nsCOMPtr<nsIWidget> widget;
    nsCOMPtr<nsIDOMWindow> window = do_QueryInterface(domwin);
    if (window) 
    {

        nsCOMPtr<nsIBaseWindow> baseWin = do_QueryInterface( getDocShell(window) );


        while (!widget && baseWin) 
        {
            baseWin->GetParentWidget(getter_AddRefs(widget));
            if (!widget) {
                nsCOMPtr<nsIDocShellTreeItem> docShellAsItem(do_QueryInterface(baseWin));
                if (!docShellAsItem)
                    return NS_ERROR_FAILURE;

                nsCOMPtr<nsIDocShellTreeItem> parent;
                docShellAsItem->GetParent(getter_AddRefs(parent));

                window = do_GetInterface(parent);
                if (!window)
                    return NS_ERROR_FAILURE;

                baseWin = do_QueryInterface( getDocShell(window) );
            }
        }
    }

    if( widget)
    {
        *outHWnd = (HWND)(widget->GetNativeData(NS_NATIVE_WINDOW ) );
        window->QueryInterface( NS_GET_IID(nsIDOMWindow) ,topmostDOMWindow);

    }

    return NS_OK;
}
NS_IMETHODIMP getDOMWindowParentNativeWindow(nsIDOMWindow *domwin, void** outHWnd)
{
    if(domwin != nsnull)
    {
        nsCOMPtr<nsIDOMDocument> aDOMDocument;
        nsresult rv = domwin->GetDocument(getter_AddRefs(aDOMDocument) );
        NS_ENSURE_TRUE(aDOMDocument, nsnull);

        nsCOMPtr<nsIDocument> aIDOcument = do_QueryInterface(aDOMDocument) ;
        NS_ENSURE_TRUE(aIDOcument, nsnull);


        nsPIDOMWindow *ansPIDOMWindow = aIDOcument ->GetWindow();//->GetContent(getter_AddRefs(ansIDOMWindow) );
        if(ansPIDOMWindow )
        {
            nsCOMPtr<nsIBaseWindow> ansIBaseWindow
                (do_QueryInterface(ansPIDOMWindow->GetDocShell()));
            NS_ENSURE_TRUE(ansIBaseWindow, nsnull);

            if(ansIBaseWindow )
            {
                
                rv = ansIBaseWindow->GetParentNativeWindow( outHWnd); //lint !e929 !e1924
                return rv;
                
            }
        }
    }
    return NS_ERROR_FAILURE;//lint !e1924
}



IMChatSessionFNMainWindow_DOMWindow::IMChatSessionFNMainWindow_DOMWindow(void):
windowclosed_(PR_FALSE),
m_hWnd(0) ,
init_size_w_(0U),
init_size_h_(0U) 
{
}

IMChatSessionFNMainWindow_DOMWindow::~IMChatSessionFNMainWindow_DOMWindow(void)
{
	if(theMainDOMWindow_)
	{
		nsCOMPtr<nsIDOMWindowInternal> active = do_QueryInterface(theMainDOMWindow_);
		if(active)
		{
			active->Close();
		}
	}

//	mFadeout.DestroyAll(TRUE);
}


/* Implementation file */
NS_IMPL_ISUPPORTS2(IMChatSessionFNMainWindow_DOMWindow, 
                   nsIDOMEventListener,
                   IFNIMToggleChatFNMainWindow
                   )



/* readonly attribute nsIDOMElement fnInput; */
NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::GetFnInput(nsISupports * *aFnInput)
{
  
     /*nsCOMPtr<nsIDOMWindow> aWindow_out = theMainDOMWindow_;
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
     nsCOMPtr<nsIDOMXULElement> frameRTE_XUL(do_QueryInterface(readerBrowser));
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
     }
     return rv;*/

    return 0;
}

/* readonly attribute nsIDOMElement fnReader; */
NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::GetFnReader(nsISupports * *aFnReader)
{
    /*nsCOMPtr<nsIDOMWindow> aWindow_out = theMainDOMWindow_;
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
     nsCOMPtr<nsIDOMXULElement> frameRTE_XUL(do_QueryInterface(readerBrowser));
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
                 pEditor->QueryInterface(NS_GET_IID(nsISupports), (void**)aFnReader);
             }
         }
     }
     return rv;*/

    return 0;
}

/* void addUIListener_Close (in nsIDOMEventListener aListener); */
NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::AddUIListener_Close(nsIDOMEventListener *aListener)
{

    _listener_closebutton = aListener;
    return NS_OK;
}

NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::AddUIListener_Invitation(nsIDOMEventListener *aListener)
{

    _listener_invitationbutton = aListener;
    return NS_OK;
}


/* void addUIListener_Submit (in nsIDOMEventListener aListener); */
NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::AddUIListener_Submit(nsIDOMEventListener *aListener)
{
    _listener_FNIMSendButton = aListener;
    return NS_OK;
}


NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::Show(PRBool show)
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

NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::Close()
{

    if(! windowclosed_ && theMainDOMWindow_)
    {
        nsCOMPtr<nsIDOMWindowInternal> ansIDOMWindowInternal = do_QueryInterface(theMainDOMWindow_);
        if(ansIDOMWindowInternal)
        {
            nsresult rv = ansIDOMWindowInternal->Close();
            if(rv  == NS_OK)
            {
                windowclosed_ = TRUE;
                theMainDOMWindow_ = nsnull;
            }
        }
    }


    _listener_FNIMSendButton    =   nsnull;
    _listener_closebutton       =   nsnull;
    _listener_invitationbutton  =   nsnull;
    _documentReadyObserver      =   nsnull;
    _destroyEvnetListener       =   nsnull;

    return  NS_OK;
}

NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::WindowVisible(PRBool *_retval)
{
    if(_retval == nsnull)
        return NS_ERROR_INVALID_ARG;

    *_retval = PR_FALSE;


    if(!::IsWindowVisible(  (HWND)m_hWnd ))
        return NS_OK;

    HWND root2 = ::GetAncestor((HWND)m_hWnd, GA_ROOT);
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

NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::GetWindowHandle( PRUint32 *win)
{

    if(win != nsnull)
    {
        if( m_hWnd  == 0)
        {
            getDOMWindowParentNativeWindow(theMainDOMWindow_, &m_hWnd);
        }

        *win =(PRUint32) m_hWnd;
    }
    return 0;

}
extern std::string   getIMUIFilePath();
NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, 
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
    



    nsresult rv;

  nsCOMPtr<nsIWindowWatcher> windowWatcher =  do_GetService("@mozilla.org/embedcomp/window-watcher;1", &rv);
  if(!windowWatcher )
      return rv ;

  nsCOMPtr<nsIDOMWindowInternal> activeParent;
  
 
  //nsCString window_feature ( "chrome,modal=no,dependent=yes,resizable=yes," );
  nsCString window_feature ( "chrome=no,titlebar=no,modal=no,resizable=yes," );

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

  init_size_w_ = (w);
  init_size_h_ = (h);
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

	rv = windowWatcher->OpenWindow(activeParent,
		window_uri.get(),
    "", ///Please note : here should not be a valid name, or there will be "close old, open new result".
    window_feature.get() ,
    nsnull,//ansSupport,
		getter_AddRefs(theMainDOMWindow_));

    if(theMainDOMWindow_  && ret)
    {
        *ret   = PR_TRUE;
    }
  


    if(rv == NS_OK)
    {
        if(theMainDOMWindow_)
        {
            PRUint32 win  = 0;
            GetWindowHandle( &win);
            //[I want to disable closing window by the ALT+F4, but its seems useless 
            /*  
            if(mHwnd && ::IsWindow(mHwnd) )
            {
            DWORD style = ::GetWindowLong( mHwnd, GWL_STYLE);
            style &= ~WS_SYSMENU;
            ::SetWindowLong(mHwnd, GWL_STYLE, style);
            }*/ 
            //]
//            if(!::IsWindow( mFadeout.m_hWnd))
            {
                //mFadeout.StartFadeOutWindow(m_hWnd, &fadeOuWindowRC );
                //mFadeout.StartFadeOutWindow((HWND)m_hWnd );
            }

//            if(::IsWindow( mFadeout.m_hWnd))
            {
                //::SetParent((HWND)m_hWnd, mFadeout.m_hWnd);
                //mFadeout.m_hWndFromCreater = (HWND)m_hWnd;
            }
        }

    }


    return NS_OK;
}

NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::AddDocumentReadyObserver(nsIObserver *aObserver)
{
    _documentReadyObserver = aObserver;
    return NS_OK;
}
NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener)
{
    _destroyEvnetListener = listener;
    return NS_OK;//has registered
}



PRBool  IMChatSessionFNMainWindow_DOMWindow:: Show( )
{

    
//    if(::IsWindowVisible(mFadeout.m_hWnd))
//    {
//        mFadeout.ShowFadeOutWindow(true);
 //   }
    
 //   else
    {
        if( ::IsWindow((HWND)m_hWnd ))
        {
            nsCOMPtr<nsIDOMElement> domElement_FNIMWindow;

            if(theMainDOMDocument_)
            {
                theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("FNIMWindow"), getter_AddRefs(domElement_FNIMWindow));
            }
            if(domElement_FNIMWindow)
            {
                domElement_FNIMWindow->SetAttribute(NS_LITERAL_STRING("FnVisible"), NS_LITERAL_STRING("true"));
            }
            ::ShowWindow((HWND)m_hWnd , SW_SHOW);
        }
    }

    return PR_TRUE;
}

PRBool  IMChatSessionFNMainWindow_DOMWindow:: Hide( )
{

    //if(::IsWindowVisible(mFadeout.m_hWnd))
    //{
    //    mFadeout.ShowFadeOutWindow(false);
    //}
    //
    //else
    {
        if( ::IsWindow((HWND)m_hWnd ))
        {
            ::ShowWindow((HWND)m_hWnd, SW_HIDE );
        }
    }


    return PR_TRUE;
}


void IMChatSessionFNMainWindow_DOMWindow::onDOMWindowLoad()
{
    nsCOMPtr<nsIDOMDocument> theMainDOMDocument_;
    theMainDOMWindow_->GetDocument(getter_AddRefs(theMainDOMDocument_));
    if(theMainDOMDocument_)
    {

        PRUint32 win  = 0;
        GetWindowHandle( &win);
        Hide();// make sure not show the popup rte now

        if(!_title.IsEmpty() )
        {
            nsCOMPtr<nsIDOMElement> title;
            theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("sub-title"), getter_AddRefs(title));
            if(title)
            {
                title->SetAttribute(NS_LITERAL_STRING("value"), _title);
            }
        }
        //FNIMSendButton 
        if(_listener_FNIMSendButton)
        {
            nsCOMPtr<nsIDOMElement> button;
            theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("FNIMSendButton"), getter_AddRefs(button));
            nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(button);
            if(eventTarget)
            {
                eventTarget->AddEventListener(NS_LITERAL_STRING("click"), _listener_FNIMSendButton, PR_FALSE);
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
            }        
        }


        if(_documentReadyObserver)// notify listener
        {
            _documentReadyObserver->Observe(nsnull,  "FNIMWebBrowserChrome_Ready", nsnull) ;
        }
        nsCOMPtr<nsIDOMElement> domElement_FNIMWindow;

        if(theMainDOMDocument_)
        {
            theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("FNIMWindow"), getter_AddRefs(domElement_FNIMWindow));
        }
        if(domElement_FNIMWindow)
        {
            nsString w_str;
            nsString h_str;
            w_str.AppendInt(init_size_w_);
            h_str.AppendInt(init_size_h_);
            domElement_FNIMWindow->SetAttribute(NS_LITERAL_STRING("width"), w_str);
            domElement_FNIMWindow->SetAttribute(NS_LITERAL_STRING("height"),h_str);
        }
    }
}

void IMChatSessionFNMainWindow_DOMWindow::onDOMWindowClose()
{

    //FNIMSendButton 
    if(_listener_FNIMSendButton && theMainDOMDocument_)
    {
        nsCOMPtr<nsIDOMElement> button;
        theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("FNIMSendButton"), getter_AddRefs(button));
        nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(button);
        if(eventTarget)
        {
            eventTarget->RemoveEventListener(NS_LITERAL_STRING("click"), _listener_FNIMSendButton, PR_FALSE);
        }
    }
    //closebutton
    if(_listener_closebutton && theMainDOMDocument_)
    {
        nsCOMPtr<nsIDOMElement> button;
        theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("closebutton"), getter_AddRefs(button));
        nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(button);
        if(eventTarget)
        {
            eventTarget->RemoveEventListener(NS_LITERAL_STRING("click"), _listener_closebutton, PR_FALSE);
        }
    }
    if(_listener_invitationbutton && theMainDOMDocument_)
    {
        nsCOMPtr<nsIDOMElement> button;
        theMainDOMDocument_->GetElementById(NS_LITERAL_STRING("FNInviteButton"), getter_AddRefs(button));
        nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(button);
        if(eventTarget)
        {
            eventTarget->RemoveEventListener(NS_LITERAL_STRING("click"), _listener_invitationbutton, PR_FALSE);
        }
    }

    if( _destroyEvnetListener)// notify listener
    {
        nsCOMPtr<nsISupports> ansISupports;
        QueryInterface(NS_GET_IID(nsISupports) ,  getter_AddRefs(ansISupports) );
        _destroyEvnetListener->OnDestroy(   ansISupports  );
    }

//    mFadeout.DestroyAll(TRUE);
}


NS_IMETHODIMP  IMChatSessionFNMainWindow_DOMWindow::HandleEvent(nsIDOMEvent *aEvent) 
{
	nsresult rv = NS_OK;

	if(aEvent != nsnull)
	{
	}
  else
  {
      if(!theMainDOMWindow_)
          return rv;// can do nothing 
      if( !theMainDOMDocument_) //window load will call this by the condition
      {
          onDOMWindowLoad();

      }
      else // mDomDocument != null //window unload will call this by the condition
      {                                           
          onDOMWindowClose();
      }
  }

	return rv;
} 



NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::GetTitle(nsAString & aTitle)
{
    aTitle = _title;
    return 0;
}
NS_IMETHODIMP IMChatSessionFNMainWindow_DOMWindow::SetTitle(const nsAString & aTitle)
{
    _title  = aTitle;
    return 0;
}