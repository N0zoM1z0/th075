#include "BackgroundCountersF180.hpp"

void BackgroundCountersF180::AdvanceAt00449EC0()
{
    animationTick = animationTick + 1;
}

void BackgroundCountersF180::AdvanceAt0044DA70()
{
    animationTick = animationTick + 1;
}

void BackgroundCountersF180::AdvanceAt0044F830()
{
    animationTick = animationTick + 1;
}

void BackgroundCountersF180::AdvanceAt00451420()
{
    animationTick = animationTick + 1;
}

void BackgroundCountersF180::AdvanceAt0044B600()
{
    animationTick = animationTick + 1;
    if (animationTick > 360)
        animationTick = 0;
}

void BackgroundCountersF180::AdvanceAt0044BB20()
{
    animationTick = animationTick + 1;
    if (animationTick > 360)
        animationTick = 0;
}

void BackgroundCountersF180::AdvanceAt0044C040()
{
    animationTick = animationTick + 1;
    if (animationTick > 360)
        animationTick = 0;
}

void BackgroundCountersF180::AdvanceAt0044D5E0()
{
    animationTick = animationTick + 1;
    if (animationTick > 2500.0)
        animationTick = 0;
}

void BackgroundCountersF180::AdvanceAt004503E0()
{
    animationTick = animationTick + 1;
    if (animationTick >= 15360.0)
        animationTick = 0;
}

void BackgroundCountersF180::AdvanceAt00450BD0()
{
    animationTick = animationTick + 1;
    animationFrame = animationFrame + 1;
    if (animationFrame > 71)
        animationFrame = 0;
}

void BackgroundCountersF180::AdvanceAt0044E3A0()
{
    animationTick = animationTick - 1;
    if (animationTick < 0)
        animationTick = 3840;
}
