#include "FighterRoundOutcomeBytesF992.hpp"
#include <string.h>
#include "FighterAnimationReset453D80.hpp"
#include "FighterVirtualActionsF159.hpp"

// The reviewed derived policies share these used no-argument call contracts.
#define DEFINE_FORWARD(owner) \
void owner::ForwardBaseAction() \
{ \
    reinterpret_cast<FighterBaseActionsF159*>(this)->SelectMovementAnimation(); \
}

#define DEFINE_NO_OP(owner, slot) \
void owner::NoOpSlot##slot() \
{ \
}

DEFINE_FORWARD(ReimuFighterActionsF159)
DEFINE_NO_OP(ReimuFighterActionsF159, 9)
DEFINE_NO_OP(ReimuFighterActionsF159, 18)
DEFINE_FORWARD(MarisaFighterActionsF159)
DEFINE_NO_OP(MarisaFighterActionsF159, 18)
DEFINE_FORWARD(SakuyaFighterActionsF159)
DEFINE_NO_OP(SakuyaFighterActionsF159, 9)
DEFINE_NO_OP(SakuyaFighterActionsF159, 18)
DEFINE_FORWARD(AliceFighterActionsF159)
DEFINE_NO_OP(AliceFighterActionsF159, 9)
DEFINE_NO_OP(AliceFighterActionsF159, 18)
DEFINE_FORWARD(PatchouliFighterActionsF159)
DEFINE_NO_OP(PatchouliFighterActionsF159, 9)
DEFINE_NO_OP(PatchouliFighterActionsF159, 18)
DEFINE_FORWARD(YoumuFighterActionsF159)
DEFINE_NO_OP(YoumuFighterActionsF159, 9)
DEFINE_NO_OP(YoumuFighterActionsF159, 18)
DEFINE_FORWARD(RemiliaFighterActionsF159)
DEFINE_NO_OP(RemiliaFighterActionsF159, 9)
DEFINE_NO_OP(RemiliaFighterActionsF159, 18)
DEFINE_FORWARD(YuyukoFighterActionsF159)
DEFINE_NO_OP(YuyukoFighterActionsF159, 9)
DEFINE_NO_OP(YuyukoFighterActionsF159, 18)
DEFINE_FORWARD(YukariFighterActionsF159)
DEFINE_NO_OP(YukariFighterActionsF159, 9)
DEFINE_NO_OP(YukariFighterActionsF159, 18)
DEFINE_FORWARD(SuikaFighterActionsF159)
DEFINE_NO_OP(SuikaFighterActionsF159, 9)
DEFINE_NO_OP(SuikaFighterActionsF159, 18)
DEFINE_FORWARD(MeilingFighterActionsF159)
DEFINE_NO_OP(MeilingFighterActionsF159, 9)
DEFINE_NO_OP(MeilingFighterActionsF159, 18)

#undef DEFINE_NO_OP
#undef DEFINE_FORWARD

void SakuyaFighterActionsF159::ResetRound()
{
    reinterpret_cast<unsigned short&>(sequenceTimer) = 0;
    fieldEFE = 0;
    fieldF16 = 0;
    scriptCounterF00 = 0;
    scriptCounterF02 = 0;
    reinterpret_cast<unsigned short&>(fieldF04) = 0;
    fieldF06 = 0;
    fieldF08 = 0;
    reinterpret_cast<unsigned short&>(fieldF0A) = 0;
    fieldEFA = 0;
    reinterpret_cast<unsigned short&>(fieldF0C) = 0;
    reinterpret_cast<unsigned short&>(fieldF0E) = 0;
    fieldF10 = 0;
    fieldF12 = 0;
    fieldF14 = 0;
    reinterpret_cast<unsigned short&>(aiWaitTimer) = 0;
    reinterpret_cast<unsigned short&>(aiStep) = 0;
    reinterpret_cast<unsigned short&>(aiCardTimer) = 0;
    fieldF16 = 0;
    reinterpret_cast<FighterBaseActionsF159*>(this)->ResetRound();
}


void FighterBaseActionsF159::ClearAuxiliaryWords()
{
    reinterpret_cast<unsigned int&>(bufferedX) = 0;
    reinterpret_cast<unsigned int&>(bufferedY) = 0;
    reinterpret_cast<unsigned int&>(bufferedA) = 0;
    reinterpret_cast<unsigned int&>(bufferedB) = 0;
    reinterpret_cast<unsigned int&>(bufferedC) = 0;
    reinterpret_cast<unsigned int&>(bufferedD) = 0;
}

void RoundResetInputCountsF159::ClearHeldCounts()
{
    memset(reinterpret_cast<unsigned char*>(this) + 0x2C, 0, 0x1C);
}

void FighterBaseActionsF159::ResetRound()
{
    reinterpret_cast<unsigned int&>(inputX) = 0;
    reinterpret_cast<unsigned int&>(inputY) = 0;
    reinterpret_cast<unsigned int&>(inputA) = 0;
    reinterpret_cast<unsigned int&>(inputB) = 0;
    reinterpret_cast<unsigned int&>(inputC) = 0;
    reinterpret_cast<unsigned int&>(inputD) = 0;
    field510 = 0;
    ClearAuxiliaryWords();
    x = (field2CC == 1) * 320 + 480;
    y = 0.0f;
    velocityX = 0.0f;
    velocityY = 0.0f;
    reinterpret_cast<unsigned int&>(field488) = 0;
    field48C = 0;
    reinterpret_cast<unsigned int&>(field490) = 0;
    reinterpret_cast<float&>(field094) = 0.0f;
    reinterpret_cast<float&>(field098) = 0.0f;
    field058 = 0;
    field05C = 0.0f;
    reinterpret_cast<unsigned int&>(field08C) = 0;
    reinterpret_cast<unsigned int&>(field090) = 0;
    field084 = 0;
    field086 = 0;
    field088 = 0;
    field3BC = 0;
    field3CA = 0;
    field3CC = 0;
    reinterpret_cast<unsigned int&>(field368) = 0;
    field36C = 0.0f;
    meter = 1000;
    meterPrevious = 1000;
    meterWait = 0;
    meterCooldown = 0;
    field3A0 = 0;
    field39C = 0;
    reinterpret_cast<unsigned char&>(field3AC) = 0;
    reinterpret_cast<unsigned char&>(field3AD) = 0;
    field3AE = 0;
    comboCount = 0;
    comboDamage = 0;
    field3C0 = 1.0f;
    field080 = 0;
    reinterpret_cast<unsigned int&>(field07C) = 0;
    action = 0;
    animationStage = 0;
    animationFrame = 0;
    reinterpret_cast<FighterAnimationReset453D80*>(this)->BindAnimation();
    field082 = 0;
    field3B8 = 0;
    field3BA = 0;
    field08A = 0;
    field3A0 = 0;
    field040 = 0;
    fieldEF8 = 0;
    facing = 1 - (field2CC == 1) * 2;
    field6EF = 0;
    reinterpret_cast<unsigned char&>(noticeState) = 0;
    reinterpret_cast<unsigned char&>(noticeState) = 0;
    noticeAxis = 25;
    noticeExtent = 0;
    noticeColor = 0;
    noticeFirst = 1;
    noticeBadge = -1;
    noticeEnabled = 0;
    reinterpret_cast<unsigned int&>(field47C) = 0;
    reinterpret_cast<unsigned char&>(field484) = 0;
    field09C = 1.0f;
    field0A0 = 1.0f;
    fadeAlpha = 0;
    F992_OUTCOME(this).outcomeAt3CE.unsignedAt3CE = 0;
    F992_OUTCOME(this).continuationAt3CF = 1;
    reinterpret_cast<RoundResetInputCountsF159*>(reinterpret_cast<unsigned char*>(this) + 0x494)->ClearHeldCounts();
    reinterpret_cast<RoundResetEffectsF159*&>(field2EC)->DeleteFourLists();
    reinterpret_cast<unsigned char&>(field366) = 2;
    reinterpret_cast<unsigned char&>(field39D) = 2;
    field3A8 = 0;
    field3A4 = 0;
    health = 10000;
    recoverableHealth = 10000;
    field52C = 0;
    field52D = 0;
    reinterpret_cast<unsigned char&>(field52F) = 0;
    field52E = 0;
    field530 = 0;
    field531 = 0;
    field6FA = -1;
    field6FC = 0;
    field6F8 = 0;
    aiWaitTimer = 0;
    aiStep = 0;
    aiCardTimer = 0;
    field314 = 0.0f;
    field318 = 0.0f;
    field31C = 0.0f;
    field320 = 0.0f;
}
