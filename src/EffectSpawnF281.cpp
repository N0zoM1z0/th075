#include "CharacterAuxAction.hpp"
#include "CombatEffects.hpp"
#include <new>

#define EFFECT static_cast<CharacterAuxObject*>(sides[side].back())

void CombatEffects::SpawnConfigured(short pattern, float x, float y, signed char kind,
                                    signed char side, unsigned char flags, unsigned char mode,
                                    const float* extra)
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
        EFFECT->field040 = 0;
        EFFECT->spawnParameters[0] = extra[0];
        EFFECT->spawnParameters[1] = extra[1];
        EFFECT->spawnParameters[2] = extra[2];
        EFFECT->spawnParameters[3] = extra[3];
        EFFECT->BindAnimation();
        EFFECT->Advance();
    }
}

#undef EFFECT
