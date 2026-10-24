#include "BattleAtlasNumber446B90.hpp"

AtlasQuad446B90::AtlasQuad446B90(float left, float top, float right, float bottom) {
    first = D3DXVECTOR4(left, top, 0.0f, 0.0f);
    second = D3DXVECTOR4(right, top, 0.0f, 0.0f);
    third = D3DXVECTOR4(right, bottom, 0.0f, 0.0f);
    fourth = D3DXVECTOR4(left, bottom, 0.0f, 0.0f);
}
