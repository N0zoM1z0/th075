#pragma once
#include "graphics/GraphicsVertex.hpp"

namespace Graphics
{
void DrawLine(const RECT *line, D3DCOLOR color);
void DrawFilledRectangle(const RECT *rectangle, D3DCOLOR color);
void DrawRectangleOutline(const RECT *rectangle, D3DCOLOR color);
}
