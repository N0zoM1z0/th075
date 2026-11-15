#pragma once
#include "BattleHud43E040.hpp"

// Scoped float/ST0 access view of the complete 28-byte unknown-origin wrapper.
// Original nominal return type and precision remain unknown.
float __cdecl BannerLog10At00442040(float);
// Declaration-only owner view; never construct or embed this partial owner.
class BattleRoundBanner441EA0 { public: void RenderRoundBanner(); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    void* field008;
    unsigned char unknown00C[0x068 - 0x00C];
    int field068;
    int field06C;
};
