#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>

class GlyphSurfaceF238 {
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
    GlyphSurfaceF238(HWND);
    ~GlyphSurfaceF238();
    void ConfigureFont(const char*, int, BYTE, BYTE, BYTE);
    void Rasterize(const char*, void*, int, int, int, int, int, BYTE, char);
};
typedef char GlyphSizeCheckF238[(sizeof(GlyphSurfaceF238)==56)?1:-1];

// This side-only view represents observed calls and physical fields, not a
// complete original game scene or named original class layout.
class ResultProgressF238 {
public:
    void Select(unsigned char a, unsigned char b);
    int* Counters();
};
extern ResultProgressF238 g_ResultProgressAt006718F8;
extern const char g_ResultCounterEmptyAt0065811E[];
extern const char g_ResultCounterFormat0At00658120[];
extern const char g_ResultCounterFormat1At00658128[];
extern const char g_ResultCounterFormat2At00658130[];
extern const char g_ResultCounterFormat3At00658138[];
extern const char g_ResultCounterFontAt00658140[];
class ResultCounterSceneF238 {public: void BuildCounterPage();};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ResultCounterSceneF238::BuildCounterPage()
{
    g_ResultProgressAt006718F8.Select(FIELD(unsigned char,0x1c3),FIELD(unsigned char,0x1c4));
    FIELD(int*,0x14)=g_ResultProgressAt006718F8.Counters();
    D3DLOCKED_RECT locked;
    {
        char line[200];
        {
            char message[500];
    strcpy(message,g_ResultCounterEmptyAt0065811E);
    sprintf(line,g_ResultCounterFormat0At00658120,FIELD(int*,0x14)[0]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat1At00658128,FIELD(int*,0x14)[1]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat2At00658130,FIELD(int*,0x14)[2]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat3At00658138,FIELD(int*,0x14)[3]);
    strcat(message,line);
    if (FIELD(IDirect3DTexture8*,0x10)->LockRect(0,&locked,0,0)==D3D_OK) {
        GlyphSurfaceF238 *glyph=new GlyphSurfaceF238(0);
        glyph->ConfigureFont(g_ResultCounterFontAt00658140,16,255,255,255);
        glyph->Rasterize(message,locked.pBits,1024,512,560,0,8,4,40);
        delete glyph;
        FIELD(IDirect3DTexture8*,0x10)->UnlockRect(0);
    }
        }
    }
}
#undef FIELD
