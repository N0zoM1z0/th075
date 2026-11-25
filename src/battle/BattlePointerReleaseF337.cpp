#include "characters/CharacterAuxAction.hpp"
#include "battle/CombatEffects.hpp"

void CombatEffects::ReleaseEntries()
{
    unsigned int index;
    for (index = 0; index < sides[0].size(); ++index) {
        delete static_cast<CharacterAuxObject*>(sides[0][index]);
    }
    sides[0].clear();
    for (index = 0; index < sides[1].size(); ++index) {
        delete static_cast<CharacterAuxObject*>(sides[1][index]);
    }
    sides[1].clear();
}
