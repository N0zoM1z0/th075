#ifndef TH075_CHARACTER_AI_4EA090_HPP
#define TH075_CHARACTER_AI_4EA090_HPP
#include "Fighter.hpp"
#include "CharacterAIPolicy.hpp"

class CharacterAI4EA090 : public Fighter {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
};
#endif
