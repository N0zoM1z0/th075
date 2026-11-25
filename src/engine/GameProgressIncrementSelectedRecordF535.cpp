#include "engine/GameProgress.hpp"
// Complete independently authored R103 GameProgress native 92-byte counter.
// The true VC7.1 original is a *postfix increment* of an lvalue, not
// prefix ++ or an explicit assignment. All preserve counter behavior
// here, but only postfix naturally reproduces the original evaluation
// register order and both native loads/store as complete 92-byte CODE.
// Signed fighter and difficulty selectors are observed at +0x16AC4/5;
// owned record extents have original 0x17F0 and 0x5FC strides.
// No complete private original owner type is asserted by this view.
void GameProgress::RecordStoryClear() {
    characters[selectedFighter].difficulties[selectedDifficulty].storyClears++;
}
