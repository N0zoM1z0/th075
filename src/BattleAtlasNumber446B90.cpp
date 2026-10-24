#include "BattleAtlasNumber446B90.hpp"

void __cdecl DrawAtlasNumberAt00446B90(float x, float y, D3DCOLOR color,
    int number, signed char style, int digits) {
    if (number < 0)
        return;
    int remaining = number;
    int textureId = (style == 10) + (style == 13) * 2;
    AtlasQuad446B90 packet(x - float(g_AtlasNumberWidthAt0068C8CC[style]), y,
        x, float(g_AtlasNumberHeightAt0068C8A0[style]) + y);
    if (digits > 0) {
        while (digits > 0) {
            Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&packet),
                &g_AtlasNumberRegionsAt0068C8F8[style][remaining % 10], color,
                g_AtlasNumberTexturesAt0068C894[textureId]);
            remaining = remaining / 10;
            reinterpret_cast<SpriteTransform*>(&packet)->TranslateQuad(
                float(-g_AtlasNumberAdvanceAt0068C868[style]), 0.0f, 0.0f);
            digits = digits - 1;
        }
    } else {
        while (remaining >= 0) {
            Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&packet),
                &g_AtlasNumberRegionsAt0068C8F8[style][remaining % 10], color,
                g_AtlasNumberTexturesAt0068C894[textureId]);
            if (remaining < 10) {
                remaining = -1;
            } else {
                remaining = remaining / 10;
            }
            reinterpret_cast<SpriteTransform*>(&packet)->TranslateQuad(
                float(-g_AtlasNumberAdvanceAt0068C868[style]), 0.0f, 0.0f);
        }
    }
}
