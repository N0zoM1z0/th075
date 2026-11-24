#pragma once

#include "Fighter.hpp"

// Call-only derived view of the Fighter receiver. No instances are created
// and no fields are added to the native Fighter layout.
class FighterTrackedEffectsF169 : public Fighter {
public:
    void SpawnTrackedEffect(short effect, float x, float y, signed char facing,
                            signed char layer, unsigned char linked);
};
