#include "battle/BattleScene.hpp"
#include "battle/BattleHud43E040.hpp"
#include "graphics/GraphicsTexturedDraw.hpp"
#include "graphics/SpriteTransform.hpp"


void ComboDisplay::Render() {
    if (alpha > 0 && count > 1) {
        short shown;
        RenderQuadPacket5E68C0 packet;
        {
            RECT region;
            SetRect(&region, 640, 54, 776, 124);
            shown = count;
            if (shown > 99)
                shown = 99;
            if (side > 0) {
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(slide + 10.0f, 132.0f,
                    slide + 10.0f + 136.0f, 202.0f);
                Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&packet),
                    &region, D3DCOLOR_ARGB(alpha, 255, 255, 255), texture);
                DrawAtlasNumberDefaultAt00446B60(slide + 10.0f + 65.0f,
                    116.0f, D3DCOLOR_ARGB(alpha, 255, 255, 255), shown, 0);
                DrawAtlasNumberDefaultAt00446B60(slide + 10.0f + 60.0f,
                    169.0f, D3DCOLOR_ARGB(alpha, 255, 255, 255), damage, 1);
                DrawAtlasNumberDefaultAt00446B60(slide + 10.0f + 67.0f,
                    187.0f, D3DCOLOR_ARGB(alpha, 255, 255, 255), rate, 1);
            } else {
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(-slide + 494.0f, 132.0f,
                    -slide + 494.0f + 136.0f, 202.0f);
                Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&packet),
                    &region, D3DCOLOR_ARGB(alpha, 255, 255, 255), texture);
                DrawAtlasNumberDefaultAt00446B60(-slide + 494.0f + 65.0f,
                    116.0f, D3DCOLOR_ARGB(alpha, 255, 255, 255), shown, 0);
                DrawAtlasNumberDefaultAt00446B60(-slide + 494.0f + 60.0f,
                    169.0f, D3DCOLOR_ARGB(alpha, 255, 255, 255), damage, 1);
                DrawAtlasNumberDefaultAt00446B60(-slide + 494.0f + 67.0f,
                    187.0f, D3DCOLOR_ARGB(alpha, 255, 255, 255), rate, 1);
            }
        }
        if (phase > 0) {
            phase -= 10;
            slide = -CameraSineAt0040D940(
                float(phase) * 0.01745328866f) * 200.0f;
        } else {
            --hold;
            if (hold < 0) {
                alpha -= 25;
                if (alpha <= 5)
                    alpha = 0;
            }
        }
    }
}
