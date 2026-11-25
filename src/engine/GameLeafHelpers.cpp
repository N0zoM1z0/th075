#include "platform/EventQueue.hpp"
#include "characters/CharacterObject.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "characters/CharacterAuxAction.hpp"
typedef CharacterAuxObject AuxEffect;

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

// Authentic empty action hook: native function keeps a thiscall receiver
// and discards one integer argument (RET 4). No artificial filler.
void CharacterObject::NoOpAt0045B850(int unused)
{
}

void Fighter::ClearNoticeTransition()
{
    noticeState = 0;
}

void AuxEffect::ClearField8()
{
    drawFrame = 0;
}

void SetClampedGameValue(int value)
{
    g_EventWaitMsAt0066C23C = value;
    if (g_EventWaitMsAt0066C23C < 0)
        g_EventWaitMsAt0066C23C = 0;
}
