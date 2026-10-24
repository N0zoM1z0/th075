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
};
