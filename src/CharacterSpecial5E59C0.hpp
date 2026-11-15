#pragma once

#include "MeilingFighter.hpp"
#include "Fighter.hpp"
void __cdecl SetCameraOverrideAt00412CC0(unsigned char, float, float, float);
void __cdecl SnapCameraAt00412CF0();

// Existing narrow global views; names and original declarations remain provisional.
extern signed char g_NoticeSelection;
extern int g_StateResetCounter;
extern unsigned char g_StateFadeAlpha;
extern signed char g_StateRepeatLevelAt006714D0;
extern unsigned char g_SequenceStageAt0067161D;
