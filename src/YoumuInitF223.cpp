#include "YoumuFighter.hpp"
#include <string.h>
// The native +0xFEC list is constructed as the final derived member.
extern const char g_YoumuNameAt006598C0[] = "youmu";
extern const char g_YoumuTagAt006598C8[];
YoumuFighter::YoumuFighter()
{
    sequenceTimer=0;
    fieldEFE=0;
    field713=1;
    strcpy(name,g_YoumuNameAt006598C0);
    strcpy(tag,g_YoumuTagAt006598C8);
    field478=0x2ef;
    field532=10;
    field06C=-10.0f;
    fieldF0C=0;
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
