#pragma once

#include <d3dx8.h>
#include <stddef.h>

// Complete physical132-byte packet established by F064/F083, with both observed
// constructor entries. Original class identity and payload partition are unknown.
class SpriteQuad40CA80 {
public:
    D3DXVECTOR4 first, second, third, fourth;
    D3DXMATRIX matrix;
    DWORD unknown80;
    SpriteQuad40CA80();
    SpriteQuad40CA80(float, float, float, float);
};
typedef char SpriteQuadSize40CA80[(sizeof(SpriteQuad40CA80) == 132) ? 1 : -1];
typedef char SpriteQuadMatrix40CA80[(offsetof(SpriteQuad40CA80, matrix) == 64) ? 1 : -1];
