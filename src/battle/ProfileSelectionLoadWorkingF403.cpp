#include "engine/GameProgress.hpp"
#include <string.h>
// Copies a ranked entry's name back into the working bytes (the reverse
// of CopyWorkingNameToRank).
void GameProgress::CopyRankNameToWorking(signed char slot) {
    memcpy(workingPlayerName,
           characters[selectedFighter].difficulties[selectedDifficulty].scores[slot].name,8);
}
