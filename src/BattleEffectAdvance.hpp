#ifndef TH075_BATTLE_EFFECT_ADVANCE_F137_HPP
#define TH075_BATTLE_EFFECT_ADVANCE_F137_HPP
#include "Actor.hpp"

// The effects share Actor's animation frame pointer and virtual Advance.
// These are native-owned objects reached only through existing pointers.
class AdvancingEffectF137 : public Actor {
public:
    virtual void Advance();
    // Target uses Actor's slot-1 Advance and its +0x74 frame pointer.
    // The unsized delete does not invoke a virtual destructor.
};

#include <deque>
class Fighter;

// This is the observed four-list manager layout, viewed through its
// advancing-effect pointer type. The bound fighter occupies the first word;
// each 20-byte native deque follows from +0x04. The game owns this object.
class BattleEffectAdvanceF137 {
public:
    void AdvanceAll();
private:
    Fighter* fighter_;
    std::deque<AdvancingEffectF137*> entries_[4];
    BattleEffectAdvanceF137();
    BattleEffectAdvanceF137(const BattleEffectAdvanceF137&);
    BattleEffectAdvanceF137& operator=(const BattleEffectAdvanceF137&);
};

typedef char BattleEffectAdvanceLayoutF137[
    sizeof(BattleEffectAdvanceF137) == 0x54 ? 1 : -1];

#endif
