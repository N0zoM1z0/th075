#include "SuikaFighter.hpp"
#include <string.h>
extern const char g_SuikaNameAt00659E24[];
extern const char g_SuikaTagAt00659E2C[];
SuikaFighter::SuikaFighter()
{
    reinterpret_cast<unsigned short&>(fieldF28)=0;
    reinterpret_cast<unsigned short&>(fieldF2A)=0;
    field713=1;
    strcpy(name,g_SuikaNameAt00659E24);
    strcpy(tag,g_SuikaTagAt00659E2C);
    field478=0x2a6;
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
