#include "ReimuFighter.hpp"
#include "FighterEffectBorrowedFieldsF973.hpp"
#include "FighterEffectPolicies.hpp"


void Fighter::SpawnBattleEffect(short effect, float x, float y,
                                                 signed char facing, signed char layer)
{
    F973_EFFECT_TAIL(this, BattleEffectQueueF135).queuePointerAt2EC->Spawn(effect, x, y, facing, layer,
        0, 0, &field314, 0, 0);
}

void Fighter::SpawnTrackedEffect(short effect, float x, float y,
                                                  signed char facing, signed char layer,
                                                  unsigned char linked, unsigned char mode)
{
    if (linked != 0) {
        F973_EFFECT_TAIL(this, BattleEffectQueueF135).queuePointerAt2EC->Spawn(effect, x, y, facing, layer,
            0, 0, &field314, &F973_EFFECT_TAIL(this, BattleEffectQueueF135).transformFirstByteAt2F0, mode);
    } else {
        F973_EFFECT_TAIL(this, BattleEffectQueueF135).queuePointerAt2EC->Spawn(effect, x, y, facing, layer,
            0, 0, &field314, 0, mode);
    }
}

void Fighter::SpawnAuxEffect(short effect, float x, float y,
                                              signed char facing, signed char layer)
{
    g_AuxiliaryEffectsF135.Spawn(effect, x, y, facing, layer, 0, 0, &field314);
}

void Fighter::PlaySound(short sound)
{
    reinterpret_cast<EffectSoundBankF135*>(reinterpret_cast<unsigned char*>(this) + 0x6D0)->Play(sound);
}

void Fighter::PlaySharedSound(short sound)
{
    g_SharedEffectSoundBankF135->Play(sound);
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
