#ifndef TH075_CHARACTER_AI_5349B0_HPP
#define TH075_CHARACTER_AI_5349B0_HPP
#include "CharacterAIPolicy.hpp"

// Pointer-only receiver view; never construct or embed an owner object.
class CharacterAI5349B0 {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Distinct observed recording/replay policy at 0x00455580.
    int ChooseRecordedIntegerRange(int lower, int upper);
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
};
#endif
