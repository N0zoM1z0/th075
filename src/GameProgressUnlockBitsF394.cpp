#include "GameProgress.hpp"
// Two independent native R103-authored progress unlock-bit policies.
// Original 16-bit signed selectors must be range guarded 0..320; C++
// signed divide and modulo preserve original negative-index math.
// Set has a native explicit invalid-index empty branch, while Test builds
// a full unsigned relational int then narrows to the original byte return.
// Both cases reflect native expression lowering, not invented owner layout.
// Physical game-owned progress bitset: signed 16-bit selectors 0..320.
// Only the observed bitfield at +0x16A9C is borrowed, never the full owner.
void GameProgress::SetUnlockBit(short selected) {
    if(selected>320 || selected<0) {} else unlockBits[selected/32] |= 1 << (selected%32);
}
unsigned char GameProgress::TestUnlockBit(short selected) {
    if(selected>320 || selected<0) return 0;
    return (int)(0u < (unlockBits[selected/32] & (1 << (selected%32))));
}
