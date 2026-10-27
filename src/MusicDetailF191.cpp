#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>

// Single-use, 56-byte allocation view, established by the independent
// constructor/deleter calls and native allocation length; full original
// class identity and the +0x18 word's purpose remain unknown.
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
    LONG glyphX, glyphY;
    GlyphSurfaceF188(HWND);
    ~GlyphSurfaceF188();
    void ConfigureFont(const char*, int, BYTE, BYTE, BYTE);
    void Rasterize(const char*, void*, int, int, int, int, int, BYTE, char);
};
typedef char GlyphSizeCheckF191[(sizeof(GlyphSurfaceF188)==56)?1:-1];

extern const char g_MusicUnknownTrackAt00657C46[];
extern const char g_MusicUnknownTitleAt00657C56[];
extern const char g_MusicNumberedDetailsAt00657C58[];
extern const char g_MusicSelectedFontAt00657C48[];
extern const char g_MusicNumberedFontAt00657C68[];
class MusicDetailsF191 {
public:
    void RenderSelectedDetails(signed char selected);
};
#define AT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
#define TRACK_FIELD(type, base) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (base) + selected * 16))

void MusicDetailsF191::RenderSelectedDetails(signed char selected)
{
    char message[2000];
    if (selected < 0 || AT(signed char, 0x3DC) <= selected)
        strcpy(message, g_MusicUnknownTrackAt00657C46);
    else
        strcpy(message, TRACK_FIELD(const char*, 0x28));

    D3DLOCKED_RECT locked;
    if (AT(IDirect3DTexture8*, 0x0C)->LockRect(0, &locked, 0, 0) == D3D_OK) {
        GlyphSurfaceF188 *glyph = new GlyphSurfaceF188(0);
        glyph->ConfigureFont(g_MusicSelectedFontAt00657C48, 16, 120, 120, 255);
        glyph->Rasterize(message, locked.pBits, 512, 512, 528, 0, 2, 4, 40);
        delete glyph;
        AT(IDirect3DTexture8*, 0x0C)->UnlockRect(0);
    }

    if (selected < 0 || AT(signed char, 0x3DC) <= selected)
        strcpy(message, g_MusicUnknownTitleAt00657C56);
    else
        sprintf(message, g_MusicNumberedDetailsAt00657C58,
                selected+1, TRACK_FIELD(const char*, 0x24), TRACK_FIELD(const char*, 0x20));

    if (AT(IDirect3DTexture8*, 0x18)->LockRect(0, &locked, 0, 0) == D3D_OK) {
        GlyphSurfaceF188 *glyph = new GlyphSurfaceF188(0);
        glyph->ConfigureFont(g_MusicNumberedFontAt00657C68, 16, 120, 120, 255);
        glyph->Rasterize(message, locked.pBits, 512, 32, 528, 0, 2, 4, 40);
        delete glyph;
        AT(IDirect3DTexture8*, 0x18)->UnlockRect(0);
    }
}
#undef AT
#undef TRACK_FIELD
