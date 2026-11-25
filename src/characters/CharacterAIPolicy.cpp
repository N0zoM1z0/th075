#include "characters/CharacterAIPolicy.hpp"
#include "characters/ReimuFighter.hpp"
#include "characters/AliceFighter.hpp"
#include "characters/YuyukoFighter.hpp"
#include "characters/YukariFighter.hpp"
#include "characters/SuikaFighter.hpp"
#include "characters/MeilingFighter.hpp"

#define OPPONENT_GUARD static_cast<Fighter*>(opponent)->IsState50To149()
#define FORWARD_COMMAND (2 - (facing == 1))
#define AIR_FORWARD_COMMAND (2 - (facing == -1))
#define AIR_BACK_COMMAND (1 + (facing == -1))

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AISeparation { float x, y; };

namespace {

// The selector indices refer to the two entries in Fighter::selectedSpellCards.
struct ReimuActionPolicy {
    enum { firstSelector = 0, firstMode = 2, secondSelector = 1,
           cancelSelector = 0, lateSelector = 1 };
};

struct AliceActionPolicy {
    enum { firstSelector = 1, firstMode = 1, secondSelector = 1,
           cancelSelector = 1, lateSelector = 1 };
};
struct YuyukoActionPolicy {
    enum { firstSelector = 1, firstMode = 1, secondSelector = 0,
           cancelSelector = 0, lateSelector = 1 };
};
struct YukariActionPolicy {
    enum { firstSelector = 1, firstMode = 1, secondSelector = 1,
           cancelSelector = 1, lateSelector = 0 };
};
struct SuikaActionPolicy {
    enum { firstSelector = 1, firstMode = 1, secondSelector = 1,
           cancelSelector = 1, lateSelector = 1 };
};
struct MeilingActionPolicy {
    enum { firstSelector = 0, firstMode = 2, secondSelector = 1,
           cancelSelector = 0, lateSelector = 1 };
};

}

int ReimuFighter::actionCountdown;
int AliceFighter::actionCountdown;
int YuyukoFighter::actionCountdown;
int YukariFighter::actionCountdown;
int SuikaFighter::actionCountdown;
int MeilingFighter::actionCountdown;

#define AI_FIGHTER ReimuFighter
#define AI_POLICY ReimuActionPolicy
#include "characters/CharacterAIPolicy.inc"
#undef AI_POLICY
#undef AI_FIGHTER

#define AI_FIGHTER AliceFighter
#define AI_POLICY AliceActionPolicy
#include "characters/CharacterAIPolicy.inc"
#undef AI_POLICY
#undef AI_FIGHTER

#define AI_FIGHTER YuyukoFighter
#define AI_POLICY YuyukoActionPolicy
#include "characters/CharacterAIPolicy.inc"
#undef AI_POLICY
#undef AI_FIGHTER

#define AI_FIGHTER YukariFighter
#define AI_POLICY YukariActionPolicy
#include "characters/CharacterAIPolicy.inc"
#undef AI_POLICY
#undef AI_FIGHTER

#define AI_FIGHTER SuikaFighter
#define AI_POLICY SuikaActionPolicy
#include "characters/CharacterAIPolicy.inc"
#undef AI_POLICY
#undef AI_FIGHTER

#define AI_FIGHTER MeilingFighter
#define AI_POLICY MeilingActionPolicy
#include "characters/CharacterAIPolicy.inc"
#undef AI_POLICY
#undef AI_FIGHTER
