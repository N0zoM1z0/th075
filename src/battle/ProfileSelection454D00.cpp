#include "engine/GameProgress.hpp"
#include "battle/FighterResourceParameters452B30.hpp"


void GameProgress::RecordSpellAttempt(signed char index)
{
    characters[selectedFighter].difficulties[0].spellAttempts[index]++;
}
