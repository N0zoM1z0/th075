#ifndef TH075_CHARACTER_AI_CARD_POLICY_HPP
#define TH075_CHARACTER_AI_CARD_POLICY_HPP
#include "CharacterAIPolicy.hpp"

// Source-defined counter bindings; original declarations and owners are unknown.
struct AI474B40CardPolicy { static int countdown; };
struct AI5E9620CardPolicy { static int countdown; };

// Pointer-only receiver view; never construct or embed an owner object.
template<class Policy> class CharacterAICardPolicy {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
};
typedef CharacterAICardPolicy<AI474B40CardPolicy> CharacterAI474B40;
typedef CharacterAICardPolicy<AI5E9620CardPolicy> CharacterAI5E9620;
#endif
