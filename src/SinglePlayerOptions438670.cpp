#include "SinglePlayerOptions438670.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define QUAD reinterpret_cast<SpriteTransform*>(&packet)
#define DRAW FIELD(RenderDrawing5E68C0*, 8)
#define VALUE reinterpret_cast<ProgressCard438A80*>(&g_BattleRecords)->GetSelectedValue()

void SinglePlayerOptions438670::RenderOptions() {
    if (FIELD(signed char, 0xEA) == 0)
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
        QUAD->TranslateQuad(408.0f, float(FIELD(signed char, 0xEC) * 32 + 120), 0.0f);
        DRAW->DrawQuad(6, &packet, &region, 0xFFFFFFFF);
    }
}

signed char ProgressCard438A80::GetSelectedValue() {
    return *reinterpret_cast<signed char*>(reinterpret_cast<char*>(this)
        + FIELD(signed char, 0x16AC4) * 0x17F0
        + FIELD(signed char, 0x16AC5) * 0x5FC + 0x556);
}

#undef VALUE
#undef DRAW
#undef QUAD
#undef FIELD
