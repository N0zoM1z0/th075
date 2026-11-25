#pragma once
#include "characters/CharacterObject.hpp"
#include "characters/youmu/YoumuFighter.hpp"
#include "characters/youmu/YoumuHistoryQueueF378.hpp"

// Both the auxiliary writer and the object's std::list::front consumer
// use ObservedInputSnapshotF378 directly, with no alternate field aliases.

// The owner gauge timer is the inherited Fighter method at 0046D000.

float __cdecl AngleAt00483300(float, float);

float __cdecl AbsFloatAt00412D90(float);
