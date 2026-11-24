#pragma once
#include "BattleSessionState.hpp"
#include "Fighter.hpp"
#include "CharacterSpecial5E68C0.hpp"
#include "BattleRender43D9D0.hpp"

// At returns a borrowed record address; only native shorts at +0/+6 are read.
// The underlying records have stride116; no complete record layout is claimed.
class HudRecordGroup43E040 { public: short* At(unsigned int); };
class HudDirectory43E040 { public: HudRecordGroup43E040*& At(unsigned int); };
void __cdecl DrawAtlasNumberAt00446B90(float, float, D3DCOLOR, int, signed char, int);
