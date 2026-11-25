#include "characters/alice/AliceFighter.hpp"
#include "battle/Fighter.hpp"
// Independently original R068-authored 256-byte Alice fighter special-state leaf.
void AliceFighter::AdvanceAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (x - opponent->x > 540.0f || x - opponent->x < -540.0f) {
        fieldF14 = 60;
    }
    if (x - opponent->x > 320.0f || x - opponent->x < -320.0f) {
        fieldF14 = fieldF14 + 1;
        if (fieldF14 > 60) fieldF14 = 60;
    }
    else {
        fieldF14 = 0;
    }
}
