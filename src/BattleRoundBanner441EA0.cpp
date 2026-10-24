#include "BattleRoundBanner441EA0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(FIELD(void*, 8))

void BattleRoundBanner441EA0::RenderRoundBanner() {
    unsigned char opacity;
    RenderQuadPacket5E68C0 packet;
    opacity = 255;
    {
        unsigned char count = static_cast<unsigned char>(BannerLog10At00442040(float(FIELD(int, 0x68)))) + 1;
        if (FIELD(int, 0x6C) > 50) {
            opacity = 255;
        } else {
            opacity = FIELD(int, 0x6C) * 5;
        }
        RECT region;
        SetRect(&region, 0, 0, 512, 42);
        packet.BuildQuad(64.0f, 120.0f, 576.0f, 162.0f);
        DRAWING->DrawQuad(9, &packet, &region, D3DCOLOR_ARGB(opacity, 255, 255, 255));
        DrawAtlasNumberDefaultAt00446B60(float(count * 19 + 320), 150.0f,
            D3DCOLOR_ARGB(opacity, 255, 255, 255), FIELD(int, 0x68), 13);
    }
}

#undef DRAWING
#undef FIELD
