
#include "stdafx.h"    
#include "Winuser.h" //for VK_XXX
#include "keyStrokeUtil.h"
//#include "WINABLE.H" // for blockInput 
#include "types.h"


#include <iostream>
namespace FN_Browser_Help
{

    void WaitInWindowMessageLoop(DWORD millis)
    {    
        DWORD end = ::GetTickCount() + millis;
        do
        {
            MSG msg;
            if (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE)) 
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            Sleep(1);
        } while (::GetTickCount() < end);
    }

    void GenerateKey ( WORD vk , BOOL bExtended, BOOL down)
    {	    
        //FN_LOG_INFO_FUNCTION();
        KEYBDINPUT  kb={0};
        INPUT    Input={0};

        // generate down 
        if(down)
        {
            if ( bExtended )
            {
                kb.dwFlags  = KEYEVENTF_EXTENDEDKEY;
            }
        }
        else
        {
            // generate up 
            ::ZeroMemory(&kb,sizeof(KEYBDINPUT));
            ::ZeroMemory(&Input,sizeof(INPUT));
            kb.dwFlags  =  KEYEVENTF_KEYUP;
            if ( bExtended )
                kb.dwFlags  |= KEYEVENTF_EXTENDEDKEY;

        }

        Input.type  = INPUT_KEYBOARD;

        kb.wScan = ::MapVirtualKey(static_cast<UINT>(vk), 0);//0 : virtual key -->scan code
        kb.wVk    = vk;
        Input.ki  =  kb;
        ::SendInput(1,&Input,sizeof(Input));//lint !e534 (ignor return value)

    }

    void SendCtrlStroke(TCHAR key)	 
    {

        //key up //--this key must be up first
        bool recC = (GetKeyState(VkKeyScan(key)) & 0x8000) != 0;
        if (recC)
            keybd_event((BYTE)VkKeyScan(key), 0, KEYEVENTF_KEYUP, 0);

        //--eliminate HotKey repeating
        //Alt up
        bool recAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
        if (recAlt)
            keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); 
        //Shift up
        bool recShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
        if (recShift)
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); 

        //Ctrl down
        bool recCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        if (!recCtrl)
            keybd_event(VK_CONTROL, 0, 0, 0); 
        //key down
        keybd_event((BYTE)VkKeyScan(key), 0, 0, 0); 
        keybd_event((BYTE)VkKeyScan(key), 0, KEYEVENTF_KEYUP, 0);
        //key up

        //Ctrl up
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
    }


    void SendSHIFTStroke(TCHAR key)	 
    {

        //key up //--this key must be up first
        bool recC = (GetKeyState(VkKeyScan(key)) & 0x8000) != 0;
        if (recC)
            keybd_event((BYTE)VkKeyScan(key), 0, KEYEVENTF_KEYUP, 0);

        //--eliminate HotKey repeating
        //Atrl up
        bool recAlt = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        if (recAlt)
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
        //atl up //
        bool recShift = (GetKeyState(VK_MENU) & 0x8000) != 0;
        if (recShift)
            keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); 

        //Shift down
        bool recCtrl = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
        if (!recCtrl)
            keybd_event(VK_SHIFT, 0, 0, 0); 
        //key down
        keybd_event((BYTE)VkKeyScan(key), 0, 0, 0); 
        keybd_event((BYTE)VkKeyScan(key), 0, KEYEVENTF_KEYUP, 0);
        //key up

        //Shift up
        keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); 
    }

    void SendATLStroke(TCHAR key)	 
    {

        //key up //--this key must be up first
        bool recC = (GetKeyState(VkKeyScan(key)) & 0x8000) != 0;
        if (recC)
            keybd_event((BYTE)VkKeyScan(key), 0, KEYEVENTF_KEYUP, 0);

        //--eliminate HotKey repeating
        //Atrl up
        bool recAlt = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        if (recAlt)
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
        //Shift up
        bool recShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
        if (recShift)
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); 

        //Atl down
        bool recCtrl = (GetKeyState(VK_MENU) & 0x8000) != 0;
        if (!recCtrl)
            keybd_event(VK_MENU, 0, 0, 0); 
        //key down
        keybd_event((BYTE)VkKeyScan(key), 0, 0, 0); 
        keybd_event((BYTE)VkKeyScan(key), 0, KEYEVENTF_KEYUP, 0);
        //key up

        //Atl up
        keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); 
    }

    void Windows_HotKey_Copy()
    {
        SendCtrlStroke(TEXT('C'))	 ;
    }
    void Windows_HotKey_Paste()
    {
        SendCtrlStroke(TEXT('V'))	 ;
    }
    void Windows_HotKey_Cut()
    {
        SendCtrlStroke(TEXT('X'))	 ;
    }
    void Windows_HotKey_SelectALL()
    {
        SendCtrlStroke(TEXT('A'))	 ;
    }
    void Windows_HotKey_Delete()
    {
        //key down
        keybd_event( VK_DELETE, 0, KEYEVENTF_EXTENDEDKEY  | 0, 0); 
        keybd_event( VK_DELETE, 0, KEYEVENTF_EXTENDEDKEY  | KEYEVENTF_KEYUP, 0);
        //key up
    }
    void Windows_HotKey_Enter()
    {
        //key down
        keybd_event( VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY  | 0, 0); 
        keybd_event( VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY  | KEYEVENTF_KEYUP, 0);
        //key up

    }
    void releaseCTRL_SHIFT_ALT_Keys()
    {

        //--eliminate HotKey repeating
        //Alt up
        bool recAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
        if (recAlt)
        {
            keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); 
        }
        //Shift up
        bool recShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
        if (recShift)
        {
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); 
        }

        //Ctrl down
        bool recCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        if(recCtrl )
        {
            //Ctrl up
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
        }
    }

    void pressCTRLKey()
    {
        //Ctrl down

        keybd_event(VK_CONTROL, 0, 0, 0); 
    }
    void releaseCTRLKey()
    {
        //Ctrl down
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
    }



    void sendString(const wstring &inputchars)
    {
        releaseCTRL_SHIFT_ALT_Keys();

        UInt32 count_char = inputchars.length(); 
        if(count_char == 0U)
        {
            return ;
        }

        UInt32 count = count_char*2;  //key down and key up 

        INPUT* p_Inputs = new INPUT[count] ;
        if(p_Inputs  == 0)
        {
            return ;
        }

        ::ZeroMemory(p_Inputs, sizeof(INPUT)* count);
        auto_ptr<INPUT> auto_Inputs;//(new INPUT[count] );

        auto_Inputs.reset( p_Inputs  );

        for(UInt32 i = 0; i < count_char; i++ )
        {
            KEYBDINPUT  kb_down={0};//KEYEVENTF_UNICODE
            KEYBDINPUT  kb_up={0};//KEYEVENTF_UNICODE
            const wchar_t ch = inputchars[i];
            kb_down.dwFlags = KEYEVENTF_UNICODE;
            kb_down.wScan = (WORD)ch;

            kb_up.dwFlags = KEYEVENTF_UNICODE |KEYEVENTF_KEYUP;
            kb_up.wScan = (WORD)ch;


            p_Inputs[i*2].type  = INPUT_KEYBOARD;
            p_Inputs[i*2].ki  =  kb_down;

            p_Inputs[i*2+1].type  = INPUT_KEYBOARD;
            p_Inputs[i*2+1].ki  =  kb_up;

        }
        ::SendInput(count,p_Inputs,sizeof(INPUT) );//lint !e534 (ignor return value)
    }

    ////    class Timer_SendKey

    Timer_SendKey::Timer_SendKey()
        :  autoSelfDelete_(FALSE)
        , window_(0)
        ,timer_elapse_(0)
        ,orinigal_cursor_(0)
    {
        POINT pt = {0};
        hotPoint_ = pt;
        //EnableHardwareKeyboard(FALSE); windows ce only
    }
    Timer_SendKey::~Timer_SendKey()
    {
        ::BlockInput(FALSE); // for sure
        //EnableHardwareKeyboard(TRUE);
    }

    void  Timer_SendKey::SetWindow(HWND awindow)
    {
        window_ = awindow;
    }
    void  Timer_SendKey::SetTimerElapse(UINT elapse)
    {
        timer_elapse_ = elapse;
    }

    BOOL Timer_SendKey::GetAutoSelfDelete()
    {
        return autoSelfDelete_;
    }
    void Timer_SendKey::SetAutoSelfDelete(BOOL bAutoSelfDelete)
    {
        autoSelfDelete_ = bAutoSelfDelete;
    }


    void Timer_SendKey::pushback_key( const Key_Stroke_Value &akey_stroke_value)
    {
        key_stroke_values_.push_back(akey_stroke_value);
    }
    void Timer_SendKey::reset()
    {
        ::KillTimer(window_, (UINT_PTR)this  );
        key_stroke_values_.clear();
        autoSelfDelete_ = FALSE;
        timer_elapse_ = 0U;
        window_ = 0;
        POINT pt = {0};
        hotPoint_ = pt;
    }
    void Timer_SendKey::SetScreenHotPoint(const POINT &pt)
    {
        hotPoint_ = pt;
    }

    HWND  Timer_SendKey::focus() 
    {	    


        //SetForegroundWindow(  window_ );  //lint !e534
        //EnableWindow(window_, TRUE);
        SetActiveWindow(window_);
        return SetFocus(window_ );
        //::SetCapture(window_ );
    }

    void  Timer_SendKey::focusByMouse() 
    {	    

        //SetForegroundWindow(  window_ );  //lint !e534
        //EnableWindow(window_, TRUE);
        SetActiveWindow(window_);
        SetFocus(window_ );

        //::PostMessage(window_, WM_LBUTTONDOWN, (WPARAM )MK_LBUTTON, (LPARAM )(MAKELPARAM(hotPoint_.x, hotPoint_.y)));
        //::PostMessage(window_, WM_LBUTTONUP,   (WPARAM )0,          (LPARAM )(MAKELPARAM(hotPoint_.x, hotPoint_.y)));

        //orinigal_cursor_ =  ::SetCursor(  LoadCursor(NULL, IDC_WAIT) );

        //for reference the following code does not work
        //::SetCapture(window_ );

        //MOUSEINPUT  ms={0};
        //INPUT    Input={0};

        //Input.type  = INPUT_MOUSE;
        //Input.mi  =  ms;
        //ms.dx = hotPoint_.x;
        //ms.dy = hotPoint_.y;
        //SetCursorPos(hotPoint_.x, hotPoint_.y); 


        //ms.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN;
        //::SendInput(1,&Input,sizeof(Input));//lint !e534 (ignor return value)

        //ms.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP;
        //::SendInput(1,&Input,sizeof(Input));//lint !e534 (ignor return value)

        //for reference the following code does not work either
        SetCursorPos(hotPoint_.x, hotPoint_.y); 
        mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, 
            hotPoint_.x,     hotPoint_.y,     0,        0) ;
        mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, 
            hotPoint_.x,     hotPoint_.y,     0,        0) ;



    }

    void  Timer_SendKey::sendkeys( BOOL usingTimer)
    {
        ::BlockInput(TRUE);
        //focusByMouse() ;
        if(usingTimer)
        {
            ::SetTimer(window_ , (UINT_PTR)this, timer_elapse_, (TIMERPROC)(Timer_SendKey::Timer_SendKey_callback));
            return ;
        }
        else
        {
            //
            focus() ;
            std::vector< Key_Stroke_Value > ::iterator itor;

            for(itor = key_stroke_values_.begin() ; itor != key_stroke_values_.end() ; itor++)
            {
                if(::GetFocus() == window_)
                {
                    Key_Stroke_Value& value  =  *itor;// return last element of mutable sequence


                    releaseCTRL_SHIFT_ALT_Keys();
                    if(( value.extendFlag & E_EXTENDKEY_CTRL )!= 0)
                    {
                        keybd_event(VK_CONTROL, 0, 0, 0); 
                    }

                    if(( value.extendFlag & E_EXTENDKEY_ATL ) != 0)
                    {
                        keybd_event(VK_MENU, 0, 0, 0); 
                    }

                    if( (value.extendFlag & E_EXTENDKEY_SHIFT  ) != 0)
                    {
                        keybd_event(VK_SHIFT, 0, 0, 0); 
                    }

                    if( (value.extendFlag & E_EXTENDKEY_EXTENDKEY ) != 0)
                    {
                        keybd_event( (BYTE)(value.tchar_), 0, KEYEVENTF_EXTENDEDKEY | 0, 0); 
                        keybd_event( (BYTE)(value.tchar_), 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                    }
                    else
                    {
                        keybd_event( (BYTE)VkKeyScan(value.tchar_), 0, 0, 0); 
                        keybd_event( (BYTE)VkKeyScan(value.tchar_), 0, KEYEVENTF_KEYUP, 0);
                    }

                    if( (value.extendFlag & E_EXTENDKEY_CTRL  ) != 0)
                    {
                        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
                    }

                    if( (value.extendFlag & E_EXTENDKEY_ATL ) != 0)
                    {
                        keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); 
                    }

                    if( (value.extendFlag & E_EXTENDKEY_SHIFT ) != 0)
                    {
                        keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); 
                    }
                }
            }//for
            ::BlockInput(FALSE);
            key_stroke_values_.clear();
            if(autoSelfDelete_)
            {
                delete this;
            }
        }//else

    }


    void  Timer_SendKey::Timer_SendKey_callback(HWND hwnd , UINT, UINT_PTR eventid, DWORD)
    {

        Timer_SendKey* aTimer_SendKey =  reinterpret_cast<Timer_SendKey*>(eventid);
        if(aTimer_SendKey )
        {
            //aTimer_SendKey->focusByMouse();
            if(!aTimer_SendKey ->key_stroke_values_.empty() )
            {

                Key_Stroke_Value& value  =  aTimer_SendKey ->key_stroke_values_.front();// return last element of mutable sequence


                releaseCTRL_SHIFT_ALT_Keys();
                if(( value.extendFlag & E_EXTENDKEY_CTRL )!= 0)
                {
                    keybd_event(VK_CONTROL, 0, 0, 0); 
                }

                if(( value.extendFlag & E_EXTENDKEY_ATL ) != 0)
                {
                    keybd_event(VK_MENU, 0, 0, 0); 
                }

                if( (value.extendFlag & E_EXTENDKEY_SHIFT  ) != 0)
                {
                    keybd_event(VK_SHIFT, 0, 0, 0); 
                }

                if( (value.extendFlag & E_EXTENDKEY_EXTENDKEY ) != 0)
                {
                    keybd_event( (BYTE)(value.tchar_), 0, KEYEVENTF_EXTENDEDKEY | 0, 0); 
                    keybd_event( (BYTE)(value.tchar_), 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                }
                else
                {
                    keybd_event( (BYTE)VkKeyScan(value.tchar_), 0, 0, 0); 
                    keybd_event( (BYTE)VkKeyScan(value.tchar_), 0, KEYEVENTF_KEYUP, 0);
                }

                if( (value.extendFlag & E_EXTENDKEY_CTRL  ) != 0)
                {
                    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
                }

                if( (value.extendFlag & E_EXTENDKEY_ATL ) != 0)
                {
                    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); 
                }

                if( (value.extendFlag & E_EXTENDKEY_SHIFT ) != 0)
                {
                    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); 
                }
                aTimer_SendKey ->key_stroke_values_.erase( aTimer_SendKey ->key_stroke_values_.begin() );// erase element at end
            }


            else
            {
                ::BlockInput(TRUE);
                ::KillTimer(hwnd, eventid  );
                if(aTimer_SendKey ->orinigal_cursor_   != 0)
                {
                    ::SetCursor( aTimer_SendKey ->orinigal_cursor_  );
                }

                if(aTimer_SendKey ->GetAutoSelfDelete() )
                {
                    delete aTimer_SendKey;
                }
            }
        }
    }


    void PostMessage_CTRL_A(HWND hwnd)
    {
        ::PostMessage(hwnd, WM_KEYDOWN, 0x11, 0x001d0001); //ctrl down
        ::PostMessage(hwnd, WM_KEYDOWN, 0x41, 0x001e0001); //A down
        //::PostMessage(hwnd, WM_CHAR, 0x01, 0x001e0001); //A char
        ::PostMessage(hwnd, WM_KEYUP, 0x41, 0xc01e0001); //A up
        ::PostMessage(hwnd, WM_KEYUP, 0x11, 0xc01d0001); //ctrl up
    }


    void PostMessage_CTRL_C(HWND hwnd)
    {
        ::PostMessage(hwnd, WM_KEYDOWN, 0x11, 0x001d0001); //ctrl down
        ::PostMessage(hwnd, WM_KEYDOWN, 0x43, 0x002e0001); //c down
        //::PostMessage(hwnd, WM_CHAR, 0x03, 0x002e0001); //c char
        ::PostMessage(hwnd, WM_KEYUP, 0x43, 0xc02e0001); //c up
        ::PostMessage(hwnd, WM_KEYUP, 0x11, 0xc01d0001); //ctrl up
    }

    void SendMessage_CTRL_A(HWND hwnd)
    {
        LRESULT lr;
        //keybd_event(VK_CONTROL, 0, 0, 0); 
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
            std::cout<<"==========BEGIN CTRL A ==========="<<std::endl;
        lr = ::SendMessage(hwnd, WM_KEYDOWN, 0x11, 0x001d0001); //ctrl down
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
            std::cout<<"ctrl down result ="<<lr<<std::endl;
        lr = ::SendMessage(hwnd, WM_KEYDOWN, 0x41, 0x001e0001); //A down
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
            std::cout<<"ctrl down result ="<<lr<<std::endl;
        //::PostMessage(hwnd, WM_CHAR, 0x01, 0x001e0001); //A char
        lr = ::SendMessage(hwnd, WM_KEYUP, 0x41, 0xc01e0001); //A up
        std::cout<<"ctrl down result ="<<lr<<std::endl;
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {
            lr = ::SendMessage(hwnd, WM_KEYUP, 0x11, 0xc01d0001); //ctrl up
            std::cout<<"ctrl down result ="<<lr<<std::endl;
            //keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
            std::cout<<"==========END CTRL A ==========="<<std::endl;
        }

    }
    void SendMessage_CTRL_C(HWND hwnd)
    {	
        LRESULT lr;
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        std::cout<<"==========BEGIN CTRL C ==========="<<std::endl;
        //keybd_event(VK_CONTROL, 0, 0, 0); 
        lr = ::SendMessage(hwnd, WM_KEYDOWN, 0x11, 0x001d0001); //ctrl down
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        std::cout<<"ctrl down result ="<<lr<<std::endl;
        lr =::SendMessage(hwnd, WM_KEYDOWN, 0x43, 0x001e0001); //c down
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        std::cout<<"c down result ="<<lr<<std::endl;
        //::PostMessage(hwnd, WM_CHAR, 0x01, 0x001e0001); //c char
        lr =::SendMessage(hwnd, WM_KEYUP, 0x43, 0xc01e0001); //c up
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        std::cout<<"c up result ="<<lr<<std::endl;
        lr =::SendMessage(hwnd, WM_KEYUP, 0x11, 0xc01d0001); //ctrl up
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {
        std::cout<<"ctrl up result ="<<lr<<std::endl;
        std::cout<<"==========END CTRL C ==========="<<std::endl;
        }
        //keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
    }

    void SendMessage_CTRL_V(HWND hwnd)
    {	
        LRESULT lr;
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {
            std::cout<<"==========BEGIN CTRL C ==========="<<std::endl;
        }
        //keybd_event(VK_CONTROL, 0, 0, 0); 
        lr = ::SendMessage(hwnd, WM_KEYDOWN, 0x11, 0x001d0001); //ctrl down
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {
            std::cout<<"ctrl down result ="<<lr<<std::endl;
        }
        lr =::SendMessage(hwnd, WM_KEYDOWN, 0x56, 0x001e0001); //v down
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {
            std::cout<<"c down result ="<<lr<<std::endl;
        }
        //::PostMessage(hwnd, WM_CHAR, 0x01, 0x001e0001); /v char
        lr =::SendMessage(hwnd, WM_KEYUP, 0x56, 0xc01e0001); //v up
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {
            std::cout<<"c up result ="<<lr<<std::endl;
        }
        lr =::SendMessage(hwnd, WM_KEYUP, 0x11, 0xc01d0001); //ctrl up
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {
            std::cout<<"ctrl up result ="<<lr<<std::endl;
            std::cout<<"==========END CTRL C ==========="<<std::endl;
        }
        //keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
    }

    void ICQSendMessage_CTRL_A(HWND hwnd)
    {

        keybd_event(VK_CONTROL, 0, 0, 0); 

        ::SendMessage(hwnd, WM_KEYDOWN, 0x11, 0x001D0001); //ctrl down
        ::SendMessage(hwnd, WM_KEYDOWN, 0x41, 0x001e0001); //A down
        //::PostMessage(hwnd, WM_CHAR, 0x01, 0x001e0001); //A char
        ::SendMessage(hwnd, WM_KEYUP, 0x41, 0xc01e0001); //A up
        ::SendMessage(hwnd, WM_KEYUP, 0x11, 0xc01d0001); //ctrl up

        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 

    }
    void ICQSendMessage_CTRL_C(HWND hwnd)
    {

        keybd_event(VK_CONTROL, 0, 0, 0); 
        ::SendMessage(hwnd, WM_KEYDOWN, 0x11, 0x001d0001); //ctrl down
        ::SendMessage(hwnd, WM_KEYDOWN, 0x43, 0x002e0001); //C down
        ::SendMessage(hwnd, WM_KEYUP, 0x43, 0xc02e0001); //C up
        ::SendMessage(hwnd, WM_KEYUP, 0x11, 0xc01d0001); //ctrl up
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
    }

};
//FN_Browser_Help