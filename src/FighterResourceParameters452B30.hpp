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
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x2CD - 0x000];
    signed char field2CD;
    unsigned char unknown2CE[0x36C - 0x2CE];
    float field36C;
    unsigned char unknown370[0x39D - 0x370];
    signed char field39D;
    unsigned char unknown39E[0x3A0 - 0x39E];
    short field3A0;
    short field3A2;
    unsigned int field3A4;
    unsigned int field3A8;
    unsigned char unknown3AC[0x464 - 0x3AC];
    unsigned char field464;
};

extern signed char g_CombatMode;
extern signed char g_FrameClockMode;
// External storage view, without an allocation-size claim.
extern unsigned char g_ProfileSelectionAt006718F8[];
