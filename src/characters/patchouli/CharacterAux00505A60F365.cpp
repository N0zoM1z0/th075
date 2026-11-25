#include "engine/FloatConstants.hpp"
#include "characters/patchouli/PatchouliFighter.hpp"
#include "battle/Fighter.hpp"
// F365: independently checked COMPLETE native 1,576-byte extended character special effect
// controller. Like the already exact F062, this uses the same inherited
// effect-spawner ABI, but its effect 817, scale 1.0f, linked flag one and
// +0xF12 distance counter are independently verified for THIS target.
// The original computes signed angular timers, a true signed comparison
// direction, directional random projectiles and three linked effects. The
// compiler register state at the F0E timer depends on authentic compound
// += (not a semantically equivalent ordinary assignment). The direction
// boolean is naturally inlined, not stored in an invented helper local.
void PatchouliFighter::AdvanceAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (opponentFreezeTimer == 0)
        fieldF0E += facing * 5;
    if (fieldF0E < 0) fieldF0E = 359;
    if (fieldF0E >= 360) fieldF0E = 0;
    if (opponentFreezeTimer == 0)
        fieldF0C = fieldF0C + 2;
    if (fieldF0C < 0) fieldF0C = 359;
    if (fieldF0C >= 360) fieldF0C = 0;
    if (fieldF10 > 0) {
        opponentVelocityDeltaX = float(fieldF10+20) * FloatConstants::OneTenth * float(facing*opponent->facing) * float(int(((opponent->x - x) * facing > 0.0f))*2-1);
        fieldF10 = fieldF10-2;
        if (RecordedRange(0,100)<50)
            SpawnBattleEffect(0x38c, float(RecordedRange(0,640)*facing)+x,0.0f,facing,1);
        else
            SpawnBattleEffect(0x38c, x-float(RecordedRange(0,640)*facing),0.0f,-facing,1);
        if (fieldF10<0) fieldF10=0;
    }
    if (fieldF0A != 1) {
        if (action > 149 && action < 154) {
            effectTransformRecord.offsetX = 0;
            effectTransformRecord.offsetY = 0;
            effectTransformRecord.offsetZ = 0;
            effectTransformRecord.scaleX = 1.0f;
            effectTransformRecord.scaleY = 1.0f;
            effectTransformRecord.alpha = 255;
            effectTransformRecord.red = 255;
            effectTransformRecord.green = 255;
            effectTransformRecord.blue = 255;
            effectTransformRecord.rotationX = 0.0f;
            effectTransformRecord.rotationY = 50.0f;
            effectTransformRecord.rotationZ = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 94.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action > 153 && action < 158) {
            effectTransformRecord.offsetX = 0;
            effectTransformRecord.offsetY = 0;
            effectTransformRecord.offsetZ = 0;
            effectTransformRecord.scaleX = 1.0f;
            effectTransformRecord.scaleY = 1.0f;
            effectTransformRecord.alpha = 255;
            effectTransformRecord.red = 255;
            effectTransformRecord.green = 255;
            effectTransformRecord.blue = 255;
            effectTransformRecord.rotationX = 0.0f;
            effectTransformRecord.rotationY = 50.0f;
            effectTransformRecord.rotationZ = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 60.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action == 158) {
            effectTransformRecord.offsetX = 0;
            effectTransformRecord.offsetY = 0;
            effectTransformRecord.offsetZ = 0;
            effectTransformRecord.scaleX = 1.0f;
            effectTransformRecord.scaleY = 1.0f;
            effectTransformRecord.alpha = 255;
            effectTransformRecord.red = 255;
            effectTransformRecord.green = 255;
            effectTransformRecord.blue = 255;
            effectTransformRecord.rotationX = 0.0f;
            effectTransformRecord.rotationY = 50.0f;
            effectTransformRecord.rotationZ = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 100.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    }
    if (x - opponent->x > 540.0f || x - opponent->x < -540.0f) {
        fieldF12 = 60;
    }
    if (x - opponent->x > 320.0f || x - opponent->x < -320.0f) {
        fieldF12 = fieldF12 + 1;
        if (fieldF12 > 60) fieldF12 = 60;
    }
    else {
        fieldF12 = 0;
    }
}
