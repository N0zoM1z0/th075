#include "FighterEffectBorrowedFieldsF973.hpp"
#include "FighterEffectPolicies.hpp"


void FighterEffectPoliciesF135::SpawnBattleEffect(short effect, float x, float y,
                                                 signed char facing, signed char layer)
{
    F973_EFFECT_TAIL(this, BattleEffectQueueF135).queuePointerAt2EC->Spawn(effect, x, y, facing, layer,
        0, 0, &field314, 0, 0);
}

void FighterEffectPoliciesF135::SpawnTrackedEffect(short effect, float x, float y,
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

void FighterEffectPoliciesF135::SpawnAuxEffect(short effect, float x, float y,
                                              signed char facing, signed char layer)
{
    g_AuxiliaryEffectsF135.Spawn(effect, x, y, facing, layer, 0, 0, &field314);
}

void FighterEffectPoliciesF135::PlaySound(short sound)
{
    reinterpret_cast<EffectSoundBankF135*>(reinterpret_cast<unsigned char*>(this) + 0x6D0)->Play(sound);
}

void FighterEffectPoliciesF135::PlaySharedSound(short sound)
{
    g_SharedEffectSoundBankF135->Play(sound);
}

void FighterEffectPoliciesF135::UpdateGaugeTimer(int amount)
{
    if (meterCooldown > 0) {
        meterCooldown = 1000;
    } else {
        meter = meter - amount;
        if (meter <= 0 && meterCooldown <= 0) {
            PlaySharedSound(43);
            meter = 0;
            meterCooldown = 1000;
        }
    }
}
