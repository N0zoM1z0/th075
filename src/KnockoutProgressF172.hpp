#pragma once
#include "Fighter.hpp"

// Call-only views of existing storage. Original identities, complete layouts
// and indexed extents remain unknown. Never instantiate or embed these owners.
class CardProgressF172 {
public:
    void MarkCardFlag(signed char key);
    void IncrementCardCounter(signed char key);
    int GetCardValue(signed char key);
    void SetCardValue(signed char key, int value);
};

class KnockoutResolutionF172 {
public:
    void ResolveKnockout();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x00C - 0x000];
    int field00C;
    unsigned char unknown010[0x018 - 0x010];
    unsigned char field018;
    unsigned char unknown019[0x01A - 0x019];
    short field01A;
    unsigned char unknown01C[0x044 - 0x01C];
    Fighter* field044;            // the two fighters
    Fighter* field048;
    unsigned char unknown04C[0x068 - 0x04C];
    int field068;
    int field06C;
};
