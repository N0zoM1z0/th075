#ifndef TH075_CHARACTER_AI_4C8CD0_HPP
#define TH075_CHARACTER_AI_4C8CD0_HPP
#include "CharacterAIPolicy.hpp"

// Pointer-only receiver view; never construct or embed an owner object.
class CharacterAI4C8CD0 {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
};
#endif
