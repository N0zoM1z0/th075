#ifndef TH075_CHARACTER_AI_532950_HPP
#define TH075_CHARACTER_AI_532950_HPP
#include "Fighter.hpp"
#include "CharacterAIPolicy.hpp"

class CharacterAI532950 : public Fighter {
public:
    void ChooseAction();
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
public:
    // Character-specific fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
};
#endif
