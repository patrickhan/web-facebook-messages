#ifndef SkypeToggleChatFNInputWindow__HEADER__
#define SkypeToggleChatFNInputWindow__HEADER__

#include "IFNIMToggle.h"
 #include "nsCOMPtr.h"

//WTL

//#define WINVER		0x0500
//#define _WIN32_WINNT	0x0501
//#define _WIN32_IE	0x0501
//#define _RICHEDIT_VER	0x0200
#include <atlbase.h>
#include <atlapp.h>
#include "atlctrls.h"
#include <atlwin.h>


//#include "IFNRichTextEditor_Service.h"

#define WM_FNRTE_SUBMIT (WM_USER +100)
//#define WM_FNRTE_TOGGLE (WM_USER +101)
/* Header file */
//SkypeToggleChatFNInputWindow is obsolete
class SkypeToggleChatFNInputWindow : public IFNIMToggleChatFNInputWindow,public IFNIMWindowCreator,
     public CWindowImpl<SkypeToggleChatFNInputWindow>
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNINPUTWINDOW
  NS_DECL_IFNIMWINDOWCREATOR

  SkypeToggleChatFNInputWindow();


BEGIN_MSG_MAP(SkypeToggleChatFNInputWindow)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_TIMER, onTimer)
END_MSG_MAP()


  LRESULT OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT onTimer(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);

    PRBool getDesiredWindowRect( RECT *rc);
    PRBool getCurrentWindowRect( RECT *prc);

private:
  ~SkypeToggleChatFNInputWindow();

  /* additional members */
protected:
    nsCOMPtr<IFNIMToggleChatInputWindow > inputWindow_;
    PRUint32 refWindow_;
    UINT_PTR  timerID_;
    BOOL windowclosed_;
};
 
 
class SkypeToggleChatFNInput : public IFNIMToggleChatFNInput
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNINPUT

  SkypeToggleChatFNInput();
  explicit SkypeToggleChatFNInput( nsISupports * ele);

private:
  ~SkypeToggleChatFNInput();

  /* additional members */
protected:

    nsCOMPtr<nsISupports > fnInput_element_;
};
 
 


 

#endif
