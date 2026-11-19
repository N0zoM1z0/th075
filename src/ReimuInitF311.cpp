#include "ReimuFighter.hpp"
#include <string.h>
extern const char g_ReimuNameAt006590C8[];
extern const char g_ReimuTagAt006590D0[];
ReimuFighter::ReimuFighter()
{
    field713=1;
    strcpy(name,g_ReimuNameAt006590C8);
    strcpy(tag,g_ReimuTagAt006590D0);
    field478=0x287;
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
