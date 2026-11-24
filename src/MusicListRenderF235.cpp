#include "MusicRoomScene.hpp"
#include "GameProgress.hpp"
#include "FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>


// Observed independent PE string addresses, including the literal 2-byte
// escape sequence used as the line suffix. No complete scene class embedded.
extern const char g_MusicListEmptyAt00657C0A[] = "";
extern const char g_MusicListHiddenAt00657C0C[] = "\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48";
extern const char g_MusicListBreakAt00657C20[];
extern const char g_MusicListFontAt00657C24[];
void MusicRoomScene::RenderTrackCatalogText()
{
    char message[2000];
    strcpy(message,g_MusicListEmptyAt00657C0A);
    for(int i=0;i<trackCount;++i) {
        if (g_GameProgress.TestUnlockBit(
                records[i].counter+100)) {
            strcat(message,records[i].second);
        } else {
            strcat(message,g_MusicListHiddenAt00657C0C);
        }
        strcat(message,g_MusicListBreakAt00657C20);
    }
    D3DLOCKED_RECT locked;
    if (canvasB->LockRect(0,&locked,0,0)==D3D_OK) {
        FontSurface *glyph = new FontSurface(0);
        glyph->ConfigureFont(g_MusicListFontAt00657C24,16,120,120,255);
        glyph->RasterizeText(message,locked.pBits,1024,1024,560,0,2,4,40);
        delete glyph;
        canvasB->UnlockRect(0);
    }
}
