#include "MarisaFighter.hpp"
#include <string.h>
extern const char g_MarisaNameAt006592A8[];
extern const char g_MarisaTagAt006592B0[];
MarisaFighter::MarisaFighter()
{
    reinterpret_cast<unsigned short&>(sequenceTimer)=0;
    fieldEFE=0;
    field713=1;
    strcpy(name,g_MarisaNameAt006592A8);
    strcpy(tag,g_MarisaTagAt006592B0);
    field478=0x299;
    reinterpret_cast<unsigned char&>(field532)=10;
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
