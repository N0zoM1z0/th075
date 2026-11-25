#include "graphics/SpriteTransform.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "battle/BattleScene.hpp"
#include "battle/BattleHud43E040.hpp"
#include <math.h>


void BattleScene::RenderRoundBanner() {
    unsigned char opacity;
    RenderQuadPacket5E68C0 packet;
    opacity = 255;
    {
        unsigned char count = static_cast<unsigned char>(::log10f(float(awardedSpellBonus))) + 1;
        if (spellBonusBannerFrames > 50) {
            opacity = 255;
        } else {
            opacity = spellBonusBannerFrames * 5;
        }
        RECT region;
        SetRect(&region, 0, 0, 512, 42);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 120.0f, 576.0f, 162.0f);
        textureManager->DrawQuad(9, packet, &region, D3DCOLOR_ARGB(opacity, 255, 255, 255));
        DrawAtlasNumberDefaultAt00446B60(float(count * 19 + 320), 150.0f,
            D3DCOLOR_ARGB(opacity, 255, 255, 255), awardedSpellBonus, 13);
    }
}
