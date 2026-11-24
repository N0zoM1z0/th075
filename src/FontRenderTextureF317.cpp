#include "FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <new>
#include "TextOverlay.hpp"
extern const char g_OverlayFontFaceAt006578B0[];
TextOverlay* g_TextRenderer;
void TextOverlay::RenderTextToTexture(const char* text,unsigned char r,unsigned char g,
        unsigned char b,unsigned char color,unsigned char depth,unsigned char restore)
{
    if (restore)
        field015=field014;
    else
        field015=0;
    D3DLOCKED_RECT locked;
    if (texture->LockRect(0,&locked,0,0)==D3D_OK) {
        if (static_cast<signed char>(depth)>5) depth=5;
        field024=color;
        field01C=0.0f;
        field020=6.0f;
        raster=new FontSurface(0);
        raster->ConfigureFont(g_OverlayFontFaceAt006578B0,
            field024,r,g,b);
        raster->RasterizeText(text,locked.pBits,0x400,0x100,0x230,
            static_cast<int>(field01C),static_cast<int>(field020),4,depth);
        delete raster;
        texture->UnlockRect(0);
        field014=depth;
    }
    field00C=5;
}

void TextOverlay::SetRasterParametersAt004135F0(unsigned char color, float rasterX, float rasterY)
{
    field024 = color;
    field01C = rasterX;
    field020 = rasterY;
}
