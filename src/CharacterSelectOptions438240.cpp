#include "CharacterSelectScene.hpp"
#include "BattleHud43E040.hpp"
#include "SpriteTransform.hpp"
extern signed char g_CombatMode;
extern signed char g_SelectOptionAt00671434[];
extern unsigned char g_SelectOptionAt00671438[];

#define QUAD reinterpret_cast<SpriteTransform*>(&packet)
#define DRAW reinterpret_cast<RenderDrawing5E68C0*>(menuTextures)

void CharacterSelectScene::RenderOptions() {
    RenderQuadPacket5E68C0 packet;
    {
        RECT region;
        for (int i = 0; i < 2; i = i + 1) {
            if ((optionsOpen[i]) == 0)
                continue;
            SetRect(&region, 0, 0, 256, 112);
            packet.BuildQuadFromRect(&region);
            QUAD->TranslateQuad(float(i * 320 + 32), 120.0f, 0.0f);
            DRAW->DrawQuad(5, &packet, &region, 0xFFFFFFFF);
            SetRect(&region, 208, 144 - g_SelectOptionAt00671438[i] * 32, 256, 176 - g_SelectOptionAt00671438[i] * 32);
            packet.BuildQuad(208.0f, 0.0f, 256.0f, 32.0f);
            QUAD->TranslateQuad(float(i * 320 + 32), 120.0f, 0.0f);
            DRAW->DrawQuad(5, &packet, &region, 0xFFFFFFFF);
            SetRect(&region, 77, 144, 202, 176);
            packet.BuildQuad(77.0f, 56.0f, 202.0f, 88.0f);
            QUAD->TranslateQuad(float(i * 320 + 32), 120.0f, 0.0f);
            DRAW->DrawQuad(5, &packet, &region, 0xFFFFFFFF);
            SetRect(&region, 77, 112, g_SelectOptionAt00671434[i] * 25 + 102, 144);
            packet.BuildQuad(77.0f, 56.0f, float(g_SelectOptionAt00671434[i] * 25 + 102), 88.0f);
            QUAD->TranslateQuad(float(i * 320 + 32), 120.0f, 0.0f);
            DRAW->DrawQuad(5, &packet, &region, 0xFFFFFFFF);
            SetRect(&region, 0, 112, 64, 144);
            packet.BuildQuad(0.0f, 0.0f, 64.0f, 32.0f);
            QUAD->TranslateQuad(float(i * 320 + 32), float((optionsCursor[i]) * 32 + 120), 0.0f);
            DRAW->DrawQuad(5, &packet, &region, 0xFFFFFFFF);
            if (g_CombatMode != 4) {
                SetRect(&region, 256, 832, 512, 1024);
                packet.BuildQuad(0.0f, 0.0f, 256.0f, 192.0f);
                QUAD->TranslateQuad(float(i * 320 + 32), 280.0f, 0.0f);
                reinterpret_cast<RenderDrawing5E68C0*>(characterTextures)->DrawQuad((static_cast<signed char>(chosenCharacter[i])) * 2 + 1, &packet, &region, 0xFFFFFFFF);
            }
        }
    }
}

#undef DRAW
#undef QUAD
