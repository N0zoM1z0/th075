#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "engine/GameSharedState.hpp"
#include "battle/FighterResourceParameters452B30.hpp"
#include "engine/GameProgress.hpp"

void Fighter::SelectResourceParameters()
{
    spellElapsedFrames = 0;
    if (cpuControlled != 0 && g_CombatMode == CombatMode::Story) {
        spellTimer = 9999;
        remainingSpellBonus =
            roundSpellBonuses[roundsRemaining];
        remainingSpellBonusFrames =
            roundSpellBonusFrames[roundsRemaining];
        if (g_ReplayModeAt0066C238 == ReplayMode::Recording)
            g_GameProgress.RecordSpellAttempt(
                reinterpret_cast<signed char*>(roundSpellRecordIds)[roundsRemaining]);
    } else {
        spellTimer = static_cast<short>(static_cast<int>(spellPower * 8800.0f / 900.0f) + 1201);
        field464 = 0;
    }
}
