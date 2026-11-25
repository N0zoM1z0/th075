#include "characters/marisa/MarisaFighter.hpp"
#include <string.h>
extern const char g_MarisaNameAt006592A8[] = "marisa";
extern const char g_MarisaTagAt006592B0[] = "01";
MarisaFighter::MarisaFighter()
{
    sequenceTimer=0;
    stageBannerHoldFrames=0;
    field713=1;
    strcpy(name,g_MarisaNameAt006592A8);
    strcpy(tag,g_MarisaTagAt006592B0);
    mainTextureCount=0x299;
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
