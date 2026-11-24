#include "CombatEffects.hpp"
#include <stdlib.h>

void CombatEffects::ReleaseEntries()
{
    struct ReleaseState {
        void* second;
        void* first;
        unsigned int i;
    };
    ReleaseState state;
    for (state.i = 0; state.i < sides[0].size(); ++state.i) {
        state.first = sides[0][state.i];
        free(state.first);
    }
    sides[0].clear();
    for (state.i = 0; state.i < sides[1].size(); ++state.i) {
        state.second = sides[1][state.i];
        free(state.second);
    }
    sides[1].clear();
}
