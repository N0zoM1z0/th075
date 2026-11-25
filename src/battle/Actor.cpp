#include "battle/Actor.hpp"
#include "engine/MathLookup.hpp"
#include <cstring>

// Actor helpers shared by fighters, character objects and effects
// (0040FA30-0040FC50, in address order).

// Advances the frame counter through the current stage; returns the stage
// reached when one completes, animationStageCount when the action wraps, else 0.
short ActorRenderingBase::AdvanceNestedFrame() {
    ++animationFrame;
    if (animationFrame >= animationFrameCount) {
        animationFrame = 0;
        ++animationStage;
        if (animationStage >= animationStageCount) {
            animationStage = 0;
            BindAnimation();
            return animationStageCount;
        }
        BindAnimation();
        return animationStage;
    }
    return 0;
}

// The action counters change together and slot 0 rebinds the animation.
void ActorRenderingBase::ResetPrimaryCounters(short value)
{
    animationFrame = 0;
    animationStage = 0;
    action = value;
    BindAnimation();
}

void ActorRenderingBase::SetThreeCounters(short first, short second, short third)
{
    animationFrame = third;
    animationStage = second;
    action = first;
    BindAnimation();
}

void ActorRenderingBase::ResetSecondaryCounter(short value)
{
    animationFrame = 0;
    animationStage = value;
    BindAnimation();
}

void ActorRenderingBase::SetPolarVelocity(float angle, float speed) {
    velocityX = MathLookup::ReadCosTable(angle) * speed;
    velocityY = -MathLookup::ReadPhaseTable(angle) * speed;
}

// Enables the sprite transform around a pivot with unit scale, no rotation
// and opaque colours.
void ActorRenderingBase::ResetTransform(float x, float y, float z) {
    transformEnabled = 1;
    pivotX = x;
    pivotY = y;
    pivotZ = z;
    std::memset(&transformRecord, 0, sizeof(transformRecord));
    scaleX = 1.0f;
    scaleY = 1.0f;
    scaleZ = 1.0f;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    color[3] = 255;
    spriteOffsetX = 0;
    spriteOffsetY = 0;
    spriteOffsetZ = 0;
    transformFlags = 0;
}

void ActorRenderingBase::ClearTransformFlag()
{
    transformEnabled = 0;
}
