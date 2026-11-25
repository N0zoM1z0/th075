#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "battle/PlayerState.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "graphics/TextOverlay.hpp"
#include "battle/CameraMotion.hpp"
#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <d3d8.h>
#include "battle/BattleScene.hpp"

extern const char g_BattleTextureDataAt0065831C[] = "data\\system\\battle.dat";
extern const char g_BattleTextureRootAt00658314[] = "data";
namespace StateAudioF196 {
}


BattleScene::BattleScene()
{
    renderSampleStartMs = timeGetTime();
    textureManager = 0;
    comboDisplays[0] = 0;
    comboDisplays[1] = 0;
    digitAtlas = 0;
    textureManager = new TextureManagerF198();
    textureManager->AllocateUnformattedSlots(11);
    textureManager->LoadDefault(
        g_BattleTextureDataAt0065831C, g_BattleTextureRootAt00658314);
    digitAtlas = new DigitAtlasesF177(
        textureManager->GetTexture(1),
        textureManager->GetTexture(8),
        textureManager->GetTexture(9));
    comboDisplays[0] =
        new ComboDisplay(textureManager->GetTexture(0), 1);
    comboDisplays[1] =
        new ComboDisplay(textureManager->GetTexture(0), -1);
    fighters[0] = g_BattleFightersAt00671418[0];
    fighters[1] = g_BattleFightersAt00671418[1];
    noticeFrames = 0;
    hudOffsetY = 0.0f;
    field094 = 0;
    victoryBadgeX = -300.0f;
    phaseFrames = 200;
    knockoutFreezeFrames = 0;
    pauseMenuOpen = 0;
    pauseOverlayAlpha = 0;
    spellBackgroundBrightness = 1.0f;
    g_FramePresentToggle = 1;
    storyDialogueEnds = 0;
    previousSecondRenderCount = 0;
    currentSecondRenderCount = 0;
    renderSampleStartMs = timeGetTime();
    restoreResources = 0;
    g_InputCanCancelAt00671632 = 0;
    if (g_CombatMode == CombatMode::Story) {
        g_TextRenderer->ConfigureText(35.0f, 360.0f, 1);
        fighters[0]->noticeEnabled = 0;
        hudOffsetY = -200.0f;
        battlePhase = BattlePhase::StoryDialogue;
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
            g_ReplayModeAt0066C238 = ReplayMode::ReplayDialogue;
            g_InputCanCancelAt00671632 = 1;
        }
        if (g_ReplayModeAt0066C238 == ReplayMode::Recording)
            g_ReplayModeAt0066C238 = ReplayMode::LiveDialogue;
    } else {
        CameraMotionOverrideF484::SetOverride(0, 0.0f, 0.0f, 0.0f);
        hudOffsetY = 0.0f;
        battlePhase = BattlePhase::RoundIntro;
    }
    elapsedBattleFrames = 0;
    replayFrame = 0;
    pauseMenuRow = 0;
    attractFrames = 0;
    spellBonusBannerFrames = 0;
    g_SequenceByteAt0066C239 = 255;
    g_SequenceByteAt0066C23A = 255;
    reduceRoundStockKeyHeldFrames = 0;
    escapeKeyHeldFrames = 0;
    victoryQuoteLine = 0;
}
