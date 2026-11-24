#pragma once

#include <windows.h>

class FontSurface {
    HWND window;
    HDC deviceContext;
    HFONT font;
    HGDIOBJ previouslySelectedFont;
    int fontHeight;
    BYTE* glyphBitmap;
    DWORD unknown018;
    int glyphHeight;
    int glyphWidth;
    int glyphPitch;
    BYTE red, green, blue;
    LONG ascent;
    LONG glyphX;
    LONG glyphY;

public:
    explicit FontSurface(HWND window);
    ~FontSurface();
    void ConfigureFont(const char* faceName, int height, BYTE red, BYTE green, BYTE blue);
    void RasterizeText(const char* text, void* pixels, int width, int height,
        int maxWidth, int spaceX, int spaceY, BYTE depth, signed char lines);

private:
    void SelectFont();
    void ReleaseRasterResources();
    void LoadGlyphOutline(UINT codepoint);
    BYTE DecodeUnit(const char* input, int* output);
    BYTE DecodeHexDigit(char digit);
    bool IsDoubleByte(char lead);
};

typedef char FontSurfaceSize[(sizeof(FontSurface) == 0x38) ? 1 : -1];
