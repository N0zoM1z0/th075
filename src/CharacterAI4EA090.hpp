#ifndef TH075_CHARACTER_AI_4EA090_HPP
#define TH075_CHARACTER_AI_4EA090_HPP
#include "CharacterAIPolicy.hpp"

// Pointer-only receiver view; never construct or embed an owner object.
class CharacterAI4EA090 {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
};
#endif
