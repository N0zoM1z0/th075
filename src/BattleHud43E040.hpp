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
class BattleHud43E040 { public: void RenderHud(); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    void* field008;
    unsigned char unknown00C[0x018 - 0x00C];
    signed char field018;
    unsigned char unknown019[0x044 - 0x019];
    Fighter* field044;            // the two fighters
    Fighter* field048;
    unsigned char unknown04C[0x050 - 0x04C];
    void* field050;
    void* field054;
    unsigned char unknown058[0x08C - 0x058];
    float field08C;
    unsigned char unknown090[0x098 - 0x090];
    unsigned char field098;
    unsigned char field099;
};
void __cdecl DrawAtlasNumberAt00446B90(float, float, D3DCOLOR, int, signed char, int);
extern unsigned char g_SequenceByteAt0066C239;
extern unsigned char g_SequenceByteAt0066C23A;
extern unsigned char g_SequenceCounterAt00671622;
