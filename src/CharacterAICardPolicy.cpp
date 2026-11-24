#include "CharacterAIPolicy.hpp"
#include "ReimuFighter.hpp"
#include "MeilingFighter.hpp"

#define OPPONENT_GUARD static_cast<Fighter*>(opponent)->IsState50To149()
#define FORWARD_COMMAND (2 - (facing == 1))
#define AIR_FORWARD_COMMAND (2 - (facing == -1))
#define AIR_BACK_COMMAND (1 + (facing == -1))

#define CARD_TYPE field370[field39D]

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AICardSeparation { float x, y; };

int ReimuFighter::cardCountdown;
int MeilingFighter::cardCountdown;

#define AI_FIGHTER ReimuFighter
#include "CharacterAICardPolicy.inc"
#undef AI_FIGHTER

#define AI_FIGHTER MeilingFighter
#include "CharacterAICardPolicy.inc"
#undef AI_FIGHTER
