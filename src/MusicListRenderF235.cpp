#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>

class GlyphSurfaceF235 {
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
    GlyphSurfaceF235(HWND);
    ~GlyphSurfaceF235();
    void ConfigureFont(const char*, int, BYTE, BYTE, BYTE);
    void Rasterize(const char*, void*, int, int, int, int, int, BYTE, char);
};
typedef char GlyphSizeCheckF235[(sizeof(GlyphSurfaceF235)==56)?1:-1];

// Observed independent PE string addresses, including the literal 2-byte
// escape sequence used as the line suffix. No complete scene class embedded.
extern const char g_MusicListEmptyAt00657C0A[];
extern const char g_MusicListHiddenAt00657C0C[];
extern const char g_MusicListBreakAt00657C20[];
extern const char g_MusicListFontAt00657C24[];
class MusicTrackProgressF235 {public: unsigned char IsUnlocked(int track);};
extern MusicTrackProgressF235 g_MusicProgressAt006718F8;
class MusicListRenderF235 {public: void RenderTrackCatalogText();};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void MusicListRenderF235::RenderTrackCatalogText()
{
    char message[2000];
    strcpy(message,g_MusicListEmptyAt00657C0A);
    for(int i=0;i<FIELD(signed char,0x3dc);++i) {
        if (g_MusicProgressAt006718F8.IsUnlocked(
                FIELD(signed char,0x1c + i*16)+100)) {
            strcat(message,FIELD(const char*,0x24 + i*16));
        } else {
            strcat(message,g_MusicListHiddenAt00657C0C);
        }
        strcat(message,g_MusicListBreakAt00657C20);
    }
    D3DLOCKED_RECT locked;
    if (FIELD(IDirect3DTexture8*,0x10)->LockRect(0,&locked,0,0)==D3D_OK) {
        GlyphSurfaceF235 *glyph = new GlyphSurfaceF235(0);
        glyph->ConfigureFont(g_MusicListFontAt00657C24,16,120,120,255);
        glyph->Rasterize(message,locked.pBits,1024,1024,560,0,2,4,40);
        delete glyph;
        FIELD(IDirect3DTexture8*,0x10)->UnlockRect(0);
    }
}
#undef FIELD
