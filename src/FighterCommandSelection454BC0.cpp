#include "FighterCommandSelection454BC0.hpp"


void SpriteSequenceParametersF154::SetSamplingMode(unsigned char mode)
{
    field010 = mode;
}

void SpriteSequenceParametersF154::SetColorMask(unsigned int mask)
{
    field014 = mask;
}

void FighterCommandSelection454BC0::SetCommandSelection(
    int selection, unsigned char mode, unsigned int mask)
{
    field47C = selection;
    field480->SetSamplingMode(mode);
    field480->SetColorMask(mask);
}
