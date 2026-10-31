#include "GameLeafHelpers.hpp"

// Native signed 16-bit animation counters occupy three adjacent words:
// Original +0x60, +0x62, +0x64. This is only a borrowed tail window
// of the unknown full virtual AnimationState owner; never instantiate it.
struct AnimationCounterTailF919 {
    short primaryAction;
    short secondaryAction;
    short animationFrame;
};
typedef char AnimationCounterTailSizeF919[
    sizeof(AnimationCounterTailF919)==6 ? 1 : -1];
#define ANIMATION_COUNTERS (*reinterpret_cast<AnimationCounterTailF919*>(reinterpret_cast<u8*>(this) + 0x60))

SpriteGeometry *SpriteGeometry::SetFourDwords(
    u32 first, u32 second, u32 third, u32 fourth)
{
    first_ = first;
    second_ = second;
    third_ = third;
    fourth_ = fourth;
    return this;
}

void AnimationState::ClearByte40()
{
    *(reinterpret_cast<u8 *>(this) + 0x40) = 0;
}

void AnimationState::ResetSecondaryCounter(short value)
{
    ANIMATION_COUNTERS.animationFrame = 0;
    ANIMATION_COUNTERS.secondaryAction = value;
    OnSecondaryCounterReset();
}

void AnimationState::ResetPrimaryCounters(short value)
{
    ANIMATION_COUNTERS.animationFrame = 0;
    ANIMATION_COUNTERS.secondaryAction = 0;
    ANIMATION_COUNTERS.primaryAction = value;
    OnSecondaryCounterReset();
}

void AnimationState::SetThreeCounters(short first, short second, short third)
{
    ANIMATION_COUNTERS.animationFrame = third;
    ANIMATION_COUNTERS.secondaryAction = second;
    ANIMATION_COUNTERS.primaryAction = first;
    OnSecondaryCounterReset();
}

void BattleEffect::ClearField74()
{
    *reinterpret_cast<u32 *>(reinterpret_cast<u8 *>(this) + 0x74) = 0;
}

void FighterState::ClearNoticeTransition()
{
    *(reinterpret_cast<u8 *>(this) + 0x6E6) = 0;
}

void AuxEffect::ClearField8()
{
    *reinterpret_cast<u32 *>(reinterpret_cast<u8 *>(this) + 8) = 0;
}

void SetClampedGameValue(int value)
{
    g_ClampedGameValue = value;
    if (g_ClampedGameValue < 0)
        g_ClampedGameValue = 0;
}
#undef ANIMATION_COUNTERS
