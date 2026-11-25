#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "engine/GameSharedState.hpp"
#include "battle/BackgroundStageBaseF479.hpp"
#include "battle/BattleScene.hpp"
#include <stdlib.h>
#include "graphics/Graphics.hpp"
#include "battle/BattleFrame.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"
#include "battle/CombatEffects.hpp"
unsigned short BattleScene::Update()
{
    PollPauseShortcut();
    Render();
    if (!pauseMenuOpen && !pauseOverlayAlpha) {
        ++elapsedBattleFrames;
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback || g_ReplayModeAt0066C238 == ReplayMode::Recording) ++replayFrame;
        UpdatePlayerEffects();
        ApplySequence();
        if (knockoutFreezeFrames <= 0) {
            fighters[0]->AdvanceGuardedState();
            fighters[1]->AdvanceGuardedState();
            if (battlePhase == BattlePhase::StoryDialogue) {
                fighters[0]->AdvanceSequence();
                fighters[0]->Advance();
                fighters[1]->Advance();
                fighters[0]->field2EC->AdvanceAll();
                fighters[1]->field2EC->AdvanceAll();
                ResolveBodySeparation();
            } else {
                fighters[0]->Advance();
                fighters[1]->Advance();
                fighters[0]->field2EC->AdvanceAll();
                fighters[1]->field2EC->AdvanceAll();
                if (battlePhase != BattlePhase::VersusRoundRecovery && battlePhase != BattlePhase::StoryRoundRecovery && battlePhase != BattlePhase::RoundIntro)
                    reinterpret_cast<BattleScene *>(this)->ResolveActiveCollisions();
                ResolveBodySeparation();
                if (g_CombatMode != CombatMode::Practice) ResolveRoundEndMode();
            }
            fighters[0]->AdvancePosition();
            fighters[1]->AdvancePosition();
            UpdatePlayerCounters();
            fighters[0]->AdvanceAuxiliary();
            fighters[1]->AdvanceAuxiliary();
            g_CombatEffects.AdvanceAndPrune();
            g_CurrentBattleStageAt00671424->Advance();
        } else {
            --knockoutFreezeFrames;
        }
        if (g_FramePresentToggle) Present();
        if (g_OptionsFlagAt00671430) g_FramePresentToggle = 1;
        else g_FramePresentToggle = static_cast<int>(!g_FramePresentToggle);
        return AdvanceState();
    } else {
        HandlePauseMenu();
        if (pauseMenuOpen) {
            if (pauseOverlayAlpha < 128) pauseOverlayAlpha += 5;
        } else {
            if (pauseOverlayAlpha > 0) pauseOverlayAlpha -= 5;
        }
        if (g_FramePresentToggle) Present();
        if (g_OptionsFlagAt00671430) g_FramePresentToggle = 1;
        else g_FramePresentToggle = static_cast<int>(!g_FramePresentToggle);
        if (!pauseMenuOpen && !pauseOverlayAlpha) {
            fighters[0]->inputBindings.held = inputSnapshots[0];
            fighters[1]->inputBindings.held = inputSnapshots[1];
        }
        return 0;
    }
}

void BattleScene::Present()
{
    Graphics::Present();
}
void BattleScene::ResolveRoundEndMode()
{
    if (battlePhase != BattlePhase::Fighting) return;
    if (g_CombatMode == CombatMode::Story) ResolveKnockout();
    else EnterRoundEnd();
}
void BattleScene::UpdatePlayerCounters()
{
    fighters[0]->UpdateCounters();
    fighters[1]->UpdateCounters();
    fighters[0]->opponentFreezeSnapshot = fighters[0]->opponentFreezeTimer;
    fighters[1]->opponentFreezeSnapshot = fighters[1]->opponentFreezeTimer;
    if (fighters[0]->opponentFreezeTimer > 0) --fighters[0]->opponentFreezeTimer;
    if (fighters[1]->opponentFreezeTimer > 0) --fighters[1]->opponentFreezeTimer;
}
void Fighter::AdvanceGuardedState()
{
    if (hitstopFrames == 0 && opponent->opponentFreezeTimer == 0) {
        if (action < 50) ForwardBaseAction();
        if (action >= 50 && action < 150 && y > 0.0f)
            ChooseFrameAction();
        DispatchActions();
    }
}
void Fighter::AdvancePosition()
{
    if (hitstopFrames == 0 && opponent->opponentFreezeTimer == 0) {
        if ((CheckHorizontalLimits() * facing) *
            (velocityX + field488 + opponent->field490) >= 0.0f)
            x += facing *
                (velocityX + field488 + opponent->field490);
        if (x < 40.0f) x = 40.0f;
        if (x > 1240.0f) x = 1240.0f;
        y += velocityY;
        if (y < 0.0f) y = 0.0f;
    }
}

signed char Fighter::CheckHorizontalLimits()
{
    if (x - 40.0f <= 0.0f ||
        opponent->x - x > 880.0f) return 1;
    if (x + 40.0f >= 1280.0f ||
        x - opponent->x > 880.0f) return -1;
    return 0;
}
void Fighter::ChooseFrameAction()
{
    if (frameInfo->flags & 0x100000) return;
    if (health <= 0) return;
    if (flashGauge > 0) {
        if (y > 0.0f) --flashGauge;
    } else if (cpuControlled != 0 && g_CombatMode == CombatMode::Practice && practiceManualAirRecovery == 0) {
        if (rand() % 2) ResetPrimaryCounters(180);
        else ResetPrimaryCounters(181);
    } else if (inputX != 0 &&
        (inputA | inputB | inputC | static_cast<int>(inputD))) {
        if (facing * inputX > 0)
            ResetPrimaryCounters(180);
        else ResetPrimaryCounters(181);
    }
}
