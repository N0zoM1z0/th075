#pragma once

// Only the observed input methods are declared. These are not full scene
// definitions and must never be instantiated or embedded in other objects.
class TitleMenuInputF184 {
public:
    void PollMenuInput();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x014 - 0x000];
    int field014;
    int field018;
    int field01C;
};
class ReplayMenuInputF184 {
public:
    void PollInput();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x015 - 0x000];
    signed char field015;
    signed char field016;
    signed char field017;
    signed char field018;
};
