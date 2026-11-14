#include "ReimuFighter.hpp"
#include "Fighter.hpp"
// R049-authored complete native 1,027-byte controller at 00470A40.
// The compiled nonrelocation stream is genuinely identical to F062;
// only the three relative call displacements differ because of the
// original function address. This independent original extent receives
// distinct credit, not reuse of F062 bytes or any new callee credit.
// Declaration-only receiver view; full character owner layout unknown.


#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

// Names are provisional. Only these field accesses and receiver ABI are observed.
void ReimuFighter::AdvanceAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (fieldF0A != 1) {
        if (action > 149 && action < 154) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 0.75f;
            field300 = 0.75f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(998, facing * 57 + x, y + 94.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action > 153 && action < 158) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 0.75f;
            field300 = 0.75f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(998, facing * 57 + x, y + 60.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action == 158) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 0.75f;
            field300 = 0.75f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(998, facing * 57 + x, y + 100.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    }
    if (x - opponent->x > 540.0f || x - opponent->x < -540.0f) {
        fieldF2A = 60;
    }
    if (x - opponent->x > 320.0f || x - opponent->x < -320.0f) {
        fieldF2A = fieldF2A + 1;
        if (fieldF2A > 60) fieldF2A = 60;
    }
    else {
        fieldF2A = 0;
    }
}

#undef FIELD
