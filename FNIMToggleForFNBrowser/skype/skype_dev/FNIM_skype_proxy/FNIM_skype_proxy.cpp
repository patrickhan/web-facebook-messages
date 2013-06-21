// FNIM_skype_proxy.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "FNIM_skype_proxy.h"
#include "SkypePlugin.h"

//// This is an example of an exported variable
//FNIM_SKYPE_PROXY_API int nFNIM_skype_proxy=0;
//
//// This is an example of an exported function.
//FNIM_SKYPE_PROXY_API int fnFNIM_skype_proxy(void)
//{
//	return 42;
//}
//
//// This is the constructor of a class that has been exported.
//// see FNIM_skype_proxy.h for the class definition
//CFNIM_skype_proxy::CFNIM_skype_proxy()
//{
//	return;
//}
//

CComObject<SkypePlugin> *static_SkypePlugin = NULL;

bool init_skype_plugin()
{
	if(static_SkypePlugin == NULL)
	{
		static_SkypePlugin =  new CComObject<SkypePlugin>(); 
		static_SkypePlugin->AddRef();
	}
	if(static_SkypePlugin != NULL)
	{
		return static_SkypePlugin->init();
	}

  return false;
}

void quit_skype_plugin()
{
	if(static_SkypePlugin!= NULL)
	{
		static_SkypePlugin->quit();
	}
}

FNIM_SKYPE_PROXY_API bool connect_skypePlugin()
{
	
	return init_skype_plugin();;
}

FNIM_SKYPE_PROXY_API void quit_skypePlugin()
{
	quit_skype_plugin();
	return ;
}


FNIM_SKYPE_PROXY_API DWORD register_SkypeAPI_IFNIMChat(SkypeAPI_IFNIMChat* aSkypeAPI_IFNIMChat, LPCTSTR shakehandMsg)
{
	if(aSkypeAPI_IFNIMChat == NULL)
		return 0u;
	if(static_SkypePlugin== NULL)
		return 0u;
	return static_SkypePlugin->register_IFNIMChat(aSkypeAPI_IFNIMChat, shakehandMsg);
}
FNIM_SKYPE_PROXY_API void unregister_SkypeAPI_IFNIMChat(DWORD cookie)
{
	if(cookie == 0)
		return ;
	if(static_SkypePlugin== NULL)
		return ;
	static_SkypePlugin->unregister_IFNIMChat(cookie);
}