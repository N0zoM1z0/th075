#include "GameLeafHelpers.hpp"

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
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x64) = 0;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x62) = value;
    OnSecondaryCounterReset();
}

void AnimationState::ResetPrimaryCounters(short value)
{
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x64) = 0;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x62) = 0;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x60) = value;
    OnSecondaryCounterReset();
}

void AnimationState::SetThreeCounters(short first, short second, short third)
{
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x64) = third;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x62) = second;
    *reinterpret_cast<short *>(reinterpret_cast<u8 *>(this) + 0x60) = first;
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
