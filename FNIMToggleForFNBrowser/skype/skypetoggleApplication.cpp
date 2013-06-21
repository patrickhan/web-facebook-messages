#include "SkypeToggleApplication.h"
#include "SkypeToggleChatSession.h"
#include "nsIArray.h"
#include "nsIMutableArray.h"
#include "nsIVariant.h"


#include <algorithm>

#include "FNIMToggleApplication_common.h"

#include "SkypeToggleChatSessionMainWindow.h"

#include "SkypeAPIWapper.h"
//////////////class SkypeApplicationTrait ///////////////////
class SkypeApplicationTrait : public IFNIMToggleApplicationTrait
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEAPPLICATIONTRAIT

  SkypeApplicationTrait()
  {
      applicationName_.AppendLiteral( "Skype.exe");
  }

private:
  ~SkypeApplicationTrait()
  {
  }

  nsEmbedString applicationName_;

};
NS_IMPL_ISUPPORTS1(SkypeApplicationTrait, IFNIMToggleApplicationTrait)

/* readonly attribute AString applicationName; */
NS_IMETHODIMP SkypeApplicationTrait::GetApplicationName(nsAString & aApplicationName)
{
    aApplicationName = applicationName_;
    return NS_OK;
}
nsresult SkypeApplicationTrait::IsMyApp(const nsAString & appToken, PRBool *_retval)
{
    if(_retval)
    {
        *_retval = applicationName_.Equals( appToken );
    }
    return NS_OK;
}
//////////////////////calss IFNIMToggleChatSessionCreator///////////////////////////

class SkypeSessionCreator : public IFNIMToggleChatSessionCreator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONCREATOR

  SkypeSessionCreator()
  {
  }

private:
  ~SkypeSessionCreator()
  {
  }

};
NS_IMPL_ISUPPORTS1(SkypeSessionCreator, IFNIMToggleChatSessionCreator)

/************************************
* @brief revert a list
*
*
*
*
*
*
*
*
*
*
*
*
*
*
************************************/

#include <list>
using namespace std;
void revert() throw()
{
    list<int> mList;
    mList.push_back(0);
    mList.push_back(1);
    mList.push_back(2);
    mList.push_back(3);

    mList.front();
}

/* readonly attribute AString applicationName; */
NS_IMETHODIMP SkypeSessionCreator::CreateSession(IFNIMToggleChatSession **_retval) 
{

    //revert();
    bool ok = SkypeAPIWapper::dll_connect();
    if(!ok)
        return NS_ERROR_FAILURE;

    SkypeToggleChatSession *psession = new SkypeToggleChatSession();
    if(psession != nsnull && _retval != nsnull)
    {
        psession->AddRef(); 
        *_retval = static_cast<IFNIMToggleChatSession*>(psession);
        return NS_OK;
    }
    return NS_ERROR_FAILURE;
}

#include "skypeAPIWapper.h"
class FNIMToggleApplication_skype : public FNIMToggleApplication_common
{
public :
    FNIMToggleApplication_skype()
    {
        //SkypeAPIWapper::dll_connect();
    }
    ~FNIMToggleApplication_skype()
    {
        SkypeAPIWapper::dll_disconnect();
    }
};

nsresult Create_SkypeToggleApplication( IFNIMToggleApplication** app)
{
    FNIMToggleApplication_skype  *aApplication = new FNIMToggleApplication_skype (); 
    if(aApplication)
    {
        aApplication->QueryInterface(NS_GET_IID(IFNIMToggleApplication), (void**)app);


        SkypeApplicationTrait * applicationTrait = new SkypeApplicationTrait();
        if(applicationTrait  )
        {
            aApplication->SetApplicationTrait(applicationTrait );
        }

        SkypeSessionCreator *aSessionCreator = new SkypeSessionCreator();
        if(aSessionCreator)
        {
            aApplication->SetSessionCreator(aSessionCreator);
        }

        SkypeChatSessionMainWindowLocator*aMainWindowLocator = new SkypeChatSessionMainWindowLocator;//tem ...
        if(aMainWindowLocator )
        {
            aApplication->SetSessionMainWindowLocator( aMainWindowLocator );
        }
        return NS_OK;
    }
    return NS_ERROR_FAILURE;
}

