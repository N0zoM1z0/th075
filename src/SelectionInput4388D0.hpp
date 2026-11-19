#pragma once
#include "InputJoystick.hpp"
#include <string.h>

// Complete copied physical block, not an original type/member-name claim.
struct HeldInputBlock4388D0 { int counts[7]; };
typedef char HeldInputBlockSize4388D0[(sizeof(HeldInputBlock4388D0) == 28) ? 1 : -1];
// Pointer-only owners: their complete layouts are unknown; never instantiate.
class InputMapping4388D0 { public: void UpdateHeldCounts(); bool IsKeyDown(unsigned char); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x004 - 0x000];
    signed char field004;
    unsigned char unknown005[0x008 - 0x005];
    int field008;
    int field00C;
    int field010;
    int field014;
    unsigned char unknown018[0x02C - 0x018];
    int field02C;
    int field030;
};
extern InputMapping4388D0 g_InputMappingAt00671638, g_InputMappingAt00671680;
// These copied subregions also lie at +0x2C in the corresponding receivers.
extern HeldInputBlock4388D0 g_HeldInputAt00671664, g_HeldInputAt006716AC;
extern signed char g_CombatMode, g_SelectActiveSideAt006714B8;
namespace Input { extern unsigned char g_KeyboardState[256]; }
namespace Graphics { void ToggleWindowMode(); }
