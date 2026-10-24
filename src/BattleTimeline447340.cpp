#include "BattleTimeline447340.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))
#define STYLE reinterpret_cast<RenderStyle43D9D0*>(FIELD(void*, 8))
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(FIELD(void*, 8))
#define QUAD reinterpret_cast<HudQuadOperations43E040*>(&packet)
#define ROTATION reinterpret_cast<TimelineQuadRotation447340*>(&packet)

void BattleTimeline447340::RenderTimeline() {
    RenderQuadPacket5E68C0 packet;
    STYLE->SetDepthMode(0);
    STYLE->SetBlendMode(0);
    switch (FIELD(signed char, 0x64)) {
        RECT rect;
    case 0:
        SetRect(&rect, FIELD(int, 0x10) * 5, 0, FIELD(int, 0x10) * 5 + 640, 64);
        packet.BuildQuad(0.0f, 208.0f - FLOAT(0x74), 640.0f, 272.0f - FLOAT(0x74));
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - FIELD(int, 0x10) * 5, 0, 640 - FIELD(int, 0x10) * 5, 64);
        packet.BuildQuad(0.0f, 208.0f + FLOAT(0x74), 640.0f, 272.0f + FLOAT(0x74));
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, FIELD(int, 0x10) * 5, 0, FIELD(int, 0x10) * 5 + 480, 64);
        packet.BuildQuad(80.0f, 208.0f - FLOAT(0x70), 560.0f, 272.0f - FLOAT(0x70));
        ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - FIELD(int, 0x10) * 5, 0, 480 - FIELD(int, 0x10) * 5, 64);
        packet.BuildQuad(80.0f, 208.0f + FLOAT(0x70), 560.0f, 272.0f + FLOAT(0x70));
        ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        if (FLOAT(0x78) >= -200.0f) {
            SetRect(&rect, 0, 0, 512, 64);
            packet.BuildQuad(64.0f, 208.0f, 576.0f, 272.0f);
            if (FLOAT(0x78) > 0.0f) {
                ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, FLOAT(0x78));
                QUAD->Scale(320.0f, 240.0f, 0.0f,
                    FLOAT(0x78) / 20.0f + 1.2f, FLOAT(0x78) / 20.0f + 1.2f, 1.0f);
            } else {
                if (FIELD(int, 0x60) > 70)
                    QUAD->Scale(320.0f, 240.0f, 0.0f,
                        FLOAT(0x78) / 200.0f + 1.2f, FLOAT(0x78) / 200.0f + 1.2f, 1.0f);
                else
                    QUAD->Scale(320.0f, 240.0f, 0.0f,
                        -FLOAT(0x78) / 200.0f + 1.2f, FLOAT(0x78) / 200.0f + 1.2f, 1.0f);
            }
            DRAWING->DrawQuad(4, &packet, &rect, 0xFFFFFFFF);
        }
        if (FIELD(int, 0x60) < 140 && FLOAT(0x80) * 40.0f < 255.0f) {
            SetRect(&rect, 0, 0, 512, 64);
            packet.BuildQuad(64.0f, 208.0f, 576.0f, 272.0f);
            QUAD->Scale(320.0f, 240.0f, 0.0f, FLOAT(0x80) + 1.2f, FLOAT(0x80) + 1.2f, 1.0f);
            STYLE->SetBlendMode(2);
            DRAWING->DrawQuad(6, &packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(FLOAT(0x80) * 40.0f), 255, 255, 255));
            STYLE->SetBlendMode(0);
        }
        if (FIELD(int, 0x60) <= 75 && FLOAT(0x7C) > -300.0f) {
            SetRect(&rect, 0, 0, 512, 128);
            packet.BuildQuad(64.0f, 176.0f, 576.0f, 304.0f);
            if (FIELD(int, 0x60) <= 10)
                ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, FLOAT(0x7C) / 5.0f);
            if (FIELD(int, 0x60) > 65)
                QUAD->Scale(320.0f, 240.0f, 0.0f,
                    -FLOAT(0x7C) / 15.0f + 1.0f, -FLOAT(0x7C) / 15.0f + 1.0f, 1.0f);
            else
                QUAD->Scale(320.0f, 240.0f, 0.0f,
                    FLOAT(0x7C) / 100.0f + 1.0f, FLOAT(0x7C) / 100.0f + 1.0f, 1.0f);
            DRAWING->DrawQuad(5, &packet, &rect, 0xFFFFFFFF);
        }
        if (FIELD(int, 0x60) < 70 && FLOAT(0x88) * 60.0f < 255.0f) {
            SetRect(&rect, 0, 0, 256, 256);
            packet.BuildQuad(192.0f, 112.0f, 448.0f, 368.0f);
            QUAD->Scale(320.0f, 240.0f, 0.0f, FLOAT(0x88), FLOAT(0x88), 1.0f);
            STYLE->SetBlendMode(2);
            DRAWING->DrawQuad(2, &packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(FLOAT(0x88) * 60.0f), 255, 255, 255));
            STYLE->SetBlendMode(0);
        }
        break;
    case 1:
        SetRect(&rect, FIELD(int, 0x10) * 5, 0, FIELD(int, 0x10) * 5 + 640, 64);
        packet.BuildQuad(0.0f, 208.0f - FLOAT(0x74), 640.0f, 272.0f - FLOAT(0x74));
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - FIELD(int, 0x10) * 5, 0, 640 - FIELD(int, 0x10) * 5, 64);
        packet.BuildQuad(0.0f, 208.0f + FLOAT(0x74), 640.0f, 272.0f + FLOAT(0x74));
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, FIELD(int, 0x10) * 5, 0, FIELD(int, 0x10) * 5 + 480, 64);
        packet.BuildQuad(80.0f, 208.0f - FLOAT(0x70), 560.0f, 272.0f - FLOAT(0x70));
        ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - FIELD(int, 0x10) * 5, 0, 480 - FIELD(int, 0x10) * 5, 64);
        packet.BuildQuad(80.0f, 208.0f + FLOAT(0x70), 560.0f, 272.0f + FLOAT(0x70));
        ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, &packet, &rect, 0xFFFFFFFF);
        if (FLOAT(0x78) >= -200.0f) {
            SetRect(&rect, 0, 0, 512, 128);
            packet.BuildQuad(64.0f, 176.0f, 576.0f, 304.0f);
            if (FLOAT(0x78) > 0.0f) {
                ROTATION->Rotate(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, FLOAT(0x78));
                QUAD->Scale(320.0f, 240.0f, 0.0f,
                    FLOAT(0x78) / 20.0f + 1.2f, FLOAT(0x78) / 20.0f + 1.2f, 1.0f);
            } else {
                if (FIELD(int, 0x60) > 70)
                    QUAD->Scale(320.0f, 240.0f, 0.0f,
                        FLOAT(0x78) / 200.0f + 1.2f, FLOAT(0x78) / 200.0f + 1.2f, 1.0f);
                else
                    QUAD->Scale(320.0f, 240.0f, 0.0f,
                        -FLOAT(0x78) / 200.0f + 1.2f, FLOAT(0x78) / 200.0f + 1.2f, 1.0f);
            }
            DRAWING->DrawQuad(7, &packet, &rect, 0xFFFFFFFF);
        }
        if (FIELD(int, 0x60) < 170 && FLOAT(0x88) * 60.0f < 255.0f) {
            SetRect(&rect, 0, 0, 256, 256);
            packet.BuildQuad(192.0f, 112.0f, 448.0f, 368.0f);
            QUAD->Scale(320.0f, 240.0f, 0.0f, FLOAT(0x88), FLOAT(0x88), 1.0f);
            STYLE->SetBlendMode(2);
            DRAWING->DrawQuad(2, &packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(FLOAT(0x88) * 60.0f), 255, 255, 255));
            STYLE->SetBlendMode(0);
        }
    }
}

#undef ROTATION
#undef QUAD
#undef DRAWING
#undef STYLE
#undef FLOAT
#undef FIELD
