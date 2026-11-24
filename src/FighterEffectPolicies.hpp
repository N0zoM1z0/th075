#ifndef TH075_FIGHTER_EFFECT_POLICIES_F135_HPP
#define TH075_FIGHTER_EFFECT_POLICIES_F135_HPP

// References to target-owned auxiliary effects and sound services only.
class AuxiliaryEffectsF135 {
public:
    void Spawn(short effect, float x, float y, signed char facing, signed char layer,
               unsigned char flagA, unsigned char flagB, const float* parameters);
};

// Bounded view of the 20-byte Fighter+0x6D0 embedded bank. Its internal
// fields and any larger shared-bank owner remain unknown.
class EffectSoundBankF135 {
public:
private:
    unsigned char unknown000[0x14];
};
typedef char EffectSoundBankF135SizeCheck[(sizeof(EffectSoundBankF135) == 0x14) ? 1 : -1];

// References to target-owned storage only; no object definitions are provided.
extern AuxiliaryEffectsF135 g_AuxiliaryEffectsF135;


#endif
