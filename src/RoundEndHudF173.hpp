#pragma once

// Call-only views of existing storage. Complete owner identities and indexed
// extents remain unknown; never instantiate or embed these partial owners.
class RoundEndF173 {
public:
    void EnterRoundEnd();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x00C - 0x000];
    int field00C;
    unsigned char unknown010[0x018 - 0x010];
    unsigned char field018;
    unsigned char unknown019[0x01A - 0x019];
    short field01A;
    unsigned char unknown01C[0x044 - 0x01C];
    unsigned char* field044;
    unsigned char* field048;
    unsigned char unknown04C[0x05D - 0x04C];
    unsigned char field05D;
};
class ModeCounterF173 {
public:
    void IncrementModeCounter(signed char category, signed char key);
};
class ComboCounterF173 {
public:
    // Native allocation callers forward the constructor receiver in EAX.
    ComboCounterF173(void* texture, signed char side);
    void UpdateComboCounter(short count, short value, short extra);
};
