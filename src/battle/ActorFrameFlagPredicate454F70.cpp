#include "battle/Actor.hpp"
#include "battle/FighterFrameFlags.hpp"

// The target takes the actor in ECX and returns the tested bit as an int.
int __fastcall FrameFlag20PredicateAt00454F70(Actor* actor)
{
    return (actor->frameInfo->flags & FrameFlags::CanCancel) > 0;
}
