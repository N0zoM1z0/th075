#include "YuyukoFighter.hpp"
#include "Fighter.hpp"
// F364: original independent 1121-byte character auxiliary controller,
// with native signed F0E +2 counter and wrap at >=360, then three
// action-specific effect 899 spawns and F10 distance counter. This is
// not a claim about the full fighter/auxiliary private owner class.
// Declaration-only receiver view, only observed fields and calls.


#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

// Names are provisional. Only these field accesses and receiver ABI are observed.
void YuyukoFighter::AdvanceAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (field3B8 == 0)
        fieldF0E = fieldF0E + 2;
    if (fieldF0E < 0)
        fieldF0E = 0;
    if (fieldF0E >= 360)
        fieldF0E = 0;
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
            SpawnTrackedEffect(899, facing * 57 + x, y + 94.0f, facing, 1, 1);
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
            SpawnTrackedEffect(899, facing * 57 + x, y + 60.0f, facing, 1, 1);
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
            SpawnTrackedEffect(899, facing * 57 + x, y + 100.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    }
    if (x - opponent->x > 540.0f || x - opponent->x < -540.0f) {
        fieldF10 = 60;
    }
    if (x - opponent->x > 320.0f || x - opponent->x < -320.0f) {
        fieldF10 = fieldF10 + 1;
        if (fieldF10 > 60) fieldF10 = 60;
    }
    else {
        fieldF10 = 0;
    }
}

#undef FIELD
