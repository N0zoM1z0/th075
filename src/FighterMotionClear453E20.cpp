#include "FighterMotionClear453E20.hpp"

// Preserve the observed DWORD zero stores without claiming the original
// declarations of these four motion fields.
#define WORD_AT(offset) (*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void FighterMotionClear453E20::ClearMotionFields()
{
    WORD_AT(0x50) = 0;
    WORD_AT(0x54) = 0;
    WORD_AT(0x58) = 0;
    WORD_AT(0x5C) = 0;
}

#undef WORD_AT
