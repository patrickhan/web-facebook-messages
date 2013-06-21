#pragma once


#include "IFNIMToggle.h"
#include "nsEmbedString.h"
#include "nsCOMArray.h"
#include <list>
#include "nsCOMPtr.h"



//WTL

//#define WINVER		0x0500
//#define _WIN32_WINNT	0x0501
//#define _WIN32_IE	0x0501
//#define _RICHEDIT_VER	0x0200
#include <atlbase.h>
//#include <atlapp.h>
//#include "atlctrls.h"
#include <atlwin.h>



class SkypeToggleButton : public IFNIMToggleButton ,
     public CWindowImpl<SkypeToggleButton >
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_IFNIMTOGGLEBUTTON
    
    SkypeToggleButton();

	BEGIN_MSG_MAP(SkypeToggleButton)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_LBUTTONUP, onClick)
    MESSAGE_HANDLER(WM_PAINT, onPaint)
    MESSAGE_HANDLER(WM_TIMER, onTimer)
  END_MSG_MAP()


  LRESULT onClick(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT onPaint(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT OnDestroy(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT OnCreate(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  LRESULT onTimer(UINT /* uMsg */, WPARAM /* wParam */, LPARAM lParam , BOOL& /* lResult */);
  


    //void setSession(IFNIMToggleChatSession * session)
    //{
    //    chat_session_ = session;
    //}

    PRBool createButton( PRUint32 refWindow );
    PRBool getDesiredWindowRect( RECT *rc);
    PRBool getCurrentWindowRect( RECT *prc);
  ~SkypeToggleButton();

protected:
  /* additional members */
   
    //nsCOMPtr<IFNIMToggleChatSession > chat_session_;
private:
    PRBool shownFnWindow_;
    PRUint32 refWindow_;
    UINT_PTR  timerID_;
    BOOL windowclosed_;
    PRBool _aToggleState;


    nsCOMArray<IFNIMToggleButtonEvnetListener> buttonEvnetListener_;
    nsCOMPtr<IFNIMWindowDestroyEvnetListener> aDestroyEvnetListener_;
};
