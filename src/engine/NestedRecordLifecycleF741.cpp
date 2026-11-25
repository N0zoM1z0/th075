#include <windows.h>
#include <string.h>
#include "battle/Actor.hpp"

FighterFrameInfo::FighterFrameInfo()
{
    memset(this, 0, sizeof(*this));
    hurtBoxes.clear();
    hitBoxes.clear();
    pose = 0;
}

FighterFrameInfo::~FighterFrameInfo()
{
    hurtBoxes.clear();
    hitBoxes.clear();
}
