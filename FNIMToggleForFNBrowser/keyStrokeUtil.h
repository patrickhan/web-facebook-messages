
//ref 
//#include "keyStrokeUtil.h"
//


#ifndef KEYSTROKEUTIL_HEADER_ 
#define KEYSTROKEUTIL_HEADER_ 
#include <xstring>
#include <vector>
#include <windows.h>
using namespace std;
namespace FN_Browser_Help
{
    void WaitInWindowMessageLoop(DWORD millis);
    void GenerateKey ( WORD vk , BOOL bExtended, BOOL down);
    void SendCtrlStroke(TCHAR key);
    void Windows_HotKey_Copy();
    void Windows_HotKey_Paste();
    void Windows_HotKey_Cut();
    void Windows_HotKey_SelectALL();
    void Windows_HotKey_Delete();
    void Windows_HotKey_Enter();

    void sendString(const wstring &inputchars);

    void releaseCTRL_SHIFT_ALT_Keys();
    void pressCTRLKey();
    void releaseCTRLKey();

    void PostMessage_CTRL_A(HWND hwnd);
    void PostMessage_CTRL_C(HWND hwnd);
    void SendMessage_CTRL_A(HWND hwnd);
    void SendMessage_CTRL_C(HWND hwnd);
    void SendMessage_CTRL_V(HWND hwnd);

	/* PeterY added */
	void ICQSendMessage_CTRL_A(HWND hwnd);
	void ICQSendMessage_CTRL_C(HWND hwnd);

class Timer_SendKey
{
public :
    struct Key_Stroke_Value
    {
        WORD tchar_;
        WORD reserve_;
        DWORD extendFlag;//ctl , alt shift 
    };


    Timer_SendKey();
    virtual ~Timer_SendKey();
    void SetAutoSelfDelete(BOOL bAutoSelfDelete);
    BOOL GetAutoSelfDelete();
    void SetWindow(HWND awindow);
    void SetTimerElapse(UINT elapse);
    void SetScreenHotPoint(const POINT &pt);
 
    virtual void pushback_key( const Key_Stroke_Value& akey_stroke_value);
    virtual void sendkeys(BOOL usingTimer);
    virtual void reset();
    virtual HWND focus();
    virtual void focusByMouse();
    static void Timer_SendKey_callback(HWND hwnd , UINT, UINT_PTR eventid, DWORD);

    enum {E_EXTENDKEY_CTRL  = 0x0000001};
    enum {E_EXTENDKEY_ATL   = 0x0000002};
    enum {E_EXTENDKEY_SHIFT = 0x0000004};
    enum {E_EXTENDKEY_EXTENDKEY = 0x0000008};
    

private:
    BOOL autoSelfDelete_;
    HWND window_;
    UINT timer_elapse_;
    POINT hotPoint_;// used to active the focus by mouse
    std::vector< Key_Stroke_Value > key_stroke_values_; 
    HCURSOR orinigal_cursor_;
};

};

//using namespace FN_Browser_Help;

#endif //KEYSTROKEUTIL_HEADER_  

