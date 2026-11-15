#include "GameProgress.hpp"
#include "SinglePlayerOptions438670.hpp"

#define QUAD reinterpret_cast<SpriteTransform*>(&packet)
#define DRAW field008
#define VALUE reinterpret_cast<GameProgress*>(&g_BattleRecords)->GetSelectedValue()

void SinglePlayerOptions438670::RenderOptions() {
    if (field0EA == 0)
        return;
    RenderQuadPacket5E68C0 packet;
    {
        RECT region;
        SetRect(&region, 0, 0, 144, 224);
        packet.BuildQuadFromRect(&region);
        QUAD->TranslateQuad(408.0f, 120.0f, 0.0f);
        DRAW->DrawQuad(6, &packet, &region, 0xFFFFFFFF);
        SetRect(&region, 144, 0, 224, VALUE * 32);
        packet.BuildQuad(0.0f, 0.0f, 80.0f, float(VALUE * 32));
        QUAD->TranslateQuad(472.0f, 120.0f, 0.0f);
        DRAW->DrawQuad(6, &packet, &region, 0xFFFFFFFF);
        SetRect(&region, 144, VALUE * 32, 224, 224);
        packet.BuildQuad(0.0f, float(VALUE * 32), 80.0f, 224.0f);
        QUAD->TranslateQuad(472.0f, 120.0f, 0.0f);
        DRAW->DrawQuad(6, &packet, &region, 0xFF808080);
        SetRect(&region, 0, 224, 64, 256);
        packet.BuildQuad(0.0f, 0.0f, 64.0f, 32.0f);
        QUAD->TranslateQuad(408.0f, float(field0EC * 32 + 120), 0.0f);
        DRAW->DrawQuad(6, &packet, &region, 0xFFFFFFFF);
    }
}

signed char GameProgress::GetSelectedValue() {
    return characters[selectedFighter].difficulties[selectedDifficulty].field556;
}

#undef VALUE
#undef DRAW
#undef QUAD
