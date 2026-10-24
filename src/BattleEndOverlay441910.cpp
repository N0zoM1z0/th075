#include "BattleEndOverlay441910.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define LEFT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x44) + (offset)))
#define RIGHT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x48) + (offset)))
#define STYLE reinterpret_cast<RenderStyle43D9D0*>(FIELD(void*, 8))
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(FIELD(void*, 8))
#define LEFT_DRAWING reinterpret_cast<RenderDrawing5E68C0*>(LEFT(void*, 0x534))
#define RIGHT_DRAWING reinterpret_cast<RenderDrawing5E68C0*>(RIGHT(void*, 0x534))
#define QUAD reinterpret_cast<HudQuadOperations43E040*>(&packet)

void BattleEndOverlay441910::RenderEndOverlay() {
    if (g_CombatMode == 5) {
        RenderModeFive();
    } else {
        RenderQuadPacket5E68C0 packet;
        {
            RECT rect;
            STYLE->SetBlendMode(0);
            SetRect(&rect, 0, 0, 640, 480);
            Graphics::DrawFilledRectangle(&rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xA1), 0, 0, 0));
            if (FIELD(unsigned char, 0xA1) < 50)
                return;
            if (FIELD(unsigned char, 0xA0) == 0)
                return;
            if (g_FrameClockMode != 2) {
                SetRect(&rect, 0, 0, 256, 256);
                packet.BuildQuadFromRect(&rect);
                if (LEFT(signed char, 0x2CD) == 0 && RIGHT(signed char, 0x2CD) == 0) {
                    QUAD->Translate(32.0f, 280.0f, 0.0f);
                    LEFT_DRAWING->DrawQuad(LEFT(signed char, 0x532) - 1, &packet, &rect, 0xFFFFFFFF);
                    QUAD->Translate(320.0f, 0.0f, 0.0f);
                    RIGHT_DRAWING->DrawQuad(RIGHT(signed char, 0x532) - 1, &packet, &rect, 0xFFFFFFFF);
                } else if (LEFT(signed char, 0x2CD) != 0) {
                    QUAD->Translate(192.0f, 280.0f, 0.0f);
                    RIGHT_DRAWING->DrawQuad(RIGHT(signed char, 0x532) - 1, &packet, &rect, 0xFFFFFFFF);
                } else {
                    QUAD->Translate(192.0f, 280.0f, 0.0f);
                    LEFT_DRAWING->DrawQuad(LEFT(signed char, 0x532) - 1, &packet, &rect, 0xFFFFFFFF);
                }
            }
            if (FIELD(signed char, 0x18) == 12 && g_StateContinueCount > 0) {
                SetRect(&rect, 288, 192, 512, 224);
                packet.BuildQuad(176.0f, 230.0f, 400.0f, 262.0f);
                DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
                SetRect(&rect, 512, g_StateContinueCount * 32 + 96, 576, g_StateContinueCount * 32 + 128);
                packet.BuildQuad(390.0f, 230.0f, 454.0f, 262.0f);
                DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
            }
            if (FIELD(signed char, 0x18) != 5 &&
                (FIELD(signed char, 0x18) != 12 || g_StateContinueCount != 0)) {
                SetRect(&rect, 384, (FIELD(signed char, 0x118) != 0) * 32 + 128,
                    512, (FIELD(signed char, 0x118) != 0) * 32 + 160);
                packet.BuildQuad(256.0f, 140.0f, 384.0f, 172.0f);
                DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
            }
            SetRect(&rect, 256, (FIELD(signed char, 0x118) != 1) * 32 + 128,
                384, (FIELD(signed char, 0x118) != 1) * 32 + 160);
            packet.BuildQuad(256.0f, 170.0f, 384.0f, 202.0f);
            DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
            if (g_FrameClockMode != 2 && g_EndOverlayFlagAt00671624 == 0 && FIELD(signed char, 0x18) != 7) {
                SetRect(&rect, 0, (FIELD(signed char, 0x118) != 2) * 32 + 128,
                    256, (FIELD(signed char, 0x118) != 2) * 32 + 155);
                packet.BuildQuad(192.0f, 200.0f, 448.0f, 227.0f);
                DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
            }

        }
    }
}

#undef QUAD
#undef RIGHT_DRAWING
#undef LEFT_DRAWING
#undef DRAWING
#undef STYLE
#undef RIGHT
#undef LEFT
#undef FIELD
