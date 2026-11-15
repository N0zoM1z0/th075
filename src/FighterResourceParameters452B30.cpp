#include "FighterResourceParameters452B30.hpp"

void FighterResourceParameters452B30::SelectResourceParameters()
{
    field3A2 = 0;
    if (field2CD != 0 && g_CombatMode == 3) {
        field3A0 = 9999;
        field3A4 =
            reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x3D0)[field39D];
        field3A8 =
            reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x400)[field39D];
        if (g_FrameClockMode == 1)
            reinterpret_cast<ProfileSelectionF155*>(g_ProfileSelectionAt006718F8)->IncrementSelectedWordCounter(
                reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(this) + 0x384)[field39D]);
    } else {
        field3A0 = static_cast<short>(static_cast<int>(field36C * 8800.0f / 900.0f) + 1201);
        field464 = 0;
    }
}
