#include "CharacterAux5E5500.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

// Names are provisional. Only these field accesses and receiver ABI are observed.
void CharacterAux5E5500::AdvanceAuxiliary() {
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
