#include "FighterMoveScalarHelpers.hpp"


void FighterMoveScalarHelpers::SetNonnegativeWord(short value)
{
    if (value < 0)
        return;
    field3B8 = value;
}

void FighterMoveScalarHelpers::BeginFadeParameters(unsigned char mode)
{
    fadeAlpha = 0xF0;
    drawMode = mode;
}
