#include "ui/MusicRoomScene.hpp"
#include "graphics/FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>


extern const char g_MusicMissingTitleAt00657C32[] = "";
extern const char g_MusicTitleFormatAt00657C34[] = "%s";
extern const char g_MusicTitleFontAt00657C38[];
void MusicRoomScene::RenderSelectedTitle(signed char selected)
{
    char message[300];
    if (selected<0 || trackCount<=selected)
        strcpy(message,g_MusicMissingTitleAt00657C32);
    else
        sprintf(message,g_MusicTitleFormatAt00657C34,records[selected].second);
    D3DLOCKED_RECT locked;
    if (canvasC->LockRect(0,&locked,0,0)==D3D_OK) {
        FontSurface *glyph = new FontSurface(0);
        glyph->ConfigureFont(g_MusicTitleFontAt00657C38,16,120,120,255);
        glyph->RasterizeText(message,locked.pBits,512,32,560,0,2,4,40);
        delete glyph;
        canvasC->UnlockRect(0);
    }
}
