#include "graphics/SpriteGeometryF211.hpp"

SpriteRectF211::SpriteRectF211(const RECT* bounds)
{
    topLeft = D3DXVECTOR4((float)bounds->left, (float)bounds->top, 0.0f, 0.0f);
    topRight = D3DXVECTOR4((float)bounds->right, (float)bounds->top, 0.0f, 0.0f);
    bottomRight = D3DXVECTOR4((float)bounds->right, (float)bounds->bottom, 0.0f, 0.0f);
    bottomLeft = D3DXVECTOR4((float)bounds->left, (float)bounds->bottom, 0.0f, 0.0f);
}
