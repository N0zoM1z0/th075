#include <string.h>
#include "battle/FighterVirtualActionsF159.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"

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
    sequenceTimer = 0;
    fieldEFE = 0;
    fieldF16 = 0;
    scriptCounterF00 = 0;
    scriptCounterF02 = 0;
    fieldF04 = 0;
    fieldF06 = 0;
    fieldF08 = 0;
    fieldF0A = 0;
    fieldEFA = 0;
    fieldF0C = 0;
    fieldF0E = 0;
    fieldF10 = 0;
    fieldF12 = 0;
    fieldF14 = 0;
    aiWaitTimer = 0;
    aiStep = 0;
    aiCardTimer = 0;
    fieldF16 = 0;
    reinterpret_cast<Fighter*>(this)->Fighter::ResetRound();
}


void Fighter::ClearAuxiliaryWords()
{
    bufferedX = 0;
    bufferedY = 0;
    bufferedA = 0;
    bufferedB = 0;
    bufferedC = 0;
    bufferedD = 0;
}

void InputMapping4388D0::ClearHeldCounts()
{
    memset(&held, 0, sizeof(held));
}

void Fighter::ResetRound()
{
    inputX = 0;
    inputY = 0;
    inputA = 0;
    inputB = 0;
    inputC = 0;
    inputD = 0;
    field510 = 0;
    ClearAuxiliaryWords();
    x = (playerSide == 1) * 320 + 480;
    y = 0.0f;
    velocityX = 0.0f;
    velocityY = 0.0f;
    field488 = 0.0f;
    field48C = 0;
    field490 = 0.0f;
    field094 = 0.0f;
    field098 = 0.0f;
    field058 = 0;
    field05C = 0.0f;
    field08C = 0.0f;
    field090 = 0.0f;
    field084 = 0;
    field086 = 0;
    field088 = 0;
    guardResponseCooldown = 0;
    field3CA = 0;
    field3CC = 0;
    pendingSpellCharge = 0.0f;
    spellPower = 0.0f;
    spirit = 1000;
    spiritPrevious = 1000;
    spiritWait = 0;
    spiritCooldown = 0;
    spellTimer = 0;
    spellDeclarationExpired = 0;
    field3AC = 0;
    field3AD = 0;
    field3AE = 0;
    comboCount = 0;
    comboDamage = 0;
    comboRate = 1.0f;
    field080 = 0;
    field07C = 0;
    action = 0;
    animationStage = 0;
    animationFrame = 0;
    BindAnimation();
    field082 = 0;
    opponentFreezeTimer = 0;
    opponentFreezeSnapshot = 0;
    field08A = 0;
    spellTimer = 0;
    field040 = 0;
    fieldEF8 = 0;
    facing = 1 - (playerSide == 1) * 2;
    field6EF = 0;
    noticeState = 0;
    noticeState = 0;
    noticeAxis = 25;
    noticeExtent = 0;
    noticeColor = 0;
    noticeFirst = 1;
    noticeBadge = -1;
    noticeEnabled = 0;
    field47C = 0;
    field484 = 0;
    field09C = 1.0f;
    field0A0 = 1.0f;
    fadeAlpha = 0;
    this->field3CE.unsignedAt3CE = 0;
    this->field3CF = 1;
    inputBindings.ClearHeldCounts();
    field2EC->DeleteFourLists();
    bombCount = 2;
    field39D = 2;
    field3A8 = 0;
    field3A4 = 0;
    health = 10000;
    recoverableHealth = 10000;
    practiceSpellSelection = 0;
    practiceSpellStock = 0;
    practiceGuardMode = 0;
    practiceManualAirRecovery = 0;
    practiceActionMode = 0;
    practiceCenterPosition = 0;
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
