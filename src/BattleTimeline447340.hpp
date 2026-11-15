#pragma once
#include "BattleHud43E040.hpp"

// Pointer-only operation view. The full native method touches coordinate
// records in the first64 bytes of the complete packet passed by this caller.
class TimelineQuadRotation447340 {
public:
    void Rotate(float, float, float, float, float, float);
};
class BattleTimeline447340 { public: void RenderTimeline(); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    void* field008;
    unsigned char unknown00C[0x010 - 0x00C];
    int field010;
    unsigned char unknown014[0x060 - 0x014];
    int field060;
    signed char field064;
    unsigned char unknown065[0x070 - 0x065];
    float field070;
    float field074;
    float field078;
    float field07C;
    float field080;
    unsigned char unknown084[0x088 - 0x084];
    float field088;
};
