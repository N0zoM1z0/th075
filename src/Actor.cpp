#include "Actor.hpp"
#include "MathLookup.hpp"
#include <cstring>

// Actor helpers shared by fighters, character objects and effects
// (0040FA30-0040FC50, in address order).

// Advances the frame counter through the current stage; returns the stage
// reached when one completes, the stage count when the action wraps, else 0.
short Actor::AdvanceNestedFrame() {
    ++animationFrame;
    if (animationFrame >= field072) {
        animationFrame = 0;
        ++animationStage;
        if (animationStage >= field070) {
            animationStage = 0;
            BindAnimation();
            return field070;
        }
        BindAnimation();
        return animationStage;
    }
    return 0;
}

// The action counters change together and slot 0 rebinds the animation.
void Actor::ResetPrimaryCounters(short value)
{
    animationFrame = 0;
    animationStage = 0;
    action = value;
    BindAnimation();
}

void Actor::SetThreeCounters(short first, short second, short third)
{
    animationFrame = third;
    animationStage = second;
    action = first;
    BindAnimation();
}

void Actor::ResetSecondaryCounter(short value)
{
    animationFrame = 0;
    animationStage = value;
    BindAnimation();
}

void Actor::SetPolarVelocity(float angle, float speed) {
    velocityX = MathLookup::ReadCosTable(angle) * speed;
    velocityY = -MathLookup::ReadPhaseTable(angle) * speed;
}

// Enables the sprite transform around a pivot with unit scale, no rotation
// and opaque colours.
void Actor::ResetTransform(float x, float y, float z) {
    field040 = 1;
    pivotX = x;
    pivotY = y;
    pivotZ = z;
    std::memset(&field010, 0, 0x24);   // field010 through rotationZ
    scaleX = 1.0f;
    scaleY = 1.0f;
    scaleZ = 1.0f;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    color[3] = 255;
    field016 = 0;
    field018 = 0;
    field01A = 0;
    field010 = 0;
}

void Actor::ClearTransformFlag()
{
    field040 = 0;
}
