#include "GameSharedState.hpp"
#include "FighterResourceParameters452B30.hpp"
#include "GameProgress.hpp"

void Fighter::SelectResourceParameters()
{
    field3A2 = 0;
    if (field2CD != 0 && g_CombatMode == 3) {
        field3A0 = 9999;
        field3A4 =
            field3D0[field39D];
        field3A8 =
            field400[field39D];
        if (g_ReplayModeAt0066C238 == 1)
            g_GameProgress.IncrementSelectedWordCounter(
                reinterpret_cast<signed char*>(field384)[field39D]);
    } else {
        field3A0 = static_cast<short>(static_cast<int>(field36C * 8800.0f / 900.0f) + 1201);
        field464 = 0;
    }
}
