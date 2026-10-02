#pragma once
#include "Graphics.hpp"

namespace Graphics
{
void CopyTextureOpaque(IDirect3DTexture8 **destination,
    IDirect3DTexture8 **source, const RECT *rectangle);
}
