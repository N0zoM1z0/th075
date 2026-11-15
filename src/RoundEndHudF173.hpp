#pragma once
#include "Fighter.hpp"

// Call-only views of existing storage. Complete owner identities and indexed
// extents remain unknown; never instantiate or embed these partial owners.
class ModeCounterF173 {
public:
    void IncrementModeCounter(signed char category, signed char key);
};
