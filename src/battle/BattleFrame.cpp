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
    if (!field0A0 && !field0A1) {
        ++field010;
        if (g_ReplayModeAt0066C238 == 2 || g_ReplayModeAt0066C238 == 1) ++field014;
        UpdatePlayerEffects();
        ApplySequence();
        if (field01A <= 0) {
            fighters[0]->AdvanceGuardedState();
            fighters[1]->AdvanceGuardedState();
            if (field018 == 7) {
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
                if (field018 != 4 && field018 != 9 && field018 != 0)
                    reinterpret_cast<BattleScene *>(this)->ResolveActiveCollisions();
                ResolveBodySeparation();
                if (g_CombatMode != 5) ResolveRoundEndMode();
            }
            fighters[0]->AdvancePosition();
            fighters[1]->AdvancePosition();
            UpdatePlayerCounters();
            fighters[0]->AdvanceAuxiliary();
            fighters[1]->AdvanceAuxiliary();
            g_CombatEffects.AdvanceAndPrune();
            g_CurrentBattleStageAt00671424->Advance();
        } else {
            --field01A;
        }
        if (g_FramePresentToggle) Present();
        if (g_OptionsFlagAt00671430) g_FramePresentToggle = 1;
        else g_FramePresentToggle = static_cast<int>(!g_FramePresentToggle);
        return AdvanceState();
    } else {
        HandlePauseMenu();
        if (field0A0) {
            if (field0A1 < 128) field0A1 += 5;
        } else {
            if (field0A1 > 0) field0A1 -= 5;
        }
        if (g_FramePresentToggle) Present();
        if (g_OptionsFlagAt00671430) g_FramePresentToggle = 1;
        else g_FramePresentToggle = static_cast<int>(!g_FramePresentToggle);
        if (!field0A0 && !field0A1) {
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
    if (field018 != 1) return;
    if (g_CombatMode == 3) ResolveKnockout();
    else EnterRoundEnd();
}
void BattleScene::UpdatePlayerCounters()
{
    fighters[0]->UpdateCounters();
    fighters[1]->UpdateCounters();
    fighters[0]->field3BA = fighters[0]->field3B8;
    fighters[1]->field3BA = fighters[1]->field3B8;
    if (fighters[0]->field3B8 > 0) --fighters[0]->field3B8;
    if (fighters[1]->field3B8 > 0) --fighters[1]->field3B8;
}
void Fighter::AdvanceGuardedState()
{
    if (field082 == 0 && opponent->field3B8 == 0) {
        if (action < 50) ForwardBaseAction();
        if (action >= 50 && action < 150 && y > 0.0f)
            ChooseFrameAction();
        DispatchActions();
    }
}
void Fighter::AdvancePosition()
{
    if (field082 == 0 && opponent->field3B8 == 0) {
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
    } else if (field2CD != 0 && g_CombatMode == 5 && field52E == 0) {
        if (rand() % 2) ResetPrimaryCounters(180);
        else ResetPrimaryCounters(181);
    } else if (inputX != 0 &&
        (inputA | inputB | inputC | static_cast<int>(inputD))) {
        if (facing * inputX > 0)
            ResetPrimaryCounters(180);
        else ResetPrimaryCounters(181);
    }
}
