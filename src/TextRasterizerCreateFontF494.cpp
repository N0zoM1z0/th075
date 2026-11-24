#include "FontSurface.hpp"

// CP932 name of the GDI system font.
#define MS_GOTHIC "\x82\x6c\x82\x72 \x83\x53\x83\x56\x83\x62\x83\x4e"
extern const char g_OverlayFontFaceAt006578B0[] = MS_GOTHIC;
extern const char g_MusicListFontAt00657C24[] = MS_GOTHIC;
extern const char g_MusicTitleFontAt00657C38[] = MS_GOTHIC;
extern const char g_MusicSelectedFontAt00657C48[] = MS_GOTHIC;
extern const char g_MusicNumberedFontAt00657C68[] = MS_GOTHIC;
extern const char g_OptionsFontFamily[] = MS_GOTHIC;
extern const char g_RecordFontAt00658110[] = MS_GOTHIC;
extern const char g_ResultCounterFontAt00658140[] = MS_GOTHIC;
#undef MS_GOTHIC

void FontSurface::ConfigureFont(const char* faceName,int height,unsigned char optA,unsigned char optB,unsigned char optC){
 fontHeight=height;
 red=optA;
 green=optB;
 blue=optC;
 font=::CreateFontA(height,0,0,0,400,0,0,0,0x80,4,0,2,0x31,faceName);
}
