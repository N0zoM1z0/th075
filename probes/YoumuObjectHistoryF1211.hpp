#pragma once
#include "CharacterObject.hpp"
#include "YoumuFighter.hpp"
#include "YoumuHistoryQueueF378.hpp"

// The object history relay reads the same 16-byte record written by the
// fighter's auxiliary update. FrontAt00540220 is the native list-front
// worker of YoumuFighter::historyQueue.
typedef ObservedInputSnapshotF378 ObjectHistoryEntryF1211;

// The owner gauge timer is the inherited Fighter method at 0046D000.

float __cdecl AngleAt00483300(float, float);

float __cdecl AbsFloatAt00412D90(float);
