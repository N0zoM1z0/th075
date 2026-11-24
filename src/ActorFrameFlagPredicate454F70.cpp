#include "Actor.hpp"

// The target takes the actor in ECX and returns the tested bit as an int.
int __fastcall FrameFlag20PredicateAt00454F70(Actor* actor)
{
    return (actor->frameInfo->flags & 0x20) > 0;
}
