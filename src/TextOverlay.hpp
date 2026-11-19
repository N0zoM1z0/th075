#ifndef TH075_TEXT_OVERLAY_HPP
#define TH075_TEXT_OVERLAY_HPP
#include <windows.h>

struct IDirect3DTexture8;
class FontGlyphRasterF317;

// The text overlay that menus and the battle notices draw through
// (g_TextRenderer). Callers still use their own declarations of these three
// methods, whose parameter types the original call sites need.
class TextOverlay {
public:
    void DrawBox();                                                 // 00412EB0
    void ConfigureText(DWORD xBits, DWORD yBits, unsigned char mode);  // 00413420 x and y arrive as raw float bits
    void RenderTextToTexture(const char* text, unsigned char r, unsigned char g,
                             unsigned char b, unsigned char color, unsigned char depth,
                             unsigned char restore);                // 00413460

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
    unsigned char field00C;             // +0x0C
    unsigned char unknown00D[0x010 - 0x00D];
    union {
        float field010;                 // +0x10 box scale
        DWORD field010Bits;             // raw transform scale word
    };
    unsigned char field014;             // +0x14
    signed char field015;               // +0x15
    unsigned char unknown016[0x018 - 0x016];
    FontGlyphRasterF317* raster;        // +0x18
    float field01C;                     // +0x1C
    float field020;                     // +0x20
    unsigned char field024;             // +0x24
    unsigned char mode;                 // +0x25
};
#endif
