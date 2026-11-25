#include "characters/CharacterObject.hpp"

// The base object constructor (0045B760): the Actor constructor runs first,
// then the object vtable (00659064) is installed and these fields cleared.
// Float members are cleared with integer stores, as the original does.
CharacterObject::CharacterObject()
{
    remainingHits = 0;
    collisionResult = CollisionResult::None;
    hitstopFrames = 0;
    collisionPointX = 0.0f;
    collisionPointY = 0.0f;
    hitReactionVelocityX = 0;
    hitReactionVelocityY = 0;
    velocityX = 0.0f;
    velocityY = 0.0f;
    field058 = 0;
    verticalAcceleration = 0.0f;
    field04C = 0.0f;
    hitInvulnerabilityFrames = 0;
    throwInvulnerabilityFrames = 0;
    grazeFrames = 0;
}
