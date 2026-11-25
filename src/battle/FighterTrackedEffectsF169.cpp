#include "characters/SuikaFighter.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"


void Fighter::SpawnTrackedEffect(
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

void SuikaFighter::SpawnTrackedEffectWithFlags(
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
