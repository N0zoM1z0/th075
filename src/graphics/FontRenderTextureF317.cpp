#include "graphics/FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <new>
#include "graphics/TextOverlay.hpp"
extern const char g_OverlayFontFaceAt006578B0[];
TextOverlay* g_TextRenderer;
void TextOverlay::RenderTextToTexture(const char* text,unsigned char r,unsigned char g,
        unsigned char b,unsigned char size,unsigned char lines,unsigned char preservePreviousLines)
{
    if (preservePreviousLines)
        unfadedLineCount=lineCount;
    else
        unfadedLineCount=0;
    D3DLOCKED_RECT locked;
    if (texture->LockRect(0,&locked,0,0)==D3D_OK) {
        if (static_cast<signed char>(lines)>5) lines=5;
        fontSize=size;
        rasterOffsetX=0.0f;
        rasterOffsetY=6.0f;
        raster=new FontSurface(0);
        raster->ConfigureFont(g_OverlayFontFaceAt006578B0,
            fontSize,r,g,b);
        raster->RasterizeText(text,locked.pBits,0x400,0x100,0x230,
            static_cast<int>(rasterOffsetX),static_cast<int>(rasterOffsetY),4,lines);
        delete raster;
        texture->UnlockRect(0);
        lineCount=lines;
    }
    newTextAlpha=5;
}

void TextOverlay::SetRasterParametersAt004135F0(unsigned char size, float rasterX, float rasterY)
{
    fontSize = size;
    rasterOffsetX = rasterX;
    rasterOffsetY = rasterY;
}
