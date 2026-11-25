#include "characters/CharacterAuxAction.hpp"
#include "battle/CombatEffects.hpp"
#include <new>

#define EFFECT static_cast<CharacterAuxObject*>(sides[side].back())

void CombatEffects::Spawn(short pattern, float x, float y, unsigned char kind,
                          signed char side, unsigned char flags, unsigned char mode)
{
    if (!patterns[pattern]) return;
    if (!pattern) return;
    if (side<0 || side>1) return;
    {
        void* empty=0;
        sides[side].push_back(empty);
        sides[side].back() = new CharacterAuxObject(this);
        EFFECT->action = pattern;
        EFFECT->animationStage = 0;
        EFFECT->animationFrame = 0;
        EFFECT->x = x;
        EFFECT->y = y;
        EFFECT->facing = kind;
        EFFECT->field067 = flags;
        EFFECT->field068 = mode;
        EFFECT->transformEnabled = 0;
        EFFECT->BindAnimation();
        EFFECT->Advance();
    }
}

#undef EFFECT
