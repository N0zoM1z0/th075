#pragma once
#include <stddef.h>

// Borrow only the two adjacent native 16-bit actor collision hold counters.
// +0x3B8 is the current countdown; +0x3BA receives its previous value
// before the current countdown is decremented. Both slots are independently
// read in whole native actor frame functions. Never embed this partial view.
struct FrameActorCollisionCountdownF1036 {
    signed short activeCountdown;
    signed short previousCountdown;
};
typedef char F1036CollisionPairSize[
    sizeof(FrameActorCollisionCountdownF1036)==4 ? 1 : -1];
typedef char F1036CollisionPreviousOffset[
    offsetof(FrameActorCollisionCountdownF1036,previousCountdown)==2 ? 1 : -1];
#define F1036_COLLISION(actor) (*reinterpret_cast<FrameActorCollisionCountdownF1036*>(reinterpret_cast<unsigned char*>(actor)+0x3B8))
