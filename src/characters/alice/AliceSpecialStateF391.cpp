#include "characters/alice/AliceFighter.hpp"
#include "battle/Fighter.hpp"
// Independently original R068-authored 256-byte Alice fighter special-state leaf.
void AliceFighter::AdvanceAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (x - opponent->x > 540.0f || x - opponent->x < -540.0f) {
        longRangeFrames = 60;
    }
    if (x - opponent->x > 320.0f || x - opponent->x < -320.0f) {
        longRangeFrames = longRangeFrames + 1;
        if (longRangeFrames > 60) longRangeFrames = 60;
    }
    else {
        longRangeFrames = 0;
    }
}
