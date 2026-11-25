#include "engine/GameSharedState.hpp"
#include "battle/FighterResourceParameters452B30.hpp"
#include "engine/GameProgress.hpp"

void Fighter::SelectResourceParameters()
{
    field3A2 = 0;
    if (field2CD != 0 && g_CombatMode == 3) {
        spellTimer = 9999;
        field3A4 =
            field3D0[field39D];
        field3A8 =
            field400[field39D];
        if (g_ReplayModeAt0066C238 == 1)
            g_GameProgress.IncrementSelectedWordCounter(
                reinterpret_cast<signed char*>(field384)[field39D]);
    } else {
        spellTimer = static_cast<short>(static_cast<int>(spellPower * 8800.0f / 900.0f) + 1201);
        field464 = 0;
    }
}
