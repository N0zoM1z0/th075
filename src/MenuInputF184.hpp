#pragma once

// Only the observed input methods are declared. These are not full scene
// definitions and must never be instantiated or embedded in other objects.
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
