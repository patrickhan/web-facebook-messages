// FNIMToggle.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif


HMODULE hModule_FNIMToggle = 0;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    hModule_FNIMToggle = hModule;
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

