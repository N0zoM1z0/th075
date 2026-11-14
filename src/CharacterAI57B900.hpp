#ifndef TH075_CHARACTER_AI_57B900_HPP
#define TH075_CHARACTER_AI_57B900_HPP
#include "Fighter.hpp"
#include "CharacterAIPolicy.hpp"

class CharacterAI57B900 : public Fighter {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
};
#endif
