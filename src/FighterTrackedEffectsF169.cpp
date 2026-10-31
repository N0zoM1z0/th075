#include "FighterEffectBorrowedFieldsF973.hpp"
#include "FighterTrackedEffectsF169.hpp"
#include "BattleEffectSpawner.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define PARAMETERS (&F973_EFFECT_PARAMETER(this).firstFloatAt314)
#define TRANSFORM (&F973_EFFECT_TAIL(this, BattleEffectSpawnerF136).transformFirstByteAt2F0)

void FighterTrackedEffectsF169::SpawnTrackedEffect(
    short effect, float x, float y, signed char facing, signed char layer,
    unsigned char linked)
{
    if (linked) {
        F973_EFFECT_TAIL(this, BattleEffectSpawnerF136).queuePointerAt2EC->Spawn(
            effect, x, y, facing, layer, 0, 0, PARAMETERS, TRANSFORM, 0);
    } else {
        F973_EFFECT_TAIL(this, BattleEffectSpawnerF136).queuePointerAt2EC->Spawn(
            effect, x, y, facing, layer, 0, 0, PARAMETERS, 0, 0);
    }
}

void FighterTrackedEffectsF169::SpawnTrackedEffectWithFlags(
    short effect, float x, float y, signed char facing, signed char layer,
    unsigned char flagA, unsigned char flagB, unsigned char linked)
{
    if (linked) {
        F973_EFFECT_TAIL(this, BattleEffectSpawnerF136).queuePointerAt2EC->Spawn(
            effect, x, y, facing, layer, flagA, flagB, PARAMETERS, TRANSFORM, 0);
    } else {
        F973_EFFECT_TAIL(this, BattleEffectSpawnerF136).queuePointerAt2EC->Spawn(
            effect, x, y, facing, layer, flagA, flagB, PARAMETERS, 0, 0);
    }
}

#undef TRANSFORM
#undef PARAMETERS
#undef FIELD
