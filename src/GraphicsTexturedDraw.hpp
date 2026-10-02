#pragma once
#include "GraphicsVertex.hpp"

namespace Graphics
{
// View of four 16-byte coordinate records; the complete caller owner is unknown.
void DrawTexturedQuad(const float (*positions)[4], const RECT *textureRectangle,
    D3DCOLOR color, IDirect3DTexture8 *texture);
void DrawProjectedTriangleStrip(ScreenVertex *vertices, int count,
    IDirect3DTexture8 *texture);
}
