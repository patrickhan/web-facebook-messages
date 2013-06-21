#ifndef FNIMToggleEngine__HEADER__
#define FNIMToggleEngine__HEADER__

#include "IFNIMToggle.h"


#include "nsAutoPtr.h"
#include "nsIObserver.h"
#include "nsWeakReference.h"
#include "nsITimer.h"
#include "nsCOMArray.h"
#include "nsEmbedString.h"

#include <map>
#include <list>
class FNIMToggleEngine : public IFNIMToggleEngine
    ,public nsIObserver
		,public nsSupportsWeakReference

{
public:
  NS_DECL_ISUPPORTS
	NS_DECL_NSIOBSERVER
  NS_DECL_IFNIMTOGGLEENGINE

  FNIMToggleEngine();

private:
  ~FNIMToggleEngine();

protected:
  /* additional members */
    nsresult Start();
    nsresult Quit();
    nsresult onTimer();
    PRBool  hasNewProcess( std::list<PRUint32>& processIDs_diff_new, std::list<PRUint32>& processIDs_diff_killed  );
    nsresult handleApplciation( PRUint32 processID, IFNIMToggleApplication * app);
    nsresult clearForProcess  ( PRUint32 processID);

    void findIMApplciation( IFNIMToggleApplication* appName, std::list<PRUint32>& processIDs  , std::map<PRUint32, nsCOMPtr<IFNIMToggleApplication>>& processIDs_out  );

    void prepareInEmbedIMProcess();
private:
     
    nsCOMPtr<nsITimer>  aNSTimer_;
     
     nsCOMArray<IFNIMToggleApplication> imAplications_;
     
     std::map<PRUint32 , nsCOMPtr<IFNIMToggleIMApplicationHandler> > imAplicationhandlers_map_;

     std::list<PRUint32> processes_cache_;
};

#endif //FNIMToggleEngine__HEADER__
