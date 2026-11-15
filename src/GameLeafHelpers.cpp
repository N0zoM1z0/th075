#include "CharacterObject.hpp"
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

void CharacterObject::ClearFrameInfo()
{
    frameInfo = 0;
}

void Fighter::ClearNoticeTransition()
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
