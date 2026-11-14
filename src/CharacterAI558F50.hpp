#ifndef TH075_CHARACTER_AI_558F50_HPP
#define TH075_CHARACTER_AI_558F50_HPP
#include "Fighter.hpp"
#include "CharacterAIPolicy.hpp"

class CharacterAI558F50 : public Fighter {
public:
    void ChooseCardAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
};
#endif
