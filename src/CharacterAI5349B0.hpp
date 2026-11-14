#ifndef TH075_CHARACTER_AI_5349B0_HPP
#define TH075_CHARACTER_AI_5349B0_HPP
#include "Fighter.hpp"
#include "CharacterAIPolicy.hpp"

class CharacterAI5349B0 : public Fighter {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Distinct observed recording/replay policy at 0x00455580.
    int ChooseRecordedIntegerRange(int lower, int upper);
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
public:
    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF12 - 0xF10];
    short fieldF12;
};
#endif
