#ifndef __GDIPLUSHELPER_HEADER__
#define __GDIPLUSHELPER_HEADER__

class GdiplusHelper
{
public:
    GdiplusHelper()
        :gdiplusToken_(0UL),
        refCount_(0L)
    {
    }
    ~GdiplusHelper();

    BOOL initialize();
    void close();
private:
 ULONG_PTR gdiplusToken_;
 volatile LONG refCount_;
};
#endif//__GDIPLUSHELPER_HEADER__

