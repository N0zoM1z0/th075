#ifndef TH075_FIGHTER_EFFECT_POLICIES_F135_HPP
#define TH075_FIGHTER_EFFECT_POLICIES_F135_HPP

// References to target-owned auxiliary effects and sound services only.
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


#endif
