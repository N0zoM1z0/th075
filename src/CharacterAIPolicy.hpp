#ifndef TH075_CHARACTER_AI_POLICY_HPP
#define TH075_CHARACTER_AI_POLICY_HPP
#include "GameLeafHelpers.hpp"

// Observed call ABI; the original declaration, spelling and origin remain unknown.
float __cdecl AbsFloatAt00412D90(float value);
extern "C" int __cdecl rand();

// These constants describe observed policy choices, not a complete owner layout.
struct AI472890Policy {
    enum { firstSelector = 0x398, firstMode = 2, secondSelector = 0x39A,
           cancelSelector = 0x398, lateSelector = 0x39A };
    static int countdown;
};

struct AI4E7DE0Policy {
    enum { firstSelector = 0x39A, firstMode = 1, secondSelector = 0x39A,
           cancelSelector = 0x39A, lateSelector = 0x39A };
    static int countdown;
};
struct AI579650Policy {
    enum { firstSelector = 0x39A, firstMode = 1, secondSelector = 0x398,
           cancelSelector = 0x398, lateSelector = 0x39A };
    static int countdown;
};
struct AI59D240Policy {
    enum { firstSelector = 0x39A, firstMode = 1, secondSelector = 0x39A,
           cancelSelector = 0x39A, lateSelector = 0x398 };
    static int countdown;
};
struct AI5C5D10Policy {
    enum { firstSelector = 0x39A, firstMode = 1, secondSelector = 0x39A,
           cancelSelector = 0x39A, lateSelector = 0x39A };
    static int countdown;
};
struct AI5E7370Policy {
    enum { firstSelector = 0x398, firstMode = 2, secondSelector = 0x39A,
           cancelSelector = 0x398, lateSelector = 0x39A };
    static int countdown;
};

// Pointer-only receiver view. Never construct or embed an owner object.
template<class Policy> class CharacterAIPolicy {
public:
    void ChooseAction();
    int ChooseIntegerRange(int lower, int upper);
};
typedef CharacterAIPolicy<AI472890Policy> CharacterAI472890;
typedef CharacterAIPolicy<AI4E7DE0Policy> CharacterAI4E7DE0;
typedef CharacterAIPolicy<AI579650Policy> CharacterAI579650;
typedef CharacterAIPolicy<AI59D240Policy> CharacterAI59D240;
typedef CharacterAIPolicy<AI5C5D10Policy> CharacterAI5C5D10;
typedef CharacterAIPolicy<AI5E7370Policy> CharacterAI5E7370;
#endif
