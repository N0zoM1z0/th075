#include "FighterTrackedEffectsF169.hpp"
#include "BattleEffectSpawner.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define PARAMETERS reinterpret_cast<const float*>(reinterpret_cast<unsigned char*>(this) + 0x314)
#define TRANSFORM (reinterpret_cast<unsigned char*>(this) + 0x2F0)

void FighterTrackedEffectsF169::SpawnTrackedEffect(
    short effect, float x, float y, signed char facing, signed char layer,
    unsigned char linked)
{
    if (linked) {
        FIELD(BattleEffectSpawnerF136*, 0x2EC)->Spawn(
            effect, x, y, facing, layer, 0, 0, PARAMETERS, TRANSFORM, 0);
    } else {
        FIELD(BattleEffectSpawnerF136*, 0x2EC)->Spawn(
            effect, x, y, facing, layer, 0, 0, PARAMETERS, 0, 0);
    }
}

void FighterTrackedEffectsF169::SpawnTrackedEffectWithFlags(
    short effect, float x, float y, signed char facing, signed char layer,
    unsigned char flagA, unsigned char flagB, unsigned char linked)
{
    if (linked) {
        FIELD(BattleEffectSpawnerF136*, 0x2EC)->Spawn(
            effect, x, y, facing, layer, flagA, flagB, PARAMETERS, TRANSFORM, 0);
    } else {
        FIELD(BattleEffectSpawnerF136*, 0x2EC)->Spawn(
            effect, x, y, facing, layer, flagA, flagB, PARAMETERS, 0, 0);
    }
}

#undef TRANSFORM
#undef PARAMETERS
#undef FIELD
