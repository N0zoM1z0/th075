#include "engine/GameProgress.hpp"
#include <string.h>

void GameProgress::SetSelection(signed char fighter, signed char difficulty)
{
    selectedFighter=fighter;
    selectedDifficulty=difficulty;
}
ProgressDifficulty* GameProgress::GetSelectedDifficultyRecord()
{
    return &characters[selectedFighter].difficulties[selectedDifficulty];
}
void GameProgress::CopyWorkingNameToRank(signed char slot)
{
    memcpy(characters[selectedFighter].difficulties[selectedDifficulty].scores[slot].name,
           workingPlayerName,8);
}

void GameProgress::RecordMatchWin(signed char winner, signed char opponent)
{
    matchWinsByFighterPair[winner][opponent]++;
}

unsigned int GameProgress::GetSpellBonusClears(signed char key)
{
    return characters[selectedFighter].difficulties[0].spellBonusClears[key];
}

unsigned int GameProgress::GetSpellAttempts(signed char key)
{
    return characters[selectedFighter].difficulties[0].spellAttempts[key];
}

void GameProgress::SetMaxComboHits(int value)
{
    characters[selectedFighter].difficulties[selectedDifficulty].maxComboHits = value;
}

void GameProgress::SetMaxComboDamage(int value)
{
    characters[selectedFighter].difficulties[selectedDifficulty].maxComboDamage = value;
}

int GameProgress::GetMaxComboHits()
{
    return characters[selectedFighter].difficulties[selectedDifficulty].maxComboHits;
}

int GameProgress::GetMaxComboDamage()
{
    return characters[selectedFighter].difficulties[selectedDifficulty].maxComboDamage;
}
