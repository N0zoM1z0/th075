#include "characters/CharacterAuxAction.hpp"
#include "battle/CombatEffects.hpp"

CharacterAuxObject::CharacterAuxObject(CombatEffects* effectOwner)
{
    owner = effectOwner;
    patterns = &owner->patterns;
    drawing = &owner->texture;
    action = 0;
    animationStage = 0;
    animationFrame = 0;
    CharacterAuxObject::BindAnimation();
}

void CharacterAuxObject::SpawnPeer(short kind, float x, float y, signed char facing, signed char side)
{
    owner->SpawnConfigured(kind, x, y, facing, side, 0, 0, spawnParameters);
}

void CharacterAuxObject::SpawnConfiguredPeer(short kind, float x, float y, signed char facing, signed char side,
                                            unsigned char flags, unsigned char mode)
{
    owner->SpawnConfigured(kind, x, y, facing, side, flags, mode, spawnParameters);
}
