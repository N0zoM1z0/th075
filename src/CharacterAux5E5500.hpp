#include "Fighter.hpp"
#pragma once

class CharacterAux5E5500 : public Fighter {
public:
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
public:
    // Character-specific fields after the shared Fighter layout.
    unsigned char unknownF10[0xF2A - 0xF10];
    short fieldF2A;
};
