#pragma once
#include "Graphics.hpp"

namespace Graphics
{
bool Create16BitTexture(unsigned short width, unsigned short height,
    IDirect3DTexture8 **texture);
bool CreateTexture(unsigned short width, unsigned short height,
    IDirect3DTexture8 **texture, unsigned char bitsPerPixel);
void ResetDevice();
}
