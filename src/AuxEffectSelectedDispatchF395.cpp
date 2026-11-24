#include "CombatEffects.hpp"

class EffectChildF395 {
public:
    virtual void Initialize();
    virtual void Release();
    virtual void Dispatch();
};

void CombatEffects::DispatchSelectedList(signed char side)
{
    std::deque<void*>::iterator current = sides[side].begin();
    std::deque<void*>::iterator end = sides[side].end();
    for (; current != end; current++) {
        static_cast<EffectChildF395*>(*current)->Dispatch();
    }
}
