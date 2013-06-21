#ifndef SkypeToggleChatFNReadWindow__HEADER__
#define SkypeToggleChatFNReadWindow__HEADER__

#include "IFNIMToggle.h"
#include "nsCOMPtr.h"
#include"nsEmbedString.h" 
#include "nsIObserver.h"
#include "nsWeakReference.h"
//WTL
//
//#define WINVER		0x0500
//#define _WIN32_WINNT	0x0501
//#define _WIN32_IE	0x0501
//#define _RICHEDIT_VER	0x0200
#include <atlbase.h>
#include <atlapp.h>
#include "atlctrls.h"
#include <atlwin.h>



//#include "IFNRichTextEditor_Service.h"

/* Header file */
//SkypeToggleChatFNReadWindow is obsolete
class SkypeToggleChatFNReadWindow : public IFNIMToggleChatFNReadWindow,public IFNIMWindowCreator,
    public CWindowImpl<SkypeToggleChatFNReadWindow >
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNREADWINDOW
  NS_DECL_IFNIMWINDOWCREATOR

  SkypeToggleChatFNReadWindow();
 

BEGIN_MSG_MAP(SkypeToggleChatFNReadWindow)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_TIMER, onTimer)
    MESSAGE_HANDLER(WM_SIZE, onSize)
END_MSG_MAP()
  LRESULT OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT onTimer(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT onSize(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);

  PRBool createFNWidnow( PRUint32 refWindow );
  PRBool getDesiredWindowRect( RECT *rc);
  PRBool getCurrentWindowRect( RECT *prc);


private:
  ~SkypeToggleChatFNReadWindow();
  BOOL isWidnowVisibleOnCreeen();

  /* additional members */
protected:
    nsCOMPtr<IFNIMToggleChatReadWindow > readWindow_;
//    nsCOMPtr<IFNRichTextEditor_Service1 > fnRTEService_;
    PRUint32 refWindow_;
    nsEmbedString content_cache_;
    UINT_PTR  timerID_;
    BOOL windowclosed_;
    BOOL reaadOnlyFalg_;

};


/* Header file */
class SkypeToggleChatFNReader: public IFNIMToggleChatFNReader
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNREADER

  SkypeToggleChatFNReader();
  explicit SkypeToggleChatFNReader(nsISupports* ele);
 


private:
  ~SkypeToggleChatFNReader();
protected:

 nsCOMPtr<nsISupports > fnreader_element_;
};


 
#endif
