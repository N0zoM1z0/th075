#include "CharacterAuxAction.hpp"
#include "CombatEffects.hpp"

void CombatEffects::AdvanceAndPrune()
{
    for (int side = 0; side < 2; ++side) {
        struct IndexCount {
            int index;
            int count;
        } state;
        state.count = sides[side].size();
        for (state.index = 0; state.index < state.count; ++state.index) {
            static_cast<CharacterAuxObject*>(sides[side][state.index])->Advance();
        }
        std::deque<void*>::iterator iterator = sides[side].begin();
        while (iterator != sides[side].end()) {
            if (static_cast<CharacterAuxObject*>(*iterator)->drawFrame == 0) {
                delete static_cast<CharacterAuxObject*>(*iterator);
                iterator = sides[side].erase(iterator);
            } else {
                iterator++;
            }
        }
    }
}
