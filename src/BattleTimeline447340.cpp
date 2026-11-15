#include "BattleScene.hpp"
#include "BattleTimeline447340.hpp"

#define STYLE reinterpret_cast<RenderStyle43D9D0*>(textures)
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(textures)
#define QUAD reinterpret_cast<HudQuadOperations43E040*>(&packet)
#define ROTATION reinterpret_cast<TimelineQuadRotation447340*>(&packet)

void BattleScene::RenderOverlayTimeline() {
    RenderQuadPacket5E68C0 packet;
    STYLE->SetDepthMode(0);
    STYLE->SetBlendMode(0);
    switch (reinterpret_cast<signed char&>(field064)) {
        RECT rect;
    case 0:
        SetRect(&rect, reinterpret_cast<int&>(field010) * 5, 0, reinterpret_cast<int&>(field010) * 5 + 640, 64);
        packet.BuildQuad(0.0f, 208.0f - field074, 640.0f, 272.0f - field074);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - reinterpret_cast<int&>(field010) * 5, 0, 640 - reinterpret_cast<int&>(field010) * 5, 64);
        packet.BuildQuad(0.0f, 208.0f + field074, 640.0f, 272.0f + field074);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, reinterpret_cast<int&>(field010) * 5, 0, reinterpret_cast<int&>(field010) * 5 + 480, 64);
        packet.BuildQuad(80.0f, 208.0f - field070, 560.0f, 272.0f - field070);
        ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - reinterpret_cast<int&>(field010) * 5, 0, 480 - reinterpret_cast<int&>(field010) * 5, 64);
        packet.BuildQuad(80.0f, 208.0f + field070, 560.0f, 272.0f + field070);
        ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        if (field078 >= -200.0f) {
            SetRect(&rect, 0, 0, 512, 64);
            packet.BuildQuad(64.0f, 208.0f, 576.0f, 272.0f);
            if (field078 > 0.0f) {
                ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, field078);
                QUAD->Scale(320.0f, 240.0f, 0.0f,
                    field078 / 20.0f + 1.2f, field078 / 20.0f + 1.2f, 1.0f);
            } else {
                if (field060 > 70)
                    QUAD->Scale(320.0f, 240.0f, 0.0f,
                        field078 / 200.0f + 1.2f, field078 / 200.0f + 1.2f, 1.0f);
                else
                    QUAD->Scale(320.0f, 240.0f, 0.0f,
                        -field078 / 200.0f + 1.2f, field078 / 200.0f + 1.2f, 1.0f);
            }
            DRAWING->DrawQuad(4, &packet, &rect, 0xFFFFFFFF);
        }
        if (field060 < 140 && field080 * 40.0f < 255.0f) {
            SetRect(&rect, 0, 0, 512, 64);
            packet.BuildQuad(64.0f, 208.0f, 576.0f, 272.0f);
            QUAD->Scale(320.0f, 240.0f, 0.0f, field080 + 1.2f, field080 + 1.2f, 1.0f);
            STYLE->SetBlendMode(2);
            DRAWING->DrawQuad(6, &packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(field080 * 40.0f), 255, 255, 255));
            STYLE->SetBlendMode(0);
        }
        if (field060 <= 75 && field07C > -300.0f) {
            SetRect(&rect, 0, 0, 512, 128);
            packet.BuildQuad(64.0f, 176.0f, 576.0f, 304.0f);
            if (field060 <= 10)
                ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, field07C / 5.0f);
            if (field060 > 65)
                QUAD->Scale(320.0f, 240.0f, 0.0f,
                    -field07C / 15.0f + 1.0f, -field07C / 15.0f + 1.0f, 1.0f);
            else
                QUAD->Scale(320.0f, 240.0f, 0.0f,
                    field07C / 100.0f + 1.0f, field07C / 100.0f + 1.0f, 1.0f);
            DRAWING->DrawQuad(5, &packet, &rect, 0xFFFFFFFF);
        }
        if (field060 < 70 && field088 * 60.0f < 255.0f) {
            SetRect(&rect, 0, 0, 256, 256);
            packet.BuildQuad(192.0f, 112.0f, 448.0f, 368.0f);
            QUAD->Scale(320.0f, 240.0f, 0.0f, field088, field088, 1.0f);
            STYLE->SetBlendMode(2);
            DRAWING->DrawQuad(2, &packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(field088 * 60.0f), 255, 255, 255));
            STYLE->SetBlendMode(0);
        }
        break;
    case 1:
        SetRect(&rect, reinterpret_cast<int&>(field010) * 5, 0, reinterpret_cast<int&>(field010) * 5 + 640, 64);
        packet.BuildQuad(0.0f, 208.0f - field074, 640.0f, 272.0f - field074);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - reinterpret_cast<int&>(field010) * 5, 0, 640 - reinterpret_cast<int&>(field010) * 5, 64);
        packet.BuildQuad(0.0f, 208.0f + field074, 640.0f, 272.0f + field074);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, reinterpret_cast<int&>(field010) * 5, 0, reinterpret_cast<int&>(field010) * 5 + 480, 64);
        packet.BuildQuad(80.0f, 208.0f - field070, 560.0f, 272.0f - field070);
        ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - reinterpret_cast<int&>(field010) * 5, 0, 480 - reinterpret_cast<int&>(field010) * 5, 64);
        packet.BuildQuad(80.0f, 208.0f + field070, 560.0f, 272.0f + field070);
        ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        if (field078 >= -200.0f) {
            SetRect(&rect, 0, 0, 512, 128);
            packet.BuildQuad(64.0f, 176.0f, 576.0f, 304.0f);
            if (field078 > 0.0f) {
                ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, field078);
                QUAD->Scale(320.0f, 240.0f, 0.0f,
                    field078 / 20.0f + 1.2f, field078 / 20.0f + 1.2f, 1.0f);
            } else {
                if (field060 > 70)
                    QUAD->Scale(320.0f, 240.0f, 0.0f,
                        field078 / 200.0f + 1.2f, field078 / 200.0f + 1.2f, 1.0f);
                else
                    QUAD->Scale(320.0f, 240.0f, 0.0f,
                        -field078 / 200.0f + 1.2f, field078 / 200.0f + 1.2f, 1.0f);
            }
            DRAWING->DrawQuad(7, &packet, &rect, 0xFFFFFFFF);
        }
        if (field060 < 170 && field088 * 60.0f < 255.0f) {
            SetRect(&rect, 0, 0, 256, 256);
            packet.BuildQuad(192.0f, 112.0f, 448.0f, 368.0f);
            QUAD->Scale(320.0f, 240.0f, 0.0f, field088, field088, 1.0f);
            STYLE->SetBlendMode(2);
            DRAWING->DrawQuad(2, &packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(field088 * 60.0f), 255, 255, 255));
            STYLE->SetBlendMode(0);
        }
    }
}

#undef ROTATION
#undef QUAD
#undef DRAWING
#undef STYLE
