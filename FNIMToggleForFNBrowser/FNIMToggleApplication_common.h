#ifndef FNIMToggleApplication__HEADER__
#define FNIMToggleApplication__HEADER__

#include "IFNIMToggle.h"
#include "nsEmbedString.h"
#include "nsCOMArray.h"
#include <list>
#include "nsCOMPtr.h"
 
class FNIMToggleApplication_common : public IFNIMToggleApplication, public IFNIMToggleApplication2
{

public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEAPPLICATION
  NS_DECL_IFNIMTOGGLEAPPLICATION2

  FNIMToggleApplication_common();

//private:
protected:
  virtual ~FNIMToggleApplication_common();

protected:
    nsresult checkChatSession( );

    nsresult  createNewSession( PRUint32 sessionMainWindow);
    nsresult  ReleaseChatSession( PRUint32 sessionMainWindow);
    
  /* additional members */
    //nsEmbedString applicationName_;
    PRUint32 processID_;
    nsCOMArray< IFNIMToggleChatSession > sessions_;

    std::list<PRUint32 > handled_window_cache;;

    nsCOMPtr<IFNIMToggleChatSessionMainWindowLocator> chatSessionMainWindowLocator_;
    nsCOMPtr<IFNIMToggleApplicationTrait> applicationTrait_;
    nsCOMPtr<IFNIMToggleChatSessionCreator> sessionCreator_;
};

#endif //FNIMToggleApplication__HEADER__
