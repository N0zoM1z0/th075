#ifndef TH075_EFFECT_DEQUE_F136_HPP
#define TH075_EFFECT_DEQUE_F136_HPP
#include "Actor.hpp"

// Call-only view of the target deque member's observed PushBack entry point.
// The complete member storage is the vendor std::deque<void*> in the manager;
// this declaration is never constructed, allocated or embedded.
class EffectDequeF136 {
public:
    void PushBack(Actor* const& effect);
};

#endif
