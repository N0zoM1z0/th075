#include "GameProgress.hpp"
// Borrowed this-pointer record layout. The original source-level complete
// record class and packed element types are unknown; these two methods never
// instantiate it.
void GameProgress::RaiseSelectedValue(signed char value)
{
    if (value > characters[selectedFighter].difficulties[selectedDifficulty].field556)
        characters[selectedFighter].difficulties[selectedDifficulty].field556 = value;
}
// characters[selectedFighter].difficulties[selectedDifficulty].field000, but
// the original adds the difficulty stride before the character stride,
// which no nested-array spelling reproduces.
#define SELECTED_COUNT (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) \
    + (0x5fc * selectedDifficulty + 0x17f0 * selectedFighter)))
void GameProgress::IncrementSelectedRecordCount()
{
    SELECTED_COUNT = SELECTED_COUNT + 1;
}
#undef SELECTED_COUNT
