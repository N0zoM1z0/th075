#include "GameProgress.hpp"
// F745: complete original R212-authored GameProgress::ClearUnlockBit.
// Match native signed short 0..320 and authentic game-owned bit DWORDs
// at receiver+0x16A9C. No guessed full private GameProgress layout.
void GameProgress::ClearUnlockBit(short selected) {
    if (selected>320 || selected<0) {} else
        unlockBits[selected/32] &= (0xffffffffu - (1u << (selected%32)));
}
