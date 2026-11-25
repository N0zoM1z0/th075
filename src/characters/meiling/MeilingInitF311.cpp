#include "characters/meiling/MeilingFighter.hpp"
#include <string.h>
extern const char g_MeilingNameAt00659F40[] = "meiling";
extern const char g_MeilingTagAt00659F48[] = "10";
MeilingFighter::MeilingFighter()
{
    field713=1;
    strcpy(name,g_MeilingNameAt00659F40);
    strcpy(tag,g_MeilingTagAt00659F48);
    mainTextureCount=0x264;
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
