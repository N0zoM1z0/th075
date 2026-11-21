#pragma once
#include <stddef.h>

// Borrowed prefix of the original background callback receiver. The 0x68-byte
// prefix is still unknown; eleven complete callbacks independently observe
// signed 32-bit animation counters at +0x68 and +0x6C. The complete owner type
// and total extent remain unknown: access only through the original this
// pointer, and never instantiate or embed this view.
class BackgroundCountersF180 {
public:
    unsigned char unknown000[0x68];
    int animationTick;
    int animationFrame;

    void AdvanceAt00449EC0();
    void AdvanceAt0044DA70();
    void AdvanceAt0044F830();
    void AdvanceAt00451420();
    void AdvanceAt0044B600();
    void AdvanceAt0044BB20();
    void AdvanceAt0044C040();
    void AdvanceAt0044D5E0();
    void AdvanceAt004503E0();
    void AdvanceAt00450BD0();
    void AdvanceAt0044E3A0();
};

typedef char BackgroundCounterOffsetsF180[
    (offsetof(BackgroundCountersF180, animationTick) == 0x68 &&
     offsetof(BackgroundCountersF180, animationFrame) == 0x6C) ? 1 : -1];
