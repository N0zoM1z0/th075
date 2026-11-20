#ifndef TH075_EFFECT_DISPATCH_F162_HPP
#define TH075_EFFECT_DISPATCH_F162_HPP
#include "Actor.hpp"
#include <deque>

// The game-owned effect objects use the common Actor slots 2/3/4 for
// primary, alternate, and overlay drawing; +0x67/+0x68 are Actor flags.
class DispatchingEffectF162 : public Actor {
public:
    virtual void Advance();
};

class Fighter;

// The same native +0x04 deque layout used by the effect advance manager,
// with the dispatch-side pointer type retained for VC7.1 template calls.
class EffectDispatchF162 {
public:
    void DispatchSelected(signed char layer);
    void DispatchAll();
private:
    Fighter* fighter_;
    std::deque<DispatchingEffectF162*> entries_[4];
    EffectDispatchF162();
    EffectDispatchF162(const EffectDispatchF162&);
    EffectDispatchF162& operator=(const EffectDispatchF162&);
};

typedef char EffectDispatchLayoutF162[sizeof(EffectDispatchF162) == 0x54 ? 1 : -1];

#endif
