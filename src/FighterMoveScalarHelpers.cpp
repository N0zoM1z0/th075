#include "FighterFadeBorrowedF986.hpp"
#include "FighterGaugeBorrowedF980.hpp"
#include "FighterMoveScalarHelpers.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void FighterMoveScalarHelpers::SetNonnegativeWord(short value)
{
    if (value < 0)
        return;
    F980_GAUGE(this).scalarAt3B8 = value;
}

void FighterMoveScalarHelpers::BeginFadeParameters(unsigned char mode)
{
    F986_FADE(this).fadeAlphaAt538 = 0xF0;
    F986_FADE(this).drawModeAt539 = mode;
}

#undef FIELD
