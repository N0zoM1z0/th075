#include <windows.h>
#include <d3d8.h>
#include <stdio.h>

// Physical 56-byte GDI glyph allocation view derived from native caller size and
// the FontSurface constructor/font/rasterizer/destructor accesses. Names and
// the unobserved +0x18 data word remain provisional; no original class identity.
// This is used only for the native ephemeral new/delete lifetime, never embedded.
class GlyphSurfaceF188 {
public:
    HWND window;
    HDC deviceContext;
    HFONT font;
    HGDIOBJ previouslySelectedFont;
    int fontHeight;
    BYTE *glyphBitmap;
    DWORD unresolvedWordAt24;
    DWORD glyphHeight;
    DWORD glyphWidth;
    DWORD glyphPitch;
    BYTE red, green, blue;
    int ascent;
    LONG glyphX;
    LONG glyphY;

    GlyphSurfaceF188(HWND);
    ~GlyphSurfaceF188();
    void ConfigureFont(const char*, int, BYTE, BYTE, BYTE);
    void Rasterize(const char*, void*, int, int, int, int, int, BYTE, char);
};
typedef char GlyphSizeCheckF188[(sizeof(GlyphSurfaceF188) == 56) ? 1 : -1];
extern const char g_OptionsMessage0[];
extern const char g_OptionsMessage1[];
extern const char g_OptionsMessage2[];
extern const char g_OptionsMessage3[];
extern const char g_OptionsMessage4[];
extern const char g_OptionsMessage5[];
extern const char g_OptionsMessage6[];
extern const char g_OptionsFontFamily[];

class OptionsSelectF186 {
public:
    void Apply(unsigned char index);
};
#define TEXTURE (*reinterpret_cast<IDirect3DTexture8**>(reinterpret_cast<BYTE*>(this) + 12))

void OptionsSelectF186::Apply(unsigned char index)
{
    char message[500];
    switch (static_cast<signed char>(index)) {
    case 0: sprintf(message, g_OptionsMessage0); break;
    case 1: sprintf(message, g_OptionsMessage1); break;
    case 2: sprintf(message, g_OptionsMessage2); break;
    case 3: sprintf(message, g_OptionsMessage3); break;
    case 4: sprintf(message, g_OptionsMessage4); break;
    case 5: sprintf(message, g_OptionsMessage5); break;
    case 6: sprintf(message, g_OptionsMessage6); break;
    }
    D3DLOCKED_RECT lock;
    if (TEXTURE->LockRect(0, &lock, 0, 0) == D3D_OK) {
        GlyphSurfaceF188* glyph = new GlyphSurfaceF188(0);
        glyph->ConfigureFont(g_OptionsFontFamily, 16, 255, 255, 255);
        glyph->Rasterize(message, lock.pBits, 1024, 512, 560, 0, 10, 4, 40);
        delete glyph;
        TEXTURE->UnlockRect(0);
    }
}
#undef TEXTURE
