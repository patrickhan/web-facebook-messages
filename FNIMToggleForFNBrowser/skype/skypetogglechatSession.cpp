
#include "stdafx.h"

#include "SkypeToggleChatSession.h"
#include "SkypeToggleChatSessionMainWindow.h"
#include "SkypeToggleChatReadWindow.h"
#include "SkypeToggleChatInputWindow.h"
#include "SkypeToggleChatFNReadWindow.h"
#include "SkypeToggleChatFNInputWindow.h"

#include "SkypeToggleButton.h"

#include "IMChatSessionFNMainWindow_DOMWindow.h"

#include "nsIObserverService.h"
#include "nsServiceManagerUtils.h"
#include "nsComponentManagerUtils.h"
#include "nsIDOMEventListener.h"
#include "nsIDOMEventTarget.h" 
#include "nsIDOMElement.h"
#include "nsIDOMEvent.h"

#define USING_SKYPE4COM 1
#ifdef USING_SKYPE4COM
#include "skypeAPIWapper.h"
#endif //USING_SKYPE4COM


#include "time.h"

void tryAddSkypeContactor(LPCTSTR fnusename, LPCTSTR skypehandler);

static const wchar_t HANDSHAKE_SULOTION[] = L"Chat with FN HACK JACKET#";

bool doubleTime2UniversalTimeString(double dtime, nsString &timeStr_out)
{

    SYSTEMTIME asystemTime ={0};
    BOOL ok =  VariantTimeToSystemTime(dtime,  &asystemTime);
    //COleDateTime is in local timezone, DateTime is in UTC, so we need to convert
    SYSTEMTIME st_utc;
    TzSpecificLocalTimeToSystemTime(NULL, &asystemTime, &st_utc);
    /*
    The range of the _mkgmtime32 function is from midnight, January 1, 1970, UTC to January 19, 3:14:07, 2038, UTC. 
    The range of _mkgmtime64 is from midnight, January 1, 1970, UTC to 23:59:59, December 31, 3000, UTC. 
    An out-of-range date results in a return value of –1. The range of _mkgmtime depends on whether _USE_32BIT_TIME_T is defined. 
    If not defined (the default) the range is that of _mkgmtime64; otherwise, the range is limited to the 32-bit range of _mkgmtime32.
    */
    tm aTM = {0};
    aTM.tm_year = (int)st_utc.wYear - 1900;
    aTM.tm_mon = (int)st_utc.wMonth;
    aTM.tm_mday = st_utc.wDay;
    aTM.tm_hour = st_utc.wHour;
    aTM.tm_min = st_utc.wMinute;
    aTM.tm_sec = st_utc.wSecond;
    __time32_t   aTime_t = _mkgmtime32(&aTM);

    _variant_t v(aTime_t) ;// we use _bstr_t(_variant_t) constructor to create _bstr_t instance
    _bstr_t date_str(v );
    date_str += _bstr_t(L"000");// we do not care about ms
    timeStr_out = date_str.GetBSTR();

    return true;
}

NS_IMPL_ISUPPORTS7(SkypeToggleChatSession, 
                   nsIObserver,
                   nsISupportsWeakReference,
                   IFNIMToggleChatSession,
                   nsIDOMEventListener,
                   IFNIMToggleButtonEvnetListener,
                   IFNIMWindowDestroyEvnetListener,
                   IFNIMToggleChatSessionContactor)


SkypeToggleChatSession::SkypeToggleChatSession():listener_Cookie_(0U),handshaked_(false)
{
  /* member initializers and constructor code */
}

SkypeToggleChatSession::~SkypeToggleChatSession()
{
    /* destructor code */
    toggleButton_ = nsnull;
    fnMainWindowLocator_    = nsnull;
    chatReadWindowLocator_  = nsnull;
    chatInputWindowLocator_  = nsnull;
    toggleButtonLocator_    = nsnull;
    
    mainWindow_ = nsnull;
    inputWindow_ = nsnull;
    readWindow_ = nsnull;

    fnReader_Window_ = nsnull;
    fnInput_Window_ = nsnull;

}

/* attribute IFNIMToggleApplication applictaion; */
NS_IMETHODIMP SkypeToggleChatSession::GetApplictaion(IFNIMToggleApplication * *aApplictaion)
{
    if(application_ )
    {
        application_ ->QueryInterface(NS_GET_IID(IFNIMToggleApplication ) , (void**)aApplictaion);
        return NS_OK;
    }
    return NS_ERROR_FAILURE;
}
NS_IMETHODIMP SkypeToggleChatSession::SetApplictaion(IFNIMToggleApplication * aApplictaion)
{
    application_ = aApplictaion;
    return NS_OK;
}

/* attribute IFNIMToggleChatSessionMainWindow mainWindow; */
NS_IMETHODIMP SkypeToggleChatSession::GetMainWindow(IFNIMToggleChatSessionMainWindow * *aMainWindow)
{
    if(mainWindow_ )
    {
        mainWindow_ ->QueryInterface(NS_GET_IID(IFNIMToggleChatSessionMainWindow ) , (void**)aMainWindow);
        return NS_OK;
    }
    return NS_ERROR_FAILURE;
}
NS_IMETHODIMP SkypeToggleChatSession::SetMainwindowHandle(PRUint32 hwnd)
{
    if(!mainWindow_)
    {
        mainWindow_ =  new SkypeToggleChatSessionMainWindow();
    }

    if(mainWindow_)
    {
       mainWindow_-> SetM_hWnd( hwnd );
       retrieveChatContactorInfo();
    }
    return NS_OK;
}


 
NS_IMETHODIMP SkypeToggleChatSession::GetInputWindow(IFNIMToggleChatInputWindow * *aInputwindow)
{
    if(inputWindow_ && nsnull != *aInputwindow )
    {
        *aInputwindow = nsnull;
        return inputWindow_->QueryInterface( NS_GET_IID(IFNIMToggleChatInputWindow ),  (void**)aInputwindow);
    }
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatSession::SetInputWindow(IFNIMToggleChatInputWindow * aInputwindow)
{
    inputWindow_ = aInputwindow;
    return NS_OK;
}

 
NS_IMETHODIMP SkypeToggleChatSession::GetReadWindow(IFNIMToggleChatReadWindow * *aReadwindow)
{
    if(readWindow_ && *aReadwindow != nsnull)
    {
        *aReadwindow = nsnull;
        return readWindow_->QueryInterface( NS_GET_IID(IFNIMToggleChatReadWindow ),  (void**)aReadwindow);
    }
    return NS_OK;

}
NS_IMETHODIMP SkypeToggleChatSession::SetReadWindow(IFNIMToggleChatReadWindow * aReadwindow)
{
    readWindow_ = aReadwindow;
    return NS_OK;
}



 
NS_IMETHODIMP SkypeToggleChatSession::GetFnInputWindow(IFNIMToggleChatFNInputWindow * *aFnInputWindow)
{
    if(fnInput_Window_ && *aFnInputWindow != nsnull)
    {
        *aFnInputWindow = nsnull;
        return fnInput_Window_->QueryInterface( NS_GET_IID(IFNIMToggleChatFNInputWindow ),  (void**)aFnInputWindow);
    }
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP SkypeToggleChatSession::SetFnInputWindow(IFNIMToggleChatFNInputWindow * aFnInputWindow)
{
    fnInput_Window_ = aFnInputWindow;
    return NS_OK;
}

 
NS_IMETHODIMP SkypeToggleChatSession::GetFnReadWindow(IFNIMToggleChatFNReadWindow * *aFnReadWindow)
{
    if(fnReader_Window_ && *aFnReadWindow != nsnull)
    {
        *aFnReadWindow = nsnull;
        return fnReader_Window_->QueryInterface( NS_GET_IID(IFNIMToggleChatFNReadWindow ),  (void**)aFnReadWindow);
    }
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP SkypeToggleChatSession::SetFnReadWindow(IFNIMToggleChatFNReadWindow * aFnReadWindow)
{
    fnReader_Window_ = aFnReadWindow ;
    return NS_OK;
}
 
NS_IMETHODIMP SkypeToggleChatSession::GetToggleButton(IFNIMToggleButton * *aToggleButton)
{
    if(toggleButton_ && *aToggleButton != nsnull)
    {
        *aToggleButton = nsnull;
        return toggleButton_->QueryInterface( NS_GET_IID(IFNIMToggleButton ),  (void**)aToggleButton);
    }
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatSession::SetToggleButton(IFNIMToggleButton * aToggleButton) 
{
    toggleButton_ = aToggleButton;
    return NS_OK;

}

#include "windows.h"

NS_IMETHODIMP SkypeToggleChatSession::Exist(PRBool *_retval)
{
    *_retval =  PR_FALSE;
    if(mainWindow_ )
    {
        PRUint32 wnd = 0U;
        mainWindow_->GetM_hWnd( &wnd);
        if(::IsWindow( (HWND)(wnd) ) )
        {
            *_retval =  PR_TRUE;
        }
    }

    return NS_OK;
}

 
NS_IMETHODIMP SkypeToggleChatSession::AddToggleButton( )
{
    if(!mainWindow_)
    {
        return NS_ERROR_FAILURE;
    }

    if(toggleButton_)
    {
        return NS_OK;
    }

    inputWindow_ = nsnull;
    readWindow_  = nsnull;
    nsresult rv = findInputWindow( getter_AddRefs(inputWindow_)  );
             rv = findReadWindow ( getter_AddRefs(readWindow_)   );

    if(readWindow_ && inputWindow_ )
    {
        createToggleButton( getter_AddRefs( toggleButton_) );
        if(!toggleButton_)
        {
            return NS_ERROR_FAILURE;
        }
        nsCOMPtr<IFNIMToggleButtonEvnetListener> aToggleButtonEvnetListener;
        this->QueryInterface( NS_GET_IID(IFNIMToggleButtonEvnetListener), getter_AddRefs(aToggleButtonEvnetListener));
        nsCOMPtr<IFNIMWindowDestroyEvnetListener> aDestroyEvnetListener;
        this->QueryInterface( NS_GET_IID(IFNIMWindowDestroyEvnetListener), getter_AddRefs(aDestroyEvnetListener));

        if(aToggleButtonEvnetListener )
        {
            toggleButton_->AddToggleEventListener(aToggleButtonEvnetListener);
        }

        if(aDestroyEvnetListener)
        {
            toggleButton_->AddDestroyEvnetListener(aDestroyEvnetListener);
        }

         rv = create_toggleButtonLocator(getter_AddRefs( toggleButtonLocator_ ));
         if(toggleButtonLocator_ )
         {
             toggleButtonLocator_ ->Locate();
             toggleButtonLocator_->SyncPosition();
         }
        
        rv = create_fnMainWindow(getter_AddRefs(fnMainWindow_) );//prepare a hidden window at first
        if(fnMainWindow_ && aDestroyEvnetListener)
        {
            fnMainWindow_->AddDestroyEvnetListener(aDestroyEvnetListener);
        }

        rv =  create_fnMainWindowLocator(getter_AddRefs(fnMainWindowLocator_));
        if(fnMainWindowLocator_)
        {
            fnMainWindowLocator_->Locate();
            fnMainWindowLocator_->SyncPosition();
        }

        //
        bool ok = create_FNIMContactListUI();
        if(ok )
        {
        }
        rv =  create_FNIMContactListUILocator(getter_AddRefs(_FNIMContactListUILocator));
        if(_FNIMContactListUILocator)
        {
            _FNIMContactListUILocator->Locate();
            _FNIMContactListUILocator->SyncPosition();
        }




        //the following code only neede when the layout is  "bedise IM" , to cover the IM input and read window 
        // if we use the clipboard methos to synchronize the content
       // rv =  create_fnReaderWindow(  getter_AddRefs(fnReader_Window_) );
       // rv =  create_fnReaderWindowLocator( getter_AddRefs(fnReader_Window_Locator_ ) );
       //if(fnReader_Window_Locator_)
       // {
       //     fnReader_Window_Locator_->Locate();
       //     fnReader_Window_Locator_->SyncPosition();
       // }
       // rv =  create_fnInputWindow(  getter_AddRefs( fnInput_Window_)   );
       // rv =  create_fnInputWindowLocator( getter_AddRefs(fnInput_Window_Locator_ ) );;
       // if(fnMainWindowLocator_)
       // {
       //     fnInput_Window_Locator_->Locate();
       //     fnInput_Window_Locator_->SyncPosition();
       // }
    }

    return NS_OK;
}


NS_IMETHODIMP SkypeToggleChatSession::Quit( )
{

    if(listener_Cookie_  != 0) 
    {
        SkypeAPIWapper::unregister_SkypeAPI_IFNIMChat(listener_Cookie_ );
        listener_Cookie_  = 0U;
    }

    if(aNSTimer_)
    {
        aNSTimer_->Cancel();
        aNSTimer_.forget();
    } 

    if(fnMainWindow_ )
    {
        fnMainWindow_->Close();
    }
    if(toggleButton_)
    {
        toggleButton_->Close();
     }

    if(fnInput_Window_)
    {
        fnInput_Window_->Close();
    }
    if(fnReader_Window_)
    {
        fnReader_Window_->Close();
    }
 
    if(fnMainWindowLocator_)
    {
        fnMainWindowLocator_->Close();
    }
    if(chatReadWindowLocator_)
    {
        chatReadWindowLocator_->Close();
    }

    if(toggleButtonLocator_)
    {
        toggleButtonLocator_->Close();
    }

    if(application_)
    {
        application_ = nsnull;
    }
    
    return NS_ERROR_NOT_IMPLEMENTED;
}

#include "windows.h"


nsresult SkypeToggleChatSession::findInputWindow( IFNIMToggleChatInputWindow ** window )
{
    if(!chatInputWindowLocator_)
    {
        SkypeChatInputWindowLocator * pSkypeChatInputWindowLocator
                        = new SkypeChatInputWindowLocator();
        if(pSkypeChatInputWindowLocator == nsnull)
        {
            return NS_ERROR_OUT_OF_MEMORY;
        }

        pSkypeChatInputWindowLocator->setReferenceWindow(mainWindow_);
        chatInputWindowLocator_  = pSkypeChatInputWindowLocator;
    }

    if(!chatInputWindowLocator_ )
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }
    PRUint32 hWnd_chat_input = 0u;
    if( NS_OK != chatInputWindowLocator_ ->Find(&hWnd_chat_input) )
    {
        return NS_ERROR_NOT_AVAILABLE;
    }

     SkypeToggleChatInputWindow* inptwindow =  new SkypeToggleChatInputWindow();
     if(inptwindow ==  nsnull)
     {
         return NS_ERROR_OUT_OF_MEMORY;
     }
     inptwindow->SetM_hWnd( hWnd_chat_input );
     return inptwindow->QueryInterface(NS_GET_IID(IFNIMToggleChatInputWindow) , (void**) window);
      
}


nsresult SkypeToggleChatSession::findReadWindow( IFNIMToggleChatReadWindow **window  )
{
    if(!chatReadWindowLocator_)
    {
        SkypeChatReadWindowLocator * pSkypeChatReadWindowLocator
            = new SkypeChatReadWindowLocator();
        if(pSkypeChatReadWindowLocator == nsnull)
        {
            return NS_ERROR_OUT_OF_MEMORY;
        }

        pSkypeChatReadWindowLocator->setReferenceWindow(mainWindow_);
        chatReadWindowLocator_  = pSkypeChatReadWindowLocator;
    }

    if(!chatReadWindowLocator_ )
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }
    PRUint32 hWnd_chat_Read = 0u;
    if( NS_OK != chatReadWindowLocator_ ->Find(&hWnd_chat_Read) )
    {
        return NS_ERROR_NOT_AVAILABLE;
    }

     SkypeToggleChatReadWindow* readwindow =  new SkypeToggleChatReadWindow();
     if(readwindow ==  nsnull)
     {
        return NS_ERROR_OUT_OF_MEMORY;
     }
     readwindow->SetM_hWnd( PRUint32 (hWnd_chat_Read ) );
     return readwindow->QueryInterface(NS_GET_IID(IFNIMToggleChatReadWindow) , (void**) window);

}
nsresult SkypeToggleChatSession::createToggleButton( IFNIMToggleButton** toggleButton )
{
    if(!mainWindow_ || !inputWindow_)
    {
        return NS_ERROR_FAILURE;
    }
    SkypeToggleButton* toggle  = new SkypeToggleButton();
    if(toggle   == nsnull)
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }
    return toggle->QueryInterface(NS_GET_IID(IFNIMToggleButton) , (void**) toggleButton);
}



nsresult SkypeToggleChatSession::create_fnInputWindow(IFNIMToggleChatFNInputWindow ** fnInput)
{
    if(!mainWindow_  )
    {
        return NS_ERROR_FAILURE;
    }
    SkypeToggleChatFNInputWindow* aSkypeToggleChatFNInputWindow  = new SkypeToggleChatFNInputWindow();
    if(aSkypeToggleChatFNInputWindow   == nsnull)
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }
    aSkypeToggleChatFNInputWindow->SetOrigianlInputWindow(inputWindow_);
    return aSkypeToggleChatFNInputWindow->QueryInterface(NS_GET_IID(IFNIMToggleChatFNInputWindow) , (void**) fnInput);
}

nsresult SkypeToggleChatSession::create_fnReaderWindow(IFNIMToggleChatFNReadWindow ** fnRead)
{
    if(!mainWindow_  )
    {
        return NS_ERROR_FAILURE;
    }
    SkypeToggleChatFNReadWindow * aSkypeToggleChatFNReadWindow  = new SkypeToggleChatFNReadWindow ();
    if(aSkypeToggleChatFNReadWindow   == nsnull)
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }
    aSkypeToggleChatFNReadWindow->SetOrigianlReadWindow(readWindow_);
    return aSkypeToggleChatFNReadWindow->QueryInterface(NS_GET_IID(IFNIMToggleChatFNReadWindow) , (void**) fnRead);
}

nsresult SkypeToggleChatSession::create_fnReaderWindowLocator(IFNIMWindowLocator ** aLocator)
{
    if(!mainWindow_  )
    {
        return NS_ERROR_FAILURE;
    }
    SkypeFNIMToggleChatFNReadWindowLocator* aSkypeFNIMToggleChatFNReadWindowLocator  
        = new SkypeFNIMToggleChatFNReadWindowLocator(readWindow_, fnReader_Window_);
    if(aSkypeFNIMToggleChatFNReadWindowLocator   == nsnull)
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }
    return aSkypeFNIMToggleChatFNReadWindowLocator->QueryInterface(NS_GET_IID(IFNIMWindowLocator) , (void**) aLocator);    
}

nsresult SkypeToggleChatSession::create_fnInputWindowLocator(IFNIMWindowLocator** aLocator)
{
    if(!mainWindow_  )
    {
        return NS_ERROR_FAILURE;
    }
    SkypeFNIMToggleChatFNInputWindowLocator* aSkypeFNIMToggleChatFNInputWindowLocator  
        = new SkypeFNIMToggleChatFNInputWindowLocator(inputWindow_, fnInput_Window_);
    if(aSkypeFNIMToggleChatFNInputWindowLocator   == nsnull)
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }
    return aSkypeFNIMToggleChatFNInputWindowLocator->QueryInterface(NS_GET_IID(IFNIMWindowLocator) , (void**) aLocator);    
}

nsresult SkypeToggleChatSession::create_fnInput(IFNIMToggleChatFNInput ** fnInput)
{
    if(!fnMainWindow_)
        return NS_ERROR_UNEXPECTED;
    if(fnInput_)
    {
        return fnInput_->QueryInterface( NS_GET_IID(IFNIMToggleChatFNInput), (void**) fnInput );
    }
    nsCOMPtr<nsISupports> input_ele;
    fnMainWindow_->GetFnInput( getter_AddRefs(input_ele));
    //if(input_ele)
    {
        SkypeToggleChatFNInput *pSkypeToggleChatFNInput =  new SkypeToggleChatFNInput(input_ele) ;
        return pSkypeToggleChatFNInput->QueryInterface( NS_GET_IID(IFNIMToggleChatFNInput), (void**) fnInput );
    }

    return NS_ERROR_FAILURE;
}

nsresult SkypeToggleChatSession::create_fnReader(IFNIMToggleChatFNReader ** fnRead)
{
    if(!fnMainWindow_)
        return NS_ERROR_UNEXPECTED;
    if(fnReader_)
    {
        return fnReader_->QueryInterface( NS_GET_IID(IFNIMToggleChatFNInput), (void**) fnRead );
    }

    nsCOMPtr<nsISupports> reader_ele;
    fnMainWindow_->GetFnReader( getter_AddRefs(reader_ele));
    //if(reader_ele) // so far the reader can be a just option
    {
        SkypeToggleChatFNReader *pSkypeToggleChatFNReader = new SkypeToggleChatFNReader(reader_ele);
        if(pSkypeToggleChatFNReader )
        {
            return pSkypeToggleChatFNReader ->QueryInterface( NS_GET_IID(IFNIMToggleChatFNReader), (void**) fnRead  );
        }
    }

    return NS_ERROR_FAILURE;
}

nsresult SkypeToggleChatSession::ShowFNWidnows( PRBool bshow )
{
    nsresult rv = NS_OK;
    if(!readWindow_  || !inputWindow_)
    {
        return rv;
    }

    toggleButton_->SetState( bshow );//

    if(bshow)
    {
        if(!fnMainWindow_)
        {
            create_fnMainWindow(getter_AddRefs(fnMainWindow_));
        }

        if(!fnInput_)
        {
            create_fnInput(getter_AddRefs(fnInput_) );
        }

        if(!fnReader_)
        {
            create_fnReader( getter_AddRefs(fnReader_));
        }

        if(!aNSTimer_)
        {
            //aNSTimer_ =  do_CreateInstance("@mozilla.org/timer;1");
            //if(!aNSTimer_) 
            //{
            //    return NS_ERROR_FAILURE;
            //}

            //nsCOMPtr<nsIObserver> abserver;
            //this->QueryInterface(NS_GET_IID(nsIObserver), (void**)getter_AddRefs(abserver) );
            //if(abserver)
            //{
            //    aNSTimer_->Init(abserver, 3000U, nsITimer::TYPE_REPEATING_SLACK);
            //}
        }
    }
    else//hide 
    {
        //when hide , stop sync timer
        if(aNSTimer_   )
        {
            aNSTimer_ ->Cancel();
            aNSTimer_  = nsnull;
        }

    }

    if(fnMainWindow_)
    {
        fnMainWindow_->Show( bshow ) ;

        if(fnInput_Window_) // fn cover window show/hide 
            fnInput_Window_->Show(bshow) ;

        if(fnReader_Window_)// fn cover window show/hide
            fnReader_Window_->Show(bshow);
    }
    if(bshow )
    {//sync input --. fninput and reader
       // syncInputContent();
       // syncReaderContent();
    }

    return NS_OK;
}

nsresult SkypeToggleChatSession::onSubmit(nsIDOMElement * e)
{
    if(e)
    {
        nsString data;
        nsresult rv = e->GetAttribute(nsString(L"dataToIm"), data);
        if(data.Length() > 0)
        {
            if(aIChat_)
            {
                send_Message(data.get() );
            }
        }
    }
    return NS_OK;
}
nsresult SkypeToggleChatSession::Submit()
{
    if(!fnInput_  || !inputWindow_)
    {
        return NS_OK;
    }

    //get content for submitting
    //nsString fninput_Content;
    //fnInput_->GetContent( fninput_Content ) ;

    //if(fninput_Content.Length() == 0)
    //{
    //    return NS_OK; // not submit empty content
    //}


    //if(aIChat_)
    //{
    //    send_Message(fninput_Content.get() );
    //}

    //else
    //{
    //    inputWindow_->SetContent( fninput_Content );
    //    inputWindow_->Submit();


    //    fnInput_->SetContent(nsString(L"") ); //empty
    //    fnInput_->SetFocus();
    //}
    //syncReaderContent();

    return NS_OK;
}




nsresult SkypeToggleChatSession::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{ 

    if(0 == CaseInsensitiveCompare(aTopic, "timer-callback", 14U) )
    {
       // syncReaderContentOnIdel();
        //syncReaderContent();
        
    }
    else if(0 == CaseInsensitiveCompare(aTopic, "FNIMWebBrowserChrome_Ready", 26U) )
    {
        onFNIMWebBrowserChrome_Ready(); 
    }
    return NS_OK;
}

nsresult SkypeToggleChatSession::onFNIMWebBrowserChrome_Ready()
{

    if(!fnMainWindow_)
        return NS_ERROR_FAILURE;
    if(!fnInput_)
    {
        create_fnInput(getter_AddRefs(fnInput_) );
    }

    if(!fnReader_)
    {
        create_fnReader( getter_AddRefs(fnReader_));
    }


    return NS_OK;
}

nsresult SkypeToggleChatSession::syncInputContent()
{ 
    return NS_ERROR_FAILURE;
  if( !inputWindow_ || !fnInput_)
        return NS_ERROR_FAILURE;


    nsString inputContent;
    nsresult  rv = inputWindow_->GetContent(inputContent);
    if(rv == NS_OK  )
    {
        if(inputContent .Length() > 0 )
        {
            fnInput_->SetContent( inputContent);
            fnInput_->SetFocus();
        }
    }
    return NS_OK;
}

nsresult SkypeToggleChatSession::syncReaderContent()
{ 
    return NS_ERROR_FAILURE;
    if( !readWindow_ || !fnReader_ )
        return NS_ERROR_FAILURE;
    nsString readerContent;
    nsresult  rv = readWindow_->GetContent(readerContent);
    if(rv == NS_OK  )
    {
        if(readerContent .Length() > readerContent_cache_.Length() )
        {
            nsString readerContent_dup = readerContent;
            if(readerContent_dup .Length() > readerContent_cache_.Length() )
            {
                readerContent_dup.Cut(0, readerContent_cache_.Length() );
                readerContent_cache_ = readerContent;

                fnReader_->AppendContent1(readerContent_dup);
            }
        }
        else if(readerContent .Length() == readerContent_cache_.Length() )
        {
            if( readerContent.Equals(readerContent_cache_) != 0)
            {
                readerContent_cache_ = readerContent;
                fnReader_->SetContent1(readerContent);
            }
        }
        else //user clear the chat content
        {//rest the content
            readerContent_cache_ = readerContent;
            fnReader_->SetContent1( readerContent );
        }
        return NS_OK;
    }
    return NS_ERROR_FAILURE;
}
nsresult SkypeToggleChatSession::syncReaderContentOnIdel()
{
    return NS_ERROR_FAILURE;
    if( !readWindow_ || !fnReader_ || !fnInput_)
        return NS_ERROR_FAILURE;

    PRBool visible = PR_FALSE;
    fnMainWindow_->WindowVisible( &visible );
    if(PR_FALSE == visible)
    {
        return NS_ERROR_FAILURE;
    }

    LASTINPUTINFO lii ={0};
    lii.cbSize =  sizeof(LASTINPUTINFO);
    BOOL get = GetLastInputInfo(          &lii );
    if(get )
    {
        if( (GetTickCount()  - lii.dwTime ) < 2000 )
            return NS_ERROR_FAILURE;
    }


    PRBool fnInputIsFocus = PR_FALSE;
    HWND focusWnd_pre = ::GetFocus();
    fnInput_->IsFocused(&fnInputIsFocus );


    syncReaderContent();//

    HWND focusWnd_now = ::GetFocus();
    if(focusWnd_pre  != focusWnd_now)
    {
        if( fnInputIsFocus  == PR_TRUE)
        {
            fnInput_->SetFocus();
        }
        else
        {
            SetFocus(focusWnd_now);
        }
    }
    return NS_OK;
}

NS_IMETHODIMP SkypeToggleChatSession::OnToggle(PRBool state, PRBool *stop )
{
    if(!handshaked_)
    {
        shakehand();
    }
    if(stop )* stop  = PR_TRUE;
    ShowFNWidnows( state  );
    return NS_OK;
}
NS_IMETHODIMP SkypeToggleChatSession::OnDestroy(nsISupports *obj)
{
    Quit( );
    return NS_OK;
}

nsresult SkypeToggleChatSession::create_fnMainWindow(IFNIMToggleChatFNMainWindow ** aFNMainWindow)
{
    if(!mainWindow_ || !readWindow_ || !inputWindow_ || aFNMainWindow == nsnull)
    {
        //lost of refrence window , return ;
        return NS_ERROR_FAILURE;
    }

    if( fnMainWindow_ )
    {
        fnMainWindow_ = nsnull;// release it if it is existed;
    }

    FNIMToggleChatSessionFNMainWindowUI  *aFNIMToggleChatSessionFNMainWindow =  new FNIMToggleChatSessionFNMainWindowUI();
    //IMChatSessionFNMainWindow_DOMWindow  *aFNIMToggleChatSessionFNMainWindow =  new IMChatSessionFNMainWindow_DOMWindow();
    if(!aFNIMToggleChatSessionFNMainWindow )
    {
        return NS_ERROR_OUT_OF_MEMORY;
    }

    nsresult rv = aFNIMToggleChatSessionFNMainWindow ->QueryInterface(NS_GET_IID(IFNIMToggleChatFNMainWindow), (void**)aFNMainWindow);
    if( rv != NS_OK)
        return rv;

    nsCOMPtr<nsIDOMEventListener> aListener_Close ;
    rv = this->QueryInterface(NS_GET_IID(nsIDOMEventListener), getter_AddRefs(aListener_Close )); 
    if( rv != NS_OK)
        return rv;

    nsCOMPtr<nsIDOMEventListener> aListener_Submit ;
    rv = this->QueryInterface(NS_GET_IID(nsIDOMEventListener), getter_AddRefs(aListener_Submit));


    nsCOMPtr<nsIDOMEventListener> aListener_Invitation ;
    rv = this->QueryInterface(NS_GET_IID(nsIDOMEventListener), getter_AddRefs(aListener_Invitation));


    if(aListener_Close)
    {
        aFNIMToggleChatSessionFNMainWindow->AddUIListener_Close(aListener_Close);
    }

    if(aListener_Submit)
    {
        aFNIMToggleChatSessionFNMainWindow->AddUIListener_Submit(aListener_Submit);
    }
    
    return rv;
}


NS_IMETHODIMP SkypeToggleChatSession::HandleEvent(nsIDOMEvent *event) 
{
    if(event == nsnull )
        return NS_ERROR_FAILURE;
    nsCOMPtr<nsIDOMEventTarget>eventTarget;
    event->GetTarget(getter_AddRefs(eventTarget));
    if(!eventTarget )
        return NS_ERROR_FAILURE;

    nsCOMPtr<nsIDOMElement > ele = do_QueryInterface(eventTarget);
    if(!ele)
        return NS_ERROR_FAILURE;

    nsString eID;
    ele->GetAttribute(NS_LITERAL_STRING("id"), eID);
    if(eID == NS_LITERAL_STRING("FNIMSendButton")     )
    {
        onSubmit(ele);
    }
    else if(eID == NS_LITERAL_STRING("FNInviteButton")     )
    {
        SendInvitation();
    }
    else if(eID == NS_LITERAL_STRING("closebutton")   )
    {
        ShowFNWidnows(PR_FALSE);
    }

    return NS_OK;
}



#include "FNIMToggleMainWindowLocator_Slideout.h"
#include "FNIMToggleMainWindowLocator_BesideIMRight.h"

nsresult SkypeToggleChatSession::create_fnMainWindowLocator(IFNIMWindowLocator ** aLocator)
{
    if(!fnMainWindowLocator_)
    {
//if using Slideout then FNIMToggleMainWindowLocator_Slideout
        //FNIMToggleMainWindowLocator_Slideout* pFNIMToggleChatFNMainWindowLocator
        //     = new FNIMToggleMainWindowLocator_Slideout( fnMainWindow_,mainWindow_,inputWindow_,readWindow_);        
//if using BesideIMRight then using FNIMToggleMainWindowLocator_BesideIMRight
        //FNIMToggleMainWindowLocator_BesideIMRight* pFNIMToggleChatFNMainWindowLocator
        //     = new FNIMToggleMainWindowLocator_BesideIMRight( fnMainWindow_,mainWindow_,inputWindow_,readWindow_);        
//if using cover the IM input and read , then ussing FNIMToggleMainWindowLocator_CoverIM        
        //FNIMToggleMainWindowLocator_CoverIM* pFNIMToggleChatFNMainWindowLocator
        //    = new FNIMToggleMainWindowLocator_CoverIM( fnMainWindow_,mainWindow_,inputWindow_,readWindow_);        

        FNIMToggleChatFNMainWindowLocator* pFNIMToggleChatFNMainWindowLocator
            = new FNIMToggleChatFNMainWindowLocator( fnMainWindow_,mainWindow_,inputWindow_,readWindow_);        


        if(pFNIMToggleChatFNMainWindowLocator == nsnull)
        {
            return NS_ERROR_OUT_OF_MEMORY;
        }
        pFNIMToggleChatFNMainWindowLocator->QueryInterface(NS_GET_IID(IFNIMWindowLocator), (void**)aLocator);
    }
    return NS_OK;
}

nsresult SkypeToggleChatSession::create_toggleButtonLocator(IFNIMWindowLocator ** aLocator)
{
    if(!fnMainWindowLocator_)
    {
        FNIMToggleButtonLocator* pFNIMToggleButtonLocator
             = new FNIMToggleButtonLocator( toggleButton_, readWindow_ );
        if(pFNIMToggleButtonLocator == nsnull)
        {
            return NS_ERROR_OUT_OF_MEMORY;
        }
        pFNIMToggleButtonLocator->QueryInterface( NS_GET_IID(IFNIMWindowLocator), (void**)aLocator );
    }
    return NS_OK;
}



static BOOL  GetWindowTextW_my(HWND m_hWnd, nsAString  &txt) throw()
{
    int nLen = ::SendMessage(m_hWnd , WM_GETTEXTLENGTH, (WPARAM)0,(LPARAM)0 );
    if(nLen >0)
    {
        TCHAR *lpszText = new TCHAR[nLen + 1];
        if (lpszText == NULL)
        {
            return FALSE;
        }

        int nLen_Copied = ::SendMessage(m_hWnd , WM_GETTEXT, (WPARAM)(nLen+1),(LPARAM)(TCHAR*)lpszText );

        if(nLen_Copied > 0)
        {
            txt.Assign( lpszText );
        }
        delete[] lpszText; 
    }
    return TRUE;
}

nsresult SkypeToggleChatSession::retrieveAccountInfo()
{
    // for account_nickname_ --
    if(mainWindow_)
    {
        nsString windowClassname;
        mainWindow_->GetClassname(windowClassname);
        if(windowClassname.IsEmpty() )
            return NS_OK;
        HWND awindow_main = ::FindWindowEx(0, 0, windowClassname.get(), nsnull);
        if(! ::IsWindow(awindow_main) )
        {
            return NS_OK;
        }

        PRUint32 wnd_handle = 0U;
        mainWindow_->GetM_hWnd(&wnd_handle); 
        HWND hwnd = (HWND ) wnd_handle;

        DWORD aProcessId1 = 0;
        DWORD aProcessId2 = 0;
        ::GetWindowThreadProcessId( awindow_main, &aProcessId1 );
        ::GetWindowThreadProcessId( hwnd,         &aProcessId2 );
        if( aProcessId1  == aProcessId2 )
        {
            GetWindowTextW_my(awindow_main, account_nickname_);
        }
        
    }
    return NS_OK;
    
    
}
nsresult SkypeToggleChatSession::retrieveChatContactorInfo()
{
#ifdef USING_SKYPE4COM
    return 0;
#else
    if(mainWindow_)
    {
        PRUint32 wnd_handle = 0U;
        mainWindow_->GetM_hWnd(&wnd_handle); 
        HWND hwnd = (HWND ) wnd_handle;
        if(::IsWindow(hwnd))
        {
            GetWindowTextW_my(hwnd , chatContactor_nickname_ );
            retrieveAccountInfo();
            nsString  aInvitationContent;
            GetInvitationContent(aInvitationContent);
        }
    }
#endif
    return 0;
}

/* attribute AString nickname; */
nsresult SkypeToggleChatSession::GetNickname(nsAString & aNickname)
{
     chatContactor_nickname_ = aNickname;

     return NS_OK;
}
nsresult SkypeToggleChatSession::SetNickname(const nsAString & aNickname)
{
    chatContactor_nickname_ = aNickname;
    return NS_OK;
}



/* attribute AString invitationContent; */
nsresult SkypeToggleChatSession::GetInvitationContent(nsAString & aInvitationContent)
{
    if(invitation_content_.IsEmpty() )
    {
        invitation_content_.AppendLiteral("Please download FNClient from http://www.federatednetworks.com to join in FN Networks");//for demo only 
    }
    aInvitationContent = invitation_content_;
    return NS_OK;
}
nsresult SkypeToggleChatSession::SetInvitationContent(const nsAString & aInvitationContent)
{
    invitation_content_ = aInvitationContent;
    return NS_OK;
}

/* void sendInvitation (); */
nsresult SkypeToggleChatSession::SendInvitation()
{
    if(!fnInput_  || !inputWindow_)
    {
        return NS_OK;
    }

    inputWindow_->SetContent( invitation_content_ );
    inputWindow_->Submit();

    fnInput_->SetFocus();

    syncReaderContent();
    return NS_OK;
}


//SkypeAPI_IFNIMChat

//
void SkypeToggleChatSession::get_Chat_Members(/*out*/ vector<wstring>&)
{
}
//
void SkypeToggleChatSession::set_Chat_Members(/*in*/ vector<wstring>&) 
{
}
//
const wstring SkypeToggleChatSession::get_Chat_OwnerMe() 
{
    wstring s;
        return s ;
}
//
void SkypeToggleChatSession::set_Chat_OwnerMe(LPCTSTR chat_owner) 
{

}
//
void SkypeToggleChatSession::on_Message_received( const wstring & sender, const wstring & msg, vector<wstring>& chat_Members)
{
}


 void SkypeToggleChatSession::retriveHandeShakeInvitation(LPCTSTR sender , LPCTSTR msg , LPCTSTR timeInDouble)
 {

     if(sender == nsnull && msg == nsnull)
         return ;
     std::wstring msg_ns(msg);
     if(msg_ns.empty() )
         return;

    PRInt32 pos = msg_ns.find(HANDSHAKE_SULOTION  );
    PRInt32 pos_username_begin = -1; 
    PRInt32 pos_username_end= -1; 
    if(pos == 0)
    {
        PRInt32 token_pos1 = msg_ns.find(L"#" );
        PRInt32 token_pos2 = msg_ns.find(L"#" , token_pos1+1 );
        if(token_pos2 > token_pos1)
        {
            std::wstring username = msg_ns.substr(token_pos1+1 , token_pos2-token_pos1-1);
            std::wstring skypehandle =sender;// msg_ns.substr(token_pos2+1);
            if(!username.empty() )
            {
                tryAddSkypeContactor( username.c_str(), skypehandle.c_str());
            }
        }
    }
 
 }
void SkypeToggleChatSession::on_chat_message_received(LPCTSTR sender , LPCTSTR msg , LPCTSTR timeInDouble) 
{
    if(!msg)
        return;

    retriveHandeShakeInvitation(  sender ,   msg ,   timeInDouble);

   //we do not want to show "our shake hand int FNRTE"
    LPCTSTR  substr  =  wcsstr(msg, (LPCTSTR)HANDSHAKE_SULOTION);
    if(substr != NULL && substr == msg)
    {//this is handshake message 
        return ;
    }
   //HANDSHAKE_SULOTION

    //Json string should be 
    //{sender:"aSender",receiver:"areceiver",massage:"this is a msg!",datatime:"1999/01/01" }

    nsString json_str;
    json_str.Append(L"{\"sender\":\"");
    json_str.Append(sender);
    json_str.Append(L"\",");

    //receiver[
    json_str.Append(L"\"receiver\":[");

    IUserCollectionPtr aIUserCollectionPtr = aIChat_->GetMembers();
    if(aIUserCollectionPtr)
    {
        nsString receiver_data;
        //std::vector<wstring> chat_members;
        long count  = aIUserCollectionPtr->GetCount();
        for (long i = 1L ; i<= count ; i++)
        {
            IUserPtr aIUserPtr = aIUserCollectionPtr->GetItem(i);
            if(aIUserPtr)
            {
                _bstr_t sender_bstr(sender);
                _bstr_t a_member_bstr = aIUserPtr->GetHandle();
                if(sender_bstr ==  a_member_bstr)
                {
                    continue; // exclude sender
                }
                nsString amember(a_member_bstr.GetBSTR());
                if(sender)
                if(receiver_data.Length() > 0 )
                {
                    receiver_data.Append(L",");
                }
                receiver_data.Append(L"{\"imHandle\":\"");
                receiver_data.Append(amember);
                receiver_data.Append(L"\",\"imName\":\"skype\"}");
                //chat_members.push_back(amember);
            }
        }
        json_str.Append(receiver_data);
    }
    json_str.Append(L"],");



    //isHandShake
    json_str.Append(L"\"isHandShake\":");
    json_str.Append(L"false"); //leave it empty now
    json_str.Append(L",");
    //]

    json_str.Append(L"\"message\":\"");
    json_str.Append(msg); //leave it empty now
    json_str.Append(L"\",");

    json_str.Append(L"\"datetime\":");
    json_str.Append(timeInDouble); //leave it empty now

    //end }
    json_str.Append(L"}");

    FNIMToggleChatSessionFNMainWindowUI * pFNIMToggleChatSessionFNMainWindowUI  = dynamic_cast<FNIMToggleChatSessionFNMainWindowUI*>(fnMainWindow_.get());
    if(pFNIMToggleChatSessionFNMainWindowUI)
    {
        pFNIMToggleChatSessionFNMainWindowUI->on_chat_message_received(json_str);
    }

}
void SkypeToggleChatSession::send_Message( LPCTSTR msg) 
{
    if(msg && aIChat_)
    {
        _bstr_t msg_bstr(msg);
        aIChat_->SendMessageW(msg_bstr);
    }
}

#include "clientservice/localAgreementRequest.h"
#include "clientservice/ReqAccount.h"
#include "clientservice/ReqCryptoService.h"
#include "clientservice/ReqCryptoService.h"
#include "../../../client/fnfirefoxhelper/IFNFireFoxHelper.h"

void tryAddSkypeContactor(LPCTSTR fnusename, LPCTSTR skypehandler)
{
    if(fnusename == nsnull || nsnull  == skypehandler)
    {
        return ;
    }

    nsCOMPtr<IFNWebSvrJSHelper> aFNWebSvrJSHelper =  do_GetService("@FNTechnologies.com/Mozilla/FNWebSvrJSHelper;1");
    if(aFNWebSvrJSHelper )
    {
        aFNWebSvrJSHelper->SendSkypeInvitation(fnusename,   skypehandler);
        
    }
}

fnstring getFNCLientOwnerUserName()
{
//there will be a bug if the fn login user is changed,
//but it calling FN_CLIENT_SERVICE::invoke_account_get_user_name everytime , it is waste of time
//maybe some day there is a notification of uer logged out
	static fnstring g_ownderUserName;
	if(g_ownderUserName.empty())
	{
		FN_CLIENT_SERVICE::invoke_account_get_user_name(g_ownderUserName);
	}

	return g_ownderUserName;

}



void SkypeToggleChatSession::shakehand()  
{//register first 
    SkypeAPIWapper::dll_connect();
    if(inputWindow_ && listener_Cookie_ == 0 && !handshaked_)
    {
        //register skype_listener


        nsString shakehandMsg(HANDSHAKE_SULOTION);
        fnstring fnusename = getFNCLientOwnerUserName();
        if( !fnusename.empty() )
        {
            shakehandMsg.Append( fnusename.c_str());
        }
        shakehandMsg.Append(L"#");
        shakehandMsg.AppendInt((int)this);

        listener_Cookie_ =  SkypeAPIWapper::register_SkypeAPI_IFNIMChat(this, shakehandMsg.get() );

        //submit from window 
        inputWindow_->SetContent(shakehandMsg);
        inputWindow_->Submit();
    }

}

void SkypeToggleChatSession::FirstTimeDumpMessages()
{
    if(aIChat_)
    {
        IChatMessageCollectionPtr aIChatMessageCollectionPtr = aIChat_->Messages;
        if(aIChatMessageCollectionPtr )
        {
            long count  = aIChatMessageCollectionPtr->Count;
            for(long i = 1L; i<= count; i++)
            {
               IChatMessagePtr aIChatMessagePtr  = aIChatMessageCollectionPtr->GetItem(i);

               if(aIChatMessagePtr)
               {
                   _bstr_t megBody = aIChatMessagePtr->Body;

                   _bstr_t from  =aIChatMessagePtr->FromHandle;
                   
                   DATE aDATE = 0.;
                   aIChatMessagePtr->get_Timestamp(&aDATE);

                   nsString timeStr;
                   doubleTime2UniversalTimeString(aDATE, timeStr);
                   Sleep(100);
                   on_chat_message_received(from.GetBSTR(), megBody.GetBSTR(), timeStr.get() );
               }
            }
        }
    }

}
void SkypeToggleChatSession::set_handshaked2( LPCTSTR sender, bool shaked)
{
    handshaked_ = shaked;

    //{sender:"Raymond",receiver:[{"imHandle":1001, "imName":"skype"},{"imHandle":1002, "imName":"skype"},], isHandShake: true, message:"this is a test 2ecd465d-b266-4308-a7bc-b403270b87a2 what are you doing?", datetime:new Date().valueOf()

    if(aIChat_ && handshaked_)
    {
        nsString json_str;
        json_str.Append(L"{\"sender\":\""); //leave it empty now as this is handshake
        json_str.Append(sender);
        json_str.Append(L"\",");

        //receiver[
        json_str.Append(L"\"receiver\":[");

        IUserCollectionPtr aIUserCollectionPtr = aIChat_->GetMembers();
        if(aIUserCollectionPtr)
        {
            nsString receiver_data;
            //std::vector<wstring> chat_members;
            long count  = aIUserCollectionPtr->GetCount();
            for (long i = 1L ; i<= count ; i++)
            {
                IUserPtr aIUserPtr = aIUserCollectionPtr->GetItem(i);
                if(aIUserPtr)
                {
                    nsString amember(aIUserPtr->GetHandle().GetBSTR());
                    if(receiver_data.Length() > 0 )
                    {
                        receiver_data.Append(L",");
                    }
                    receiver_data.Append(L"{\"imHandle\":\"");
                    receiver_data.Append(amember);
                    receiver_data.Append(L"\",\"imName\":\"skype\"}");
                    //chat_members.push_back(amember);
                }
            }
            json_str.Append(receiver_data);
        }
        json_str.Append(L"],");

        //]

        //isHandShake
        json_str.Append(L"\"isHandShake\":");
        json_str.Append(L"true"); //leave it empty now
        json_str.Append(L",");
        //]

        //message
        json_str.Append(L"\"message\":\""); //isHandShake = true , dose not care about the message
        json_str.Append(L"\",");

        //datetime
        json_str.Append(L"\"datetime\":");
        json_str.Append(L"0"); //leave it empty now isHandShake = true , dose not care about it

        //end }
        json_str.Append(L"}");

        FNIMToggleChatSessionFNMainWindowUI * pFNIMToggleChatSessionFNMainWindowUI  = dynamic_cast<FNIMToggleChatSessionFNMainWindowUI*>(fnMainWindow_.get());
        if(pFNIMToggleChatSessionFNMainWindowUI)
        {
            pFNIMToggleChatSessionFNMainWindowUI->on_chat_message_received(json_str);
        }
    }



    FirstTimeDumpMessages();
}


void SkypeToggleChatSession::set_handshaked( bool shaked)
{
    handshaked_ = shaked;

    //{sender:"Raymond",receiver:[{"imHandle":1001, "imName":"skype"},{"imHandle":1002, "imName":"skype"},], isHandShake: true, message:"this is a test 2ecd465d-b266-4308-a7bc-b403270b87a2 what are you doing?", datetime:new Date().valueOf()

    if(aIChat_ && handshaked_)
    {
        nsString json_str;
        json_str.Append(L"{\"sender\":\""); //leave it empty now as this is handshake
        json_str.Append(L"\",");

        //receiver[
        json_str.Append(L"\"receiver\":[");

        IUserCollectionPtr aIUserCollectionPtr = aIChat_->GetMembers();
        if(aIUserCollectionPtr)
        {
            nsString receiver_data;
            //std::vector<wstring> chat_members;
            long count  = aIUserCollectionPtr->GetCount();
            for (long i = 1L ; i<= count ; i++)
            {
                IUserPtr aIUserPtr = aIUserCollectionPtr->GetItem(i);
                if(aIUserPtr)
                {
                    nsString amember(aIUserPtr->GetHandle().GetBSTR());
                    if(receiver_data.Length() > 0 )
                    {
                        receiver_data.Append(L",");
                    }
                    receiver_data.Append(L"{\"imHandle\":\"");
                    receiver_data.Append(amember);
                    receiver_data.Append(L"\",\"imName\":\"skype\"}");
                    //chat_members.push_back(amember);
                }
            }
            json_str.Append(receiver_data);
        }
        json_str.Append(L"],");

        //]

        //isHandShake
        json_str.Append(L"\"isHandShake\":");
        json_str.Append(L"true"); //leave it empty now
        json_str.Append(L",");
        //]

        //message
        json_str.Append(L"\"message\":\""); //isHandShake = true , dose not care about the message
        json_str.Append(L"\",");

        //datetime
        json_str.Append(L"\"datetime\":");
        json_str.Append(L"0"); //leave it empty now isHandShake = true , dose not care about it

        //end }
        json_str.Append(L"}");

        FNIMToggleChatSessionFNMainWindowUI * pFNIMToggleChatSessionFNMainWindowUI  = dynamic_cast<FNIMToggleChatSessionFNMainWindowUI*>(fnMainWindow_.get());
        if(pFNIMToggleChatSessionFNMainWindowUI)
        {
            pFNIMToggleChatSessionFNMainWindowUI->on_chat_message_received(json_str);
        }
    }



    FirstTimeDumpMessages();

}
DWORD SkypeToggleChatSession::get_cookie() 
{
    return listener_Cookie_;
}
void  SkypeToggleChatSession::set_Skype_chat_obj(IChat * pIChat) 
{
    aIChat_ = pIChat;
    //invoke
}
IChat* SkypeToggleChatSession::get_Skype_chat_obj( )  
{
    return (IChat*)aIChat_;
}

void SkypeToggleChatSession::notify_chatMember_changed()
{
    //TODO
}
void SkypeToggleChatSession::stop()
{
}

bool SkypeToggleChatSession::create_FNIMContactListUI()
{
    _FNIMContactListUIPtr.reset(new FNIMContactListUI());
    if(_FNIMContactListUIPtr)
    {
        return true;
    }

    return false;
}

bool SkypeToggleChatSession::create_FNIMContactListUILocator(IFNIMWindowLocator ** aLocator)
{


     if(!_FNIMContactListUILocator)
    {
        FNIMContactListUI_Locator* pFNIMContactListUI_Locator
            = new FNIMContactListUI_Locator( _FNIMContactListUIPtr, mainWindow_.get() );
        if(pFNIMContactListUI_Locator == nsnull)
        {
            return false;
        }
        pFNIMContactListUI_Locator->QueryInterface( NS_GET_IID(IFNIMWindowLocator), (void**)aLocator );

        return true;
    }

    return false;
}