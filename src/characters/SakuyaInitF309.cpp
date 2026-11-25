#include "characters/SakuyaFighter.hpp"
#include <string.h>
extern const char g_SakuyaNameAt0065949C[] = "sakuya";
extern const char g_SakuyaTagAt006594A4[] = "02";
SakuyaFighter::SakuyaFighter()
{
    sequenceTimer=0;
    stageBannerHoldFrames=0;
    field713=1;
    strcpy(name,g_SakuyaNameAt0065949C);
    strcpy(tag,g_SakuyaTagAt006594A4);
    field478=0x27d;
    field532=10;
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
