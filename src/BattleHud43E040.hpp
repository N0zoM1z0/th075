#pragma once
#include "Fighter.hpp"
#include "CharacterSpecial5E68C0.hpp"
#include "BattleRender43D9D0.hpp"

// Declaration-only views. Never construct or embed these partial owners.
class HudQuadOperations43E040 {
public:
    void Translate(float, float, float);
    void Scale(float, float, float, float, float, float);
};
// At returns a borrowed record address; only native shorts at +0/+6 are read.
// The underlying records have stride116; no complete record layout is claimed.
class HudRecordGroup43E040 { public: short* At(unsigned int); };
class HudDirectory43E040 { public: HudRecordGroup43E040*& At(unsigned int); };
class HudCombo43E040 { public: void Render(); public:
    // Observed fields; meanings not yet known.
    IDirect3DTexture8* field000;
    short field004;
    short field006;
    short field008;
    unsigned char field00A;
    signed char field00B;
    short field00C;
    short field00E;
    float field010;
};
void __cdecl DrawAtlasNumberAt00446B90(float, float, D3DCOLOR, int, signed char, int);
extern unsigned char g_SequenceByteAt0066C239;
extern unsigned char g_SequenceByteAt0066C23A;
extern unsigned char g_SequenceCounterAt00671622;
