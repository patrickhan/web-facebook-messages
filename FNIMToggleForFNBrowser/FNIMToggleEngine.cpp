#include "FNIMToggleEngine.h"
#include "nsEmbedString.h"

#pragma warning(disable: 4311 )
#pragma warning(disable: 4312 )
#include "nsTArray.h"
#pragma warning( default :4311)//pointer truncation from 'nsVoidArray::Impl *const ' to 'PRWord'
#pragma warning( default :4312)//conversion from 'PRWord' to 'void *' of greater size



#include "nsIObserverService.h"
#include "nsServiceManagerUtils.h"
#include "nsComponentManagerUtils.h"

#include "FNToggleImage.h"
#include "FNIMToggleIMApplicationHandler.h"


#include <algorithm>
/* Implementation file */


NS_IMPL_ISUPPORTS3(FNIMToggleEngine, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMToggleEngine);


FNIMToggleEngine::FNIMToggleEngine()
{
    /* member initializers and constructor code */
}

FNIMToggleEngine::~FNIMToggleEngine()
{
    /* destructor code */
}



NS_IMETHODIMP 
FNIMToggleEngine::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{//wiil be call wehn xpxom start up
  
    //FN_LOG_INFO_FUNCTION()
    nsresult rv;
    if( 0 == CaseInsensitiveCompare(aTopic, "profile-after-change", 20U) )
    {
        //register NS_XPCOM_SHUTDOWN_OBSERVER_ID
        nsCOMPtr<nsIObserverService> svc =
            do_GetService("@mozilla.org/observer-service;1", &rv);
        if (NS_SUCCEEDED(rv) && svc) {
            svc->AddObserver(this, "xpcom-shutdown", PR_TRUE);
            svc->AddObserver(this, "profile-change-teardown", PR_TRUE);
            
        }

        Start();

    }
    else if( 0 == CaseInsensitiveCompare(aTopic, "xpcom-shutdown", 14U)  || 0 == CaseInsensitiveCompare(aTopic, "profile-change-teardown", 23U)	)
    {
        //unregister NS_XPCOM_SHUTDOWN_OBSERVER_ID
        nsCOMPtr<nsIObserverService> svc =
            do_GetService("@mozilla.org/observer-service;1", &rv);
        if (NS_SUCCEEDED(rv) && svc) {
            // unregister 
            svc->RemoveObserver(this, "xpcom-shutdown");
            svc->RemoveObserver(this, "profile-change-teardown");
        }

        Quit();

    }
    else if(0 == CaseInsensitiveCompare(aTopic, "timer-callback", 14U) )
    {

        onTimer();
    }

    return NS_OK;
}

nsresult FNIMToggleEngine::Start()
{
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

    prepareInEmbedIMProcess();

    FNToggleImageDraw::initialize();
    return NS_OK;
}

nsresult FNIMToggleEngine::Quit()
{
    FNToggleImageDraw::quit();

    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_ = nsnull;
    }

    std::map<PRUint32 , nsCOMPtr<IFNIMToggleIMApplicationHandler> >::iterator itor1;
    for(itor1 = imAplicationhandlers_map_.begin() ; itor1 != imAplicationhandlers_map_.end() ; itor1++)
    {
        itor1->second->Quit(); 
    }
    imAplicationhandlers_map_.clear();
    imAplications_.Clear();

    return NS_OK;

}


#include <windows.h>
#include <tchar.h>
#include "psapi.h"

void getProcessName( DWORD processID ,  nsEmbedString& aModuleBaseName )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
            &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    // Print the process name and identifier.

    aModuleBaseName = szProcessName;
    //_tprintf( TEXT("%s  (PID: %u)\n"), szProcessName, processID );

    CloseHandle( hProcess );
}
nsresult FNIMToggleEngine::clearForProcess  ( PRUint32 processID)
{

    std::map<PRUint32 , nsCOMPtr<IFNIMToggleIMApplicationHandler> >::iterator itor;
    itor = imAplicationhandlers_map_.find(processID);

    if(itor == imAplicationhandlers_map_.end() )
    {//on found 
        return NS_OK;
    }

    itor->second->Quit();
    imAplicationhandlers_map_.erase(itor);

    return NS_OK;

}

void FNIMToggleEngine::findIMApplciation( IFNIMToggleApplication* app, std::list<PRUint32>& processIDs  , std::map<PRUint32, nsCOMPtr<IFNIMToggleApplication>>& processIDs_out  )
{

    if(app == nsnull)
        return ;
    // get the name and process identifier for each process.

    //nsEmbedString appName;
    //app->GetApplicationName(appName);
    //if(appName.Length()  == 0U )
    //{
    //    return; //should not reach here
    //}

    std::list<PRUint32> ::iterator itor;
    nsresult rv = NS_OK;

    for ( itor = processIDs.begin() ; itor!=processIDs.end() ; itor++ )
    {
        nsEmbedString aModuleBaseName;
        getProcessName( (DWORD)(*itor), aModuleBaseName );

        PRBool bret = PR_FALSE;
        rv =  app->IsMyApp(aModuleBaseName, &bret);
        if( bret )
        {
            processIDs_out[*itor ] = app;
        }
    }
}
#include <algorithm>


PRBool FNIMToggleEngine::hasNewProcess( std::list<PRUint32>& processIDs_diff_new, std::list<PRUint32>& processIDs_diff_killed  )
{
    typedef std::list<PRUint32> PRUint32_List;

    processIDs_diff_new.clear();
    processIDs_diff_killed.clear();

    DWORD aProcesses[1024], cbNeeded, cProcesses;


    if ( !::EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return PR_FALSE;
    }

    cProcesses = cbNeeded / sizeof(DWORD);

    std::list<PRUint32> processIDs;
    for ( PRUint32 i = 0; i < cProcesses; i++ )
    {
        if(aProcesses[ i] != 0) //0 :  system idle
        {
            processIDs.push_back(aProcesses[ i]);
        }
    }
    processIDs.sort();

    if(processes_cache_.size() == 0) //first time
    {
        processes_cache_.assign( processIDs.begin(), processIDs.end() );
        processIDs_diff_new.assign( processIDs.begin(), processIDs.end() );
    }
    else
    {
        //get the differences of the 2 process list
        //in processIDs but ont in processes_cache_ 

        std::insert_iterator<PRUint32_List> aIter_processIDs_diff_new_temp( processIDs_diff_new, processIDs_diff_new.begin ( ) );
        std::set_difference( processIDs.begin(), processIDs.end() , 
            processes_cache_.begin(), processes_cache_.end() , 
            aIter_processIDs_diff_new_temp );


        //get the differences of the 2 process list
        //in processes_cache_ but ont in processIDs
        std::insert_iterator<PRUint32_List> aIter_processIDs_diff_killed_temp( processIDs_diff_killed, processIDs_diff_killed.begin ( ) );
        std::set_difference( processes_cache_.begin(), processes_cache_.end() , 
            processIDs.begin(), processIDs.end() , 
            aIter_processIDs_diff_killed_temp );

        //set the processes_cache_
        processes_cache_.assign( processIDs.begin(), processIDs.end() );
        if(processIDs_diff_new.empty() )
        {//not change 
            return PR_FALSE;
        }
    }
    return PR_TRUE;
}


nsresult FNIMToggleEngine::onTimer()
{
    std::list<PRUint32> processIDs_diff;

    std::list<PRUint32> processIDs_diff_killed;

    //filter with cahed processes
    if( hasNewProcess( processIDs_diff , processIDs_diff_killed ) == PR_FALSE)
    {
        if(!processIDs_diff_killed.empty() )
        {//TODO clean the process related data
            std::list<PRUint32> ::iterator itor;
            for ( itor = processIDs_diff_killed.begin() ; itor!=processIDs_diff_killed.end() ; itor++ )
            {
                clearForProcess(*itor);
            }
        }

        return NS_OK;
    }


    //filter with interested applications
    std::map<PRUint32, nsCOMPtr<IFNIMToggleApplication>> processIDs_out;
    PRInt32 len = imAplications_.Count();
    for(PRInt32 index = 0; index < len; ++index)
    {
        nsCOMPtr<IFNIMToggleApplication> app = imAplications_.ObjectAt( index );

        findIMApplciation(app, processIDs_diff, processIDs_out);
    }


    //handle the targeted process
    std::map<PRUint32, nsCOMPtr<IFNIMToggleApplication>> ::iterator itor;
    for ( itor = processIDs_out.begin() ; itor!=processIDs_out.end() ; itor++ )
    {
        nsCOMPtr<IFNIMToggleApplication> p = itor->second;
        handleApplciation( itor->first, p );
    }

    return NS_OK;

}

nsresult FNIMToggleEngine::handleApplciation( PRUint32 processID , IFNIMToggleApplication * app)
{
    std::map<PRUint32 , nsCOMPtr<IFNIMToggleIMApplicationHandler> >::iterator itor;
    itor = imAplicationhandlers_map_.find(processID);
    if(itor != imAplicationhandlers_map_.end() )
    {//there is a handler has covered this process

        return NS_OK;
    }
    nsCOMPtr<IFNIMToggleIMApplicationHandler> handler = new FNIMToggleIMApplicationHandler();
    handler->Init(processID, app) ;
    imAplicationhandlers_map_[processID] = handler;
    ::MessageBox(0,L"FNIMToggleEngine::handleApplciation",L"",0);
    return NS_OK;
}


/* void registerIMApp (in IFNIMToggleApplication anIMapp); */
NS_IMETHODIMP FNIMToggleEngine::RegisterIMApp(IFNIMToggleApplication *anIMapp)
{

    if(anIMapp == nsnull)
    {
        return NS_ERROR_INVALID_ARG;
    }
    nsEmbedString appName;
    anIMapp->GetApplicationName(appName);
    if(appName.Length()  == 0U )
    {
        return NS_ERROR_NOT_AVAILABLE;
    }

    PRBool hadit = PR_FALSE;
    PRInt32 len = imAplications_.Count();
    for(PRInt32 index = 0; index < len; ++index)
    {

        nsCOMPtr<IFNIMToggleApplication> app = imAplications_.ObjectAt( index );
        nsEmbedString name;
        app->GetApplicationName(name);
        if(name.Equals(appName) )
        {
            return NS_OK;//has registered
        }
    }
    if(hadit == PR_FALSE)
    {
        imAplications_.AppendObject(anIMapp);
    }
    return NS_OK;
}

/* void unRegisterIMApp (in IFNIMToggleApplication anIMapp); */
NS_IMETHODIMP FNIMToggleEngine::UnRegisterIMApp(IFNIMToggleApplication *anIMapp)
{
    if(anIMapp == nsnull)
    {
        return NS_ERROR_INVALID_ARG;
    }
    nsEmbedString appName;
    anIMapp->GetApplicationName( appName );
    if(appName.Length()  == 0U )
    {
        return NS_ERROR_NOT_AVAILABLE;
    }

    PRBool hadit = PR_FALSE;
    PRInt32 len = imAplications_.Count( );
    for(PRInt32 index = 0; index < len; ++index)
    {

        nsCOMPtr<IFNIMToggleApplication> app = imAplications_.ObjectAt( index );
        nsEmbedString name;
        app->GetApplicationName( name );
        if( name.Equals( appName ) )
        {   //has registered
            imAplications_.RemoveObjectAt( index );
            return NS_OK;
        }
    }

    return NS_ERROR_FAILURE;
}

#include "./skype/skypetoggleApplication.h"
//#include "./yahoo/yahootoggleApplication.h"
//#include "./google/googletoggleApplication.h"
//#include "./icq/icqtoggleApplication.h"
//#include "./miranda/mirandatoggleApplication.h"
//#include "./pidgin/pidgintoggleApplication.h"
//#include "./aol/aoltoggleApplication.h"
//#include "./WindowsLiveMessager/LiveMSNtoggleApplication.h"
//#include "./netmeeting/FNIMToggleApplication.h"

void FNIMToggleEngine::prepareInEmbedIMProcess()
{
    nsresult rv = NS_OK;
    nsCOMPtr<IFNIMToggleApplication> skypeapp ;
    rv = Create_SkypeToggleApplication( getter_AddRefs(skypeapp) );
    //nsCOMPtr<IFNIMToggleApplication> skypeapp = new SkypeToggleApplication();
    if(skypeapp)
    {
        RegisterIMApp(skypeapp  );
    }

    //nsCOMPtr<IFNIMToggleApplication> app ;//= new FNIMToggleApplication();
    //nsresult rv = Create_FNIMToggleApplication( getter_AddRefs(app) );
    //if(app)
    //{
    //    RegisterIMApp(app );
    //}

    //nsCOMPtr<IFNIMToggleApplication> yahooapp ;//= new YahooToggleApplication();
    //rv = Create_yahooIMToggleApplication( getter_AddRefs(yahooapp ) );
    //if(yahooapp )
    //    RegisterIMApp(yahooapp  );

    //nsCOMPtr<IFNIMToggleApplication> googleapp ;//= new GoogleToggleApplication();
    //rv = Create_googleIMToggleApplication( getter_AddRefs(googleapp) );
    //if(googleapp)
    //    RegisterIMApp(googleapp  );

    //nsCOMPtr<IFNIMToggleApplication> icqapp ;//= new ICQToggleApplication();
    //rv = Create_ICQToggleApplication( getter_AddRefs(icqapp ) );
    //if(icqapp )
    //    RegisterIMApp(icqapp  );

    //nsCOMPtr<IFNIMToggleApplication> mirandaapp;// = new MirandaToggleApplication();
    //rv = Create_mirandaToggleApplication( getter_AddRefs(mirandaapp) );
    //if(mirandaapp)
    //    RegisterIMApp(mirandaapp );

    //nsCOMPtr<IFNIMToggleApplication> pidginapp ;//= new PidginToggleApplication();
    //rv = Create_pidginToggleApplication( getter_AddRefs(pidginapp ) );
    //if(pidginapp )
    //    RegisterIMApp(pidginapp );

    //nsCOMPtr<IFNIMToggleApplication> aolapp ;//= new AolToggleApplication();
    //rv = Create_AOLIMToggleApplication( getter_AddRefs(aolapp ) );
    //if(aolapp )
    //    RegisterIMApp(aolapp );


    //nsCOMPtr<IFNIMToggleApplication> widnowsLiveMsgApp ;//= new LiveMSNToggleApplication();
    //rv = Create_widnowsLiveIMToggleApplication( getter_AddRefs(widnowsLiveMsgApp) );
    //if(widnowsLiveMsgApp)
    //    RegisterIMApp(widnowsLiveMsgApp );

  //TODO more applications
}