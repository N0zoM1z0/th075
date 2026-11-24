#include "FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>


// Observed independent PE string addresses, including the literal 2-byte
// escape sequence used as the line suffix. No complete scene class embedded.
extern const char g_MusicListEmptyAt00657C0A[];
extern const char g_MusicListHiddenAt00657C0C[];
extern const char g_MusicListBreakAt00657C20[];
extern const char g_MusicListFontAt00657C24[];
class MusicTrackProgressF235 {public: unsigned char IsUnlocked(int track);};
extern MusicTrackProgressF235 g_MusicProgressAt006718F8;
class MusicListRenderF235 {public: void RenderTrackCatalogText();public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x010 - 0x000];
    IDirect3DTexture8* field010;
    unsigned char unknown014[0x3DC - 0x014];
    signed char field3DC;
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void MusicListRenderF235::RenderTrackCatalogText()
{
    char message[2000];
    strcpy(message,g_MusicListEmptyAt00657C0A);
    for(int i=0;i<field3DC;++i) {
        if (g_MusicProgressAt006718F8.IsUnlocked(
                FIELD(signed char,0x1c + i*16)+100)) {
            strcat(message,FIELD(const char*,0x24 + i*16));
        } else {
            strcat(message,g_MusicListHiddenAt00657C0C);
        }
        strcat(message,g_MusicListBreakAt00657C20);
    }
    D3DLOCKED_RECT locked;
    if (field010->LockRect(0,&locked,0,0)==D3D_OK) {
        FontSurface *glyph = new FontSurface(0);
        glyph->ConfigureFont(g_MusicListFontAt00657C24,16,120,120,255);
        glyph->RasterizeText(message,locked.pBits,1024,1024,560,0,2,4,40);
        delete glyph;
        field010->UnlockRect(0);
    }
}
#undef FIELD
