#pragma once
#include "BattleHud43E040.hpp"
#include "SpriteTransform.hpp"

// Pointer-only owner interface; the complete scene layout remains unknown.
class CharacterSelectOptions438240 { public: void RenderOptions(); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    RenderDrawing5E68C0* field008;
    unsigned char unknown00C[0x044 - 0x00C];
    RenderDrawing5E68C0* field044;
};
extern signed char g_CombatMode;
// Indexed byte observations; original declarations and array extents are unknown.
extern signed char g_SelectOptionAt00671434[];
extern unsigned char g_SelectOptionAt00671438[];
