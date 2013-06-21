#ifndef SkypeToggleChatSessionMainWindow__HEADER__
#define SkypeToggleChatSessionMainWindow__HEADER__


#include "IFNIMToggle.h"
#include "nsEmbedString.h"
#include "nsIMutableArray.h"
#include "nsCOMPtr.h"
#include <list>
/* Header file */
class SkypeToggleChatSessionMainWindow : public IFNIMToggleChatSessionMainWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONMAINWINDOW

  SkypeToggleChatSessionMainWindow();


  void getSubSesssionWindowClassName(nsEmbedString  &className);
private:
  ~SkypeToggleChatSessionMainWindow();

protected:
  /* additional members */

    nsEmbedString  window_caption_;
    nsEmbedString  window_classname_;
    nsEmbedString  subSessionWindow_classname_;

    PRInt32 m_hWnd;

};


class SkypeChatSessionMainWindowLocator :  public IFNIMToggleChatSessionMainWindowLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR

  SkypeChatSessionMainWindowLocator ();

  void addWindow( PRUint32 wnd);
private:
  ~SkypeChatSessionMainWindowLocator ();


  
    std::list<PRUint32> hWnds_;

};

 

#include "nsITimer.h"
#include "nsIObserver.h"
#include "nsWeakReference.h"
#include "windows.h"
//typedef struct MyRECT
//{
//    long    left;
//    long    top;
//    long    right;
//    long    bottom;
//}  ;


class FNIMToggleChatFNMainWindowLocator : public IFNIMWindowLocator
    ,public nsIObserver
		,public nsSupportsWeakReference 
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOBSERVER
  NS_DECL_IFNIMWINDOWLOCATOR
  
public:
    FNIMToggleChatFNMainWindowLocator();
    
    FNIMToggleChatFNMainWindowLocator(
        IFNIMToggleChatFNMainWindow * fnmw,
        IFNIMToggleChatSessionMainWindow *mw,
        IFNIMToggleChatInputWindow *inw,
        IFNIMToggleChatReadWindow* rw);

    ~FNIMToggleChatFNMainWindowLocator();
protected:
    nsresult getPos_expected( RECT *rc);
    nsresult adjustLayout(const RECT* prc );

    nsCOMPtr<IFNIMToggleChatSessionMainWindow > mainWindow_;
    nsCOMPtr<IFNIMToggleChatInputWindow >       inputWindow_;
    nsCOMPtr<IFNIMToggleChatReadWindow >        readWindow_;
    nsCOMPtr<IFNIMToggleChatFNMainWindow>       fnMainWindow_;

    nsCOMPtr<nsITimer>  aNSTimer_;

    RECT rc_ecpected_ ;
};





class FNIMToggleButtonLocator : public IFNIMWindowLocator
    ,public nsIObserver
		,public nsSupportsWeakReference 
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOBSERVER
  NS_DECL_IFNIMWINDOWLOCATOR
  
public:
    FNIMToggleButtonLocator ();
    
    FNIMToggleButtonLocator (
        IFNIMToggleButton * button,
        IFNIMToggleChatReadWindow *inw   );

    ~FNIMToggleButtonLocator ();
protected:
    nsresult getPos_expected( RECT *rc);
    nsresult adjustLayout(const RECT* prc );

    nsCOMPtr<IFNIMToggleButton > button_;
    nsCOMPtr<IFNIMToggleChatReadWindow >       readWindow_;

    nsCOMPtr<nsITimer>  aNSTimer_;

    RECT rc_ecpected_ ;
};





class SkypeFNIMToggleChatFNReadWindowLocator : public IFNIMWindowLocator
    ,public nsIObserver
    ,public nsSupportsWeakReference 
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOBSERVER
  NS_DECL_IFNIMWINDOWLOCATOR

  SkypeFNIMToggleChatFNReadWindowLocator();
 
   explicit SkypeFNIMToggleChatFNReadWindowLocator( 
       IFNIMToggleChatReadWindow  *readw  , 
       IFNIMToggleChatFNReadWindow *fnreadw   );

  ~SkypeFNIMToggleChatFNReadWindowLocator();
  
protected:


    nsresult adjustLayout(const RECT* prc );

    PRBool getDesiredWindowRect( RECT *rc);
    PRBool getCurrentWindowRect( RECT *prc);
    
    nsCOMPtr<IFNIMToggleChatReadWindow>       readWindow_;
    nsCOMPtr<IFNIMToggleChatFNReadWindow >    fnreadWindow_;
    nsCOMPtr<nsITimer>  aNSTimer_;
    RECT rc_ecpected_ ;
    HWND refWindow_;
};

class SkypeFNIMToggleChatFNInputWindowLocator : public IFNIMWindowLocator
    ,public nsIObserver
    ,public nsSupportsWeakReference 
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIOBSERVER
    NS_DECL_IFNIMWINDOWLOCATOR

    SkypeFNIMToggleChatFNInputWindowLocator();

    explicit SkypeFNIMToggleChatFNInputWindowLocator(
        IFNIMToggleChatInputWindow *inw  , 
        IFNIMToggleChatFNInputWindow* fninw);
 
    ~SkypeFNIMToggleChatFNInputWindowLocator();

protected:

    PRBool getDesiredWindowRect( RECT *rc);
    PRBool getCurrentWindowRect( RECT *prc);
    nsresult adjustLayout(const RECT* prc );
    nsCOMPtr<IFNIMToggleChatInputWindow >         inputWindow_;
    nsCOMPtr<IFNIMToggleChatFNInputWindow >       fninputWindow_;
    nsCOMPtr<nsITimer>  aNSTimer_;
    RECT rc_ecpected_ ;
    HWND refWindow_;
};

#endif //

