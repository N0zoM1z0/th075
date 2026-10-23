#ifndef TH075_CHARACTER_AI_49B070_HPP
#define TH075_CHARACTER_AI_49B070_HPP
#include "CharacterAIPolicy.hpp"

// Existing observed signed-byte global view; original declaration is unknown.
extern signed char g_StateRepeatLevelAt006714D0;

// Pointer-only receiver view; never construct or embed an owner object.
class CharacterAI49B070 {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
    // Observed signed dword view; the original declaration and owner are unknown.
    static int countdown;
};
#endif
