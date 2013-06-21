#include "FNIMToggleApplication_common.h"
#include "SkypeToggleChatSession.h"
#include "nsIArray.h"
#include "nsIMutableArray.h"
#include "nsIVariant.h"


#include <algorithm>




/* Implementation file */
NS_IMPL_ISUPPORTS2(FNIMToggleApplication_common, IFNIMToggleApplication, IFNIMToggleApplication2)

FNIMToggleApplication_common::FNIMToggleApplication_common():processID_(0U)
{
  /* member initializers and constructor code */
   // applicationName_.AppendLiteral( "Skype.exe");
}


NS_IMETHODIMP FNIMToggleApplication_common::GetApplicationTrait(IFNIMToggleApplicationTrait * *aApplicationTrait) 
{
    if(aApplicationTrait == nsnull)
        return NS_ERROR_INVALID_ARG;
    if(applicationTrait_ )
    {
        *aApplicationTrait = applicationTrait_.get();
        (*aApplicationTrait)->AddRef();
    }
    return NS_OK;
}
NS_IMETHODIMP FNIMToggleApplication_common::SetApplicationTrait(IFNIMToggleApplicationTrait * aApplicationTrait) 
{
    applicationTrait_ = aApplicationTrait;
    return NS_OK;
}


/* attribute IFNIMToggleChatSessionMainWindowLocator sessionMainWindowLocator_; */
NS_IMETHODIMP FNIMToggleApplication_common::GetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * *aSessionMainWindowLocator)
{
    if(aSessionMainWindowLocator == nsnull)
        return NS_ERROR_INVALID_ARG;
    if(chatSessionMainWindowLocator_ )
    {
        *aSessionMainWindowLocator = chatSessionMainWindowLocator_.get();
        (*aSessionMainWindowLocator)->AddRef();
    }
    return NS_OK;

}
NS_IMETHODIMP FNIMToggleApplication_common::SetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * aSessionMainWindowLocator)
{
    chatSessionMainWindowLocator_ = aSessionMainWindowLocator;
    return NS_OK;
}



/* attribute IFNIMToggleChatSessionCreator sessionCreator; */
NS_IMETHODIMP FNIMToggleApplication_common::GetSessionCreator(IFNIMToggleChatSessionCreator * *aSessionCreator)
{
    if(aSessionCreator == nsnull)
        return NS_ERROR_INVALID_ARG;
    if(sessionCreator_ )
    {
        *aSessionCreator = sessionCreator_.get();
        (*aSessionCreator)->AddRef();
    }
    return NS_OK;

}
NS_IMETHODIMP FNIMToggleApplication_common::SetSessionCreator(IFNIMToggleChatSessionCreator * aSessionCreator)
{
    sessionCreator_ = aSessionCreator;
    return NS_OK;
}


FNIMToggleApplication_common::~FNIMToggleApplication_common()
{
  /* destructor code */
}
NS_IMETHODIMP FNIMToggleApplication_common::GetFNInputHWND(PRUint32 topLevel, PRUint32 *_retval)
{
	return NS_OK;
}

/* boolean setToggleMap (in PRUint32 top, in PRUint32 toggle); */
NS_IMETHODIMP FNIMToggleApplication_common::SetFNInputHWND(PRUint32 top, PRUint32 toggle) 
{

	return NS_OK;
}

/* readonly attribute AString applicationName; */
NS_IMETHODIMP FNIMToggleApplication_common::GetApplicationName(nsAString & aApplicationName)
{
    if(applicationTrait_)
    {
        applicationTrait_->GetApplicationName(aApplicationName);
    }
    //aApplicationName = applicationName_;
    return NS_OK;
}
nsresult FNIMToggleApplication_common::IsMyApp(const nsAString & appToken, PRBool *_retval)
{
    if(_retval)
    {
        applicationTrait_->IsMyApp(appToken, _retval);
       // *_retval = applicationName_.Equals( appToken );
    }
    return NS_OK;
}


NS_IMETHODIMP FNIMToggleApplication_common::Start(PRUint32 processID)
{
    if(processID != 0xFFFFFFFF)
    {
        processID_ = processID;
    }
     
    nsresult rv = checkChatSession( );

    return rv;
}

NS_IMETHODIMP FNIMToggleApplication_common::Quit( )
{
    for(PRInt32 i = 0; i < sessions_.Count() ; i++)
    {
      nsCOMPtr<IFNIMToggleChatSession> aSession  =   sessions_[i];
      if(aSession  )
      {
          aSession  ->Quit();
      }
    }

    sessions_.Clear();
    handled_window_cache_.clear();
    
    return NS_OK;
}
#include "SkypeToggleChatSessionMainWindow.h"
#include "windows.h"
nsresult FNIMToggleApplication_common::checkChatSession( )
{
    typedef std::list<PRUint32> PRUint32_List;
    if(!chatSessionMainWindowLocator_)
        return NS_ERROR_FAILURE;

    nsCOMPtr<nsIArray > foundwindow;
    nsCOMPtr<IFNIMToggleChatSessionMainWindowLocator_InProcess> aWindowLocator_InProcess
         = do_QueryInterface(chatSessionMainWindowLocator_);
    if(aWindowLocator_InProcess)
    {
        aWindowLocator_InProcess->Find_InProcess( processID_, getter_AddRefs(foundwindow )  ) ;
    }
    else
    {
        chatSessionMainWindowLocator_->Find( getter_AddRefs(foundwindow )  ) ;
    }
    if(!foundwindow)
    {
        return NS_OK;
    }
    PRUint32 count = 0U;
    foundwindow->GetLength( &count); 


    PRUint32_List hwnds;
    for(PRUint32 i = 0U; i < count; i++)
    {
        nsCOMPtr<nsIWritableVariant>  val;
        foundwindow->QueryElementAt(i ,NS_GET_IID(nsIWritableVariant), (void**)getter_AddRefs(val) );
        if(val)
        {
            PRInt32 iv = 0;
            val->GetAsInt32( &iv);
            
            HWND hwnd = (HWND)iv;
            if(::IsWindow( hwnd ))
            {
                DWORD processId = 0;
                ::GetWindowThreadProcessId( hwnd,    &processId);
                if(processId != processID_) //not in this process 
                {
                    continue;
                }
                else
                {
                    hwnds.push_back( (PRUint32)iv );
                }
            }
        }
    }

    hwnds.sort();//set_difference is for sorted 
    hwnds.unique();

    PRUint32_List new_windows ;
    PRUint32_List killed_windows;

    if(handled_window_cache_.empty() )
    {
        handled_window_cache_.assign( hwnds.begin(), hwnds.end() );
        new_windows .assign( hwnds.begin(), hwnds.end() );
    }
    else
    {
        insert_iterator<PRUint32_List> aIter_new_windows( new_windows, new_windows.begin ( ) );
        std::set_difference( hwnds.begin(), hwnds.end() , 
            handled_window_cache_.begin(), handled_window_cache_.end() , 
            aIter_new_windows );

        insert_iterator<PRUint32_List > aIter_killed_windows( killed_windows, killed_windows.begin ( ) );
        std::set_difference( 
            handled_window_cache_.begin(), handled_window_cache_.end() , 
            hwnds.begin(), hwnds.end() , 
            aIter_killed_windows);

        
        for(PRUint32_List::iterator itor2 = handled_window_cache_.begin();
            itor2!= handled_window_cache_.end(); itor2++)
        {
            PRUint32 awindow = *itor2;
            int k = 0;
        }
        for(PRUint32_List::iterator itor3 = killed_windows.begin();
            itor3!= killed_windows.end(); itor3++)
        {
            PRUint32 awindow = *itor3;
            int k = 0;
        }
        for(PRUint32_List::iterator itor1 = new_windows.begin();
            itor1!= new_windows.end(); itor1++)
        {
            PRUint32 awindow = *itor1;
            int k = 0;
        }
    }

    PRUint32_List::iterator itor;
    for(itor = new_windows.begin(); itor!= new_windows.end() ; itor++)
    {
        PRUint32 new_window = *itor;
        nsresult rv = createNewSession(new_window  );
        if(rv == NS_OK)
        {
        }
    }


    for(itor = killed_windows.begin(); itor!= killed_windows.end() ; itor++)
    {
        PRUint32 killed_window = *itor;
        ReleaseChatSession(killed_window  );
        handled_window_cache_.remove(killed_window);
    }

    handled_window_cache_.merge(new_windows);
    handled_window_cache_.unique();
    
    return NS_OK;
}

nsresult  FNIMToggleApplication_common::ReleaseChatSession( PRUint32 sessionMainWindow)
{
    for(PRInt32 i = 0; i < sessions_.Count() ; i++)
    {
        nsCOMPtr<IFNIMToggleChatSession>  aSession=      sessions_[i];
        nsCOMPtr<IFNIMToggleChatSessionMainWindow> aMainWindow;
        aSession->GetMainWindow(getter_AddRefs(aMainWindow));
        if(aMainWindow)
        {
            PRUint32 wnd = 0 ;
            aMainWindow->GetM_hWnd(&wnd );
            if( sessionMainWindow!= 0 && wnd  == sessionMainWindow )
            {
                sessions_.RemoveObjectAt(i);
                break;
            }
        }
    }

    return NS_OK;
}
nsresult  FNIMToggleApplication_common::createNewSession( PRUint32 sessionMainWindow)
{
    if(!sessionCreator_)
    {
        return NS_ERROR_FAILURE;
    }

    nsCOMPtr<IFNIMToggleChatSession> session;
    sessionCreator_->CreateSession(getter_AddRefs(session) );
    if(session)
    {
        session->SetApplictaion(this);
        session->SetMainwindowHandle(sessionMainWindow);
        session->AddToggleButton();

        sessions_.AppendObject( session );
        return NS_OK;
   }

    return NS_ERROR_FAILURE;
}


nsresult  FNIMToggleApplication_common::RemoveSession(IFNIMToggleChatSession *aSession)
{
    if(aSession != nsnull)
    {
        nsCOMPtr<IFNIMToggleChatSession>  aSession_in  = aSession ;

        for(PRInt32 i = 0; i < sessions_.Count() ; i++)
        {
            nsCOMPtr<IFNIMToggleChatSession>  aSession_temp =      sessions_[i];
            if( aSession_in == aSession_temp )
            {
                sessions_.RemoveObjectAt(i);
                break;
            }
        }
    }
    return NS_OK;
}

