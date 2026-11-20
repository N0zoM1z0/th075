#include "Actor.hpp"

// Provisional natural C++ reconstruction of the unreferenced 00454F70 leaf.
// Its owner/original role remains unclassified; retain the address in the name.
int __fastcall FrameFlag20PredicateAt00454F70(Actor* actor)
{
    return (actor->frameInfo->flags & 0x20) > 0;
}
