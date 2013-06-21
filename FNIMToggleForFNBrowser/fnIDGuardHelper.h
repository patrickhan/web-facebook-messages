#ifndef FNIDGUARDHELPER_HEADER__
#define FNIDGUARDHELPER_HEADER__



//lint +libh(../../../include/common/global.h)
// or #include <../../../include/common/global.h>

#pragma warning(disable:4018) //there are some warning C4018: '<' : signed/unsigned mismatch, I mask them in my project
#pragma warning(disable:4996) //workspace\fn360\src\include\common\memprotect/basic_fnstring.h(323) : warning C4996: 'wcstombs' was declared deprecated
#include "../../../include/common/global.h"
#pragma warning( default :4018) //automatically excluding xxx
#pragma warning( default :4996) //automatically excluding xxx

#ifdef _DEBUG

#pragma comment(lib,"..\\..\\buildlib\\debug\\libUtils.lib" )

//libUtils.lib is a release lib , to close the link  warning LNK4098: defaultlib 'msvcrt.lib' conflicts
// add the following line 
//#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")

#else
#pragma comment(lib,"..\\..\\buildlib\\release\\libUtils.lib" )

#endif 

class fnIDGuardHelper
{
public:
    static fnstring getFNIDGuardImagesPath()
    {
        /*const FNGlobalConfig &Config = FNGlobalConfig::GetFNGlobalConfig();
        fnstring fnIDGuardImagesPath = Config.GetEnvPath();
        if(fnIDGuardImagesPath .length() > 0)
        {
            if(fnIDGuardImagesPath.length() > 0)
            {
                wchar_t endChar = fnIDGuardImagesPath .at(fnIDGuardImagesPath.length() -1);

                if( endChar != L'\\')
                {
                    fnIDGuardImagesPath +=  L"\\";
                }
               fnIDGuardImagesPath += L"chrome\\content\\images\\";
            }
        }*/
         fnstring xulrunnerPath = getFNXULPath();
         xulrunnerPath  += L"images\\";
        return xulrunnerPath;
    }

    static fnstring getFNIDGuardPath()
    {
        const FNGlobalConfig &Config = FNGlobalConfig::GetFNGlobalConfig();
        fnstring fn_IniPath = Config.GetIniPath();
        if(fn_IniPath .length() > 0)
        {
            if(fn_IniPath.length() > 0)
            {
                wchar_t endChar = fn_IniPath .at(fn_IniPath.length() -1);

                if( endChar != L'\\')
                {
                    fn_IniPath +=  L"\\";
                }
            }
        }
        return fn_IniPath;
    }
    static fnstring getFNXULPath()
    {
        const FNGlobalConfig &Config = FNGlobalConfig::GetFNGlobalConfig();
        fnstring fn_xul_path = Config.GetEnvPath();
        if(fn_xul_path .length() > 0)
        {
            if(fn_xul_path.length() > 0)
            {
                wchar_t endChar = fn_xul_path .at(fn_xul_path.length() -1);

                if( endChar != L'\\')
                {
                    fn_xul_path +=  L"\\";
                }
            }
        }
        return fn_xul_path;
    }
};

#endif //FNIDGUARDHELPER_HEADER__

