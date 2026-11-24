#include <windows.h>
#include "TextOverlay.hpp"
void TextOverlay::ConfigureText(float positionX, float positionY, unsigned char mode)
{
 xBits=reinterpret_cast<const DWORD&>(positionX);
 yBits=reinterpret_cast<const DWORD&>(positionY);
 field010Bits=0;
 field015=0;
 field014=0;
 this->mode=mode;
}
