#ifndef TH075_FIGHTER_EFFECT_POLICIES_F135_HPP
#define TH075_FIGHTER_EFFECT_POLICIES_F135_HPP

// Declaration-only views of existing receivers. Names are provisional; these
// interfaces establish neither complete owner layouts nor allocation sizes.
// Never define, construct, copy, or embed instances of these private owners.
class BattleEffectQueueF135 {
public:
    void Spawn(short effect, float x, float y, signed char facing, signed char layer,
               unsigned char flagA, unsigned char flagB, const float* parameters,
               const void* transform, unsigned char mode);
};

class AuxiliaryEffectsF135 {
public:
    void Spawn(short effect, float x, float y, signed char facing, signed char layer,
               unsigned char flagA, unsigned char flagB, const float* parameters);
};

class EffectSoundBankF135 {
public:
    void Play(int sound);
};

// References to target-owned storage only; no object definitions are provided.
extern AuxiliaryEffectsF135 g_AuxiliaryEffectsF135;
extern EffectSoundBankF135* g_SharedEffectSoundBankF135;

class FighterEffectPoliciesF135 {
public:
    void SpawnBattleEffect(short effect, float x, float y, signed char facing, signed char layer);
    void SpawnTrackedEffect(short effect, float x, float y, signed char facing, signed char layer,
                            unsigned char linked, unsigned char mode);
    void SpawnAuxEffect(short effect, float x, float y, signed char facing, signed char layer);
    void PlaySound(short sound);
    void PlaySharedSound(short sound);
    void UpdateGaugeTimer(int amount);
};

#endif
