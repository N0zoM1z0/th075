#include "GameProgress.hpp"
// Source-compatible borrowed game progress / completion record view.
// Neither this receiver nor the encoded record storage is instantiated.

namespace GameProgressF203 {
unsigned char CheckSelection(signed char selection, signed char mode)
{
    unsigned char matches = 1;
    int i;
    if (mode == 0) {
        switch (selection) {
        case 6:
            matches = 0;
            matches = matches | (g_GameProgress.TestUnlockBit(0) |
                       g_GameProgress.TestUnlockBit(20) |
                       g_GameProgress.TestUnlockBit(40));
            matches = matches | (g_GameProgress.TestUnlockBit(1) |
                       g_GameProgress.TestUnlockBit(21) |
                       g_GameProgress.TestUnlockBit(41));
            matches = matches | (g_GameProgress.TestUnlockBit(5) |
                       g_GameProgress.TestUnlockBit(25) |
                       g_GameProgress.TestUnlockBit(45));
            break;
        case 7:
            matches = 0;
            matches = matches | (g_GameProgress.TestUnlockBit(2) |
                       g_GameProgress.TestUnlockBit(22) |
                       g_GameProgress.TestUnlockBit(42));
            matches = matches | (g_GameProgress.TestUnlockBit(4) |
                       g_GameProgress.TestUnlockBit(24) |
                       g_GameProgress.TestUnlockBit(44));
            break;
        case 8:
            matches = 0;
            for (i = 0; i < 6; ++i)
                matches = matches | (g_GameProgress.TestUnlockBit(i + 20) |
                           g_GameProgress.TestUnlockBit(i + 40));
            break;
        case 9:
        case 10:
            matches = 0;
            for (i = 0; i < 6; ++i)
                matches = matches | (g_GameProgress.TestUnlockBit(i + 40));
            break;
        }
    } else {
        switch (selection) {
        case 6:
        case 7:
            for (i = 0; i < 6; ++i)
                matches = matches & (g_GameProgress.TestUnlockBit(i + 40));
            break;
        case 8:
            matches = g_GameProgress.TestUnlockBit(46) &
                      g_GameProgress.TestUnlockBit(47);
            break;
        case 9:
            matches = g_GameProgress.TestUnlockBit(48);
            break;
        case 10:
            matches = 0;
            break;
        }
    }
    return matches;
}
}
