#pragma once
#include "BattleHud43E040.hpp"
#include "SpriteTransform.hpp"
#include "BattleCombat.hpp"

// Pointer-only receiver views; their complete original layouts are unknown.
class SinglePlayerOptions438670 { public: void RenderOptions(); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    RenderDrawing5E68C0* field008;
    unsigned char unknown00C[0x0EA - 0x00C];
    signed char field0EA;
    unsigned char unknown0EB[0x0EC - 0x0EB];
    signed char field0EC;
};
class ProgressCard438A80 { public: signed char GetSelectedValue(); };
