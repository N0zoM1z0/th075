#include "FighterGaugeBorrowedF980.hpp"
#include "FighterEffectBorrowedFieldsF973.hpp"
#include "FighterEffectPolicies.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void FighterEffectPoliciesF135::SpawnBattleEffect(short effect, float x, float y,
                                                 signed char facing, signed char layer)
{
    F973_EFFECT_TAIL(this, BattleEffectQueueF135).queuePointerAt2EC->Spawn(effect, x, y, facing, layer,
        0, 0, &F973_EFFECT_PARAMETER(this).firstFloatAt314, 0, 0);
}

void FighterEffectPoliciesF135::SpawnTrackedEffect(short effect, float x, float y,
                                                  signed char facing, signed char layer,
                                                  unsigned char linked, unsigned char mode)
{
    if (linked != 0) {
        F973_EFFECT_TAIL(this, BattleEffectQueueF135).queuePointerAt2EC->Spawn(effect, x, y, facing, layer,
            0, 0, &F973_EFFECT_PARAMETER(this).firstFloatAt314, &F973_EFFECT_TAIL(this, BattleEffectQueueF135).transformFirstByteAt2F0, mode);
    } else {
        F973_EFFECT_TAIL(this, BattleEffectQueueF135).queuePointerAt2EC->Spawn(effect, x, y, facing, layer,
            0, 0, &F973_EFFECT_PARAMETER(this).firstFloatAt314, 0, mode);
    }
}

void FighterEffectPoliciesF135::SpawnAuxEffect(short effect, float x, float y,
                                              signed char facing, signed char layer)
{
    g_AuxiliaryEffectsF135.Spawn(effect, x, y, facing, layer, 0, 0, &F973_EFFECT_PARAMETER(this).firstFloatAt314);
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
    if (F980_GAUGE(this).cooldownAt3B6 > 0) {
        F980_GAUGE(this).cooldownAt3B6 = 1000;
    } else {
        F980_GAUGE(this).meterAt3B0 = F980_GAUGE(this).meterAt3B0 - amount;
        if (F980_GAUGE(this).meterAt3B0 <= 0 && F980_GAUGE(this).cooldownAt3B6 <= 0) {
            PlaySharedSound(43);
            F980_GAUGE(this).meterAt3B0 = 0;
            F980_GAUGE(this).cooldownAt3B6 = 1000;
        }
    }
}

#undef FIELD
