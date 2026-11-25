#ifndef TH075_TEXT_OVERLAY_HPP
#define TH075_TEXT_OVERLAY_HPP
#include <windows.h>
#include "graphics/TextureManagerF198.hpp"

struct IDirect3DTexture8;
class FontSurface;

class TextOverlay {
public:
    TextOverlay();
    ~TextOverlay();
    void DrawBox();                                                 // 00412EB0
    void ConfigureText(float positionX, float positionY, unsigned char mode);
    void RenderTextToTexture(const char* text, unsigned char r, unsigned char g,
                             unsigned char b, unsigned char size, unsigned char lines,
                             unsigned char preservePreviousLines);                // 00413460
    void SetRasterParametersAt004135F0(unsigned char size, float rasterX, float rasterY);

    union {
        IDirect3DTexture8* texture;     // +0x00 texture pointer view
        DWORD textureBits;              // raw 32-bit overlay draw handle
    };
    union {
        float x;                        // +0x04
        DWORD xBits;                    // raw float argument view
    };
    union {
        float y;                        // +0x08
        DWORD yBits;                    // raw float argument view
    };
    unsigned char newTextAlpha;         // +0x0C
    unsigned char unknown00D[0x010 - 0x00D];
    union {
        float boxScaleY;                 // +0x10 box scale
        DWORD boxScaleYBits;             // raw vertical-scale word
    };
    unsigned char lineCount;            // +0x14
    signed char unfadedLineCount;       // +0x15
    unsigned char unknown016[0x018 - 0x016];
    FontSurface* raster;                // +0x18
    float rasterOffsetX;                // +0x1C
    float rasterOffsetY;                // +0x20
    unsigned char fontSize;             // +0x24
    unsigned char mode;                 // +0x25
    unsigned char unknown026[2];
    TextureManagerF198 textureManager;  // +0x28
};

typedef char TextOverlaySize[(sizeof(TextOverlay) == 120) ? 1 : -1];

extern TextOverlay* g_TextRenderer;
#endif
