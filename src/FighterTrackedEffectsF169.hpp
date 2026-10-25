#pragma once

// Call-only receiver; original class identity and complete layout are unknown.
// Never construct, allocate or embed this private owner.
class FighterTrackedEffectsF169 {
public:
    void SpawnTrackedEffect(short effect, float x, float y, signed char facing,
                            signed char layer, unsigned char linked);
    void SpawnTrackedEffectWithFlags(short effect, float x, float y,
                                     signed char facing, signed char layer,
                                     unsigned char flagA, unsigned char flagB,
                                     unsigned char linked);
};
