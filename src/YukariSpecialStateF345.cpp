#include "Fighter.hpp"
// Yukari's special-state counters. The step/threshold logic and the
// Yukari-only fields F12/F32 were verified against the original; the
// distance checks share their shape with CharacterAux5E5500 (F062).
class YukariSpecialF345 : public Fighter {
public:
    void UpdateSpecialState();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
public:
    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF12 - 0xF10];
    short fieldF12;
    unsigned char unknownF14[0xF32 - 0xF14];
    short fieldF32;
};
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void YukariSpecialF345::UpdateSpecialState() {
    if (field3B8 == 0)
        fieldF12 = fieldF12 + 2;
    if (fieldF12 >= 180)
        fieldF12 = -180;
    if (velocityX == 0.0f && field3AC > 0)
        field3AC = 0;
    if (animationStage == 0 && animationFrame == 0 && fieldF0A == 0) {
        if (action > 149 && action < 154) {
            SpawnTrackedEffect(830, facing*57 + x, y + 94.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action > 153 && action < 158) {
            SpawnTrackedEffect(830, facing*57 + x, y + 60.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action == 158) {
            SpawnTrackedEffect(830, facing*57 + x, y + 100.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    }
    if (x-opponent->x > 540.0f || x-opponent->x < -540.0f)
        fieldF32=60;
    if (x-opponent->x > 320.0f || x-opponent->x < -320.0f) {
        fieldF32=fieldF32+1;
        if (fieldF32>60) fieldF32=60;
    } else {
        fieldF32=0;
    }
}
#undef FIELD
