



//lint -elib(*)


// OS headers
//lint -e829
#include <stdio.h>

// Frozen APIs
#include "nsStringAPI.h"
#include "nsIComponentManager.h"
#include "nsIDOMWindow.h"
//#include "nsIGenericFactory.h"
#include "nsIInterfaceRequestor.h"
#include "nsIRequest.h"
#include "nsIURI.h"
#include "nsIWebProgress.h"
#include "nsCWebBrowser.h"
#include "nsIWebBrowserFocus.h"
#include "nsIObserver.h"
// Glue APIs (not frozen, but safe to use because they are statically linked)
#include "nsComponentManagerUtils.h"

// NON-FROZEN APIS!
#include "nsIWebNavigation.h"

#include "FNRichTextEditorWapper.h"
#include "nsIDOMDocument.h"
#include "nsIDOMWindow.h"
#include "FNIMWebBrowserChromeUI.h"

#include <list>
#include <iostream>
using namespace std;
//lint -e{1401,1926,1927,1928}
FNIMWebBrowserChrome::FNIMWebBrowserChrome(nsIWebBrowser * aBrowser, HWND  aNativeWindow)
{
    mWebBrowser = aBrowser;
    mNativeWindow = aNativeWindow;
    mSizeSet = PR_FALSE;
}
//lint -e{1540}
FNIMWebBrowserChrome::~FNIMWebBrowserChrome()
{
   // FNIMWebBrowserChromeUI::Destroyed(this);
}



//*****************************************************************************
// FNIMWebBrowserChrome::nsISupports
//*****************************************************************************   

NS_IMPL_ADDREF(FNIMWebBrowserChrome)//lint !e920
NS_IMPL_RELEASE(FNIMWebBrowserChrome)//lint !e1960 !e920
//lint --e{1960,534,1924,525,929,970}
NS_INTERFACE_MAP_BEGIN(FNIMWebBrowserChrome)
   NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(nsISupports, nsIWebBrowserChrome)
   NS_INTERFACE_MAP_ENTRY(nsIInterfaceRequestor)
   NS_INTERFACE_MAP_ENTRY(nsIWebBrowserChrome)
   NS_INTERFACE_MAP_ENTRY(nsIEmbeddingSiteWindow)
   NS_INTERFACE_MAP_ENTRY(nsIWebProgressListener) // optional
   //NS_INTERFACE_MAP_ENTRY(nsISHistoryListener)
   NS_INTERFACE_MAP_ENTRY(nsISupportsWeakReference)
   NS_INTERFACE_MAP_ENTRY(nsIObserver)
   NS_INTERFACE_MAP_ENTRY(nsIContextMenuListener)
   NS_INTERFACE_MAP_ENTRY(nsITooltipListener)
NS_INTERFACE_MAP_END

//*****************************************************************************
// FNIMWebBrowserChrome::nsIInterfaceRequestor
//*****************************************************************************   

NS_IMETHODIMP FNIMWebBrowserChrome::GetInterface(const nsIID &aIID, void** aInstancePtr)
{
    NS_ENSURE_ARG_POINTER(aInstancePtr);//lint !e1924

    *aInstancePtr = 0;
    if (aIID.Equals(NS_GET_IID(nsIDOMWindow)))//lint !e970
    {
        if (mWebBrowser)
        {
            return mWebBrowser->GetContentDOMWindow((nsIDOMWindow **) aInstancePtr);//lint !e929  !e1924
        }
        return NS_ERROR_NOT_INITIALIZED;//lint !e1960 !e1924
    }
    return QueryInterface(aIID, aInstancePtr);
}

//*****************************************************************************
// FNIMWebBrowserChrome::nsIWebBrowserChrome
//*****************************************************************************   
//lint -e{715}
NS_IMETHODIMP FNIMWebBrowserChrome::SetStatus(PRUint32 aType, const PRUnichar* aStatus)
{
    FNIMWebBrowserChromeUI::UpdateStatusBarText(this, aStatus);
    return NS_OK;//lint !e1960
}
//lint -e{1961}
NS_IMETHODIMP FNIMWebBrowserChrome::GetWebBrowser(nsIWebBrowser** aWebBrowser)
{
    NS_ENSURE_ARG_POINTER(aWebBrowser);//lint !e1924
    *aWebBrowser = mWebBrowser;
    NS_IF_ADDREF(*aWebBrowser);//lint !e534
    return NS_OK;//lint !e1960
}

NS_IMETHODIMP FNIMWebBrowserChrome::SetWebBrowser(nsIWebBrowser* aWebBrowser)
{
    mWebBrowser = aWebBrowser;
    return NS_OK;//lint !e1960
}
//lint -e{1961}
NS_IMETHODIMP FNIMWebBrowserChrome::GetChromeFlags(PRUint32* aChromeMask)
{
    *aChromeMask = mChromeFlags;
    return NS_OK;//lint !e1960
}

NS_IMETHODIMP FNIMWebBrowserChrome::SetChromeFlags(PRUint32 aChromeMask)
{

    mChromeFlags = aChromeMask;
    return NS_OK;//lint !e1960
}

NS_IMETHODIMP FNIMWebBrowserChrome::DestroyBrowserWindow(void)
{
    removeUIListeners();
    FNIMWebBrowserChromeUI::Destroy(this);
    return NS_OK;//lint !e1960
}


// IN: The desired browser client area dimensions.
NS_IMETHODIMP FNIMWebBrowserChrome::SizeBrowserTo(PRInt32 aWidth, PRInt32 aHeight)
{
  /* This isn't exactly correct: we're setting the whole window to
     the size requested for the browser. At time of writing, though,
     it's fine and useful for winEmbed's purposes. */
  FNIMWebBrowserChromeUI::SizeTo(this, aWidth, aHeight);
  mSizeSet = PR_TRUE;
  return NS_OK;//lint !e1960
}

//lint -e{1961,715}
NS_IMETHODIMP FNIMWebBrowserChrome::ShowAsModal(void)
{
	return NS_ERROR_FAILURE;//lint !e1924
}
//lint -e{1961,715}
NS_IMETHODIMP FNIMWebBrowserChrome::IsWindowModal(bool *_retval)
{
    *_retval = PR_FALSE;
    return NS_ERROR_NOT_IMPLEMENTED;//lint !e1924
}
//lint -e{1961,715}
NS_IMETHODIMP FNIMWebBrowserChrome::ExitModalEventLoop(nsresult aStatus)
{
  //mContinueModalLoop = PR_FALSE;
  return NS_OK;//lint !e1960
}

//*****************************************************************************
// FNIMWebBrowserChrome::nsIWebBrowserChromeFocus
//*****************************************************************************
//lint -e{1961}
NS_IMETHODIMP FNIMWebBrowserChrome::FocusNextElement()
{
    return NS_ERROR_NOT_IMPLEMENTED;//lint !e1924
}
//lint -e{1961}
NS_IMETHODIMP FNIMWebBrowserChrome::FocusPrevElement()
{
    return NS_ERROR_NOT_IMPLEMENTED;//lint !e1924
}

//*****************************************************************************
// FNIMWebBrowserChrome::nsIWebProgressListener
//*****************************************************************************   
//lint -e{952,715,534}
NS_IMETHODIMP FNIMWebBrowserChrome::OnProgressChange(nsIWebProgress *progress, nsIRequest *request,
                                                  PRInt32 curSelfProgress, PRInt32 maxSelfProgress,
                                                  PRInt32 curTotalProgress, PRInt32 maxTotalProgress)
{
    FNIMWebBrowserChromeUI::UpdateProgress(this, curTotalProgress, maxTotalProgress);
    return NS_OK;//lint !e1960
}
//lint -e{952,715,534}
NS_IMETHODIMP FNIMWebBrowserChrome::OnStateChange(nsIWebProgress *progress, nsIRequest *request,
                                               PRUint32 progressStateFlags, nsresult status)
{
    if ((progressStateFlags & STATE_START) && (progressStateFlags & STATE_IS_DOCUMENT))//lint !e1960
    {
        FNIMWebBrowserChromeUI::UpdateBusyState(this, PR_TRUE);
    }

    if ((progressStateFlags & STATE_STOP) && (progressStateFlags & STATE_IS_DOCUMENT))//lint !e1960
    {
        //FNIMWebBrowserChromeUI::UpdateBusyState(this, PR_FALSE);
        //FNIMWebBrowserChromeUI::UpdateProgress(this, 0, 100);
        //FNIMWebBrowserChromeUI::UpdateStatusBarText(this, nsnull);
        nsCOMPtr<nsIDOMWindow>  domWindow;
        nsCOMPtr<nsIDOMWindow>  thisDomWindow;
        if(progress)
        {
            progress->GetDOMWindow(getter_AddRefs(domWindow));
        }
        if(mWebBrowser)
        {
            mWebBrowser->GetContentDOMWindow(getter_AddRefs(thisDomWindow));//lint !e534
        }
        if(thisDomWindow && domWindow && domWindow == thisDomWindow)
        {
            ContentFinishedLoading();
        }

    }

    return NS_OK;//lint !e1960
}

//lint -e{952,715,534}
NS_IMETHODIMP FNIMWebBrowserChrome::OnLocationChange(nsIWebProgress* aWebProgress,
                                                 nsIRequest* aRequest,
                                                 nsIURI *location,
                                                 PRUint32 aFlags)
{
  PRBool isSubFrameLoad = PR_FALSE; // Is this a subframe load
  if (aWebProgress) {
    nsCOMPtr<nsIDOMWindow>  domWindow;
    nsCOMPtr<nsIDOMWindow>  topDomWindow;
    aWebProgress->GetDOMWindow(getter_AddRefs(domWindow));
    if (domWindow) { // Get root domWindow
      domWindow->GetTop(getter_AddRefs(topDomWindow));
    }
    if (domWindow != topDomWindow)
    {
      isSubFrameLoad = PR_TRUE;
    }
  }
  if (!isSubFrameLoad)
  {
    FNIMWebBrowserChromeUI::UpdateCurrentURI(this);
  }
  return NS_OK;//lint !e1960
}

//lint -e{952,715}
NS_IMETHODIMP FNIMWebBrowserChrome::OnStatusChange(nsIWebProgress* aWebProgress,
                                 nsIRequest* aRequest,
                                 nsresult aStatus,
                                 const PRUnichar* aMessage)
{
    FNIMWebBrowserChromeUI::UpdateStatusBarText(this, aMessage);
    return NS_OK;//lint !e1960
}



//lint -e{1961,952,715}
NS_IMETHODIMP FNIMWebBrowserChrome::OnSecurityChange(nsIWebProgress *aWebProgress, 
                                    nsIRequest *aRequest, 
                                    PRUint32 state)
{
    return NS_OK;//lint !e1960
}


//static void
//AppendIntToCString(PRInt32 info1, nsCString& aResult)
//{
//  char intstr[10];
//  _snprintf(intstr, sizeof(intstr) - 1, "%i", info1);
//  intstr[sizeof(intstr) - 1] = '\0';
//  aResult.AppendInt(intstr);
//}


void FNIMWebBrowserChrome::ContentFinishedLoading()
{
  // if it was a chrome window and no one has already specified a size,
    // size to content
    if (mWebBrowser && !mSizeSet &&
        (mChromeFlags & nsIWebBrowserChrome::CHROME_OPENAS_CHROME)) //lint !e1960 !e737
    {
        //nsCOMPtr<nsIDOMWindow> contentWin;
        //mWebBrowser->GetContentDOMWindow(getter_AddRefs(contentWin));//lint !e534
        //if (contentWin)
        //{
        //    contentWin->SizeToContent();//lint !e534
        //}
        //FNIMWebBrowserChromeUI::ShowWindow(this, PR_TRUE);
    }
    addUIListeners();

    if(_documentReadyObserver)
    {
        _documentReadyObserver->Observe(nsnull,  "FNIMWebBrowserChrome_Ready", nsnull) ;
    }
}



//*****************************************************************************
// FNIMWebBrowserChrome::nsIEmbeddingSiteWindow
//*****************************************************************************   
//lint -e{1961,715}
NS_IMETHODIMP FNIMWebBrowserChrome::SetDimensions(PRUint32 aFlags, PRInt32 x, PRInt32 y, PRInt32 cx, PRInt32 cy)
{
    return NS_OK;//lint !e1924
}
//lint -e{1961,534}
NS_IMETHODIMP FNIMWebBrowserChrome::GetDimensions(PRUint32 aFlags, PRInt32 *x, PRInt32 *y, PRInt32 *cx, PRInt32 *cy)
{

    RECT rc ={0};
    ::GetClientRect(mNativeWindow, &rc);
    if (aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION)
    {
        if (*x)
            *x = rc.left;
        if (*y)
            *y = rc.top;
    }
    if (aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER ||
        aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER)
    {
        if (*cx)
            *cx = rc.right - rc.left;
        if (*cy)
            *cy = rc.bottom - rc.top;
    }
    return NS_OK;
}

/* void setFocus (); */
//lint -e{1961,534}
NS_IMETHODIMP FNIMWebBrowserChrome::SetFocus()
{
	nsCOMPtr<nsIBaseWindow> browserBaseWindow = do_QueryInterface(mWebBrowser);
	/*if(!browserBaseWindow )
		return FALSE;;

	mOwner->mWebBrowserAsWin->SetFocus();*/

	nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(mWebBrowser);
	if (browserAsFocus && browserBaseWindow)//lint !e1960
	{
		browserBaseWindow->SetFocus();
		browserAsFocus->Activate();
		//browserAsFocus->SetFocusAtFirstElement();
	}

   // FNIMWebBrowserChromeUI::SetFocus(this);
    return NS_OK;//lint !e1960
}

/* attribute wstring title; */
//lint -e{1961,715}
NS_IMETHODIMP FNIMWebBrowserChrome::GetTitle(PRUnichar * *aTitle)
{
   NS_ENSURE_ARG_POINTER(aTitle);//lint !e1924

   *aTitle = nsnull;
   
   return NS_ERROR_NOT_IMPLEMENTED;//lint !e1924
}
//lint -e{1961,715}
NS_IMETHODIMP FNIMWebBrowserChrome::SetTitle(const PRUnichar * aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;//lint !e1924
}

/* attribute boolean visibility; */
//lint -e{1961,715}
NS_IMETHODIMP FNIMWebBrowserChrome::GetVisibility(bool * aVisibility)
{
    NS_ENSURE_ARG_POINTER(aVisibility);//lint !e1924
    *aVisibility = PR_TRUE;
    return NS_OK;//lint !e1960
}
//lint -e{1961,715}
NS_IMETHODIMP FNIMWebBrowserChrome::SetVisibility(bool aVisibility)
{
    return NS_OK;//lint !e1960
}

/* attribute nativeSiteWindow siteWindow */
NS_IMETHODIMP FNIMWebBrowserChrome::GetSiteWindow(void * *aSiteWindow)
{
   NS_ENSURE_ARG_POINTER(aSiteWindow);//lint !e1924

   *aSiteWindow = mNativeWindow;
   return NS_OK;//lint !e1960
}


//*****************************************************************************
// FNIMWebBrowserChrome::nsIObserver
//*****************************************************************************   
//lint -e{952,715,970}
NS_IMETHODIMP FNIMWebBrowserChrome::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *someData)
{
    nsresult rv = NS_OK;//lint !e1960
    //if (strcmp(aTopic, "profile-change-teardown") == 0)//lint !e1960
    //{
    //    // A profile change means death for this window
    //    FNIMWebBrowserChromeUI::Destroy(this);
    //}
    return rv;
}

//*****************************************************************************
// FNIMWebBrowserChrome::nsIContextMenuListener
//*****************************************************************************   

/* void OnShowContextMenu (in unsigned long aContextFlags, in nsIDOMEvent aEvent, in nsIDOMNode aNode); */
NS_IMETHODIMP FNIMWebBrowserChrome::OnShowContextMenu(PRUint32 aContextFlags, nsIDOMEvent *aEvent, nsIDOMNode *aNode)
{
    FNIMWebBrowserChromeUI::ShowContextMenu(this, aContextFlags, aEvent, aNode);
    return NS_OK;//lint !e1960
}

//*****************************************************************************
// FNIMWebBrowserChrome::nsITooltipListener
//*****************************************************************************   

/* void OnShowTooltip (in long aXCoords, in long aYCoords, in wstring aTipText); */
NS_IMETHODIMP FNIMWebBrowserChrome::OnShowTooltip(PRInt32 aXCoords, PRInt32 aYCoords, const PRUnichar *aTipText)
{
    FNIMWebBrowserChromeUI::ShowTooltip(this, aXCoords, aYCoords, aTipText);
    return NS_OK;//lint !e1960
}

/* void OnHideTooltip (); */
NS_IMETHODIMP FNIMWebBrowserChrome::OnHideTooltip()
{
    FNIMWebBrowserChromeUI::HideTooltip(this);
    return NS_OK;//lint !e1960
}


///////////////////////////////////////////
//UI event handlers
#include "nsIDOMElement.h"
#include "nsIDOMWindow.h"
#include "nsIDOMDocument.h"
#include "nsIDOMEventListener.h"
#include "nsIDOMEventTarget.h"
#include "nsIDOMEvent.h"

nsresult FNIMWebBrowserChrome::addUIListeners()
{
    if(!mWebBrowser || ! _listener_FNIMSendButton || !_listener_closebutton)
        return NS_ERROR_FAILURE;

    nsCOMPtr<nsIDOMWindow> aContentDOMWindow;
    nsresult rv = mWebBrowser->GetContentDOMWindow( getter_AddRefs(aContentDOMWindow) );
    if(!aContentDOMWindow)
        return rv;
    nsCOMPtr<nsIDOMDocument> domdoc;
    rv = aContentDOMWindow->GetDocument( getter_AddRefs(domdoc));
    if(!domdoc)
        return rv;


    nsCOMPtr<nsIDOMElement > ele;
    rv = domdoc->GetElementById( NS_LITERAL_STRING("FNIMSendButton"),  getter_AddRefs(ele));
    nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(ele);

    if(eventTarget)
    {
        eventTarget->AddEventListener(NS_LITERAL_STRING("click"), _listener_FNIMSendButton, PR_FALSE);
    }

    nsCOMPtr<nsIDOMElement > ele_closebutton;
    rv = domdoc->GetElementById( NS_LITERAL_STRING("closebutton"),  getter_AddRefs(ele_closebutton));
    nsCOMPtr<nsIDOMEventTarget>eventTarget_closebutton = do_QueryInterface(ele_closebutton);
    if(eventTarget_closebutton)
    {
        eventTarget_closebutton->AddEventListener(NS_LITERAL_STRING("click"), _listener_closebutton, PR_FALSE);
    }
    //onInvitationSend
    nsCOMPtr<nsIDOMElement > ele_FNInviteButton;
    rv = domdoc->GetElementById( NS_LITERAL_STRING("FNInviteButton"),  getter_AddRefs(ele_FNInviteButton));
    nsCOMPtr<nsIDOMEventTarget>eventTarget_FNInviteButton = do_QueryInterface(ele_FNInviteButton);

    if(eventTarget_FNInviteButton)
    {
        eventTarget_FNInviteButton->AddEventListener(NS_LITERAL_STRING("click"), _listener_FNInviteButton, PR_FALSE);
    }


    return NS_OK;
}
nsresult FNIMWebBrowserChrome::removeUIListeners()
{

    if(!mWebBrowser)
        return NS_ERROR_FAILURE;

    nsCOMPtr<nsIDOMWindow> aContentDOMWindow;
    nsresult rv = mWebBrowser->GetContentDOMWindow( getter_AddRefs(aContentDOMWindow) );
    if(!aContentDOMWindow)
        return rv;
    nsCOMPtr<nsIDOMDocument> domdoc;
    rv = aContentDOMWindow->GetDocument( getter_AddRefs(domdoc));
    if(!domdoc)
        return rv;

    nsCOMPtr<nsIDOMElement > ele;
    rv = domdoc->GetElementById( NS_LITERAL_STRING("FNIMSendButton"),  getter_AddRefs(ele));
    nsCOMPtr<nsIDOMEventTarget>eventTarget = do_QueryInterface(ele);
    if(eventTarget && _listener_FNIMSendButton)
    {
        eventTarget->RemoveEventListener(NS_LITERAL_STRING("click"), _listener_FNIMSendButton, PR_FALSE);

    }

    nsCOMPtr<nsIDOMElement > ele_closebutton;
    rv = domdoc->GetElementById( NS_LITERAL_STRING("closebutton"),  getter_AddRefs(ele_closebutton));
    nsCOMPtr<nsIDOMEventTarget>eventTarget_closebutton = do_QueryInterface(ele_closebutton);
    if(eventTarget_closebutton && _listener_closebutton)
    {

        eventTarget_closebutton->RemoveEventListener(NS_LITERAL_STRING("click"), _listener_closebutton, PR_FALSE);

    }
    //onInvitationSend
    nsCOMPtr<nsIDOMElement > ele_FNInviteButton;
    rv = domdoc->GetElementById( NS_LITERAL_STRING("FNInviteButton"),  getter_AddRefs(ele));
    nsCOMPtr<nsIDOMEventTarget>eventTarget_FNInviteButton = do_QueryInterface(ele_FNInviteButton);

    if(eventTarget_FNInviteButton)
    {
        eventTarget_FNInviteButton->RemoveEventListener(NS_LITERAL_STRING("click"), _listener_FNInviteButton, PR_FALSE);
    }

    //

    _listener_closebutton =  nsnull;
    _listener_FNIMSendButton =  nsnull;
    _listener_FNInviteButton = nsnull;
    _documentReadyObserver = nsnull;

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// FNIMWebBrowserChromeUI

//////////////////////////////////////////////////////////////////////////////////////////
//
//
////
////  FUNCTION: ResizeEmbedding()
////
////  PURPOSE: Resizes the webbrowser window to fit its container.
////
//lint -e{839}
nsresult FNIMWebBrowserChromeUI::ResizeEmbedding(nsIWebBrowserChrome* chrome)
{
    if (!chrome)
        return NS_ERROR_FAILURE;//lint !e1924

    nsCOMPtr<nsIEmbeddingSiteWindow> embeddingSite = do_QueryInterface(chrome);
    HWND hWnd;
    embeddingSite->GetSiteWindow((void **) & hWnd);//lint !e1924 !e929

    if (!hWnd)
        return NS_ERROR_NULL_POINTER;//lint !e1924

    RECT rect;
    GetClientRect(hWnd, &rect);

    // Make sure the browser is visible and sized
    nsCOMPtr<nsIWebBrowser> webBrowser;
    chrome->GetWebBrowser(getter_AddRefs(webBrowser));
    nsCOMPtr<nsIBaseWindow> webBrowserAsWin = do_QueryInterface(webBrowser);
    if (webBrowserAsWin)
    {
        webBrowserAsWin->SetPositionAndSize(rect.left, 
            rect.top, 
            rect.right - rect.left, 
            rect.bottom - rect.top,
            PR_TRUE);
        webBrowserAsWin->SetVisibility(PR_TRUE);
    }

    return NS_OK;
}


HWND FNIMWebBrowserChromeUI::GetBrowserFromChrome(nsIWebBrowserChrome *aChrome)
{
    if (!aChrome)
    {
        return NULL;
    }
    nsCOMPtr<nsIEmbeddingSiteWindow> baseWindow = do_QueryInterface(aChrome);
    HWND hwnd = NULL;
    baseWindow->GetSiteWindow((void **) & hwnd);//lint !e1924 !e929
    return hwnd;
}


//
// FUNCTION: Destroy()
//
// PURPOSE: Destroy the window specified by the chrome
//
void FNIMWebBrowserChromeUI::Destroy(nsIWebBrowserChrome* chrome)
{
    if(chrome == NULL) return ;

    nsCOMPtr<nsIWebBrowser> webBrowser;
    nsCOMPtr<nsIWebNavigation> webNavigation;

    chrome->GetWebBrowser(getter_AddRefs(webBrowser));
    webNavigation = do_QueryInterface(webBrowser);
    if (webNavigation)
        webNavigation->Stop(nsIWebNavigation::STOP_ALL);

    chrome->ExitModalEventLoop(NS_OK);

    HWND hwndDlg = FNIMWebBrowserChromeUI::GetBrowserFromChrome(chrome);
    if (hwndDlg == NULL)
        return;

    // Explicitly destroy the embedded browser and then the chrome

    // First the browser
    nsCOMPtr<nsIWebBrowser> browser = nsnull;
    chrome->GetWebBrowser(getter_AddRefs(browser));
    nsCOMPtr<nsIBaseWindow> browserAsWin = do_QueryInterface(browser);
    if (browserAsWin)
        browserAsWin->Destroy();

    // Now the chrome
    chrome->SetWebBrowser(nsnull);
    NS_RELEASE(chrome);
}

//
// FUNCTION: Set the input focus onto the browser window
//
void FNIMWebBrowserChromeUI::SetFocus(nsIWebBrowserChrome *chrome)
{
    HWND hwndDlg = FNIMWebBrowserChromeUI::GetBrowserFromChrome(chrome);
    if (hwndDlg == NULL)
    {
        return;
    }
    ::SetFocus(hwndDlg); 
}

//
//  FUNCTION: UpdateStatusBarText()
//
//  PURPOSE: Set the status bar text.
//lint -e{952,715,818}
void FNIMWebBrowserChromeUI::UpdateStatusBarText(nsIWebBrowserChrome *aChrome, const PRUnichar* aStatusText)
{
    /*   HWND hwndDlg = FNIMWebBrowserChromeUI::GetBrowserFromChrome(aChrome);
    nsCString status; 
    if (aStatusText) {
    nsString wStatusText(aStatusText);
    NS_UTF16ToCString(wStatusText, NS_CSTRING_ENCODING_NATIVE_FILESYSTEM,
    status);
    }

    SetDlgItemText(hwndDlg, IDC_STATUS, status.get());*/
}


//
//  FUNCTION: UpdateCurrentURI()
//
//  PURPOSE: Updates the URL address field
//
//lint -e{952,715,818}
void FNIMWebBrowserChromeUI::UpdateCurrentURI(nsIWebBrowserChrome *aChrome)
{
    /* nsCOMPtr<nsIWebBrowser> webBrowser;
    nsCOMPtr<nsIWebNavigation> webNavigation;
    aChrome->GetWebBrowser(getter_AddRefs(webBrowser));
    webNavigation = do_QueryInterface(webBrowser);

    nsCOMPtr<nsIURI> currentURI;
    webNavigation->GetCurrentURI(getter_AddRefs(currentURI));
    if (currentURI)
    {
    nsCString uriString;
    currentURI->GetAsciiSpec(uriString);
    HWND hwndDlg = FNIMWebBrowserChromeUI::GetBrowserFromChrome(aChrome);
    SetDlgItemText(hwndDlg, IDC_ADDRESS, uriString.get());
    }*/
}


//
//  FUNCTION: UpdateBusyState()
//
//  PURPOSE: Refreshes the stop/go buttons in the browser dialog
//lint -e{952,715,818}
void FNIMWebBrowserChromeUI::UpdateBusyState(nsIWebBrowserChrome *aChrome, PRBool aBusy)
{
    /* HWND hwndDlg = FNIMWebBrowserChromeUI::GetBrowserFromChrome(aChrome);
    HWND button;
    button = GetDlgItem(hwndDlg, IDC_STOP);
    if (button)
    EnableWindow(button, aBusy);
    button = GetDlgItem(hwndDlg, IDC_GO);
    if (button)
    EnableWindow(button, !aBusy);
    UpdateUI(aChrome);*/
}


//
//  FUNCTION: UpdateProgress()
//
//  PURPOSE: Refreshes the progress bar in the browser dialog
//lint -e{952,715,818}
void FNIMWebBrowserChromeUI::UpdateProgress(nsIWebBrowserChrome *aChrome, PRInt32 aCurrent, PRInt32 aMax)
{
    //HWND hwndDlg = FNIMWebBrowserChromeUI::GetBrowserFromChrome(aChrome);
    //HWND hwndProgress = GetDlgItem(hwndDlg, IDC_PROGRESS);
    //if (aCurrent < 0)
    //{
    //    aCurrent = 0;
    //}
    //if (aCurrent > aMax)
    //{
    //    aMax = aCurrent + 20; // What to do?
    //}
    //if (hwndProgress)
    //{
    //    SendMessage(hwndProgress, PBM_SETRANGE, 0, MAKELPARAM(0, aMax));
    //    SendMessage(hwndProgress, PBM_SETPOS, aCurrent, 0);
    //}
}

//
//  FUNCTION: ShowContextMenu()
//
//  PURPOSE: Display a context menu for the given node
//lint -e{952,715,818}
void FNIMWebBrowserChromeUI::ShowContextMenu(nsIWebBrowserChrome *aChrome, PRUint32 aContextFlags, nsIDOMEvent *aEvent, nsIDOMNode *aNode)
{
    // TODO code to test context flags and display a popup menu should go here
}

//
//  FUNCTION: ShowTooltip()
//
//  PURPOSE: Show a tooltip
//lint -e{952,715,818}
void FNIMWebBrowserChromeUI::ShowTooltip(nsIWebBrowserChrome *aChrome, PRInt32 aXCoords, PRInt32 aYCoords, const PRUnichar *aTipText)
{
    // TODO code to show a tooltip should go here
}

//
//  FUNCTION: HideTooltip()
//
//  PURPOSE: Hide the tooltip
//
//lint -e{818,952,715}
void FNIMWebBrowserChromeUI::HideTooltip(nsIWebBrowserChrome *aChrome)
{
    // TODO code to hide a tooltip should go here
}

void FNIMWebBrowserChromeUI::ShowWindow(nsIWebBrowserChrome *aChrome, PRBool aShow)
{
    HWND win = FNIMWebBrowserChromeUI::GetBrowserFromChrome(aChrome);
    ::ShowWindow(win, aShow ? SW_RESTORE : SW_HIDE);
}

void FNIMWebBrowserChromeUI::SizeTo(nsIWebBrowserChrome *aChrome, PRInt32 aWidth, PRInt32 aHeight)
{
    HWND hchrome = FNIMWebBrowserChromeUI::GetBrowserFromChrome(aChrome);
    HWND hbrowser = FNIMWebBrowserChromeUI::GetBrowserFromChrome(aChrome);
    RECT chromeRect, browserRect;

    ::GetWindowRect(hchrome,  &chromeRect);
    ::GetWindowRect(hbrowser, &browserRect);

    PRInt32 decoration_x = (browserRect.left - chromeRect.left) + 
        (chromeRect.right - browserRect.right);
    PRInt32 decoration_y = (browserRect.top - chromeRect.top) + 
        (chromeRect.bottom - browserRect.bottom);

    ::MoveWindow(hchrome, chromeRect.left, chromeRect.top,
        aWidth+decoration_x,
        aHeight+decoration_y, TRUE);
}



