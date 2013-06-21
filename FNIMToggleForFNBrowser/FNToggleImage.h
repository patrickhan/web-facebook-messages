#ifndef FNTOGGLEIMAGE_HEADER__
#define FNTOGGLEIMAGE_HEADER__
#include "windows.h"

class FNToggleImageDraw
{
public :

    static void initialize();
    static void quit();
    static void draw(HDC dc, RECT* prc);
};




#endif // FNTOGGLEIMAGE_HEADER__

