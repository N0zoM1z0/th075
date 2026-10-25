#pragma once

// Pointer-only interfaces; neither complete owner layout is established.
// Do not construct or embed either owner.
class ProfileSelectionF155 {
public:
    void IncrementSelectedWordCounter(signed char index);
};

class FighterResourceParameters452B30 {
public:
    void SelectResourceParameters();
};

extern signed char g_CombatMode;
extern signed char g_FrameClockMode;
// External storage view, without an allocation-size claim.
extern unsigned char g_ProfileSelectionAt006718F8[];
