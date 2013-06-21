// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
//
//BOOL APIENTRY DllMain( HMODULE hModule,
//                       DWORD  ul_reason_for_call,
//                       LPVOID lpReserved
//					 )
//{
//	switch (ul_reason_for_call)
//	{
//	case DLL_PROCESS_ATTACH:
//	case DLL_THREAD_ATTACH:
//	case DLL_THREAD_DETACH:
//	case DLL_PROCESS_DETACH:
//		break;
//	}
//	return TRUE;
//}
//


class CATLProject1Module : public ATL::CAtlDllModuleT< CATLProject1Module >
{
public :
	//DECLARE_LIBID(LIBID_ATLProject1Lib)
	//DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECT1, "{D9BDEF77-7754-4C35-8DC8-EC75252BF57E}")
};

extern class CATLProject1Module _AtlModule;


CATLProject1Module _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
