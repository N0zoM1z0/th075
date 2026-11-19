#pragma once
#include "CharacterObject.hpp"
#include "YoumuFighter.hpp"
#include "YoumuHistoryQueueF378.hpp"

// The object history relay reads the same 16-byte value that the fighter's
// auxiliary update appends. R243 classifies FrontAt00540220 as the native
// list-front worker over the same borrowed +0xFEC list; these aliases keep
// the action-side field names without inventing a second container type.
typedef ObservedInputSnapshotF378 ObjectHistoryEntryF1211;
typedef ObservedEffectQueueF378 ObjectHistoryListF1211;

// The owner gauge timer is the inherited Fighter method at 0046D000.

float __cdecl AngleAt00483300(float, float);

float __cdecl AbsFloatAt00412D90(float);
