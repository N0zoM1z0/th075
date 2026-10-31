#include "FighterComboBorrowedF1006.hpp"
#include "FighterVitalBorrowedF999.hpp"
#include "FighterRoundOutcomeBytesF992.hpp"
#include "FighterFadeBorrowedF986.hpp"
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

#define WORD(offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this) + (offset)))
void SakuyaFighterActionsF159::ResetRound()
{
    WORD(0xEFC) = 0;
    WORD(0xEFE) = 0;
    WORD(0xF16) = 0;
    WORD(0xF00) = 0;
    WORD(0xF02) = 0;
    WORD(0xF04) = 0;
    WORD(0xF06) = 0;
    WORD(0xF08) = 0;
    WORD(0xF0A) = 0;
    WORD(0xEFA) = 0;
    WORD(0xF0C) = 0;
    WORD(0xF0E) = 0;
    WORD(0xF10) = 0;
    WORD(0xF12) = 0;
    WORD(0xF14) = 0;
    WORD(0x512) = 0;
    WORD(0x514) = 0;
    WORD(0x516) = 0;
    WORD(0xF16) = 0;
    reinterpret_cast<FighterBaseActionsF159*>(this)->ResetRound();
}
#undef WORD


#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
void FighterBaseActionsF159::ClearAuxiliaryWords()
{
    FIELD(unsigned int, 0x4F8) = 0;
    FIELD(unsigned int, 0x4FC) = 0;
    FIELD(unsigned int, 0x500) = 0;
    FIELD(unsigned int, 0x504) = 0;
    FIELD(unsigned int, 0x508) = 0;
    FIELD(unsigned int, 0x50C) = 0;
}

void RoundResetInputCountsF159::ClearHeldCounts()
{
    memset(reinterpret_cast<unsigned char*>(this) + 0x2C, 0, 0x1C);
}

void FighterBaseActionsF159::ResetRound()
{
    FIELD(unsigned int, 0x4DC) = 0;
    FIELD(unsigned int, 0x4E0) = 0;
    FIELD(unsigned int, 0x4E8) = 0;
    FIELD(unsigned int, 0x4EC) = 0;
    FIELD(unsigned int, 0x4F0) = 0;
    FIELD(unsigned int, 0x4F4) = 0;
    FIELD(unsigned char, 0x510) = 0;
    ClearAuxiliaryWords();
    FIELD(float, 0x44) = (FIELD(signed char, 0x2CC) == 1) * 320 + 480;
    FIELD(float, 0x48) = 0.0f;
    FIELD(float, 0x50) = 0.0f;
    FIELD(float, 0x54) = 0.0f;
    FIELD(unsigned int, 0x488) = 0;
    FIELD(unsigned int, 0x48C) = 0;
    FIELD(unsigned int, 0x490) = 0;
    FIELD(float, 0x94) = 0.0f;
    FIELD(float, 0x98) = 0.0f;
    FIELD(unsigned int, 0x58) = 0;
    FIELD(float, 0x5C) = 0.0f;
    FIELD(unsigned int, 0x8C) = 0;
    FIELD(unsigned int, 0x90) = 0;
    FIELD(short, 0x84) = 0;
    FIELD(short, 0x86) = 0;
    FIELD(short, 0x88) = 0;
    FIELD(short, 0x3BC) = 0;
    FIELD(short, 0x3CA) = 0;
    FIELD(short, 0x3CC) = 0;
    FIELD(unsigned int, 0x368) = 0;
    FIELD(float, 0x36C) = 0.0f;
    FIELD(short, 0x3B0) = 1000;
    FIELD(short, 0x3B2) = 1000;
    FIELD(short, 0x3B4) = 0;
    FIELD(short, 0x3B6) = 0;
    FIELD(short, 0x3A0) = 0;
    FIELD(unsigned char, 0x39C) = 0;
    FIELD(unsigned char, 0x3AC) = 0;
    FIELD(unsigned char, 0x3AD) = 0;
    FIELD(unsigned char, 0x3AE) = 0;
    F1006_COMBO(this).countAt3C4 = 0;
    F1006_COMBO(this).damageAt3C6 = 0;
    FIELD(float, 0x3C0) = 1.0f;
    FIELD(short, 0x80) = 0;
    FIELD(unsigned int, 0x7C) = 0;
    FIELD(short, 0x60) = 0;
    FIELD(short, 0x62) = 0;
    FIELD(short, 0x64) = 0;
    reinterpret_cast<FighterAnimationReset453D80*>(this)->BindAnimation();
    FIELD(short, 0x82) = 0;
    FIELD(short, 0x3B8) = 0;
    FIELD(short, 0x3BA) = 0;
    FIELD(short, 0x8A) = 0;
    FIELD(short, 0x3A0) = 0;
    FIELD(unsigned char, 0x40) = 0;
    FIELD(short, 0xEF8) = 0;
    FIELD(signed char, 0x66) = 1 - (FIELD(signed char, 0x2CC) == 1) * 2;
    FIELD(unsigned char, 0x6EF) = 0;
    FIELD(unsigned char, 0x6E6) = 0;
    FIELD(unsigned char, 0x6E6) = 0;
    FIELD(short, 0x6EA) = 25;
    FIELD(short, 0x6EC) = 0;
    FIELD(unsigned char, 0x6E9) = 0;
    FIELD(unsigned char, 0x6E8) = 1;
    FIELD(signed char, 0x6E7) = -1;
    FIELD(unsigned char, 0x6EE) = 0;
    FIELD(unsigned int, 0x47C) = 0;
    FIELD(unsigned char, 0x484) = 0;
    FIELD(float, 0x9C) = 1.0f;
    FIELD(float, 0xA0) = 1.0f;
    F986_FADE(this).fadeAlphaAt538 = 0;
    F992_OUTCOME(this).outcomeAt3CE.unsignedAt3CE = 0;
    F992_OUTCOME(this).continuationAt3CF = 1;
    reinterpret_cast<RoundResetInputCountsF159*>(reinterpret_cast<unsigned char*>(this) + 0x494)->ClearHeldCounts();
    FIELD(RoundResetEffectsF159*, 0x2EC)->DeleteFourLists();
    FIELD(unsigned char, 0x366) = 2;
    FIELD(unsigned char, 0x39D) = 2;
    FIELD(unsigned int, 0x3A8) = 0;
    FIELD(unsigned int, 0x3A4) = 0;
    F999_VITAL(this).currentAt324 = 10000;
    F999_VITAL(this).recoverableAt326 = 10000;
    FIELD(unsigned char, 0x52C) = 0;
    FIELD(unsigned char, 0x52D) = 0;
    FIELD(unsigned char, 0x52F) = 0;
    FIELD(unsigned char, 0x52E) = 0;
    FIELD(unsigned char, 0x530) = 0;
    FIELD(unsigned char, 0x531) = 0;
    FIELD(short, 0x6FA) = -1;
    FIELD(short, 0x6FC) = 0;
    FIELD(unsigned char, 0x6F8) = 0;
    FIELD(short, 0x512) = 0;
    FIELD(short, 0x514) = 0;
    FIELD(short, 0x516) = 0;
    FIELD(float, 0x314) = 0.0f;
    FIELD(float, 0x318) = 0.0f;
    FIELD(float, 0x31C) = 0.0f;
    FIELD(float, 0x320) = 0.0f;
}
#undef FIELD
