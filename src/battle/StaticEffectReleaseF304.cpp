#include "battle/CombatEffects.hpp"

CombatEffects::~CombatEffects()
{
    ReleaseEntries();
    for (unsigned int index = 0; index < patterns.size(); ++index) {
        if (patterns[index])
            delete patterns[index];
    }
    patterns.clear();
}

EffectPatternSequence::EffectPatternSequence()
{
    frames.clear();
}

EffectPatternSequence::~EffectPatternSequence()
{
    frames.clear();
}
