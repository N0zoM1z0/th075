#include "engine/GameProgress.hpp"
unsigned char ProgressRecordsF736::CheckEncodedItem(signed char code) {
    if (code % 10 < 6) return 1;
    return g_GameProgress.TestUnlockBit(
        static_cast<int>(code) + 200);
}
