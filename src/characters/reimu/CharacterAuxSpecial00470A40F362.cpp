#include "characters/reimu/ReimuFighter.hpp"
#include "battle/Fighter.hpp"
// R049-authored complete native 1,027-byte controller at 00470A40.
// The compiled nonrelocation stream is genuinely identical to F062;
// only the three relative call displacements differ because of the
// original function address. This independent original extent receives
// distinct credit, not reuse of F062 bytes or any new callee credit.
// Declaration-only receiver view; full character owner layout unknown.



// Names are provisional. Only these field accesses and receiver ABI are observed.
void ReimuFighter::AdvanceAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (fieldF0A != 1) {
        if (action > 149 && action < 154) {
            effectTransformRecord.offsetX = 0;
            effectTransformRecord.offsetY = 0;
            effectTransformRecord.offsetZ = 0;
            effectTransformRecord.scaleX = 0.75f;
            effectTransformRecord.scaleY = 0.75f;
            effectTransformRecord.alpha = 255;
            effectTransformRecord.red = 255;
            effectTransformRecord.green = 255;
            effectTransformRecord.blue = 255;
            effectTransformRecord.rotationX = 0.0f;
            effectTransformRecord.rotationY = 50.0f;
            effectTransformRecord.rotationZ = 0.0f;
            SpawnTrackedEffect(998, facing * 57 + x, y + 94.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action > 153 && action < 158) {
            effectTransformRecord.offsetX = 0;
            effectTransformRecord.offsetY = 0;
            effectTransformRecord.offsetZ = 0;
            effectTransformRecord.scaleX = 0.75f;
            effectTransformRecord.scaleY = 0.75f;
            effectTransformRecord.alpha = 255;
            effectTransformRecord.red = 255;
            effectTransformRecord.green = 255;
            effectTransformRecord.blue = 255;
            effectTransformRecord.rotationX = 0.0f;
            effectTransformRecord.rotationY = 50.0f;
            effectTransformRecord.rotationZ = 0.0f;
            SpawnTrackedEffect(998, facing * 57 + x, y + 60.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action == 158) {
            effectTransformRecord.offsetX = 0;
            effectTransformRecord.offsetY = 0;
            effectTransformRecord.offsetZ = 0;
            effectTransformRecord.scaleX = 0.75f;
            effectTransformRecord.scaleY = 0.75f;
            effectTransformRecord.alpha = 255;
            effectTransformRecord.red = 255;
            effectTransformRecord.green = 255;
            effectTransformRecord.blue = 255;
            effectTransformRecord.rotationX = 0.0f;
            effectTransformRecord.rotationY = 50.0f;
            effectTransformRecord.rotationZ = 0.0f;
            SpawnTrackedEffect(998, facing * 57 + x, y + 100.0f, facing, 1, 1);
            fieldF0A = 1;
        }
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
