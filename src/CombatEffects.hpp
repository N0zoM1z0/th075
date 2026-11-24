#pragma once

#include "Actor.hpp"
#include "TextureManagerF198.hpp"
#include <deque>

struct EffectPatternSequence {
    std::vector<FighterFrameInfoHeader> frames;
    EffectPatternSequence();
    ~EffectPatternSequence();
};

class CombatEffects {
public:
    CombatEffects();
    ~CombatEffects();
    void ReleaseEntries();
    void DispatchSelectedList(signed char side);
    void AdvanceAndPrune();
    void LoadResources();
    void LoadPatternCatalog();
    void Spawn(short effect, float x, float y, unsigned char kind,
               signed char side, unsigned char flags, unsigned char mode);
    void SpawnConfigured(short effect, float x, float y, signed char facing, signed char side,
                         unsigned char flags, unsigned char mode, const float* parameters);

    std::deque<void*> sides[2];
    TextureManagerF198 texture;
    std::vector<EffectPatternSequence*> patterns;
};

typedef char CombatEffectsLayout[(sizeof(CombatEffects) == 0x88 &&
    offsetof(CombatEffects, texture) == 0x28 &&
    offsetof(CombatEffects, patterns) == 0x78) ? 1 : -1];

extern CombatEffects g_CombatEffects;
