#include "YuyukoFighter.hpp"
#include <string.h>
extern const char g_YuyukoNameAt00659B74[];
extern const char g_YuyukoTagAt00659B7C[];
YuyukoFighter::YuyukoFighter()
{
    sequenceTimer=0;
    fieldEFE=0;
    fieldEFA=0;
    reinterpret_cast<unsigned short&>(fieldF10)=0;
    field713=1;
    strcpy(name,g_YuyukoNameAt00659B74);
    strcpy(tag,g_YuyukoTagAt00659B7C);
    field478=0x21c;
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
