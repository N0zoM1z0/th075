#include "characters/marisa/MarisaFighter.hpp"
#include "battle/Fighter.hpp"
// F361: independently native-observed 1,027-byte character special effect
// controller. Like the already exact F062, this uses the same inherited
// effect-spawner ABI, but its effect 817, scale 1.0f, linked flag zero and
// +0xF32 distance counter are independently verified for THIS target.
// Declaration-only receiver view: full original fighter layout is unknown.



// Names are provisional. Only these field accesses and receiver ABI are observed.
void MarisaFighter::AdvanceAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (fieldF0A != 1) {
        if (action > 149 && action < 154) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 94.0f, facing, 1, 0);
            fieldF0A = 1;
        }
        if (action > 153 && action < 158) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 60.0f, facing, 1, 0);
            fieldF0A = 1;
        }
        if (action == 158) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 100.0f, facing, 1, 0);
            fieldF0A = 1;
        }
    }
    if (x - opponent->x > 540.0f || x - opponent->x < -540.0f) {
        fieldF32 = 60;
    }
    if (x - opponent->x > 320.0f || x - opponent->x < -320.0f) {
        fieldF32 = fieldF32 + 1;
        if (fieldF32 > 60) fieldF32 = 60;
    }
    else {
        fieldF32 = 0;
    }
}
