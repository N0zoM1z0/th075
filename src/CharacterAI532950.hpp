#ifndef TH075_CHARACTER_AI_532950_HPP
#define TH075_CHARACTER_AI_532950_HPP
#include "CharacterAIPolicy.hpp"

// Pointer-only receiver view; never construct or embed an owner object.
class CharacterAI532950 {
public:
    void ChooseAction();
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
};
#endif
