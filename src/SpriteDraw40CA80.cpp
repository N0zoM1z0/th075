#include "SpriteDraw40CA80.hpp"
#include <string.h>

#define ENTRIES reinterpret_cast<SpriteEntries40CA80*>(reinterpret_cast<char*>(this) + 8)
#define ENTRY_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(ENTRIES->At(texture)) + (offset)))

void TimelineDrawing438D00::DrawSprite(int texture, float x, float y, DWORD color,
    float pivotX, float pivotY, float scale, float angle, unsigned char flags) {
    SpriteQuad40CA80 quad;
    {
        RECT region;
        region.left = 0;
        region.top = 0;
        region.right = ENTRY_FIELD(int, 4);
        region.bottom = ENTRY_FIELD(int, 8);
        if (scale == 1.0f && angle == 0.0f) {
            if (flags & 1)
                quad = SpriteQuad40CA80(x + pivotX - region.right, y - pivotY,
                    x + pivotX, y - pivotY + region.bottom);
            else
                quad = SpriteQuad40CA80(x - pivotX, y - pivotY,
                    x - pivotX + region.right, y - pivotY + region.bottom);
        } else if (scale != 1.0f && angle == 0.0f) {
            if (flags & 1)
                quad = SpriteQuad40CA80(x + pivotX - region.right * scale, y - pivotY,
                    x + pivotX, region.bottom * scale + y - pivotY);
            else
                quad = SpriteQuad40CA80(x - pivotX, y - pivotY,
                    x - pivotX + region.right * scale, region.bottom * scale + y - pivotY);
        } else {
            float cosine, sine;
            cosine = CameraCosineAt0040D900(angle * 0.017453288659f) * scale;
            sine = CameraSineAt0040D940(angle * 0.017453288659f) * scale;
            quad.first.x = x - pivotX * cosine + pivotY * sine;
            quad.first.y = y - pivotX * sine - pivotY * cosine;
            quad.fourth.x = x - pivotX * cosine - (region.bottom - pivotY) * sine;
            quad.fourth.y = y - pivotX * sine + (region.bottom - pivotY) * cosine;
            quad.second.x = (region.right - pivotX) * cosine + x + pivotY * sine;
            quad.second.y = (region.right - pivotX) * sine + y - pivotY * cosine;
            quad.third.x = (region.right - pivotX) * cosine + x - (region.bottom - pivotY) * sine;
            quad.third.y = (region.right - pivotX) * sine + y + (region.bottom - pivotY) * cosine;
        }
        if (flags & 1) {
            D3DXVECTOR4 swap;
            swap = quad.first;
            quad.first = quad.second;
            quad.second = swap;
            swap = quad.fourth;
            quad.fourth = quad.third;
            quad.third = swap;
        }
        Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&quad), &region,
            color, reinterpret_cast<SpriteTextures40CA80*>(this)->GetTexture(texture));
    }
}

#undef ENTRY_FIELD
#undef ENTRIES

SpriteQuad40CA80::SpriteQuad40CA80() {
    memset(this, 0, sizeof(*this));
}
