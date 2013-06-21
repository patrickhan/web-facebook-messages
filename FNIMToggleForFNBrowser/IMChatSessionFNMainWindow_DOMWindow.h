
#ifndef IMChatSessionFNMainWindow_DOMWindow_Header__
#define IMChatSessionFNMainWindow_DOMWindow_Header__

#pragma once


#include "IFNIMToggle.h"
#include "nsEmbedString.h"
#include "nsIMutableArray.h"
#include "nsCOMPtr.h"

#include "nsIDOMWindow.h"
#include "nsIDOMEventListener.h"
#include "nsIDOMDocument.h"

//#include "FadeoutSpecialWindow.h"

class IMChatSessionFNMainWindow_DOMWindow :
    public IFNIMToggleChatFNMainWindow,
    public nsIDOMEventListener 
{

    NS_DECL_ISUPPORTS
    NS_DECL_IFNIMTOGGLECHATFNMAINWINDOW
    NS_DECL_NSIDOMEVENTLISTENER 

public:
    IMChatSessionFNMainWindow_DOMWindow(void);
    ~IMChatSessionFNMainWindow_DOMWindow(void);

    PRBool  Show( );

    PRBool  Hide( );

    void onDOMWindowLoad();
    void onDOMWindowClose();
protected :
    
    nsCOMPtr<nsIDOMEventListener> _listener_FNIMSendButton;
    nsCOMPtr<nsIDOMEventListener> _listener_closebutton;
    nsCOMPtr<nsIDOMEventListener> _listener_invitationbutton;
    nsCOMPtr<nsIObserver> _documentReadyObserver;
    nsCOMPtr<IFNIMWindowDestroyEvnetListener> _destroyEvnetListener;

    nsCOMPtr<nsIDOMWindow> theMainDOMWindow_;
    nsCOMPtr<nsIDOMDocument> theMainDOMDocument_;

    PRBool windowclosed_;
    void* m_hWnd;
    nsString _title  ;
    PRUint32 init_size_w_;
    PRUint32 init_size_h_;

//    CFadeOutWndForFNIMToggle mFadeout;
};

#endif //IMChatSessionFNMainWindow_DOMWindow_Header__
