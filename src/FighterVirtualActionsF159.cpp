#include "FighterRoundOutcomeBytesF992.hpp"
#include <string.h>
#include "FighterAnimationReset453D80.hpp"
#include "FighterVirtualActionsF159.hpp"

// The reviewed derived policies share these used no-argument call contracts.
#define DEFINE_FORWARD(owner) \
void owner::ForwardBaseAction() \
{ \
    reinterpret_cast<Fighter*>(this)->Fighter::ForwardBaseAction(); \
}

#define DEFINE_EMPTY(owner, method) \
void owner::method() \
{ \
}

DEFINE_FORWARD(ReimuFighter)
DEFINE_EMPTY(ReimuFighter, RenderChain)
DEFINE_EMPTY(ReimuFighter, NoOpSlot18)
DEFINE_FORWARD(MarisaFighter)
DEFINE_EMPTY(MarisaFighter, NoOpSlot18)
DEFINE_FORWARD(SakuyaFighter)
DEFINE_EMPTY(SakuyaFighter, RenderChain)
DEFINE_EMPTY(SakuyaFighter, NoOpSlot18)
DEFINE_FORWARD(AliceFighter)
DEFINE_EMPTY(AliceFighter, RenderChain)
DEFINE_EMPTY(AliceFighter, NoOpSlot18)
DEFINE_FORWARD(PatchouliFighter)
DEFINE_EMPTY(PatchouliFighter, RenderChain)
DEFINE_EMPTY(PatchouliFighter, NoOpSlot18)
DEFINE_FORWARD(YoumuFighter)
DEFINE_EMPTY(YoumuFighter, RenderChain)
DEFINE_EMPTY(YoumuFighter, NoOpSlot18)
DEFINE_FORWARD(RemiliaFighter)
DEFINE_EMPTY(RemiliaFighter, RenderChain)
DEFINE_EMPTY(RemiliaFighter, NoOpSlot18)
DEFINE_FORWARD(YuyukoFighter)
DEFINE_EMPTY(YuyukoFighter, RenderChain)
DEFINE_EMPTY(YuyukoFighter, NoOpSlot18)
DEFINE_FORWARD(YukariFighter)
DEFINE_EMPTY(YukariFighter, RenderChain)
DEFINE_EMPTY(YukariFighter, NoOpSlot18)
DEFINE_FORWARD(SuikaFighter)
DEFINE_EMPTY(SuikaFighter, RenderChain)
DEFINE_EMPTY(SuikaFighter, NoOpSlot18)
DEFINE_FORWARD(MeilingFighter)
DEFINE_EMPTY(MeilingFighter, RenderChain)
DEFINE_EMPTY(MeilingFighter, NoOpSlot18)

#undef DEFINE_EMPTY
#undef DEFINE_FORWARD

void SakuyaFighter::ResetRound()
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
    reinterpret_cast<Fighter*>(this)->Fighter::ResetRound();
}


void Fighter::ClearAuxiliaryWords()
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

void Fighter::ResetRound()
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
    field094 = 0.0f;
    field098 = 0.0f;
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
    reinterpret_cast<unsigned int&>(cardGauge) = 0;
    field36C = 0.0f;
    spirit = 1000;
    spiritPrevious = 1000;
    spiritWait = 0;
    spiritCooldown = 0;
    field3A0 = 0;
    field39C = 0;
    reinterpret_cast<unsigned char&>(field3AC) = 0;
    reinterpret_cast<unsigned char&>(field3AD) = 0;
    field3AE = 0;
    comboCount = 0;
    comboDamage = 0;
    comboRate = 1.0f;
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
