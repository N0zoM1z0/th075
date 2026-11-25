#include "battle/BackgroundStages.hpp"

void Background00bF376::Advance()
{
    field68 = field68 + 1;
}

void BackgroundBG04bF377::Advance()
{
    field68 = field68 + 1;
}

void BackgroundBG06aF377::Advance()
{
    field68 = field68 + 1;
}

void BackgroundBG09aF377::Advance()
{
    field68 = field68 + 1;
}

void BackgroundBG02aF377::Advance()
{
    field68 = field68 + 1;
    if (field68 > 360)
        field68 = 0;
}

void BackgroundBG02bF377::Advance()
{
    field68 = field68 + 1;
    if (field68 > 360)
        field68 = 0;
}

void BackgroundBG02cF377::Advance()
{
    field68 = field68 + 1;
    if (field68 > 360)
        field68 = 0;
}

void BackgroundBG04aF377::Advance()
{
    field68 = field68 + 1;
    if (field68 > 2500.0)
        field68 = 0;
}

void BackgroundBG07aF377::Advance()
{
    field68 = field68 + 1;
    if (field68 >= 15360.0)
        field68 = 0;
}

void BackgroundBG08aF377::Advance()
{
    field68 = field68 + 1;
    field6C = field6C + 1;
    if (field6C > 71)
        field6C = 0;
}

void BackgroundBG05aF377::Advance()
{
    field68 = field68 - 1;
    if (field68 < 0)
        field68 = 3840;
}
