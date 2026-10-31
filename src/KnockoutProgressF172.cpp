#include "ProgressSelectionKeysF954.hpp"
#include "KnockoutProgressF172.hpp"
#include "BattleCombat.hpp"
#include "FighterResourceParameters452B30.hpp"

// Existing byte storage keeps its canonical unsigned carrier. The continuation
// test below explicitly uses the signed byte interpretation observed here.
extern unsigned char g_SequenceCounterAt00671622;
// Observed dword accumulation; original name and signedness remain unknown.
extern unsigned int g_KnockoutAccumulationAt0067160C;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FIRST(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x44) + (offset)))
#define SECOND(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x48) + (offset)))
#define SECOND_ARRAY(type, offset) reinterpret_cast<type*>(FIELD(unsigned char*, 0x48) + (offset))
#define CARD_ARRAY(type, offset) reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + F954_PROGRESS_KEYS(this).fighterAt16AC4 * 0x17F0 + (offset))
#define CARD_RECORDS reinterpret_cast<CardProgressF172*>(&g_BattleRecords)

void CardProgressF172::MarkCardFlag(signed char key)
{
    CARD_ARRAY(unsigned char, 0x4C0)[key] = 1;
}

void CardProgressF172::IncrementCardCounter(signed char key)
{
    CARD_ARRAY(unsigned short, 0x268)[key]++;
}

int CardProgressF172::GetCardValue(signed char key)
{
    return CARD_ARRAY(int, 0x10)[key];
}

void CardProgressF172::SetCardValue(signed char key, int value)
{
    CARD_ARRAY(int, 0x10)[key] = value;
}

void KnockoutResolutionF172::ResolveKnockout()
{
    if (SECOND(short, 0x324) <= 0) {
        FIRST(unsigned char, 0x3CE) = 0;
        SECOND(unsigned char, 0x3CE) = 1;
        if (SECOND(int, 0x3A4) > 0) {
            if (g_FrameClockMode == 1) {
                if (FIRST(unsigned char, 0x464) != 0)
                    CARD_RECORDS->MarkCardFlag(
                        SECOND_ARRAY(signed char, 0x384)[SECOND(signed char, 0x39D)]);
                CARD_RECORDS->IncrementCardCounter(
                    SECOND_ARRAY(signed char, 0x384)[SECOND(signed char, 0x39D)]);
                if (SECOND(int, 0x3A4) > CARD_RECORDS->GetCardValue(
                        SECOND_ARRAY(signed char, 0x384)[SECOND(signed char, 0x39D)])) {
                    CARD_RECORDS->SetCardValue(
                        SECOND_ARRAY(signed char, 0x384)[SECOND(signed char, 0x39D)],
                        SECOND(int, 0x3A4));
                }
            }
            g_KnockoutAccumulationAt0067160C += SECOND(unsigned int, 0x3A8);
            FIRST(unsigned long, 0x2D0) = FIRST(unsigned long, 0x2D0) + SECOND(int, 0x3A4);
            if (FIRST(unsigned long, 0x2D0) > g_MaxCombatScore)
                g_MaxCombatScore = FIRST(unsigned long, 0x2D0);
            FIELD(int, 0x6C) = 120;
            FIELD(int, 0x68) = SECOND(int, 0x3A4);
            SECOND(int, 0x3A4) = 0;
        }
        if (FIRST(short, 0x3A0) > 0)
            FIRST(float, 0x36C) = 0.0f;
        FIRST(short, 0x3A0) = 0;
        SECOND(short, 0x3A0) = 0;
        FIRST(unsigned char, 0x39C) = 0;
        SECOND(unsigned char, 0x39C) = 0;
        SECOND(signed char, 0x39D)--;
        SECOND(unsigned char, 0x3CF) = 0;
        SECOND(short, 0x326) = 0;
        FIRST(unsigned char, 0x464) = 1;
        if (FIRST(short, 0x324) <= 0)
            FIRST(short, 0x324) = 1;
        if (SECOND(signed char, 0x39D) > 0) {
            FIELD(unsigned char, 0x18) = 9;
            FIELD(int, 0xC) = 147;
            if (SECOND_ARRAY(signed char, 0x32B)[SECOND(signed char, 0x39D)] == 0) {
                SECOND(short, 0x324) = SECOND_ARRAY(short, 0x33E)[SECOND(signed char, 0x39D)];
                SECOND(short, 0x326) = SECOND_ARRAY(short, 0x33E)[SECOND(signed char, 0x39D)];
                SECOND(int, 0x3A8) = 0;
            }
        } else {
            FIELD(unsigned char, 0x18) = 11;
            FIELD(int, 0xC) = 180;
            FIELD(short, 0x1A) = 60;
        }
    } else if (FIRST(short, 0x324) <= 0) {
        SECOND(short, 0x326) = SECOND_ARRAY(short, 0x33E)[SECOND(signed char, 0x39D)];
        FIRST(short, 0x3A0) = 0;
        FIRST(unsigned char, 0x39C) = 0;
        FIRST(signed char, 0x39D)--;
        FIRST(unsigned char, 0x3CE) = 1;
        SECOND(unsigned char, 0x3CE) = 0;
        FIRST(unsigned char, 0x3CF) = 0;
        FIRST(unsigned char, 0x464) = 0;
        if (FIRST(signed char, 0x39D) != 0) {
            FIRST(short, 0x326) = 10000;
            FIRST(short, 0x324) = 10000;
            FIELD(unsigned char, 0x18) = 10;
            FIELD(int, 0xC) = 300;
            FIELD(short, 0x1A) = 60;
        } else if (static_cast<signed char>(g_SequenceCounterAt00671622) > 0) {
            g_SequenceCounterAt00671622--;
            FIRST(signed char, 0x39D) = 2;
            FIELD(unsigned char, 0x18) = 10;
            FIELD(int, 0xC) = 300;
            FIELD(short, 0x1A) = 60;
        } else {
            FIELD(unsigned char, 0x18) = 11;
            FIELD(int, 0xC) = 180;
            FIELD(short, 0x1A) = 60;
        }
    }
}

#undef CARD_RECORDS
#undef CARD_ARRAY
#undef SECOND_ARRAY
#undef SECOND
#undef FIRST
#undef FIELD
