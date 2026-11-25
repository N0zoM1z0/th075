#include "graphics/SpriteTransform.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "battle/BattleScene.hpp"
#include "battle/BattleModeFive448710.hpp"

#define STYLE reinterpret_cast<RenderStyle43D9D0*>(textures)
#define DRAWING reinterpret_cast<TextureManagerF198*>(textures)
#define PORTRAIT reinterpret_cast<TextureManagerF198*>(fighters[0]->field534)
#define QUAD reinterpret_cast<SpriteTransform*>(&packet)

void BattleScene::RenderModeFive() {
    int i;
    RenderQuadPacket5E68C0 packet;
    {
        D3DCOLOR color;
        RECT region;
        reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        Graphics::DrawFilledRectangle(&region, D3DCOLOR_ARGB(field0A1, 0, 0, 0));
        if (field0A1 < 50)
            return;
        for (i = 0; i < 9; i = i + 1) {
            if (i == field118) color = 0xFFFFFFFF;
            else color = 0xFF808080;
            SetRect(&region, 0, i * 24, 240, i * 24 + 24);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuadFromRect(&region);
            if (i > 5)
                QUAD->TranslateQuad(0.0f, 24.0f, 0.0f);
            QUAD->TranslateQuad(10.0f, 90.0f, 0.0f);
            DRAWING->DrawQuad(10, packet, &region, color);
        }
        for (i = 0; i < 6; i = i + 1) {
            if (i == fighters[1]->practiceSpellSelection) color = 0xFFFFFFFF;
            else color = 0xFF808080;
            SetRect(&region, i % 3 * 72, i / 3 * 24 + 216, i % 3 * 72 + 72, i / 3 * 24 + 240);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
            QUAD->TranslateQuad(float(i * 60 + 260), 90.0f, 0.0f);
            DRAWING->DrawQuad(10, packet, &region, color);
        }
        for (i = 0; i < 10; i = i + 1) {
            if (i == fighters[1]->practiceSpellStock) color = 0xFFFFFFFF;
            else color = 0xFF808080;
            SetRect(&region, i * 24, 264, i * 24 + 24, 288);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(float(i * 24), 0.0f, float(i * 24 + 24), 24.0f);
            QUAD->TranslateQuad(260.0f, 114.0f, 0.0f);
            DRAWING->DrawQuad(10, packet, &region, color);
        }
        if (fighters[1]->practiceGuardMode == 0) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 288, 72, 312);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
        QUAD->TranslateQuad(260.0f, 138.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        if (fighters[1]->practiceGuardMode == 1) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 72, 288, 168, 312);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 96.0f, 24.0f);
        QUAD->TranslateQuad(332.0f, 138.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        if (fighters[1]->practiceGuardMode == 2) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 312, 120, 336);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 120.0f, 24.0f);
        QUAD->TranslateQuad(428.0f, 138.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        if (fighters[1]->practiceGuardMode == 3) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 120, 312, 168, 336);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 48.0f, 24.0f);
        QUAD->TranslateQuad(548.0f, 138.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        for (i = 0; i < 2; i = i + 1) {
            if (i == fighters[1]->practiceManualAirRecovery) color = 0xFFFFFFFF;
            else color = 0xFF808080;
            SetRect(&region, i * 72, 336, i * 72 + 72, 360);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
            QUAD->TranslateQuad(float(i * 72 + 260), 162.0f, 0.0f);
            DRAWING->DrawQuad(10, packet, &region, color);
        }
        if (fighters[1]->practiceActionMode == 0) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 360, 72, 384);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
        QUAD->TranslateQuad(260.0f, 186.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        if (fighters[1]->practiceActionMode == 1) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 72, 360, 168, 384);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 96.0f, 24.0f);
        QUAD->TranslateQuad(332.0f, 186.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        if (fighters[1]->practiceActionMode == 2) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 384, 72, 408);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
        QUAD->TranslateQuad(428.0f, 186.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        if (fighters[1]->practiceActionMode == 3) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 72, 384, 168, 408);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 96.0f, 24.0f);
        QUAD->TranslateQuad(500.0f, 186.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        if (fighters[1]->practiceCenterPosition == 0) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 408, 72, 432);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
        QUAD->TranslateQuad(260.0f, 210.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        if (fighters[1]->practiceCenterPosition == 1) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 72, 408, 168, 432);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, 0.0f, 96.0f, 24.0f);
        QUAD->TranslateQuad(332.0f, 210.0f, 0.0f);
        DRAWING->DrawQuad(10, packet, &region, color);
        SetRect(&region, 0, 0, 256, 256);
        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuadFromRect(&region);
        QUAD->TranslateQuad(340.0f, 280.0f, 0.0f);
        PORTRAIT->DrawQuad(fighters[0]->field532 - 1, packet, &region, 0xFFFFFFFF);
    }
}

#undef QUAD
#undef PORTRAIT
#undef DRAWING
#undef STYLE
