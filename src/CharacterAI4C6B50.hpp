#ifndef TH075_CHARACTER_AI_4C6B50_HPP
#define TH075_CHARACTER_AI_4C6B50_HPP
#include "Fighter.hpp"
#include "CharacterAIPolicy.hpp"

class CharacterAI4C6B50 : public Fighter {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; the original declaration and owner are unknown.
    static int countdown;
};
#endif
