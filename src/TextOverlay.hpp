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

    IDirect3DTexture8* texture;         // +0x00
    float x;                            // +0x04
    float y;                            // +0x08
    unsigned char field00C;             // +0x0C
    unsigned char unknown00D[0x010 - 0x00D];
    float field010;                     // +0x10 box scale
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
