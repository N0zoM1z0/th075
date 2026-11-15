#include "BattleHud43E040.hpp"
#include "GraphicsTexturedDraw.hpp"

#define ALPHA field00A
#define TEXTURE field000

void HudCombo43E040::Render() {
    if (ALPHA > 0 && field004 > 1) {
        short count;
        RenderQuadPacket5E68C0 packet;
        {
            RECT region;
            SetRect(&region, 640, 54, 776, 124);
            count = field004;
            if (count > 99)
                count = 99;
            if (field00B > 0) {
                packet.BuildQuad(field010 + 10.0f, 132.0f,
                    field010 + 10.0f + 136.0f, 202.0f);
                Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&packet),
                    &region, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), TEXTURE);
                DrawAtlasNumberDefaultAt00446B60(field010 + 10.0f + 65.0f,
                    116.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), count, 0);
                DrawAtlasNumberDefaultAt00446B60(field010 + 10.0f + 60.0f,
                    169.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), field006, 1);
                DrawAtlasNumberDefaultAt00446B60(field010 + 10.0f + 67.0f,
                    187.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), field008, 1);
            } else {
                packet.BuildQuad(-field010 + 494.0f, 132.0f,
                    -field010 + 494.0f + 136.0f, 202.0f);
                Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&packet),
                    &region, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), TEXTURE);
                DrawAtlasNumberDefaultAt00446B60(-field010 + 494.0f + 65.0f,
                    116.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), count, 0);
                DrawAtlasNumberDefaultAt00446B60(-field010 + 494.0f + 60.0f,
                    169.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), field006, 1);
                DrawAtlasNumberDefaultAt00446B60(-field010 + 494.0f + 67.0f,
                    187.0f, D3DCOLOR_ARGB(ALPHA, 255, 255, 255), field008, 1);
            }
        }
        if (field00E > 0) {
            field00E -= 10;
            field010 = -CameraSineAt0040D940(
                float(field00E) * 0.01745328866f) * 200.0f;
        } else {
            --field00C;
            if (field00C < 0) {
                ALPHA -= 25;
                if (ALPHA <= 5)
                    ALPHA = 0;
            }
        }
    }
}

#undef TEXTURE
#undef ALPHA
