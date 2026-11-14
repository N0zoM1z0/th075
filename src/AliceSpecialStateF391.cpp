#include "AliceFighter.hpp"
#include "Fighter.hpp"
// Independently original R068-authored 256-byte Alice fighter special-state leaf.
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
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
#undef FIELD
