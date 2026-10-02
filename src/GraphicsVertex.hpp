#pragma once
#include "Graphics.hpp"

namespace Graphics
{
// Complete local/input vertex record evidenced by FVF 0x144 and stride 28.
struct ScreenVertex
{
    float x, y, z, rhw;
    D3DCOLOR color;
    float u, v;
};
}
