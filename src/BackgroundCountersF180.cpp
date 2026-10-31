#include "BackgroundCountersF180.hpp"

// Original game stage callback receiver has two directly adjacent signed
// 32-bit animation state counters at offsets 0x68 and 0x6C. This is a
// *borrowed tail view* only: the full background object type is unknown
// and must not be allocated or embedded via this small view.
struct BackgroundCounterWindowF913 {
    int animationTick;
    int animationFrame;
};
typedef char BackgroundCounterWindowF913SizeIs8[
    (sizeof(BackgroundCounterWindowF913) == 8) ? 1 : -1
];
#define COUNTERS (*reinterpret_cast<BackgroundCounterWindowF913*>(reinterpret_cast<unsigned char*>(this) + 0x68))
#define COUNTER (COUNTERS.animationTick)
#define FRAME (COUNTERS.animationFrame)

void BackgroundCountersF180::AdvanceAt00449EC0()
{
    COUNTER = COUNTER + 1;
}

void BackgroundCountersF180::AdvanceAt0044DA70()
{
    COUNTER = COUNTER + 1;
}

void BackgroundCountersF180::AdvanceAt0044F830()
{
    COUNTER = COUNTER + 1;
}

void BackgroundCountersF180::AdvanceAt00451420()
{
    COUNTER = COUNTER + 1;
}

void BackgroundCountersF180::AdvanceAt0044B600()
{
    COUNTER = COUNTER + 1;
    if (COUNTER > 360)
        COUNTER = 0;
}

void BackgroundCountersF180::AdvanceAt0044BB20()
{
    COUNTER = COUNTER + 1;
    if (COUNTER > 360)
        COUNTER = 0;
}

void BackgroundCountersF180::AdvanceAt0044C040()
{
    COUNTER = COUNTER + 1;
    if (COUNTER > 360)
        COUNTER = 0;
}

void BackgroundCountersF180::AdvanceAt0044D5E0()
{
    COUNTER = COUNTER + 1;
    if (COUNTER > 2500.0)
        COUNTER = 0;
}

void BackgroundCountersF180::AdvanceAt004503E0()
{
    COUNTER = COUNTER + 1;
    if (COUNTER >= 15360.0)
        COUNTER = 0;
}

void BackgroundCountersF180::AdvanceAt00450BD0()
{
    COUNTER = COUNTER + 1;
    FRAME = FRAME + 1;
    if (FRAME > 71)
        FRAME = 0;
}

void BackgroundCountersF180::AdvanceAt0044E3A0()
{
    COUNTER = COUNTER - 1;
    if (COUNTER < 0)
        COUNTER = 3840;
}

#undef FRAME
#undef COUNTER
#undef COUNTERS
