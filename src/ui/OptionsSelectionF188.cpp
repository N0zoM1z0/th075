#include "graphics/FontSurface.hpp"
#include "ui/OptionsScene.hpp"
#include <windows.h>
#include <d3d8.h>
#include <stdio.h>

extern const char g_OptionsMessage0[];
extern const char g_OptionsMessage1[];
extern const char g_OptionsMessage2[];
extern const char g_OptionsMessage3[];
extern const char g_OptionsMessage4[];
extern const char g_OptionsMessage5[];
extern const char g_OptionsMessage6[];
extern const char g_OptionsFontFamily[];


void OptionsScene::Apply(unsigned char index)
{
    char message[500];
    switch (static_cast<signed char>(index)) {
    case 0: sprintf(message, g_OptionsMessage0); break;
    case 1: sprintf(message, g_OptionsMessage1); break;
    case 2: sprintf(message, g_OptionsMessage2); break;
    case 3: sprintf(message, g_OptionsMessage3); break;
    case 4: sprintf(message, g_OptionsMessage4); break;
    case 5: sprintf(message, g_OptionsMessage5); break;
    case 6: sprintf(message, g_OptionsMessage6); break;
    }
    D3DLOCKED_RECT lock;
    if (canvas->LockRect(0, &lock, 0, 0) == D3D_OK) {
        FontSurface* glyph = new FontSurface(0);
        glyph->ConfigureFont(g_OptionsFontFamily, 16, 255, 255, 255);
        glyph->RasterizeText(message, lock.pBits, 1024, 512, 560, 0, 10, 4, 40);
        delete glyph;
        canvas->UnlockRect(0);
    }
}
