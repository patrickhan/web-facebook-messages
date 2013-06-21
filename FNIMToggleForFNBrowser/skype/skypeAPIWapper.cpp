#include "skypeAPIWapper.h"

///class SkypeAPIWapper


#pragma comment(lib, "./skype/skype_dev/FNIM_skype_proxy")
 
extern HMODULE hModule_FNIMToggle ;

HMODULE hModule_FNIM_skype_proxy = 0 ;
bool SkypeAPIWapper::dll_connect()
{
    if(hModule_FNIM_skype_proxy == 0)
    {
        TCHAR tisFile[1024] ={0};
        ::GetModuleFileName(hModule_FNIMToggle, tisFile, 1023U);
        wstring path (tisFile);
        wstring::size_type pos = path.find_last_of(L"\\");
        path.replace(pos+1, path.length()-pos, L"FNIM_skype_proxy.dll");


        hModule_FNIM_skype_proxy = ::LoadLibrary(path.c_str());
    }
    if(hModule_FNIM_skype_proxy!= 0)
    {
        return ::connect_skypePlugin();
    }

    return false ;
}

void SkypeAPIWapper::dll_disconnect()
{
    if(hModule_FNIM_skype_proxy != 0)
    {
        ::quit_skypePlugin();
    }
}

DWORD SkypeAPIWapper::register_SkypeAPI_IFNIMChat(SkypeAPI_IFNIMChat* aSkypeAPI_IFNIMChat, LPCTSTR shakehandMsg)
{
    if(hModule_FNIM_skype_proxy != 0)
    {
        return ::register_SkypeAPI_IFNIMChat(aSkypeAPI_IFNIMChat, shakehandMsg);
    }
    return 0;
}

void SkypeAPIWapper::unregister_SkypeAPI_IFNIMChat(DWORD cookie)
{
    if(hModule_FNIM_skype_proxy != 0)
    {
        ::unregister_SkypeAPI_IFNIMChat(cookie);
    }
}

 