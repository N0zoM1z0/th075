#include "battle/Fighter.hpp"
#include "battle/CommandListF283.hpp"


void CommandListF283::SetSamplingMode(unsigned char mode)
{
    this->mode = mode;
}

void CommandListF283::SetColorMask(unsigned int mask)
{
    colorMask = mask;
}

void Fighter::SetCommandSelection(
    int selection, unsigned char mode, unsigned int mask)
{
    spriteHistoryHoldFrames = selection;
    spriteHistory->SetSamplingMode(mode);
    spriteHistory->SetColorMask(mask);
}
