
#include "stdafx.h"
#include "clipBoardUtil.h"
//#include "types.h"
//#include "smallutils.h"
#include "global.h"
namespace FN_Browser_Help
{
    /********************************/
    FN_ClipboardBackup::FN_ClipboardBackup():hwnd_ref(0)
    {
    }
    FN_ClipboardBackup::FN_ClipboardBackup(HWND hwnd):hwnd_ref(hwnd)
    {
        Backup(hwnd) ;
    }
    FN_ClipboardBackup::~FN_ClipboardBackup()
    {
        if(::IsWindow(hwnd_ref))
        {
            Restore( hwnd_ref ) ;
        }
        ClearBackupDatas();
    }
    BOOL FN_ClipboardBackup::Backup(HWND hwnd) 
    {
        //if(backupHwnd == NULL) 
        //{
        //	backupHwnd = ::GetClipboardOwner();
        //}else if(restoreHwnd != ::GetClipboardOwner()) 
        //{
        //	backupHwnd = ::GetClipboardOwner();
        //}	
        //


        if(! ::OpenClipboard(hwnd)) 
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {
                std::cout<<"Backup LAST ERROR #= "<<::GetLastError()<<std::endl;
                std::cout<<"Backup owner hwnd="<<::GetClipboardOwner()<<std::endl;
                std::cout<<"FN_ClipboardBackup::Backup(HWND hwnd) cannot OpenClipboard(..)... failed!!!!!!!!!!!!!!!"<<std::endl;
            }
            ::EmptyClipboard();
            if(! ::CloseClipboard()) 
            {
                if(DEBUG_TRACE_OUTPUT_CONSOLE)
                {
                    std::cout<<"FN_ClipboardBackup::Backup(HWND hwnd) cannot CloseClipboard(..)... failed!!!!!!!!!!!!!!!"<<std::endl;
                }
            }
            return false;
        }
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {

            std::cout<<"Backup owner hwnd="<<hwnd<<std::endl;
        }
        ClearBackupDatas();

        UINT format = 0;

        while( (format = ::EnumClipboardFormats(format)) != 0)
        {
            ClipboardData data;
            data.m_nFormat = format;

            if(format <= 14) 
            {
                data.m_szFormatName[0] = 0;
            }else if( GetClipboardFormatName (format, data.m_szFormatName, 100) == 0)
            {
                data.m_szFormatName[0] = 0;
            }

            HANDLE hMem = ::GetClipboardData(format);
            if(hMem == NULL) {
                continue;
            }

            data.m_nLength = ::GlobalSize(hMem);

            LPVOID pMem = ::GlobalLock(hMem);
            data.m_pData = new BYTE[data.m_nLength];
            memcpy(data.m_pData, pMem, data.m_nLength);
            //				m_lstData.AddTail(data);
            userClipboardList.push_back(data);
        }
        //::EmptyClipboard();
        if( ! ::CloseClipboard()) 
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {

                std::cout<<"Backup owner hwnd="<<::GetClipboardOwner()<<std::endl;
                std::cout<<"FN_ClipboardBackup::Backup(HWND hwnd) cannot CloseClipboard(..)... failed!!!!!!!!!!!!!!!"<<std::endl;
            }
        }

        return TRUE;
    }

    BOOL FN_ClipboardBackup::Restore(HWND hwnd)
    {
        //restoreHwnd = ::GetClipboardOwner();

        if (! ::OpenClipboard((hwnd)))
        {	
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {

                std::cout<<"Restore LAST ERROR #= "<<::GetLastError()<<std::endl;
                std::cout<<"Restore owner hwnd="<<::GetClipboardOwner()<<std::endl;
                std::cout<<"FN_ClipboardBackup::Restore(HWND hwnd) OpenClipboard()... failed!!!!!!!!!!!"<<std::endl;
            }
            return false;
        }
        ::EmptyClipboard();


        while(userClipboardList.size() > 0) 
        {

            ClipboardData data = userClipboardList.front();
            userClipboardList.pop_front();
            if(data.m_nFormat > 0) 
            {
                UINT format = data.m_nFormat;
                if(data.m_szFormatName[0] != 0)
                {
                    UINT u = RegisterClipboardFormat(data.m_szFormatName);
                    if(u>0) format = u;
                }
                HANDLE hMem = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, data.m_nLength);
                LPVOID pMem = ::GlobalLock(hMem);

                memcpy(pMem, data.m_pData, data.m_nLength);
                ::SetClipboardData(format, hMem);
                ::GlobalUnlock(hMem);
            }

        }

        //POSITION pos = m_lstData.GetHeadPosition();


        //while( pos != NULL)
        //{
        //	ClipboardData &data = m_lstData.GetNext(pos);
        //	UINT format = data.m_nFormat;
        //	if(data.m_szFormatName[0] != 0)
        //	{
        //		UINT u = RegisterClipboardFormat(data.m_szFormatName);
        //		if(u>0) format = u;
        //	}
        //	HANDLE hMem = ::GlobalAlloc(GMEM_MOVEABLE | GEME_DDESHARE, data.m_nLength);
        //	LPVOID pMem = ::GlobalLock(hMem);

        //	memcpy(pMem, data.m_pData, data.m_nLength);
        //	::GlobalUnlock(hMem);
        //	::SetClipboardData(format, hMem);
        //}

        //std::cout<<"before close restore curr hwnd="<<::GetClipboardOwner()<<std::endl;
        if(! ::CloseClipboard()) 
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {

                std::cout<<"CloseClipboard owner hwnd="<<::GetClipboardOwner()<<std::endl;
                std::cout<<"CloseClipboard GetOpenClipboardWindow hwnd="<<::GetOpenClipboardWindow()<<std::endl;
                std::cout<<"FN_ClipboardBackup::Restore(HWND hwnd) CloseClipboard()... failed!!!!!!!!!!!"<<std::endl;
            }

        }
        return true;
    }

    VOID FN_ClipboardBackup::ClearBackupDatas()
    {
        userClipboardList.clear();
        //delete [] userClipboardData.m_pData;

        //POSITION pos = m_lstData.GetHeadPosition();
        //while(pos != NULL) 
        //{
        //	ClipboardData &data = m_lstData.GetNext(pos);
        //	delete [] data.m_pData;
        //}
        //m_lstData.RemoveAll();
    }



    /********************************/



    wstring GetClipboardText(HWND hwnd) 
    {	    
        //FN_LOG_INFO_FUNCTION()

        wstring out_s = L" ";

        //::EmptyClipboard();



        if (!OpenClipboard(hwnd)) 
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {

                std::cout<<"GetClipboardText GetClipboardOwner hwnd="<<::GetClipboardOwner()<<std::endl;
                std::cout<<"GetClipboardText GetOpenClipboardWindow hwnd="<<::GetOpenClipboardWindow()<<std::endl;
                std::cout<<"GetClipboardText::OpenClipboard() failed!!!!!"<<std::endl;
            }
            return out_s; 
        }
        HGLOBAL hglb;
        if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) 
        {
            if(IsClipboardFormatAvailable(CF_TEXT)) 
            {
                hglb = GetClipboardData(CF_TEXT); 
            }
            if(! ::EmptyClipboard() )
            {
                if(DEBUG_TRACE_OUTPUT_CONSOLE)
                {

                    std::cout<<"EmptyClipboard Failed !!!!!!!!!!"<<std::endl;
                }
            }

        }else if (IsClipboardFormatAvailable(CF_UNICODETEXT)){
            hglb = GetClipboardData(CF_UNICODETEXT); 
            if(! ::EmptyClipboard() )
            {
                if(DEBUG_TRACE_OUTPUT_CONSOLE)
                {

                    std::cout<<"EmptyClipboard Failed !!!!!!!!!!"<<std::endl;
                }
            }

        }else 
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {

                std::cout<<"IT SHOULD NOT DISPLAY ::IsClipboardFormatAvailable::"<<std::endl;
            }
        }

        if (hglb != NULL) 
        { 

            LPTSTR lptstr = reinterpret_cast< LPTSTR>( GlobalLock(hglb)); 
            if (lptstr != NULL) 
            { 

                // Call the application-defined ReplaceSelection 
                // function to insert the text and repaint the 
                // window. 

                out_s =  lptstr;
                GlobalUnlock(hglb); 
            }

        } 

        if( ! CloseClipboard()) 
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {

                std::cout<<"GetClipboardText clipboardOwner hwnd="<<::GetClipboardOwner()<<std::endl;
                std::cout<<"GetClipboardText::CloseClipboard() failed!!!!!"<<std::endl;
            }
        }		

        //::EmptyClipboard();
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {

            std::cout<<"==================noraml Begin out_s============="<<std::endl;
            std::wcout<<out_s<<">END<"<<std::endl;
            std::cout<<"==================normal End out_s============="<<std::endl;
        }
        return out_s;

    }

    BOOL GetClipboardTextEx(HWND hwnd, wstring &content) 
    {	    
        //FN_LOG_INFO_FUNCTION()

        wstring out_s = L" ";

        if (!OpenClipboard(hwnd)) 
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {

                std::cout<<"GetClipboardText GetClipboardOwner hwnd="<<::GetClipboardOwner()<<std::endl;
                std::cout<<"GetClipboardText GetOpenClipboardWindow hwnd="<<::GetOpenClipboardWindow()<<std::endl;
                std::cout<<"GetClipboardText::OpenClipboard() failed!!!!!"<<std::endl;
            }
            content = out_s;
            return FALSE;
        }

        HGLOBAL hglb = NULL;
        if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) 
        {
            if(IsClipboardFormatAvailable(CF_TEXT)) 
            {
                hglb = GetClipboardData(CF_TEXT); 

                if(! ::EmptyClipboard() )
                {
                    if(DEBUG_TRACE_OUTPUT_CONSOLE)
                    {

                        std::cout<<"EmptyClipboard Failed !!!!!!!!!!"<<std::endl;
                    }
                }

            }
            else
            {
                if(DEBUG_TRACE_OUTPUT_CONSOLE)
                {

                    std::cout<<"it's neither UNICODE NOR TEXT"<<std::endl;
                }
                ::CloseClipboard(); 
                return FALSE;
            }
        }
        else
        {
            hglb = GetClipboardData(CF_UNICODETEXT); 
            if(! ::EmptyClipboard() )
            {
                if(DEBUG_TRACE_OUTPUT_CONSOLE)
                {

                    std::cout<<"EmptyClipboard Failed !!!!!!!!!!"<<std::endl;
                }
            }

        }


        if (hglb != NULL) 
        { 

            LPTSTR lptstr = reinterpret_cast< LPTSTR>( GlobalLock(hglb)); 
            if (lptstr != NULL) 
            { 

                // Call the application-defined ReplaceSelection 
                // function to insert the text and repaint the 
                // window. 

                out_s =  lptstr;
                GlobalUnlock(hglb); 
            }else
            {
                if(DEBUG_TRACE_OUTPUT_CONSOLE)
                {

                    std::cout<<"lpstr = null@@@@@"<<std::endl;
                }
                content = out_s;
                ::CloseClipboard(); 
                return FALSE;
            }


        } 
        else
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {
                std::cout<<"$$$hglb = NULL"<<std::endl;
            }
            content = out_s;
            ::CloseClipboard(); 
            return FALSE;
        }

        if( ! CloseClipboard()) 
        {
            if(DEBUG_TRACE_OUTPUT_CONSOLE)
            {
                std::cout<<"GetClipboardText clipboardOwner hwnd="<<::GetClipboardOwner()<<std::endl;
                std::cout<<"GetClipboardText::CloseClipboard() failed!!!!!"<<std::endl;
            }
        }		

        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {

            std::cout<<"==================EX Begin out_s============="<<std::endl;
            //std::wcout<<out_s<<std::endl;
            std::cout<<"==================EX End out_s============="<<std::endl;
        }
        content = out_s;

        ::CloseClipboard(); 
        return TRUE;

    }




    void  ClearClipboardText(HWND hwnd) 
    {	   
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {
            std::cout<<"CALLED ### ClearClipboardText #### "<<std::endl;
        }
        // FN_LOG_INFO_FUNCTION()
        if (::OpenClipboard(hwnd)) 
        {
            //(void)::EmptyClipboard();
            if(IsClipboardFormatAvailable(CF_UNICODETEXT)) 
            {
                ::EmptyClipboard();
                //SetClipboardData(CF_TEXT, NULL); 
                //SetClipboardData(CF_UNICODETEXT, NULL); 
            }
            ::EmptyClipboard();
            ::CloseClipboard(); 
            //
        }

    }

    BOOL WriteClipData(HWND hwnd, LPCTSTR buff)
    {
        if(DEBUG_TRACE_OUTPUT_CONSOLE)
        {

            std::cout<<"CALLED ### WriteClipData #### "<<std::endl;
        }
        string  astr = FN_T2A(buff);
        wstring wstr = FN_T2W(buff);

        // Open the Clipboard
        if (!::OpenClipboard(hwnd))
            return FALSE;

        ::EmptyClipboard();

        // Allocate a global memory object for the Data
        HGLOBAL hgDataA = GlobalAlloc(GMEM_MOVEABLE, astr.length()+1); 
        //ASSERT(hgDataA != 0);
        if (!hgDataA)
        {
            CloseClipboard();
            return FALSE;
        }

        HGLOBAL hgDataW = GlobalAlloc(GMEM_MOVEABLE, (wstr.length()+1)*sizeof(wchar_t)); 
        //ASSERT(hgDataW != 0);
        if (!hgDataW)
        {
            ::GlobalFree(hgDataA);
            CloseClipboard();
            return FALSE;
        }


        // Lock the handle and copy the text to the buffer. 
        BYTE* pDataA = (BYTE*)GlobalLock(hgDataA); 
        memcpy(pDataA, astr.c_str(), astr.length()+1);
        GlobalUnlock(hgDataA); 

        BYTE* pDataW = (BYTE*)GlobalLock(hgDataW); 
        memcpy(pDataW, wstr.c_str(), (wstr.length() + 1) * 2);
        GlobalUnlock(hgDataW); 

        // Place the handle on the clipboard. 
        SetClipboardData(CF_TEXT, hgDataA); 
        SetClipboardData(CF_UNICODETEXT, hgDataW); 

        // Close Clipboard
        CloseClipboard();

        return TRUE;
    }


}//namespace