#include <stdlib.h>
#include "Graphics.hpp"
#include "BattleFrame.hpp"
#include "FrameActorCollisionCountdownF1036.hpp"
#include "FrameActorMotionPairsF1037.hpp"
#define FIELD_AT(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define PLAYER(offset) FIELD_AT(Fighter *, this, offset)
#define EFFECTS(offset) FIELD_AT(FrameEffectOwner *, PLAYER(offset), 0x2EC)
short BattleFrame::UpdateFrame()
{
    PollPauseShortcut();
    OnFrameStart();
    if (!FIELD_AT(unsigned char, this, 0xA0) && !FIELD_AT(unsigned char, this, 0xA1)) {
        ++FIELD_AT(int, this, 0x10);
        if (g_FrameClockMode == 2 || g_FrameClockMode == 1) ++FIELD_AT(int, this, 0x14);
        UpdatePlayerEffects();
        ApplySequence();
        if (FIELD_AT(short, this, 0x1A) <= 0) {
            PLAYER(0x44)->AdvanceGuardedState();
            PLAYER(0x48)->AdvanceGuardedState();
            if (FIELD_AT(signed char, this, 0x18) == 7) {
                PLAYER(0x44)->AdvanceSequence();
                PLAYER(0x44)->Advance();
                PLAYER(0x48)->Advance();
                EFFECTS(0x44)->AdvanceAll();
                EFFECTS(0x48)->AdvanceAll();
                ResolveBodySeparation();
            } else {
                PLAYER(0x44)->Advance();
                PLAYER(0x48)->Advance();
                EFFECTS(0x44)->AdvanceAll();
                EFFECTS(0x48)->AdvanceAll();
                if (FIELD_AT(signed char, this, 0x18) != 4 && FIELD_AT(signed char, this, 0x18) != 9 && FIELD_AT(signed char, this, 0x18) != 0)
                    reinterpret_cast<BattleActiveCollision *>(this)->ResolveActiveCollisions();
                ResolveBodySeparation();
                if (g_CombatMode != 5) ResolveRoundEndMode();
            }
            PLAYER(0x44)->AdvancePosition();
            PLAYER(0x48)->AdvancePosition();
            UpdatePlayerCounters();
            PLAYER(0x44)->AdvanceAuxiliary();
            PLAYER(0x48)->AdvanceAuxiliary();
            reinterpret_cast<FrameAuxEffects *>(&g_CombatEffects)->AdvanceAndPrune();
            g_DrawDispatcher->Slot1();
        } else {
            --FIELD_AT(short, this, 0x1A);
        }
        if (g_FramePresentToggle) Present();
        if (g_FramePresentEveryTick) g_FramePresentToggle = 1;
        else g_FramePresentToggle = static_cast<int>(!g_FramePresentToggle);
        return AdvanceState();
    } else {
        HandlePauseMenu();
        if (FIELD_AT(unsigned char, this, 0xA0)) {
            if (FIELD_AT(unsigned char, this, 0xA1) < 128) FIELD_AT(unsigned char, this, 0xA1) += 5;
        } else {
            if (FIELD_AT(unsigned char, this, 0xA1) > 0) FIELD_AT(unsigned char, this, 0xA1) -= 5;
        }
        if (g_FramePresentToggle) Present();
        if (g_FramePresentEveryTick) g_FramePresentToggle = 1;
        else g_FramePresentToggle = static_cast<int>(!g_FramePresentToggle);
        if (!FIELD_AT(unsigned char, this, 0xA0) && !FIELD_AT(unsigned char, this, 0xA1)) {
            FIELD_AT(FrameInputSnapshot, PLAYER(0x44), 0x4C0) = FIELD_AT(FrameInputSnapshot, this, 0xA4);
            FIELD_AT(FrameInputSnapshot, PLAYER(0x48), 0x4C0) = FIELD_AT(FrameInputSnapshot, this, 0xC0);
        }
        return 0;
    }
}

void BattleFrame::Present()
{
    Graphics::Present();
}
void BattleFrame::ResolveRoundEndMode()
{
    if (FIELD_AT(signed char, this, 0x18) != 1) return;
    if (g_CombatMode == 3) ResolveSpecialRoundEnd();
    else ResolveNormalRoundEnd();
}
void BattleFrame::UpdatePlayerCounters()
{
    PLAYER(0x44)->UpdateCounters();
    PLAYER(0x48)->UpdateCounters();
    F1036_COLLISION(PLAYER(0x44)).previousCountdown = F1036_COLLISION(PLAYER(0x44)).activeCountdown;
    F1036_COLLISION(PLAYER(0x48)).previousCountdown = F1036_COLLISION(PLAYER(0x48)).activeCountdown;
    if (F1036_COLLISION(PLAYER(0x44)).activeCountdown > 0) --F1036_COLLISION(PLAYER(0x44)).activeCountdown;
    if (F1036_COLLISION(PLAYER(0x48)).activeCountdown > 0) --F1036_COLLISION(PLAYER(0x48)).activeCountdown;
}
void Fighter::AdvanceGuardedState()
{
    if (field082 == 0 && F1036_COLLISION(opponent).activeCountdown == 0) {
        if (action < 50) ForwardBaseAction();
        if (action >= 50 && action < 150 && y > 0.0f)
            ChooseFrameAction();
        DispatchActions();
    }
}
void Fighter::AdvancePosition()
{
    if (field082 == 0 && F1036_COLLISION(opponent).activeCountdown == 0) {
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
        F1037_POSITION(opponent).xPosition - x > 880.0f) return 1;
    if (x + 40.0f >= 1280.0f ||
        x - F1037_POSITION(opponent).xPosition > 880.0f) return -1;
    return 0;
}
void Fighter::ChooseFrameAction()
{
    if (FIELD_AT(unsigned long, frameInfo, 0x3C) & 0x100000) return;
    if (health <= 0) return;
    if (flashGauge > 0) {
        if (y > 0.0f) --flashGauge;
    } else if (field2CD != 0 && g_CombatMode == 5 && reinterpret_cast<signed char&>(field52E) == 0) {
        if (rand() % 2) reinterpret_cast<CombatActor *>(this)->ResetPrimaryCounters(180);
        else reinterpret_cast<CombatActor *>(this)->ResetPrimaryCounters(181);
    } else if (inputX != 0 &&
        (inputA | inputB | inputC | reinterpret_cast<int&>(inputD))) {
        if (facing * inputX > 0)
            reinterpret_cast<CombatActor *>(this)->ResetPrimaryCounters(180);
        else reinterpret_cast<CombatActor *>(this)->ResetPrimaryCounters(181);
    }
}
