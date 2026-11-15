#pragma once

// Read-only pointer view of a single scene method; no full layout.
class TitleAdvanceF185 {
public:
    unsigned short Advance();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x00C - 0x000];
    unsigned int field00C;
    unsigned int field010;
    unsigned char unknown014[0x018 - 0x014];
    int field018;
    int field01C;
    unsigned char field020;
    unsigned char field021;
    unsigned char field022;
    unsigned char field023;
    unsigned char unknown024[0x038 - 0x024];
    signed char field038;
};
