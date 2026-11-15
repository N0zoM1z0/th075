#include <windows.h>
#include "TextOverlay.hpp"
void TextOverlay::ConfigureText(DWORD xBits,DWORD yBits,unsigned char mode)
{
 reinterpret_cast<DWORD&>(x)=xBits;
 reinterpret_cast<DWORD&>(y)=yBits;
 reinterpret_cast<DWORD&>(field010)=0;
 field015=0;
 field014=0;
 this->mode=mode;
}
