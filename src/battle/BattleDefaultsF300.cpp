#include "characters/CharacterObject.hpp"

// The base object constructor (0045B760): the Actor constructor runs first,
// then the object vtable (00659064) is installed and these fields cleared.
// Float members are cleared with integer stores, as the original does.
CharacterObject::CharacterObject()
{
    field080 = 0;
    field07C = 0;
    hitstopFrames = 0;
    collisionPointX = 0.0f;
    collisionPointY = 0.0f;
    hitReactionVelocityX = 0;
    hitReactionVelocityY = 0;
    velocityX = 0.0f;
    velocityY = 0.0f;
    field058 = 0;
    field05C = 0.0f;
    field04C = 0.0f;
    field084 = 0;
    field086 = 0;
    field088 = 0;
}
