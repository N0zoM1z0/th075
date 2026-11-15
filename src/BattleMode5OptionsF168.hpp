#pragma once

// Call-only receiver view; original class name and complete layout are unknown.
// Do not instantiate, allocate or embed this owner.
class BattleMode5OptionsF168 {
public:
    void HandleMode5Options();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x018 - 0x000];
    unsigned char field018;
    unsigned char unknown019[0x044 - 0x019];
    unsigned char* field044;
    unsigned char* field048;
    unsigned char unknown04C[0x0A0 - 0x04C];
    unsigned char field0A0;
    unsigned char unknown0A1[0x118 - 0x0A1];
    signed char field118;
};
