#include "characters/ReimuFighter.hpp"
#include "audio/SoundBank.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"
#include "battle/CombatEffects.hpp"

#undef PlaySound

void Fighter::SpawnBattleEffect(short effect, float x, float y,
                                                 signed char facing, signed char layer)
{
    field2EC->Spawn(effect, x, y, facing, layer,
        0, 0, effectParameters, 0, 0);
}

void Fighter::SpawnTrackedEffect(short effect, float x, float y,
                                                  signed char facing, signed char layer,
                                                  unsigned char linked, unsigned char mode)
{
    if (linked != 0) {
        field2EC->Spawn(effect, x, y, facing, layer,
            0, 0, effectParameters, &effectTransformRecord, mode);
    } else {
        field2EC->Spawn(effect, x, y, facing, layer,
            0, 0, effectParameters, 0, mode);
    }
}

void Fighter::SpawnAuxEffect(short effect, float x, float y,
                                              signed char facing, signed char layer)
{
    g_CombatEffects.SpawnConfigured(effect, x, y, facing, layer, 0, 0, effectParameters);
}

void Fighter::PlaySound(short sound)
{
    soundBank.Play(sound);
}

void Fighter::PlaySharedSound(short sound)
{
    g_SoundBank->Play(sound);
}

void Fighter::UpdateGaugeTimer(int amount)
{
    if (spiritCooldown > 0) {
        spiritCooldown = 1000;
    } else {
        spirit = spirit - amount;
        if (spirit <= 0 && spiritCooldown <= 0) {
            PlaySharedSound(43);
            spirit = 0;
            spiritCooldown = 1000;
        }
    }
}
