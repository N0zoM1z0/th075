#include "GameProgress.hpp"
#include "FighterResourceParameters452B30.hpp"


void GameProgress::IncrementSelectedWordCounter(signed char index)
{
    characters[selectedFighter].difficulties[0].cardCounters2[index]++;
}
