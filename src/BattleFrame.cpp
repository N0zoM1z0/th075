#include <stdlib.h>
#include "Graphics.hpp"
#include "BattleFrame.hpp"
#define FIELD(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define PLAYER(offset) FIELD(FrameActor *, this, offset)
#define EFFECTS(offset) FIELD(FrameEffectOwner *, PLAYER(offset), 0x2EC)
short BattleFrame::UpdateFrame()
{
    PollPauseShortcut();
    OnFrameStart();
    if (!FIELD(unsigned char, this, 0xA0) && !FIELD(unsigned char, this, 0xA1)) {
        ++FIELD(int, this, 0x10);
        if (g_FrameClockMode == 2 || g_FrameClockMode == 1) ++FIELD(int, this, 0x14);
        UpdatePlayerEffects();
        ApplySequence();
        if (FIELD(short, this, 0x1A) <= 0) {
            PLAYER(0x44)->AdvanceGuardedState();
            PLAYER(0x48)->AdvanceGuardedState();
            if (FIELD(signed char, this, 0x18) == 7) {
                PLAYER(0x44)->AdvanceMode7();
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
                if (FIELD(signed char, this, 0x18) != 4 && FIELD(signed char, this, 0x18) != 9 && FIELD(signed char, this, 0x18) != 0)
                    reinterpret_cast<BattleActiveCollision *>(this)->ResolveActiveCollisions();
                ResolveBodySeparation();
                if (g_CombatMode != 5) ResolveRoundEndMode();
            }
            PLAYER(0x44)->AdvancePosition();
            PLAYER(0x48)->AdvancePosition();
            UpdatePlayerCounters();
            PLAYER(0x44)->FinishFrame();
            PLAYER(0x48)->FinishFrame();
            reinterpret_cast<FrameAuxEffects *>(&g_CombatEffects)->AdvanceAndPrune();
            g_DrawDispatcher->Slot1();
        } else {
            --FIELD(short, this, 0x1A);
        }
        if (g_FramePresentToggle) Present();
        if (g_FramePresentEveryTick) g_FramePresentToggle = 1;
        else g_FramePresentToggle = static_cast<int>(!g_FramePresentToggle);
        return AdvanceState();
    } else {
        HandlePauseMenu();
        if (FIELD(unsigned char, this, 0xA0)) {
            if (FIELD(unsigned char, this, 0xA1) < 128) FIELD(unsigned char, this, 0xA1) += 5;
        } else {
            if (FIELD(unsigned char, this, 0xA1) > 0) FIELD(unsigned char, this, 0xA1) -= 5;
        }
        if (g_FramePresentToggle) Present();
        if (g_FramePresentEveryTick) g_FramePresentToggle = 1;
        else g_FramePresentToggle = static_cast<int>(!g_FramePresentToggle);
        if (!FIELD(unsigned char, this, 0xA0) && !FIELD(unsigned char, this, 0xA1)) {
            FIELD(FrameInputSnapshot, PLAYER(0x44), 0x4C0) = FIELD(FrameInputSnapshot, this, 0xA4);
            FIELD(FrameInputSnapshot, PLAYER(0x48), 0x4C0) = FIELD(FrameInputSnapshot, this, 0xC0);
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
    if (FIELD(signed char, this, 0x18) != 1) return;
    if (g_CombatMode == 3) ResolveSpecialRoundEnd();
    else ResolveNormalRoundEnd();
}
void BattleFrame::UpdatePlayerCounters()
{
    PLAYER(0x44)->UpdateCounters();
    PLAYER(0x48)->UpdateCounters();
    FIELD(short, PLAYER(0x44), 0x3BA) = FIELD(short, PLAYER(0x44), 0x3B8);
    FIELD(short, PLAYER(0x48), 0x3BA) = FIELD(short, PLAYER(0x48), 0x3B8);
    if (FIELD(short, PLAYER(0x44), 0x3B8) > 0) --FIELD(short, PLAYER(0x44), 0x3B8);
    if (FIELD(short, PLAYER(0x48), 0x3B8) > 0) --FIELD(short, PLAYER(0x48), 0x3B8);
}
void FrameActor::AdvanceGuardedState()
{
    if (FIELD(short, this, 0x82) == 0 && FIELD(short, FIELD(void *, this, 0x2E8), 0x3B8) == 0) {
        if (FIELD(short, this, 0x60) < 50) Slot8();
        if (FIELD(short, this, 0x60) >= 50 && FIELD(short, this, 0x60) < 150 && FIELD(float, this, 0x48) > 0.0f)
            ChooseAction();
        Slot10();
    }
}
void FrameActor::AdvancePosition()
{
    if (FIELD(short, this, 0x82) == 0 && FIELD(short, FIELD(void *, this, 0x2E8), 0x3B8) == 0) {
        if ((CheckHorizontalLimits() * FIELD(signed char, this, 0x66)) *
            (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x50) + *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x488) + *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(FIELD(void *, this, 0x2E8)) + 0x490)) >= 0.0f)
            *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) += FIELD(signed char, this, 0x66) *
                (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x50) + *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x488) + *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(FIELD(void *, this, 0x2E8)) + 0x490));
        if (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) < 40.0f) *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) = 40.0f;
        if (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) > 1240.0f) *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) = 1240.0f;
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x48) += *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x54);
        if (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x48) < 0.0f) *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x48) = 0.0f;
    }
}

signed char FrameActor::CheckHorizontalLimits()
{
    if (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) - 40.0f <= 0.0f ||
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(FIELD(void *, this, 0x2E8)) + 0x44) - *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) > 880.0f) return 1;
    if (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) + 40.0f >= 1280.0f ||
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) - *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(FIELD(void *, this, 0x2E8)) + 0x44) > 880.0f) return -1;
    return 0;
}
void FrameActor::ChooseAction()
{
    if (FIELD(unsigned long, FIELD(void *, this, 0x74), 0x3C) & 0x100000) return;
    if (FIELD(short, this, 0x324) <= 0) return;
    if (FIELD(short, this, 0x3C8) > 0) {
        if (FIELD(float, this, 0x48) > 0.0f) --FIELD(short, this, 0x3C8);
    } else if (FIELD(signed char, this, 0x2CD) != 0 && g_CombatMode == 5 && FIELD(signed char, this, 0x52E) == 0) {
        if (rand() % 2) reinterpret_cast<CombatActor *>(this)->ResetPrimaryCounters(180);
        else reinterpret_cast<CombatActor *>(this)->ResetPrimaryCounters(181);
    } else if (FIELD(int, this, 0x4DC) != 0 &&
        (FIELD(int, this, 0x4E8) | FIELD(int, this, 0x4EC) | FIELD(int, this, 0x4F0) | FIELD(int, this, 0x4F4))) {
        if (FIELD(signed char, this, 0x66) * FIELD(int, this, 0x4DC) > 0)
            reinterpret_cast<CombatActor *>(this)->ResetPrimaryCounters(180);
        else reinterpret_cast<CombatActor *>(this)->ResetPrimaryCounters(181);
    }
}
