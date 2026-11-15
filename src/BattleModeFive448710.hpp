#pragma once
#include "BattleHud43E040.hpp"

// Pointer-only owner view; never construct or embed this partial receiver.
class BattleModeFive448710 { public: void RenderMenu(); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    void* field008;
    unsigned char unknown00C[0x044 - 0x00C];
    char* field044;
    char* field048;
    unsigned char unknown04C[0x0A1 - 0x04C];
    unsigned char field0A1;
    unsigned char unknown0A2[0x118 - 0x0A2];
    signed char field118;
};
