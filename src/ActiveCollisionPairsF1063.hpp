#pragma once
#include <stddef.h>
#include "BattleActiveCollision.hpp"

// Two independently observed contiguous real 32-bit player pointers at
// BattleActiveCollision owner+0x44/+0x48, and two real HUD pointers at
// +0x50/+0x54. These are borrowed array windows, not a complete owner
// layout or additional dynamic allocations; +0x4C remains unidentified.
struct ActiveCollisionActorPairF1063 {
    CombatActor* actors[2];
};
struct ActiveCollisionDisplayPairF1063 {
    ComboDisplay* displays[2];
};
typedef char F1063ActorPairSize[sizeof(ActiveCollisionActorPairF1063)==8?1:-1];
typedef char F1063DisplayPairSize[sizeof(ActiveCollisionDisplayPairF1063)==8?1:-1];
typedef char F1063ActorSecondOffset[offsetof(ActiveCollisionActorPairF1063,actors)==0 && sizeof(CombatActor*)==4?1:-1];
typedef char F1063DisplaySecondOffset[offsetof(ActiveCollisionDisplayPairF1063,displays)==0 && sizeof(ComboDisplay*)==4?1:-1];
#define F1063_ACTORS(owner) (*reinterpret_cast<ActiveCollisionActorPairF1063*>(reinterpret_cast<unsigned char*>(owner)+0x44))
#define F1063_DISPLAYS(owner) (*reinterpret_cast<ActiveCollisionDisplayPairF1063*>(reinterpret_cast<unsigned char*>(owner)+0x50))
