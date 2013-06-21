#include "stdafx.h"

#include "fnIDGuardHelper.h"

#include <atlbase.h>
#include <atlcom.h>

#include <gdiplus.h>
using namespace Gdiplus;

#include "GdiplusHelper.h"

#include <delayimp.h>

//
// Exception information
//
#define FACILITY_VISUALCPP  ((LONG)0x6d)
#define VcppException(sev,err)  ((sev) | (FACILITY_VISUALCPP<<16) | err)


ExternC
PfnDliHook   __pfnDliNotifyHook2;

// This is the failure hook, dliNotify = {dliFailLoadLib|dliFailGetProc}
ExternC
PfnDliHook   __pfnDliFailureHook2;


ExternC
BOOL WINAPI
__FUnloadDelayLoadedDLL2(LPCSTR szDll);

// structure definitions for the list of unload records
typedef struct UnloadInfo * PUnloadInfo;
typedef struct UnloadInfo {
    PUnloadInfo     puiNext;
    PCImgDelayDescr pidd;
    } UnloadInfo;

// from delayhlp.cpp
// the default delay load helper places the unloadinfo records in the 
// list headed by the following pointer.
ExternC
PUnloadInfo __puiHead;

/*
If the notification is dliFailLoadLib, the hook function can return: 
0, if it cannot handle the failure.
An HMODULE, if the failure hook fixed the problem and loaded the library itself.

If the notification is dliFailGetProc, the hook function can return: 
0, if it cannot handle the failure.
A valid proc address (import function address), if the failure hook succeeded in getting the address itself.

*/
FARPROC WINAPI  myfnDliFailureHook2( unsigned        dliNotify,    PDelayLoadInfo  pdli    )
{
    
    if(dliFailLoadLib == dliNotify)
    {
        wstring path = fnIDGuardHelper:: getFNXULPath().c_str();
         path += L"gdiplus.dll";
         return (FARPROC)::LoadLibrary(path.c_str() );
    }
    return 0;
}

BOOL GdiplusHelper::initialize()
{
    InterlockedIncrement(&refCount_ );
    __pfnDliFailureHook2 = myfnDliFailureHook2;

    if(gdiplusToken_ == 0UL)
    {
        GdiplusStartupInput gdiplusStartupInput;

        GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput, NULL);
    }
    return gdiplusToken_ != 0UL;
}
void GdiplusHelper::close()
{  
    InterlockedDecrement(&refCount_ );
    if(refCount_  == 0L)
    {
        if(gdiplusToken_ != 0UL)
            GdiplusShutdown(gdiplusToken_); 
        gdiplusToken_ = 0UL;
    }

}

GdiplusHelper::~GdiplusHelper()
{
    close();
}