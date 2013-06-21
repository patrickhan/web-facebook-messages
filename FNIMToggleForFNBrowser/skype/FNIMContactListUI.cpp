#include "FNIMContactListUI.h"


#include "nsIWindowWatcher.h"
#include "nsIDOMWindow.h" 
#include <nsServiceManagerUtils.h>
#include "nsComponentManagerUtils.h"
#include "nsStringAPI.h"

//////////////////class FNIMContactListUI_Locator 
NS_IMPL_ISUPPORTS3(FNIMContactListUI_Locator, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMWindowLocator);

  
FNIMContactListUI_Locator::FNIMContactListUI_Locator()
{
    ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}

FNIMContactListUI_Locator::FNIMContactListUI_Locator(boost::shared_ptr<FNIMContactListUI> aFNIMContactListUI , IFNIMToggleChatSessionMainWindow* amainWindow)
{
    _FNIMContactListUI = aFNIMContactListUI;
    mainWindow_ = amainWindow;
    ::SetRectEmpty((LPRECT)(&rc_ecpected_));
}
   
  


FNIMContactListUI_Locator::~FNIMContactListUI_Locator()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 
}

////////////////////////////////////////////////////////////////
// the expected area should be the smae size as IM chat Session window and just beside the window's right
nsresult FNIMContactListUI_Locator::getPos_expected(RECT *rc)
{
    nsresult ret = NS_ERROR_FAILURE;
    if(rc == NULL)
        return ret;

    if(!mainWindow_)
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

    //POINT pt= {0};
    //::ClientToScreen(parent , &pt);

    //prc->bottom    = rc.top - pt.y  ;
    //prc->right   = rc.right - pt.x;
    //prc->left  = prc->right   - FN_TOOGLE_BUTTON_WIDTH;
    //prc->top = prc->bottom    - FN_TOOGLE_BUTTON_HEIGHT;


    rc->right    = rc_sessionWindow.right -  rc_sessionWindow.left -10;
    rc->left   = rc->right - 400;
    rc->top     = 50 ;
    rc->bottom  = rc->top + 50 ;
    return NS_OK;
}

extern HWND getFNDesptopWidnow();
extern HWND getFNDesptopWidnowView();


nsresult FNIMContactListUI_Locator:: adjustLayout(const RECT* prc )
{
    if(!_FNIMContactListUI)
        return NS_ERROR_FAILURE;

    HWND win = _FNIMContactListUI->m_hWnd;
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

nsresult FNIMContactListUI_Locator::SyncPosition()
{
    if(! _FNIMContactListUI||  !mainWindow_)
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

nsresult FNIMContactListUI_Locator::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{

    if(0 == CaseInsensitiveCompare(aTopic, "timer-callback", 14U)  && mainWindow_)
    {
        HWND fnMainWindow_handle = 0;
        mainWindow_->GetM_hWnd((PRUint32*)&fnMainWindow_handle);
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
nsresult FNIMContactListUI_Locator::Locate( )
{

    if(!mainWindow_ || !_FNIMContactListUI)
        return NS_ERROR_FAILURE;


    RECT rc ={0};
    nsresult rv =  getPos_expected( &rc );
    if(rv!= NS_OK || ::IsRectEmpty(&rc))
        return NS_ERROR_FAILURE;

    HWND parent  = 0;
    mainWindow_->GetM_hWnd( (PRUint32*)&parent  );
 

    PRBool created = PR_FALSE;
    rv = _FNIMContactListUI->CreateNew((PRUint32 )parent, 
        (PRInt32)rc.left, (PRInt32)rc.top, 
        (PRUint32)(rc.right-rc.left), PRUint32(rc.bottom-rc.top), 
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0U, &created);
    HWND newWindow = _FNIMContactListUI->m_hWnd;
    if(!::IsWindow(newWindow ))
    {
        return NS_ERROR_FAILURE;
    }

    ::SetWindowPos(newWindow , HWND_TOP, rc.left, rc.top, 0,0, SWP_NOSIZE);


    return 0;
}


nsresult FNIMContactListUI_Locator::Close()
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    }
    mainWindow_= nsnull;
    _FNIMContactListUI.reset();

    return NS_OK;
}


//WTL

//#define WINVER		0x0500
//#define _WIN32_WINNT	0x0501
//#define _WIN32_IE	0x0501
//#define _RICHEDIT_VER	0x0200
#include <atlbase.h>
//#include <atlapp.h>
//#include "atlctrls.h"
#include <atlwin.h>
///////////////FNIMContactListUI class

#include "SkypeToggleButton.h"

#include "FNToggleImage.h"
 

NS_IMPL_ISUPPORTS2(FNIMContactListUI, 
                   nsIObserver,
                   nsISupportsWeakReference 
                   );

FNIMContactListUI::FNIMContactListUI()
: windowclosed_(FALSE)
{
    /* member initializers and constructor code */
}

FNIMContactListUI::~FNIMContactListUI()
{
    /* destructor code */
}


/* readonly attribute long m_hWnd; */
void FNIMContactListUI::Close()
{
    if(! windowclosed_ )
    {
        windowclosed_ = TRUE; 
        if(::IsWindow(m_hWnd) )
        {
            DestroyWindow();
        }
    }   
}

 
LRESULT FNIMContactListUI::OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    if(! windowclosed_ )
    {
        windowclosed_ = TRUE;
        Close();
    }
    return 0;
}

LRESULT FNIMContactListUI::OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */)
{
    windowclosed_ = FALSE;
    CreateBrowser( );
    return 0;
}

bool FNIMContactListUI::CreateNew(PRUint32 parent, 
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


         HRGN  rng = ::CreateRoundRectRgn(0,0,w,  h, 15,15);
         if(rng!= NULL)
         {
            ::SetWindowRgn(newW, rng, FALSE) ;

            //::DeleteObject(  (HGDIOBJ) rng);
         }

        if(_retval)
        {
            *_retval = PR_TRUE;
        }
        return true;
    }
    return false;
}

extern NS_IMETHODIMP getDOMWindowParentNativeWindow(nsIDOMWindow *domwin, void** outHWnd);

std::string  getIMUIFilePath_FNIMHandles()
{
    char pathFile[1024] ={0};
    ::GetModuleFileNameA(NULL, pathFile, 1023U);
    std::string path (pathFile);
    std::string::size_type pos = path.find_last_of("\\");
    path.replace(pos+1, path.length()-pos, "fnwebim\\fnskypeHandles.html");

    return path  ;
}
extern std::string getIMUIFilePath();
//lint -e{1762,831,774,948}
#include "FNIMWebBrowserChromeUI.h"
#include "nsIBaseWindow.h"
#include "nsIWebNavigation.h"
BOOL  FNIMContactListUI::CreateBrowser()
{
    if( ansIWebBrowser_ )
        return TRUE;
    //Create browsersite widnow
    HWND browserSiteWidnow = m_hWnd;
    if(!::IsWindow(browserSiteWidnow))
        return FALSE;

    nsCOMPtr<nsIWebBrowser>  aWebBrowser = do_CreateInstance("@mozilla.org/embedding/browser/nsWebBrowser;1");
    if (!aWebBrowser)
        return FALSE;

    ansIWebBrowser_ = aWebBrowser ;

    FNIMWebBrowserChrome *aBrowserChrome = new FNIMWebBrowserChrome( aWebBrowser, browserSiteWidnow);
    if (aBrowserChrome == NULL)
    {
        return FALSE;
    }
    aBrowserChrome->AddRef();
    aBrowserChrome->SetChromeFlags(nsIWebBrowserChrome::CHROME_ALL );
    aBrowserChrome->SetParent(nsnull);
    //aBrowserChrome->setChatSession( chat_Session_ );

    nsresult rv = aWebBrowser->SetContainerWindow(static_cast<nsIWebBrowserChrome*>(aBrowserChrome));
    if(NS_FAILED(rv) )
        return FALSE;
    nsCOMPtr<nsIBaseWindow> browserBaseWindow = do_QueryInterface(aWebBrowser);
    if(!browserBaseWindow )
        return FALSE;

    RECT rcLocation;
    ::GetWindowRect(browserSiteWidnow,//hparentWindow, 
        &rcLocation);

    rv  = browserBaseWindow->InitWindow( browserSiteWidnow,//hparentWindow,
        nsnull, 
        0, 0, 
        rcLocation.right - rcLocation.left, 
        rcLocation.bottom- rcLocation.top);
    if(NS_FAILED(rv) )
        return FALSE;

    rv = browserBaseWindow->Create();
    if(NS_FAILED(rv) )
        return FALSE;

    nsCOMPtr<nsIWebProgressListener> listener(static_cast<nsIWebProgressListener*>(aBrowserChrome));
    nsCOMPtr<nsIWeakReference> thisListener(do_GetWeakReference(listener));
    (void)aWebBrowser->AddWebBrowserListener(thisListener,  NS_GET_IID(nsIWebProgressListener));


    nsCOMPtr<nsIObserver> anObserver ;
    rv = this->QueryInterface(NS_GET_IID(nsIObserver), getter_AddRefs(anObserver));
    if(anObserver)
    {

        aBrowserChrome->set_documentReadyObserver(anObserver);
    }

    // Visible
    browserBaseWindow->SetVisibility(PR_TRUE);

    // Activated
    //nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(aWebBrowser);

    //if(browserAsFocus)
    //	browserAsFocus->Activate();

    nsCOMPtr<nsIWebNavigation> webNav(do_QueryInterface(aWebBrowser));
    if(!webNav)
        return  0;

    //[using the following surfix is to avoid the browser get url content from cache 
    //mozilla do cache to speed up, even though you set the parameter LOAD_FLAGS_BYPASS_CACHE

    std::string filepath = getIMUIFilePath_FNIMHandles();
    nsCString window_uri("file:///" );

    window_uri +=filepath.c_str();
    window_uri +="?nothing=";
    static int kkk = 0l;
    window_uri.AppendInt(kkk++ );

    webNav->LoadURI( NS_ConvertASCIItoUTF16(window_uri).get(),
        nsIWebNavigation::LOAD_FLAGS_NONE | nsIWebNavigation::LOAD_FLAGS_BYPASS_CACHE,// not cache
        nsnull,
        nsnull,
        nsnull);

    return TRUE;
}

nsresult FNIMContactListUI::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{

    if(0 == CaseInsensitiveCompare(aTopic, "FNIMWebBrowserChrome_Ready", 26U) )
    {
        onFNIMWebBrowserChrome_Ready(); 
    }
    return NS_OK;
}
#include "nsIDOMDocument.h"
#include "nsIDOMElement.h"
#include "SqliteOper_v2.h"
int getIMHandles( nsString &out)
{
    const  FNGlobalConfig &config1 = FNGlobalConfig::GetFNGlobalConfig();
    const fnstring &fn_DBFilePath = config1.GetDBFilePath();
	SQLiteOperParam_v2 dbconnParam;
	dbconnParam.m_databasename = fn_DBFilePath;
	
	CSqliteoper_v2 dbconn;
	if(dbconn.open(dbconnParam) == false)
	{
		return 0;
	}
    fnstring sqlstr = _T("SELECT imHandle FROM SecureKeyImHandleMap  INNER JOIN securekey  ON SecureKeyImHandleMap.contactId = securekey.id where imName='skype'");

    if(dbconn.query_syn(sqlstr ) == false)
    {
        return FALSE;
    }

     //"[{'imHandle':'1111111'},{'imHandle':'21111111'},{'imHandle':'31111111'},{'imHandle':'41111111'},{'imHandle':'51111111'}]"));

    nsString imHandleobjs;
    for(UINT counter = 0; counter < dbconn.rec_num(); ++counter)
    {
        //m_conn : it is easy to throw exceptoin
        try
        {
            std::wstring out = dbconn.getItemValue<std::wstring>(counter, 0);
            if(out.length() > 0)
            {
                nsString imHandleobj(L"{'imHandle':'");
                imHandleobj.Append(out.c_str());
                imHandleobj.Append(L"'}");
                imHandleobjs.Append(imHandleobj);
                imHandleobjs.Append(L",");
            }
        }
        catch(...)
        {
            //alog << " refreshEmails m_conn.getItemValue 3"<< FNSQLITE::endlog;
        }
    }

    out.Truncate();
    if(imHandleobjs.Length()> 0)
    {
        out.Append(L"[");
        out.Append(imHandleobjs);
        out.Append(L"]");
    }


	dbconn.close();
	return 0;
	
}
nsresult FNIMContactListUI::onFNIMWebBrowserChrome_Ready()
{

  if(ansIWebBrowser_)
  {
      nsCOMPtr<nsIDOMWindow> doWindow;
      ansIWebBrowser_->GetContentDOMWindow(getter_AddRefs(doWindow));
      if(doWindow)
      {
         // doWindow->PostMessageMoz(
          //nsIDOMWindow->postMessage
          nsCOMPtr<nsIDOMDocument> document;
          doWindow->GetDocument( getter_AddRefs(document) );
          if(document)
          {
              nsCOMPtr<nsIDOMElement> element;
              document->GetElementById(nsString(L"contact-container"), getter_AddRefs(element));
              if(element)
              {
                  nsString out;
                  getIMHandles( out);
                  element->SetAttribute(nsString(L"list"), out);//nsString(L"[{'imHandle':'1111111'},{'imHandle':'21111111'},{'imHandle':'31111111'},{'imHandle':'41111111'},{'imHandle':'51111111'}]"));
              }
          }
      }
  }


    return NS_OK;
}
/*BOOL  FNIMContactListUI::CreateBrowser()
{

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
    nsCString window_feature ( "chrome,dependent=yes,titlebar=no,modal=no,resizable=yes," );

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
    std::string filepath = getIMUIFilePath_FNIMHandles();
    nsCString window_uri("file:///" );

    window_uri +=filepath.c_str();
    window_uri +="?nothing=";
    window_uri.AppendInt(kkk++ ); 

    rv = windowWatcher->OpenWindow(activeParent,
        window_uri.get(),
        "", ///Please note : here should not be a valid name, or there will be "close old, open new result".
        window_feature.get() ,
        nsnull,//ansSupport,
        getter_AddRefs(theMainDOMWindow_));

    BOOL *ret = 0;
    if(theMainDOMWindow_  && ret)
    {
        *ret   = PR_TRUE;

        //theMainDOMWindow_->AddEventListener(NS_LITERAL_STRING("load"), _listener_FNIMSendButton, PR_FALSE);
    }



    if(rv == NS_OK)
    {
        if(theMainDOMWindow_)
        {
            HWND win  = 0;
            getDOMWindowParentNativeWindow(theMainDOMWindow_, (void**) &win  );
            if(::IsWindow(win))
            {
                ::SetParent(win, m_hWnd);
                ::MoveWindow(win,0, 0, w,h, TRUE);
                ::ShowWindow(win,SW_SHOW);
            }
        }
    }

    return TRUE;

}
*/