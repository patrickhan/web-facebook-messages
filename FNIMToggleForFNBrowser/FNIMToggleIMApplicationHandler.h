#pragma once
#include "IFNIMToggle.h"
#include "nsCOMPtr.h"
#include "nsEmbedString.h"
#include "nsITimer.h"
#include "nsIObserver.h"
#include "nsWeakReference.h"
class FNIMToggleIMApplicationHandler : public IFNIMToggleIMApplicationHandler
        ,public nsIObserver
		,public nsSupportsWeakReference
{
public:
  NS_DECL_ISUPPORTS
	NS_DECL_NSIOBSERVER
  NS_DECL_IFNIMTOGGLEIMAPPLICATIONHANDLER

  FNIMToggleIMApplicationHandler();

  nsresult onTimer();
private:
  ~FNIMToggleIMApplicationHandler();

protected:
    /* additional members */
    nsCOMPtr<IFNIMToggleApplication> app_;
    nsEmbedString applicationName_;

    nsCOMPtr<nsITimer>  aNSTimer_;
};
