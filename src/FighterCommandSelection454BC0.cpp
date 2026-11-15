#include "FighterCommandSelection454BC0.hpp"


void SpriteSequenceParametersF154::SetSamplingMode(unsigned char mode)
{
    field010 = mode;
}

void SpriteSequenceParametersF154::SetColorMask(unsigned int mask)
{
    field014 = mask;
}

void Fighter::SetCommandSelection(
    int selection, unsigned char mode, unsigned int mask)
{
    field47C = selection;
    reinterpret_cast<SpriteSequenceParametersF154*&>(field480)->SetSamplingMode(mode);
    reinterpret_cast<SpriteSequenceParametersF154*&>(field480)->SetColorMask(mask);
}
