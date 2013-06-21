#ifndef SkypeToggleChatInputWindow__HEADER__
#define SkypeToggleChatInputWindow__HEADER__


#include "IFNIMToggle.h"
#include "nsCOMPtr.h"
#include "nsEmbedString.h"
class SkypeToggleChatInputWindow : public IFNIMToggleChatInputWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATINPUTWINDOW

  SkypeToggleChatInputWindow();

private:
  ~SkypeToggleChatInputWindow();

protected:
  /* additional members */
    nsEmbedString  window_caption_;
    nsEmbedString  window_classname_;
    PRInt32 m_hWnd;
};


///////////////////////////////////////////////////////////////////////////
////SkypeChatInputWindowLocator
class SkypeChatInputWindowLocator :public IFNIMToggleChatInputWindowLocator
{

  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATINPUTWINDOWLOCATOR

public:
    SkypeChatInputWindowLocator()
    {
    }
    ~SkypeChatInputWindowLocator()
    {
    }
    void setReferenceWindow(IFNIMToggleChatSessionMainWindow* main_Wnd)
    {
        mainWindow_ = main_Wnd ;
    }

     nsCOMPtr<IFNIMToggleChatSessionMainWindow >  mainWindow_;

};


#endif //
