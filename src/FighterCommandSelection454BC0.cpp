#include "Fighter.hpp"
#include "CommandListF283.hpp"


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
    field47C = selection;
    field480->SetSamplingMode(mode);
    field480->SetColorMask(mask);
}
