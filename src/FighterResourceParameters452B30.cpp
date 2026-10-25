#include "FighterResourceParameters452B30.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
void FighterResourceParameters452B30::SelectResourceParameters()
{
    FIELD(short, 0x3A2) = 0;
    if (FIELD(signed char, 0x2CD) != 0 && g_CombatMode == 3) {
        FIELD(short, 0x3A0) = 9999;
        FIELD(unsigned int, 0x3A4) =
            reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x3D0)[FIELD(signed char, 0x39D)];
        FIELD(unsigned int, 0x3A8) =
            reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x400)[FIELD(signed char, 0x39D)];
        if (g_FrameClockMode == 1)
            reinterpret_cast<ProfileSelectionF155*>(g_ProfileSelectionAt006718F8)->IncrementSelectedWordCounter(
                reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(this) + 0x384)[FIELD(signed char, 0x39D)]);
    } else {
        FIELD(short, 0x3A0) = static_cast<short>(static_cast<int>(FIELD(float, 0x36C) * 8800.0f / 900.0f) + 1201);
        FIELD(unsigned char, 0x464) = 0;
    }
}

#undef FIELD
