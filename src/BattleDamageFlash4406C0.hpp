#pragma once
#include "Fighter.hpp"
#include "BattleHud43E040.hpp"

// Pointer-only AL predicate view; the complete native body returns 0/1 in AL.
// Original nominal declarations and the complete actor layout remain unknown.
class FlashPredicate4406C0 { public: bool IsState95To99(); };
class BattleDamageFlash4406C0 { public: void RenderFlash(); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    void* field008;
    unsigned char unknown00C[0x044 - 0x00C];
    Fighter* field044;            // the two fighters
    Fighter* field048;
};
