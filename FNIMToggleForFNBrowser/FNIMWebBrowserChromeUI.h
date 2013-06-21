
#ifndef __WEBBROWSERCHROME__FNIMUI
#define __WebBrowserChrome__FNIMUI
#pragma once

#include <windows.h>

// FROZEN APIs
//lint -e451
#include "nsStringAPI.h"

#include "nsIWebBrowserChrome.h"
#include "nsIWebBrowserChromeFocus.h"

#include "nsIContextMenuListener.h"
#include "nsIEmbeddingSiteWindow.h"
#include "nsIInterfaceRequestor.h"
#include "nsIObserver.h"
#include "nsITooltipListener.h"
#include "nsIWebProgressListener.h"
#include "nsIWebBrowser.h"
#include "nsIDOMEventListener.h"
// GLUE APIs (not frozen, but safe because we're statically linking them)
#include "nsCOMPtr.h"
#include "nsIInterfaceRequestorUtils.h"
#include "nsWeakReference.h"
#include "nsEmbedString.h"

#include "IFNIMToggle.h"
 
class FNIMWebBrowserChromeUI
{
public:
    
    static void Destroy(nsIWebBrowserChrome* chrome);
    //static void Destroyed(nsIWebBrowserChrome* chrome);
    static void SetFocus(nsIWebBrowserChrome *chrome);
    static void UpdateStatusBarText(nsIWebBrowserChrome *aChrome, const PRUnichar* aStatusText);
    static void UpdateCurrentURI(nsIWebBrowserChrome *aChrome);
    static void UpdateBusyState(nsIWebBrowserChrome *aChrome, PRBool aBusy);
    static void UpdateProgress(nsIWebBrowserChrome *aChrome, PRInt32 aCurrent, PRInt32 aMax);
   // static void GetResourceStringById(PRInt32 aID, char ** aReturn);
    static void ShowContextMenu(nsIWebBrowserChrome *aChrome, PRUint32 aContextFlags, nsIDOMEvent *aEvent, nsIDOMNode *aNode);
    static void ShowTooltip(nsIWebBrowserChrome *aChrome, PRInt32 aXCoords, PRInt32 aYCoords, const PRUnichar *aTipText);
    static void HideTooltip(nsIWebBrowserChrome *aChrome);
    static void ShowWindow(nsIWebBrowserChrome *aChrome, PRBool aShow);
    static void SizeTo(nsIWebBrowserChrome *aChrome, PRInt32 aWidth, PRInt32 aHeight);
    static nsresult ResizeEmbedding(nsIWebBrowserChrome* chrome);
    static HWND FNIMWebBrowserChromeUI::GetBrowserFromChrome(nsIWebBrowserChrome *aChrome);
};
//lint --e{451, 1510,1509,1712,1748,1960,970,1736}
class FNIMWebBrowserChrome   : public nsIWebBrowserChrome,
                           public nsIWebBrowserChromeFocus,
                           public nsIWebProgressListener,
                           public nsIEmbeddingSiteWindow,
                           public nsIInterfaceRequestor,
                           //public nsISHistoryListener,
                           public nsIObserver,
                           public nsIContextMenuListener,
                           public nsITooltipListener,
                           public nsSupportsWeakReference

{
public:
    FNIMWebBrowserChrome(nsIWebBrowser * aBrowser, HWND  aNativeWindow);
    virtual ~FNIMWebBrowserChrome();

    NS_DECL_ISUPPORTS
    NS_DECL_NSIWEBBROWSERCHROME
    NS_DECL_NSIWEBBROWSERCHROMEFOCUS
    NS_DECL_NSIWEBPROGRESSLISTENER
    NS_DECL_NSIEMBEDDINGSITEWINDOW
    NS_DECL_NSIINTERFACEREQUESTOR
    //NS_DECL_NSISHISTORYLISTENER
    NS_DECL_NSIOBSERVER
    NS_DECL_NSICONTEXTMENULISTENER
    NS_DECL_NSITOOLTIPLISTENER

 
   void  SetParent(nsIWebBrowserChrome *aParent)
   {
       mDependentParent = aParent; 
    }
	///Patrick m_temp_ContentText is buffer used to set the content of the editor
   void SetEditorPreContent(const nsAString & content)
   {
	   m_temp_ContentText_editor = content;
   }
   void SetReaderorPreContent(const nsAString & content)
   {
	   m_temp_ContentText_reader = content;
   }
   void ContentFinishedLoading();

   nsresult addUIListeners();
   nsresult removeUIListeners();

   void set_listener_FNIMSendButton(nsIDOMEventListener*  alistener)
   {
       _listener_FNIMSendButton = alistener;
   }

   void set_listener_closebutton(nsIDOMEventListener*  alistener   )
   {
       _listener_closebutton = alistener;
   }
   void set_documentReadyObserver(nsIObserver*  anObserver   )
   {
       _documentReadyObserver = anObserver;
   }


protected:

    HWND         mNativeWindow;
    PRUint32     mChromeFlags;
    PRBool       mContinueModalLoop;
    PRBool       mSizeSet;

    nsEmbedString m_temp_ContentText_editor;
    nsEmbedString m_temp_ContentText_reader;

    nsCOMPtr<nsIWebBrowser> mWebBrowser;
    nsCOMPtr<nsIWebBrowserChrome> mDependentParent; // opener (for dependent windows only)

    //ui listeners 
    nsCOMPtr<nsIDOMEventListener> _listener_FNIMSendButton;
    nsCOMPtr<nsIDOMEventListener> _listener_closebutton;
    nsCOMPtr<nsIDOMEventListener> _listener_FNInviteButton;
    nsCOMPtr<nsIObserver> _documentReadyObserver;
};

#endif /* __WebBrowserChrome__FNIMUI */
