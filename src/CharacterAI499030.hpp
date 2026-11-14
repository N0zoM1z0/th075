#ifndef TH075_CHARACTER_AI_499030_HPP
#define TH075_CHARACTER_AI_499030_HPP
#include "Fighter.hpp"
#include "CharacterAIPolicy.hpp"

class CharacterAI499030 : public Fighter {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
public:
    // Character-specific fields after the shared Fighter layout.
    unsigned char unknownF10[0xF14 - 0xF10];
    short fieldF14;
};
#endif
