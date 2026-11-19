#include "RemiliaFighter.hpp"
#include <string.h>
extern const char g_RemiliaNameAt00659A34[];
extern const char g_RemiliaTagAt00659A3C[];
RemiliaFighter::RemiliaFighter()
{
    sequenceTimer=0;
    fieldEFE=0;
    reinterpret_cast<unsigned short&>(field6FA)=0;
    reinterpret_cast<unsigned short&>(field6FC)=0;
    field6F8=0;
    field713=1;
    strcpy(name,g_RemiliaNameAt00659A34);
    strcpy(tag,g_RemiliaTagAt00659A3C);
    field478=0x2a0;
    reinterpret_cast<unsigned char&>(field532)=11;
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
