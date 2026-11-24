#include "SpriteTransform.hpp"
#include "TextureManagerF198.hpp"
#include "BattleScene.hpp"
#include "BattleTimeline447340.hpp"

#define STYLE reinterpret_cast<RenderStyle43D9D0*>(textures)
#define DRAWING reinterpret_cast<TextureManagerF198*>(textures)
#define QUAD reinterpret_cast<SpriteTransform*>(&packet)

void BattleScene::RenderOverlayTimeline() {
    RenderQuadPacket5E68C0 packet;
    reinterpret_cast<TextureManagerF198*>(STYLE)->SetDepthMode(0);
    reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
    switch (field064) {
        RECT rect;
    case 0:
        SetRect(&rect, field010 * 5, 0, field010 * 5 + 640, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 208.0f - field074, 640.0f, 272.0f - field074);
        DRAWING->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - field010 * 5, 0, 640 - field010 * 5, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 208.0f + field074, 640.0f, 272.0f + field074);
        DRAWING->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, field010 * 5, 0, field010 * 5 + 480, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(80.0f, 208.0f - field070, 560.0f, 272.0f - field070);
        QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - field010 * 5, 0, 480 - field010 * 5, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(80.0f, 208.0f + field070, 560.0f, 272.0f + field070);
        QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        if (field078 >= -200.0f) {
            SetRect(&rect, 0, 0, 512, 64);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 208.0f, 576.0f, 272.0f);
            if (field078 > 0.0f) {
                QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, field078);
                QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                    field078 / 20.0f + 1.2f, field078 / 20.0f + 1.2f, 1.0f);
            } else {
                if (field060 > 70)
                    QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                        field078 / 200.0f + 1.2f, field078 / 200.0f + 1.2f, 1.0f);
                else
                    QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                        -field078 / 200.0f + 1.2f, field078 / 200.0f + 1.2f, 1.0f);
            }
            DRAWING->DrawQuad(4, packet, &rect, 0xFFFFFFFF);
        }
        if (field060 < 140 && field080 * 40.0f < 255.0f) {
            SetRect(&rect, 0, 0, 512, 64);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 208.0f, 576.0f, 272.0f);
            QUAD->ScaleQuad(320.0f, 240.0f, 0.0f, field080 + 1.2f, field080 + 1.2f, 1.0f);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(2);
            DRAWING->DrawQuad(6, packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(field080 * 40.0f), 255, 255, 255));
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
        }
        if (field060 <= 75 && field07C > -300.0f) {
            SetRect(&rect, 0, 0, 512, 128);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 176.0f, 576.0f, 304.0f);
            if (field060 <= 10)
                QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, field07C / 5.0f);
            if (field060 > 65)
                QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                    -field07C / 15.0f + 1.0f, -field07C / 15.0f + 1.0f, 1.0f);
            else
                QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                    field07C / 100.0f + 1.0f, field07C / 100.0f + 1.0f, 1.0f);
            DRAWING->DrawQuad(5, packet, &rect, 0xFFFFFFFF);
        }
        if (field060 < 70 && field088 * 60.0f < 255.0f) {
            SetRect(&rect, 0, 0, 256, 256);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(192.0f, 112.0f, 448.0f, 368.0f);
            QUAD->ScaleQuad(320.0f, 240.0f, 0.0f, field088, field088, 1.0f);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(2);
            DRAWING->DrawQuad(2, packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(field088 * 60.0f), 255, 255, 255));
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
        }
        break;
    case 1:
        SetRect(&rect, field010 * 5, 0, field010 * 5 + 640, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 208.0f - field074, 640.0f, 272.0f - field074);
        DRAWING->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - field010 * 5, 0, 640 - field010 * 5, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 208.0f + field074, 640.0f, 272.0f + field074);
        DRAWING->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, field010 * 5, 0, field010 * 5 + 480, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(80.0f, 208.0f - field070, 560.0f, 272.0f - field070);
        QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        SetRect(&rect, 0 - field010 * 5, 0, 480 - field010 * 5, 64);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(80.0f, 208.0f + field070, 560.0f, 272.0f + field070);
        QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, 90.0f);
        DRAWING->DrawQuad(3, packet, &rect, 0xFFFFFFFF);
        if (field078 >= -200.0f) {
            SetRect(&rect, 0, 0, 512, 128);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(64.0f, 176.0f, 576.0f, 304.0f);
            if (field078 > 0.0f) {
                QUAD->RotateQuad(320.0f, 240.0f, 0.0f, 0.0f, 0.0f, field078);
                QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                    field078 / 20.0f + 1.2f, field078 / 20.0f + 1.2f, 1.0f);
            } else {
                if (field060 > 70)
                    QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                        field078 / 200.0f + 1.2f, field078 / 200.0f + 1.2f, 1.0f);
                else
                    QUAD->ScaleQuad(320.0f, 240.0f, 0.0f,
                        -field078 / 200.0f + 1.2f, field078 / 200.0f + 1.2f, 1.0f);
            }
            DRAWING->DrawQuad(7, packet, &rect, 0xFFFFFFFF);
        }
        if (field060 < 170 && field088 * 60.0f < 255.0f) {
            SetRect(&rect, 0, 0, 256, 256);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(192.0f, 112.0f, 448.0f, 368.0f);
            QUAD->ScaleQuad(320.0f, 240.0f, 0.0f, field088, field088, 1.0f);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(2);
            DRAWING->DrawQuad(2, packet, &rect,
                D3DCOLOR_ARGB(255 - static_cast<unsigned char>(field088 * 60.0f), 255, 255, 255));
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
        }
    }
}

#undef QUAD
#undef DRAWING
#undef STYLE
