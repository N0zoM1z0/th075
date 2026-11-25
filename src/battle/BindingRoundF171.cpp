#include "battle/BindingRoundF171.hpp"
#include "input/Input.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include <string.h>

namespace Input { extern unsigned char g_JoystickCount; }


void InputMapping4388D0::SetBindings(const void* source)
{
    memcpy(&keys, source, sizeof(keys));
    if (keys.device >= Input::g_JoystickCount) {
        // Original CP932 message: パッドが見つかりません
        Input::ShowError("\x83\x70\x83\x62\x83\x68\x82\xaa\x8c\xa9\x82\xc2\x82\xa9\x82\xe8\x82\xdc\x82\xb9\x82\xf1");
        memset(&keys, 0, sizeof(keys));
        keys.device = -1;
    }
    memset(&held, 0, sizeof(held));
}

void Fighter::SetBindings(const void* source)
{
    inputBindings.SetBindings(source);
}

void Fighter::BindOpponent(void* other)
{
    opponent = static_cast<Fighter*>(other);
}

void Fighter::RecordRoundFields(
    signed char index, short health, signed char kind, signed char recordId,
    signed char spellVariant, int bonus, int bonusFrames,
    int bonusDecay)
{
    if (opponent->roundsRemaining < index)
        opponent->roundsRemaining = index;
    if (index == 1) {
        opponent->healthLimits[0] = health;
        opponent->roundKind[0] = kind;
        opponent->roundSpellRecordIds[0] = recordId;
        opponent->roundSpellVariants[0] = spellVariant;
        opponent->roundSpellBonuses[0] = bonus;
        opponent->roundSpellBonusFrames[0] = bonusFrames;
        opponent->roundSpellBonusDecay[0] = bonusDecay;
    }
    opponent->healthLimits[index] = health;
    opponent->roundKind[index] = kind;
    opponent->roundSpellRecordIds[index] = recordId;
    opponent->roundSpellVariants[index] = spellVariant;
    opponent->roundSpellBonuses[index] = bonus;
    opponent->roundSpellBonusFrames[index] = bonusFrames;
    opponent->roundSpellBonusDecay[index] = bonusDecay;
    opponent->startingRoundCount = opponent->roundsRemaining;
}
