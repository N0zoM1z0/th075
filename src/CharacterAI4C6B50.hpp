#ifndef TH075_CHARACTER_AI_4C6B50_HPP
#define TH075_CHARACTER_AI_4C6B50_HPP
#include "CharacterAIPolicy.hpp"

// Pointer-only receiver view; never construct or embed an owner object.
class CharacterAI4C6B50 {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; the original declaration and owner are unknown.
    static int countdown;
};
#endif
