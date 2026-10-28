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

// The target's missing-title string and explicit sprintf format have
// distinct native references; the source does not manufacture title bytes.
extern const char g_MusicMissingTitleAt00657C32[];
extern const char g_MusicTitleFormatAt00657C34[];
extern const char g_MusicTitleFontAt00657C38[];
class MusicTitleRenderF235 {public: void RenderSelectedTitle(signed char selected);};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define RECORD(type,off) FIELD(type,(off)+selected*16)
void MusicTitleRenderF235::RenderSelectedTitle(signed char selected)
{
    char message[300];
    if (selected<0 || FIELD(signed char,0x3dc)<=selected)
        strcpy(message,g_MusicMissingTitleAt00657C32);
    else
        sprintf(message,g_MusicTitleFormatAt00657C34,RECORD(const char*,0x24));
    D3DLOCKED_RECT locked;
    if (FIELD(IDirect3DTexture8*,0x14)->LockRect(0,&locked,0,0)==D3D_OK) {
        GlyphSurfaceF235 *glyph = new GlyphSurfaceF235(0);
        glyph->ConfigureFont(g_MusicTitleFontAt00657C38,16,120,120,255);
        glyph->Rasterize(message,locked.pBits,512,32,560,0,2,4,40);
        delete glyph;
        FIELD(IDirect3DTexture8*,0x14)->UnlockRect(0);
    }
}
#undef RECORD
#undef FIELD
