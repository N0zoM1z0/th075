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
class ResultCounterSceneF238 {public: void BuildCounterPage();public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x010 - 0x000];
    IDirect3DTexture8* field010;
    int* field014;
    unsigned char unknown018[0x1C3 - 0x018];
    unsigned char field1C3;
    unsigned char field1C4;
};
void ResultCounterSceneF238::BuildCounterPage()
{
    g_ResultProgressAt006718F8.Select(field1C3,field1C4);
    field014=g_ResultProgressAt006718F8.Counters();
    D3DLOCKED_RECT locked;
    {
        char line[200];
        {
            char message[500];
    strcpy(message,g_ResultCounterEmptyAt0065811E);
    sprintf(line,g_ResultCounterFormat0At00658120,field014[0]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat1At00658128,field014[1]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat2At00658130,field014[2]);
    strcat(message,line);
    sprintf(line,g_ResultCounterFormat3At00658138,field014[3]);
    strcat(message,line);
    if (field010->LockRect(0,&locked,0,0)==D3D_OK) {
        GlyphSurfaceF238 *glyph=new GlyphSurfaceF238(0);
        glyph->ConfigureFont(g_ResultCounterFontAt00658140,16,255,255,255);
        glyph->Rasterize(message,locked.pBits,1024,512,560,0,8,4,40);
        delete glyph;
        field010->UnlockRect(0);
    }
        }
    }
}
