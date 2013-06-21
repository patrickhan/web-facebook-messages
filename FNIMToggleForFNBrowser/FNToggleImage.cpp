#include "FNToggleImage.h"

#include "Shlwapi.h"
#include "fnIDGuardHelper.h"

#include <gdiplus.h>
using namespace Gdiplus;
#include "GdiplusHelper.h"

#include <xstring> 

#include <atlcomcli.h>

class FNToggleImage 
{
public :

    FNToggleImage ();
    ~FNToggleImage ();
    //const std::wstring & getImageFilePath() const;

    void draw(HDC dc, RECT* prc);
    void initialize();
    void quit();
private:
    CComPtr<IStream> streamImage_;
    //std::wstring iamge_path_;

    BOOL initialied_;
};



const WCHAR FN_TOGGLE_BUTTON_IMAGE_FNEDITOR_ON[]  = L"fntoggleopen.png";//L"fntoggleopen.gif";


FNToggleImage ::FNToggleImage (): initialied_(FALSE)
{

}

FNToggleImage ::~FNToggleImage ()
{

}

//const wstring & FNToggleImage::getImageFilePath() const
//{
//    return iamge_path_;
//}


void FNToggleImage ::initialize()
{
    if(initialied_ )
    {
        return ;
    }

    fnstring iamge_path_ = fnIDGuardHelper::getFNIDGuardImagesPath();
    iamge_path_ += FN_TOGGLE_BUTTON_IMAGE_FNEDITOR_ON;

    streamImage_ = NULL;
    
    if(!streamImage_)
    {
        SHCreateStreamOnFile(iamge_path_.c_str(),    STGM_READ,    &streamImage_);
    }
    CSingleton<GdiplusHelper>::GetInst().initialize();

    initialied_ = TRUE;
}

void FNToggleImage ::quit()
{
    CSingleton<GdiplusHelper>::GetInst().close();
    streamImage_.Release();
}

 
void FNToggleImage ::draw(HDC hdc, RECT* prc)
{
    if(streamImage_ && prc != NULL)
    {
        Gdiplus::Image aImage(streamImage_);
        Graphics aGraphics(hdc);
        Gdiplus::Rect aRect(prc->left, prc->top, prc->right-prc->left,prc->bottom-prc->top);

        Gdiplus::SolidBrush aBrush(Gdiplus::Color(59,59,59) ); //(Gdiplus::Color(FN_WINDOW_BACKGROUND_COLOR ) );
        aGraphics.FillRectangle( static_cast< Gdiplus::Brush*>(&aBrush), aRect);
        aGraphics.DrawImage(&aImage, aRect);
    }
}

///FNToggleImageDraw

void FNToggleImageDraw::draw(HDC dc, RECT* prc)
{
    CSingleton<FNToggleImage>::GetInst().initialize();
    CSingleton<FNToggleImage>::GetInst().draw(  dc,  prc);
}

void FNToggleImageDraw::initialize()
{
       CSingleton<FNToggleImage>::GetInst().initialize();
}
void FNToggleImageDraw::quit()
{
       CSingleton<FNToggleImage>::GetInst().quit();
}
 