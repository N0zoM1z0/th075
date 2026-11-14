#ifndef TH075_CHARACTER_AI_557380_HPP
#define TH075_CHARACTER_AI_557380_HPP
#include "Fighter.hpp"
#include "CharacterAIPolicy.hpp"

class CharacterAI557380 : public Fighter {
public:
    void ChooseAction();
    // Observed signed dword view; original declaration and owner are unknown.
    static int countdown;
};
#endif
