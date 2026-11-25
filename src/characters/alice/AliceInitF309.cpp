#include "characters/alice/AliceFighter.hpp"
#include <string.h>
extern const char g_AliceNameAt006595F8[] = "alice";
extern const char g_AliceTagAt00659600[] = "03";
AliceFighter::AliceFighter()
{
    sequenceTimer=0;
    stageBannerHoldFrames=0;
    field713=1;
    strcpy(name,g_AliceNameAt006595F8);
    strcpy(tag,g_AliceTagAt00659600);
    mainTextureCount=0x2ad;
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
