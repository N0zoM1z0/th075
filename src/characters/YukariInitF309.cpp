#include "characters/YukariFighter.hpp"
#include <string.h>
extern const char g_YukariNameAt00659CB0[] = "yukari";
extern const char g_YukariTagAt00659CB8[] = "08";
YukariFighter::YukariFighter()
{
    sequenceTimer=0;
    fieldEFE=0;
    field713=1;
    strcpy(name,g_YukariNameAt00659CB0);
    strcpy(tag,g_YukariTagAt00659CB8);
    field478=0x25e;
    field532=12;
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
