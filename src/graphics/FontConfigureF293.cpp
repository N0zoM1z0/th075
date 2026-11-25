#include <windows.h>
#include "graphics/TextOverlay.hpp"
void TextOverlay::ConfigureText(float positionX, float positionY, unsigned char mode)
{
 xBits=reinterpret_cast<const DWORD&>(positionX);
 yBits=reinterpret_cast<const DWORD&>(positionY);
 boxScaleYBits=0;
 unfadedLineCount=0;
 lineCount=0;
 this->mode=mode;
}
