#ifndef ISkypeToggleChatReadWindow__HEADER__
#define ISkypeToggleChatReadWindow__HEADER__

#include "IFNIMToggle.h"
#include "nsCOMPtr.h"
#include "nsEmbedString.h"
class SkypeToggleChatReadWindow : public IFNIMToggleChatReadWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATREADWINDOW

  SkypeToggleChatReadWindow();

private:
  ~SkypeToggleChatReadWindow();

protected:
  /* additional members */
    nsEmbedString  window_caption_;
    nsEmbedString  window_classname_;
    PRInt32 m_hWnd;
};
 

////SkypeChatReadWindowLocator
class SkypeChatReadWindowLocator :public IFNIMToggleChatReadWindowLocator
{

  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATREADWINDOWLOCATOR

public:
    SkypeChatReadWindowLocator()
    {
    }
    ~SkypeChatReadWindowLocator()
    {
    }
    void setReferenceWindow(IFNIMToggleChatSessionMainWindow* main_Wnd)
    {
        mainWindow_ = main_Wnd ;
    }

     nsCOMPtr<IFNIMToggleChatSessionMainWindow >  mainWindow_;

}; 


#endif
