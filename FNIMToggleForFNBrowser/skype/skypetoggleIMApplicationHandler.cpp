#include "SkypeToggleIMApplicationHandler.h"
#include "nsIObserverService.h"
#include "nsServiceManagerUtils.h"
#include "nsComponentManagerUtils.h"

/* Implementation file */
NS_IMPL_ISUPPORTS3(SkypeToggleIMApplicationHandler, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMToggleIMApplicationHandler)

SkypeToggleIMApplicationHandler::SkypeToggleIMApplicationHandler()
{
  /* member initializers and constructor code */

}

SkypeToggleIMApplicationHandler::~SkypeToggleIMApplicationHandler()
{
  /* destructor code */
}


NS_IMETHODIMP SkypeToggleIMApplicationHandler::Init(PRUint32 processID, IFNIMToggleApplication *app)
{

    //processID_ = processID;
    app_ = app;
    if(app_ )
    {
        app_ ->Start(processID);


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
                aNSTimer_->Init(abserver, 5000U, nsITimer::TYPE_REPEATING_SLACK);
            }
        }

    }
    return NS_OK;
}

NS_IMETHODIMP SkypeToggleIMApplicationHandler::Quit( )
{
    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 
    
    if(app_)
    {
        app_->Quit();
    }
    app_ = nsnull;


    return NS_OK;
}




NS_IMETHODIMP 
SkypeToggleIMApplicationHandler::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{//wiil be call wehn xpxom start up

    if(0 == CaseInsensitiveCompare(aTopic, "timer-callback", 14U) )
    {

        onTimer();
    }

    return NS_OK;
}


nsresult SkypeToggleIMApplicationHandler::onTimer()
{
    if(app_ )
    {
        app_ ->Start(0xFFFFFFFF);
    }
    return NS_OK;

}