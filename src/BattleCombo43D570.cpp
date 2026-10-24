#include "BattleHud43E040.hpp"
#include "GraphicsTexturedDraw.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define ALPHA FIELD(unsigned char, 0xA)
#define TEXTURE FIELD(IDirect3DTexture8*, 0)

void HudCombo43E040::Render() {
    if (ALPHA > 0 && FIELD(short, 4) > 1) {
        short count;
        RenderQuadPacket5E68C0 packet;
        {
            RECT region;
            SetRect(&region, 640, 54, 776, 124);
            count = FIELD(short, 4);
            if (count > 99)
                count = 99;
            if (FIELD(signed char, 0xB) > 0) {
                packet.BuildQuad(FIELD(float, 0x10) + 10.0f, 132.0f,
                    FIELD(float, 0x10) + 10.0f + 136.0f, 202.0f);
                Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&packet),
                    &region, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), TEXTURE);
                DrawAtlasNumberDefaultAt00446B60(FIELD(float, 0x10) + 10.0f + 65.0f,
                    116.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), count, 0);
                DrawAtlasNumberDefaultAt00446B60(FIELD(float, 0x10) + 10.0f + 60.0f,
                    169.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), FIELD(short, 6), 1);
                DrawAtlasNumberDefaultAt00446B60(FIELD(float, 0x10) + 10.0f + 67.0f,
                    187.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), FIELD(short, 8), 1);
            } else {
                packet.BuildQuad(-FIELD(float, 0x10) + 494.0f, 132.0f,
                    -FIELD(float, 0x10) + 494.0f + 136.0f, 202.0f);
                Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&packet),
                    &region, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), TEXTURE);
                DrawAtlasNumberDefaultAt00446B60(-FIELD(float, 0x10) + 494.0f + 65.0f,
                    116.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), count, 0);
                DrawAtlasNumberDefaultAt00446B60(-FIELD(float, 0x10) + 494.0f + 60.0f,
                    169.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), FIELD(short, 6), 1);
                DrawAtlasNumberDefaultAt00446B60(-FIELD(float, 0x10) + 494.0f + 67.0f,
                    187.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), FIELD(short, 8), 1);
            }
        }
        if (FIELD(short, 0xE) > 0) {
            FIELD(short, 0xE) -= 10;
            FIELD(float, 0x10) = -CameraSineAt0040D940(
                float(FIELD(short, 0xE)) * 0.01745328866f) * 200.0f;
        } else {
            --FIELD(short, 0xC);
            if (FIELD(short, 0xC) < 0) {
                ALPHA -= 25;
                if (ALPHA <= 5)
                    ALPHA = 0;
            }
        }
    }
}

#undef TEXTURE
#undef ALPHA
#undef FIELD
