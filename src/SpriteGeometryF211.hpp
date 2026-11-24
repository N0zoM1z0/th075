#pragma once

#include <d3dx8.h>
#include <stddef.h>

class SpriteRectF211 {
public:
    D3DXVECTOR4 topLeft, topRight, bottomRight, bottomLeft;
    D3DXMATRIX matrix;
    DWORD unknown80;

    SpriteRectF211(const RECT* bounds);
};

typedef char SpriteRectLayoutF211[(offsetof(SpriteRectF211, matrix) == 64 &&
    sizeof(SpriteRectF211) == 132) ? 1 : -1];
