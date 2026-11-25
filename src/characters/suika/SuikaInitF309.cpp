#include "characters/suika/SuikaFighter.hpp"
#include <string.h>
extern const char g_SuikaNameAt00659E24[] = "suika";
extern const char g_SuikaTagAt00659E2C[] = "09";
SuikaFighter::SuikaFighter()
{
    fieldF28=0;
    suikaStageBannerHoldFrames=0;
    field713=1;
    strcpy(name,g_SuikaNameAt00659E24);
    strcpy(tag,g_SuikaTagAt00659E2C);
    mainTextureCount=0x2a6;
    overlayTextureCount=10;
    field06C=-10.0f;
    field705[0]=4;
    field705[1]=4;
    field705[2]=4;
    field705[3]=4;
    field705[4]=4;
    field705[5]=4;
    field705[6]=4;
    field705[7]=1;
    field705[8]=1;
    field705[9]=3;
}
