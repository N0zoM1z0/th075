#include "SpriteQuad.hpp"
#include <string.h>

SpriteQuad40CA80::SpriteQuad40CA80() {
    memset(this, 0, sizeof(*this));
}

SpriteQuad40CA80::SpriteQuad40CA80(float left, float top, float right, float bottom) {
    first = D3DXVECTOR4(left, top, 0.0f, 0.0f);
    second = D3DXVECTOR4(right, top, 0.0f, 0.0f);
    third = D3DXVECTOR4(right, bottom, 0.0f, 0.0f);
    fourth = D3DXVECTOR4(left, bottom, 0.0f, 0.0f);
}
