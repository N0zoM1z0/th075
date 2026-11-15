#pragma once
#include "BattleHud43E040.hpp"

// Narrow global access views; original declarations and names are unknown.
extern signed char g_FrameClockMode;
extern signed char g_StateContinueCount;
extern unsigned char g_EndOverlayFlagAt00671624;

// Pointer-only receiver view. Never construct or embed this partial owner.
class BattleEndOverlay441910 {
public:
    void RenderEndOverlay();
    void RenderModeFive();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    void* field008;
    unsigned char unknown00C[0x018 - 0x00C];
    signed char field018;
    unsigned char unknown019[0x044 - 0x019];
    char* field044;
    char* field048;
    unsigned char unknown04C[0x0A0 - 0x04C];
    unsigned char field0A0;
    unsigned char field0A1;
    unsigned char unknown0A2[0x118 - 0x0A2];
    signed char field118;
};
