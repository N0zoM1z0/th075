#include "Fighter.hpp"
#pragma once

// Declaration-only receiver views; never construct or embed these partial owners.
class StageOpponent5E59C0 {
public:
    void ResetPrimaryCounters(short);
};
class CharacterSpecial5E59C0 : public Fighter {
public:
    void InitializeStage();
    void RecordRoundFields(signed char, short, signed char, signed char, signed char, int, int, int);
public:
    // Character-specific fields after the shared Fighter layout.
    unsigned char unknownF10[0xFF4 - 0xF10];
    unsigned char fieldFF4;
    unsigned char fieldFF5;
    unsigned char fieldFF6;
    unsigned char fieldFF7;
};
void __cdecl SetCameraOverrideAt00412CC0(unsigned char, float, float, float);
void __cdecl SnapCameraAt00412CF0();

// Existing narrow global views; names and original declarations remain provisional.
extern signed char g_NoticeSelection;
extern int g_StateResetCounter;
extern unsigned char g_StateFadeAlpha;
extern signed char g_StateRepeatLevelAt006714D0;
extern unsigned char g_SequenceStageAt0067161D;
