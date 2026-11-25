#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "engine/GameSharedState.hpp"
#include "graphics/SpriteTransform.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "battle/BattleScene.hpp"
#include "battle/BattleEndOverlay441910.hpp"

#define LEFT_DRAWING fighters[0]->overlayTextures
#define RIGHT_DRAWING fighters[1]->overlayTextures
#define QUAD reinterpret_cast<SpriteTransform*>(&packet)

void BattleScene::RenderEndOverlay() {
    if (g_CombatMode == CombatMode::Practice) {
        RenderModeFive();
    } else {
        RenderQuadPacket5E68C0 packet;
        {
            RECT rect;
            textureManager->SetBlendMode(0);
            SetRect(&rect, 0, 0, 640, 480);
            Graphics::DrawFilledRectangle(&rect, D3DCOLOR_ARGB(pauseOverlayAlpha, 0, 0, 0));
            if (pauseOverlayAlpha < 50)
                return;
            if (pauseMenuOpen == 0)
                return;
            if (g_ReplayModeAt0066C238 != ReplayMode::Playback) {
                SetRect(&rect, 0, 0, 256, 256);
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuadFromRect(&rect);
                if (fighters[0]->cpuControlled == 0 && fighters[1]->cpuControlled == 0) {
                    QUAD->TranslateQuad(32.0f, 280.0f, 0.0f);
                    LEFT_DRAWING->DrawQuad(fighters[0]->overlayTextureCount - 1, packet, &rect, 0xFFFFFFFF);
                    QUAD->TranslateQuad(320.0f, 0.0f, 0.0f);
                    RIGHT_DRAWING->DrawQuad(fighters[1]->overlayTextureCount - 1, packet, &rect, 0xFFFFFFFF);
                } else if (fighters[0]->cpuControlled != 0) {
                    QUAD->TranslateQuad(192.0f, 280.0f, 0.0f);
                    RIGHT_DRAWING->DrawQuad(fighters[1]->overlayTextureCount - 1, packet, &rect, 0xFFFFFFFF);
                } else {
                    QUAD->TranslateQuad(192.0f, 280.0f, 0.0f);
                    LEFT_DRAWING->DrawQuad(fighters[0]->overlayTextureCount - 1, packet, &rect, 0xFFFFFFFF);
                }
            }
            if (battlePhase == BattlePhase::StoryContinuePrompt && g_ContinueCountAt00671623 > 0) {
                SetRect(&rect, 288, 192, 512, 224);
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(176.0f, 230.0f, 400.0f, 262.0f);
                textureManager->DrawQuad(0, packet, &rect, 0xFFFFFFFF);
                SetRect(&rect, 512, g_ContinueCountAt00671623 * 32 + 96, 576, g_ContinueCountAt00671623 * 32 + 128);
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(390.0f, 230.0f, 454.0f, 262.0f);
                textureManager->DrawQuad(0, packet, &rect, 0xFFFFFFFF);
            }
            if (battlePhase != BattlePhase::VictoryQuote &&
                (battlePhase != BattlePhase::StoryContinuePrompt || g_ContinueCountAt00671623 != 0)) {
                SetRect(&rect, 384, (pauseMenuRow != 0) * 32 + 128,
                    512, (pauseMenuRow != 0) * 32 + 160);
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(256.0f, 140.0f, 384.0f, 172.0f);
                textureManager->DrawQuad(0, packet, &rect, 0xFFFFFFFF);
            }
            SetRect(&rect, 256, (pauseMenuRow != 1) * 32 + 128,
                384, (pauseMenuRow != 1) * 32 + 160);
            reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(256.0f, 170.0f, 384.0f, 202.0f);
            textureManager->DrawQuad(0, packet, &rect, 0xFFFFFFFF);
            if (g_ReplayModeAt0066C238 != ReplayMode::Playback && g_ContinueUsedAt00671624 == 0 && battlePhase != BattlePhase::StoryDialogue) {
                SetRect(&rect, 0, (pauseMenuRow != 2) * 32 + 128,
                    256, (pauseMenuRow != 2) * 32 + 155);
                reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(192.0f, 200.0f, 448.0f, 227.0f);
                textureManager->DrawQuad(0, packet, &rect, 0xFFFFFFFF);
            }

        }
    }
}

#undef QUAD
#undef RIGHT_DRAWING
#undef LEFT_DRAWING
