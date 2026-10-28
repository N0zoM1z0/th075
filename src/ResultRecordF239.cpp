#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>

class GlyphSurfaceF239 {
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
    GlyphSurfaceF239(HWND);
    ~GlyphSurfaceF239();
    void ConfigureFont(const char*, int, BYTE, BYTE, BYTE);
    void Rasterize(const char*, void*, int, int, int, int, int, BYTE, char);
};
typedef char GlyphSizeCheckF239[(sizeof(GlyphSurfaceF239)==56)?1:-1];

// Borrowed original record selection and deque access interfaces. No full
// nominal class/allocator ownership layout is reconstructed in this source.
class ResultRecordProgressF239 {public:
    void Select(unsigned char first, unsigned char second);
    void* GetSelectedRecordAddress();
};
extern ResultRecordProgressF239 g_RecordProgressAt006718F8;
class ResultNameDequeF239 {public:
    int Size();
    char** Entry(int index);
};
extern const char g_RecordEmptyAt006580B1[];
extern const char g_RecordEmptyNameAt006580B4[];
extern const char g_RecordMissingFormatAt006580D8[];
extern const char g_RecordFullFormatAt006580F4[];
extern const char g_RecordFontAt00658110[];
class ResultRecordSceneF239 {public: void BuildRecordPage();};
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(type,offset) (*reinterpret_cast<type*>(RAW+(offset)))
#define META(index,offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x14))+(offset)+2*(index)))
#define NAMES (*reinterpret_cast<ResultNameDequeF239*>(RAW+0x18))
void ResultRecordSceneF239::BuildRecordPage()
{
    g_RecordProgressAt006718F8.Select(FIELD(unsigned char,0x1c3),0);
    FIELD(void*,0x14)=g_RecordProgressAt006718F8.GetSelectedRecordAddress();
    D3DLOCKED_RECT locked;
    {
        char line[200];
        {
            char message[2000];
            strcpy(message,g_RecordEmptyAt006580B1);
            for (int i=FIELD(short,0x1bc)*10;
                 i<FIELD(short,0x1bc)*10+10 && i<NAMES.Size(); ++i) {
                if (META(i,0x394)==0)
                    sprintf(line,g_RecordMissingFormatAt006580D8,i+1,g_RecordEmptyNameAt006580B4,0,0);
                else
                    sprintf(line,g_RecordFullFormatAt006580F4,i+1,*NAMES.Entry(i),
                            static_cast<unsigned int>(META(i,0x268)),static_cast<unsigned int>(META(i,0x394)));
                strcat(message,line);
            }
            if (FIELD(IDirect3DTexture8*,0x10)->LockRect(0,&locked,0,0)==D3D_OK) {
                GlyphSurfaceF239* glyph=new GlyphSurfaceF239(0);
                glyph->ConfigureFont(g_RecordFontAt00658110,16,120,120,255);
                glyph->Rasterize(message,locked.pBits,1024,512,640,0,16,4,40);
                delete glyph;
                FIELD(IDirect3DTexture8*,0x10)->UnlockRect(0);
            }
        }
    }
}
#undef NAMES
#undef META
#undef FIELD
#undef RAW
