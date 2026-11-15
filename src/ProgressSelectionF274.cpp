#include "GameProgress.hpp"
#include <string.h>

// Borrowed game-profile owner method ABI only. The complete original score
// matrix and profile metadata layout are not inferred from these accesses.
void GameProgress::SetSelection(signed char fighter, signed char difficulty)
{
    selectedFighter=fighter;
    selectedDifficulty=difficulty;
}
ProgressDifficulty* GameProgress::GetSelectedRecordAddress()
{
    return &characters[selectedFighter].difficulties[selectedDifficulty];
}
void GameProgress::StoreWorkingEightBytes(signed char slot)
{
    memcpy(characters[selectedFighter].difficulties[selectedDifficulty].scores[slot].name,
           field16A94,8);
}
