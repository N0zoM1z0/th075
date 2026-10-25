#include "FighterCommandSelection454BC0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void SpriteSequenceParametersF154::SetSamplingMode(unsigned char mode)
{
    FIELD(unsigned char, 0x10) = mode;
}

void SpriteSequenceParametersF154::SetColorMask(unsigned int mask)
{
    FIELD(unsigned int, 0x14) = mask;
}

void FighterCommandSelection454BC0::SetCommandSelection(
    int selection, unsigned char mode, unsigned int mask)
{
    FIELD(int, 0x47C) = selection;
    FIELD(SpriteSequenceParametersF154*, 0x480)->SetSamplingMode(mode);
    FIELD(SpriteSequenceParametersF154*, 0x480)->SetColorMask(mask);
}

#undef FIELD
