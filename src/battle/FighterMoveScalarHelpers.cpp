#include "battle/FighterMoveScalarHelpers.hpp"


void Fighter::SetNonnegativeWord(short value)
{
    if (value < 0)
        return;
    field3B8 = value;
}

void Fighter::BeginFadeParameters(unsigned char mode)
{
    fadeAlpha = 0xF0;
    drawMode = mode;
}
