#include "CharacterAuxAction.hpp"
#include "CombatEffects.hpp"

void CombatEffects::DispatchSelectedList(signed char side)
{
    std::deque<void*>::iterator current = sides[side].begin();
    std::deque<void*>::iterator end = sides[side].end();
    for (; current != end; current++) {
        static_cast<CharacterAuxObject*>(*current)->Render();
    }
}
