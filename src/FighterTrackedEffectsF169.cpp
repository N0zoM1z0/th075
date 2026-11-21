#include "Fighter.hpp"
#include "EffectManagerLifetimeF161.hpp"
#include "FighterTrackedEffectsF169.hpp"


void FighterTrackedEffectsF169::SpawnTrackedEffect(
    short effect, float x, float y, signed char facing, signed char layer,
    unsigned char linked)
{
    if (linked) {
        field2EC->Spawn(
            effect, x, y, facing, layer, 0, 0,
            &field314, &effectTransformRecord, 0);
    } else {
        field2EC->Spawn(
            effect, x, y, facing, layer, 0, 0,
            &field314, 0, 0);
    }
}

void FighterTrackedEffectsF169::SpawnTrackedEffectWithFlags(
    short effect, float x, float y, signed char facing, signed char layer,
    unsigned char flagA, unsigned char flagB, unsigned char linked)
{
    if (linked) {
        field2EC->Spawn(
            effect, x, y, facing, layer, flagA, flagB,
            &field314, &effectTransformRecord, 0);
    } else {
        field2EC->Spawn(
            effect, x, y, facing, layer, flagA, flagB,
            &field314, 0, 0);
    }
}
