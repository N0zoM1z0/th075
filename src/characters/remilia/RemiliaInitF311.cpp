#include "characters/remilia/RemiliaFighter.hpp"
#include <string.h>
extern const char g_RemiliaNameAt00659A34[] = "remilia";
extern const char g_RemiliaTagAt00659A3C[] = "06";
RemiliaFighter::RemiliaFighter()
{
    sequenceTimer=0;
    stageBannerHoldFrames=0;
    queuedMusicDelayFrames=0;
    queuedMusicTrack=0;
    stageBannerEnabled=0;
    field713=1;
    strcpy(name,g_RemiliaNameAt00659A34);
    strcpy(tag,g_RemiliaTagAt00659A3C);
    mainTextureCount=0x2a0;
    overlayTextureCount=11;
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
