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

void GameProgress::IncrementModeCounter(signed char category, signed char key)
{
    modeCounts[category][key]++;
}

unsigned int GameProgress::ReadSelectedWord268(signed char key)
{
    return characters[selectedFighter].difficulties[0].cardCounters[key];
}

unsigned int GameProgress::ReadSelectedWord394(signed char key)
{
    return characters[selectedFighter].difficulties[0].cardCounters2[key];
}

void GameProgress::SetSelectedValue8(int value)
{
    characters[selectedFighter].difficulties[selectedDifficulty].field008 = value;
}

void GameProgress::SetSelectedValue12(int value)
{
    characters[selectedFighter].difficulties[selectedDifficulty].field00C = value;
}

int GameProgress::GetSelectedValue8()
{
    return characters[selectedFighter].difficulties[selectedDifficulty].field008;
}

int GameProgress::GetSelectedValue12()
{
    return characters[selectedFighter].difficulties[selectedDifficulty].field00C;
}
