#pragma once

// Call-only view of existing storage; complete owner layout and original
// nominal identities remain unknown. Never instantiate or embed this owner.
class PauseDebugF175 {
public:
    void HandlePauseMenu();
    void ProcessDebugKeys();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x00C - 0x000];
    int field00C;
    unsigned char unknown010[0x018 - 0x010];
    signed char field018;
    unsigned char unknown019[0x044 - 0x019];
    unsigned char* field044;
    unsigned char* field048;
    unsigned char unknown04C[0x0A0 - 0x04C];
    unsigned char field0A0;
    unsigned char unknown0A1[0x118 - 0x0A1];
    signed char field118;
};
