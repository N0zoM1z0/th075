#include "FighterEffectPolicies.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void FighterEffectPoliciesF135::SpawnBattleEffect(short effect, float x, float y,
                                                 signed char facing, signed char layer)
{
    FIELD(BattleEffectQueueF135*, 0x2EC)->Spawn(effect, x, y, facing, layer,
        0, 0, &FIELD(float, 0x314), 0, 0);
}

void FighterEffectPoliciesF135::SpawnTrackedEffect(short effect, float x, float y,
                                                  signed char facing, signed char layer,
                                                  unsigned char linked, unsigned char mode)
{
    if (linked != 0) {
        FIELD(BattleEffectQueueF135*, 0x2EC)->Spawn(effect, x, y, facing, layer,
            0, 0, &FIELD(float, 0x314), &FIELD(unsigned char, 0x2F0), mode);
    } else {
        FIELD(BattleEffectQueueF135*, 0x2EC)->Spawn(effect, x, y, facing, layer,
            0, 0, &FIELD(float, 0x314), 0, mode);
    }
}

void FighterEffectPoliciesF135::SpawnAuxEffect(short effect, float x, float y,
                                              signed char facing, signed char layer)
{
    g_AuxiliaryEffectsF135.Spawn(effect, x, y, facing, layer, 0, 0, &FIELD(float, 0x314));
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
    if (FIELD(short, 0x3B6) > 0) {
        FIELD(short, 0x3B6) = 1000;
    } else {
        FIELD(short, 0x3B0) = FIELD(short, 0x3B0) - amount;
        if (FIELD(short, 0x3B0) <= 0 && FIELD(short, 0x3B6) <= 0) {
            PlaySharedSound(43);
            FIELD(short, 0x3B0) = 0;
            FIELD(short, 0x3B6) = 1000;
        }
    }
}

#undef FIELD
