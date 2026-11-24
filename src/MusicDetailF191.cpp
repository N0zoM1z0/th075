#include "MusicRoomScene.hpp"
#include "FontSurface.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <string.h>

// Single-use, 56-byte allocation view, established by the independent
// constructor/deleter calls and native allocation length; full original
// class identity and the +0x18 word's purpose remain unknown.

extern const char g_MusicUnknownTrackAt00657C46[];
extern const char g_MusicUnknownTitleAt00657C56[];
extern const char g_MusicNumberedDetailsAt00657C58[];
extern const char g_MusicSelectedFontAt00657C48[];
extern const char g_MusicNumberedFontAt00657C68[];
void MusicRoomScene::RenderSelectedDetails(signed char selected)
{
    char message[2000];
    if (selected < 0 || trackCount <= selected)
        strcpy(message, g_MusicUnknownTrackAt00657C46);
    else
        strcpy(message, records[selected].third);

    D3DLOCKED_RECT locked;
    if (canvasA->LockRect(0, &locked, 0, 0) == D3D_OK) {
        FontSurface *glyph = new FontSurface(0);
        glyph->ConfigureFont(g_MusicSelectedFontAt00657C48, 16, 120, 120, 255);
        glyph->RasterizeText(message, locked.pBits, 512, 512, 528, 0, 2, 4, 40);
        delete glyph;
        canvasA->UnlockRect(0);
    }

    if (selected < 0 || trackCount <= selected)
        strcpy(message, g_MusicUnknownTitleAt00657C56);
    else
        sprintf(message, g_MusicNumberedDetailsAt00657C58,
                selected+1, records[selected].second, records[selected].first);

    if (canvasD->LockRect(0, &locked, 0, 0) == D3D_OK) {
        FontSurface *glyph = new FontSurface(0);
        glyph->ConfigureFont(g_MusicNumberedFontAt00657C68, 16, 120, 120, 255);
        glyph->RasterizeText(message, locked.pBits, 512, 32, 528, 0, 2, 4, 40);
        delete glyph;
        canvasD->UnlockRect(0);
    }
}
