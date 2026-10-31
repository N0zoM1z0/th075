#include "ProgressSelectionKeysF954.hpp"
#include "FighterResourceParameters452B30.hpp"

#define BANK F954_PROGRESS_KEYS(this).fighterAt16AC4
#define COUNTERS reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this) + BANK * 0x17F0 + 0x394)

void ProfileSelectionF155::IncrementSelectedWordCounter(signed char index)
{
    COUNTERS[index]++;
}

#undef COUNTERS
#undef BANK
