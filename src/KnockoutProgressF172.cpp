#include "FighterRoundOutcomeBytesF992.hpp"
#include "ProgressSelectionKeysF954.hpp"
#include "KnockoutProgressF172.hpp"
#include "BattleScene.hpp"
#include "FighterResourceParameters452B30.hpp"

// Existing byte storage keeps its canonical unsigned carrier. The continuation
// test below explicitly uses the signed byte interpretation observed here.
extern unsigned char g_SequenceCounterAt00671622;
// Observed dword accumulation; original name and signedness remain unknown.
extern unsigned int g_KnockoutAccumulationAt0067160C;

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
    if (field048->health <= 0) {
        F992_OUTCOME(field044).outcomeAt3CE.unsignedAt3CE = 0;
        F992_OUTCOME(field048).outcomeAt3CE.unsignedAt3CE = 1;
        if (reinterpret_cast<int&>(field048->field3A4) > 0) {
            if (g_FrameClockMode == 1) {
                if (field044->field464 != 0)
                    CARD_RECORDS->MarkCardFlag(
                        reinterpret_cast<signed char*>(field048->field384)[field048->field39D]);
                CARD_RECORDS->IncrementCardCounter(
                    reinterpret_cast<signed char*>(field048->field384)[field048->field39D]);
                if (reinterpret_cast<int&>(field048->field3A4) > CARD_RECORDS->GetCardValue(
                        reinterpret_cast<signed char*>(field048->field384)[field048->field39D])) {
                    CARD_RECORDS->SetCardValue(
                        reinterpret_cast<signed char*>(field048->field384)[field048->field39D],
                        reinterpret_cast<int&>(field048->field3A4));
                }
            }
            g_KnockoutAccumulationAt0067160C += field048->field3A8;
            reinterpret_cast<unsigned long&>(field044->score) = reinterpret_cast<unsigned long&>(field044->score) + reinterpret_cast<int&>(field048->field3A4);
            if (reinterpret_cast<unsigned long&>(field044->score) > g_MaxCombatScore)
                g_MaxCombatScore = reinterpret_cast<unsigned long&>(field044->score);
            field06C = 120;
            field068 = reinterpret_cast<int&>(field048->field3A4);
            reinterpret_cast<int&>(field048->field3A4) = 0;
        }
        if (field044->field3A0 > 0)
            field044->field36C = 0.0f;
        field044->field3A0 = 0;
        field048->field3A0 = 0;
        field044->field39C = 0;
        field048->field39C = 0;
        field048->field39D--;
        F992_OUTCOME(field048).continuationAt3CF = 0;
        field048->recoverableHealth = 0;
        field044->field464 = 1;
        if (field044->health <= 0)
            field044->health = 1;
        if (field048->field39D > 0) {
            field018 = 9;
            field00C = 147;
            if (reinterpret_cast<signed char*>(field048->field32A + 1)[field048->field39D] == 0) {
                field048->health = field048->healthLimits[field048->field39D];
                field048->recoverableHealth = field048->healthLimits[field048->field39D];
                reinterpret_cast<int&>(field048->field3A8) = 0;
            }
        } else {
            field018 = 11;
            field00C = 180;
            field01A = 60;
        }
    } else if (field044->health <= 0) {
        field048->recoverableHealth = field048->healthLimits[field048->field39D];
        field044->field3A0 = 0;
        field044->field39C = 0;
        field044->field39D--;
        F992_OUTCOME(field044).outcomeAt3CE.unsignedAt3CE = 1;
        F992_OUTCOME(field048).outcomeAt3CE.unsignedAt3CE = 0;
        F992_OUTCOME(field044).continuationAt3CF = 0;
        field044->field464 = 0;
        if (field044->field39D != 0) {
            field044->recoverableHealth = 10000;
            field044->health = 10000;
            field018 = 10;
            field00C = 300;
            field01A = 60;
        } else if (static_cast<signed char>(g_SequenceCounterAt00671622) > 0) {
            g_SequenceCounterAt00671622--;
            field044->field39D = 2;
            field018 = 10;
            field00C = 300;
            field01A = 60;
        } else {
            field018 = 11;
            field00C = 180;
            field01A = 60;
        }
    }
}

#undef CARD_RECORDS
#undef CARD_ARRAY
