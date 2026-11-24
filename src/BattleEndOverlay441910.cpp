#include "TextureManagerF198.hpp"
#include "BattleScene.hpp"
#include "BattleEndOverlay441910.hpp"

#define STYLE reinterpret_cast<RenderStyle43D9D0*>(textures)
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(textures)
#define LEFT_DRAWING reinterpret_cast<RenderDrawing5E68C0*>(fighters[0]->field534)
#define RIGHT_DRAWING reinterpret_cast<RenderDrawing5E68C0*>(fighters[1]->field534)
#define QUAD reinterpret_cast<HudQuadOperations43E040*>(&packet)

void BattleScene::RenderEndOverlay() {
    if (g_CombatMode == 5) {
        RenderModeFive();
    } else {
        RenderQuadPacket5E68C0 packet;
        {
            RECT rect;
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
            SetRect(&rect, 0, 0, 640, 480);
            Graphics::DrawFilledRectangle(&rect, D3DCOLOR_ARGB(field0A1, 0, 0, 0));
            if (field0A1 < 50)
                return;
            if (field0A0 == 0)
                return;
            if (g_FrameClockMode != 2) {
                SetRect(&rect, 0, 0, 256, 256);
                packet.BuildQuadFromRect(&rect);
                if (fighters[0]->field2CD == 0 && fighters[1]->field2CD == 0) {
                    QUAD->Translate(32.0f, 280.0f, 0.0f);
                    LEFT_DRAWING->DrawQuad(fighters[0]->field532 - 1, &packet, &rect, 0xFFFFFFFF);
                    QUAD->Translate(320.0f, 0.0f, 0.0f);
                    RIGHT_DRAWING->DrawQuad(fighters[1]->field532 - 1, &packet, &rect, 0xFFFFFFFF);
                } else if (fighters[0]->field2CD != 0) {
                    QUAD->Translate(192.0f, 280.0f, 0.0f);
                    RIGHT_DRAWING->DrawQuad(fighters[1]->field532 - 1, &packet, &rect, 0xFFFFFFFF);
                } else {
                    QUAD->Translate(192.0f, 280.0f, 0.0f);
                    LEFT_DRAWING->DrawQuad(fighters[0]->field532 - 1, &packet, &rect, 0xFFFFFFFF);
                }
            }
            if (field018 == 12 && g_StateContinueCount > 0) {
                SetRect(&rect, 288, 192, 512, 224);
                packet.BuildQuad(176.0f, 230.0f, 400.0f, 262.0f);
                DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
                SetRect(&rect, 512, g_StateContinueCount * 32 + 96, 576, g_StateContinueCount * 32 + 128);
                packet.BuildQuad(390.0f, 230.0f, 454.0f, 262.0f);
                DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
            }
            if (field018 != 5 &&
                (field018 != 12 || g_StateContinueCount != 0)) {
                SetRect(&rect, 384, (field118 != 0) * 32 + 128,
                    512, (field118 != 0) * 32 + 160);
                packet.BuildQuad(256.0f, 140.0f, 384.0f, 172.0f);
                DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
            }
            SetRect(&rect, 256, (field118 != 1) * 32 + 128,
                384, (field118 != 1) * 32 + 160);
            packet.BuildQuad(256.0f, 170.0f, 384.0f, 202.0f);
            DRAWING->DrawQuad(0, &packet, &rect, 0xFFFFFFFF);
            if (g_FrameClockMode != 2 && g_EndOverlayFlagAt00671624 == 0 && field018 != 7) {
                SetRect(&rect, 0, (field118 != 2) * 32 + 128,
                    256, (field118 != 2) * 32 + 155);
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
