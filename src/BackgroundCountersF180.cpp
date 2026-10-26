#include "BackgroundCountersF180.hpp"

#define COUNTER (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x68))
#define FRAME (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6C))

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
