// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FNIM_SKYPE_PROXY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FNIM_SKYPE_PROXY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FNIM_SKYPE_PROXY_EXPORTS
#define FNIM_SKYPE_PROXY_API __declspec(dllexport)   
#else
#define FNIM_SKYPE_PROXY_API __declspec(dllimport)   
#endif

//// This class is exported from the FNIM_skype_proxy.dll
//class FNIM_SKYPE_PROXY_API CFNIM_skype_proxy {
//public:
//	CFNIM_skype_proxy(void);
//	// TODO: add your methods here.
//};
//
//extern FNIM_SKYPE_PROXY_API int nFNIM_skype_proxy;
//
//FNIM_SKYPE_PROXY_API int fnFNIM_skype_proxy(void);

#include "SkypeAPI_IFNIMChat.h"
