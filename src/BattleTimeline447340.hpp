#pragma once
#include "BattleHud43E040.hpp"

// Pointer-only operation view. The full native method touches coordinate
// records in the first64 bytes of the complete packet passed by this caller.
class TimelineQuadRotation447340 {
public:
    void Rotate(float, float, float, float, float, float);
};
class BattleTimeline447340 { public: void RenderTimeline(); };
