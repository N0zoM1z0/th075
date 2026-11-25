#include "characters/remilia/RemiliaFighter.hpp"
#include "battle/Fighter.hpp"
// F363: original character special-effect policy with distance threshold
// checks before the action-window effect spawns (unlike F062/F361).
// Native effect 850, +0xF0C distance counter and 1.0f scale are specific
// to this 1,028-byte original body, not assumptions from a shared class.
// Declaration-only receiver view; complete owner layout unknown.



// Names are provisional. Only these field accesses and receiver ABI are observed.
void RemiliaFighter::AdvanceAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (x - opponent->x > 540.0f || x - opponent->x < -540.0f) {
        fieldF0C = 60;
    }
    if (x - opponent->x > 320.0f || x - opponent->x < -320.0f) {
        fieldF0C = fieldF0C + 1;
        if (fieldF0C > 60) fieldF0C = 60;
    }
    else {
        fieldF0C = 0;
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
            SpawnTrackedEffect(850, facing * 57 + x, y + 94.0f, facing, 1, 1);
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
            SpawnTrackedEffect(850, facing * 57 + x, y + 60.0f, facing, 1, 1);
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
            SpawnTrackedEffect(850, facing * 57 + x, y + 100.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    }

}
