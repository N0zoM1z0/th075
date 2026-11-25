#include "engine/GameProgress.hpp"
#include <string.h>
// Copies a ranked entry's name back into the working bytes (the reverse
// of StoreWorkingEightBytes).
void GameProgress::LoadWorkingEightBytes(signed char slot) {
    memcpy(field16A94,
           characters[selectedFighter].difficulties[selectedDifficulty].scores[slot].name,8);
}
