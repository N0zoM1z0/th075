#include "characters/yukari/YukariFighter.hpp"
#include "battle/Fighter.hpp"
// Yukari's special-state counters. The step/threshold logic and the
// Yukari-only fields F12/F32 were verified against the original; the
// distance checks share their shape with MeilingFighter (F062).

void YukariFighter::AdvanceAuxiliary() {
    if (opponentFreezeTimer == 0)
        spellOrbitAngle = spellOrbitAngle + 2;
    if (spellOrbitAngle >= 180)
        spellOrbitAngle = -180;
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
        longRangeFrames=60;
    if (x-opponent->x > 320.0f || x-opponent->x < -320.0f) {
        longRangeFrames=longRangeFrames+1;
        if (longRangeFrames>60) longRangeFrames=60;
    } else {
        longRangeFrames=0;
    }
}
