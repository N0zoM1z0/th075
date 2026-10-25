#include "FighterResourceParameters452B30.hpp"

#define BANK (*reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(this) + 0x16AC4))
#define COUNTERS reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this) + BANK * 0x17F0 + 0x394)

void ProfileSelectionF155::IncrementSelectedWordCounter(signed char index)
{
    COUNTERS[index]++;
}

#undef COUNTERS
#undef BANK
