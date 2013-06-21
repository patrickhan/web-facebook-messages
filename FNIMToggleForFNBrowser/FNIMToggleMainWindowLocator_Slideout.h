#ifndef FNIMToggleMainWindowLocator_Slideout_header__
#define FNIMToggleMainWindowLocator_Slideout_header__
#pragma once

#include "IFNIMToggle.h"
#include "nsITimer.h"
#include "nsIObserver.h"
#include "nsWeakReference.h"
#include "windows.h"
class FNIMToggleMainWindowLocator_Slideout: public IFNIMWindowLocator
    ,public nsIObserver
		,public nsSupportsWeakReference 
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOBSERVER
  NS_DECL_IFNIMWINDOWLOCATOR
public:
    FNIMToggleMainWindowLocator_Slideout(void);
    ~FNIMToggleMainWindowLocator_Slideout(void);

    FNIMToggleMainWindowLocator_Slideout(
        IFNIMToggleChatFNMainWindow * fnmw,
        IFNIMToggleChatSessionMainWindow *mw,
        IFNIMToggleChatInputWindow *inw,
        IFNIMToggleChatReadWindow* rw);

protected:
    nsresult getPos_expected( RECT *rc);
    nsresult adjustLayout(const RECT* prc );

    nsCOMPtr<IFNIMToggleChatSessionMainWindow > mainWindow_;
    nsCOMPtr<IFNIMToggleChatInputWindow >       inputWindow_;
    nsCOMPtr<IFNIMToggleChatReadWindow >        readWindow_;
    nsCOMPtr<IFNIMToggleChatFNMainWindow>       fnMainWindow_;

    nsCOMPtr<nsITimer>  aNSTimer_;

    RECT rc_ecpected_ ;
};

#endif //FNIMToggleMainWindowLocator_Slideout_header__
