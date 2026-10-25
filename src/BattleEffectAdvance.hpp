#ifndef TH075_BATTLE_EFFECT_ADVANCE_F137_HPP
#define TH075_BATTLE_EFFECT_ADVANCE_F137_HPP

// Pointer-only receiver views. Complete game owner layouts and original
// class identities remain unknown; never construct or embed these owners.
class AdvancingEffectF137 {
public:
    virtual void UnknownSlot0();
    virtual void Advance();
    // This static view follows the observed unsized deallocation path with
    // no destructor call. It establishes no other type's destruction contract.
};

class BattleEffectAdvanceF137 {
public:
    void AdvanceAll();
};

#endif
