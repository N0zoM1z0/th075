#include <windows.h>
#include "TextOverlay.hpp"
void TextOverlay::ConfigureText(DWORD xBits,DWORD yBits,unsigned char mode)
{
 this->xBits=xBits;
 this->yBits=yBits;
 field010Bits=0;
 field015=0;
 field014=0;
 this->mode=mode;
}
