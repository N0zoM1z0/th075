#include "FighterVirtualActionsF159.hpp"
#include "GameLeafHelpers.hpp"
#include "BattleCombat.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define RESET(state) reinterpret_cast<AnimationState*>(this)->ResetPrimaryCounters(state)
#define UPDATE_FACING() reinterpret_cast<CombatActor*>(this)->UpdateFacingFromOpponent()

void FighterBaseActionsF159::SelectMovementAnimation()
{
    if (FIELD(float, 0x48) <= 0.0f) {
        FIELD(unsigned char, 0x3AD) = 0;
        FIELD(unsigned char, 0x3AE) = 0;
    }
    if (FIELD(float, 0x48) <= 0.0f &&
        FIELD(short, 0x60) != 6 &&
        FIELD(short, 0x60) != 7 &&
        FIELD(short, 0x60) != 8) {
        if (FIELD(int, 0x4E0) < 0) {
            UPDATE_FACING();
            if (FIELD(int, 0x4DC) == 0) {
                if (FIELD(unsigned int, 0x4F4) > 0) {
                    if (FIELD(short, 0x60) != 204)
                        RESET(204);
                } else if (FIELD(short, 0x60) != 6) {
                    RESET(6);
                }
            } else if (FIELD(signed char, 0x66) * FIELD(int, 0x4DC) > 0) {
                if (FIELD(unsigned int, 0x4F4) > 0) {
                    if (FIELD(short, 0x60) != 205)
                        RESET(205);
                } else if (FIELD(short, 0x60) != 7) {
                    RESET(7);
                }
            } else if (FIELD(signed char, 0x66) * FIELD(int, 0x4DC) < 0) {
                if (FIELD(unsigned int, 0x4F4) > 0) {
                    if (FIELD(short, 0x60) != 206)
                        RESET(206);
                } else if (FIELD(short, 0x60) != 8) {
                    RESET(8);
                }
            }
        } else {
            if (FIELD(int, 0x4E0) > 0) {
                if (FIELD(short, 0x60) != 2 && FIELD(short, 0x60) != 1) {
                    RESET(1);
                } else if (FIELD(short, 0x60) != 1) {
                    RESET(2);
                }
            } else if (FIELD(int, 0x4DC) != 0) {
                UPDATE_FACING();
                if (FIELD(signed char, 0x66) * FIELD(int, 0x4DC) > 0) {
                    if (FIELD(unsigned int, 0x4F4) > 0) {
                        if (FIELD(short, 0x60) != 200)
                            RESET(200);
                    } else if (FIELD(short, 0x60) != 4) {
                        RESET(4);
                    }
                } else {
                    if (FIELD(unsigned int, 0x4F4) > 0) {
                        if (FIELD(short, 0x60) != 201)
                            RESET(201);
                    } else if (FIELD(short, 0x60) != 5) {
                        RESET(5);
                    }
                }
            } else {
                if (FIELD(short, 0x60) == 1 || FIELD(short, 0x60) == 2) {
                    RESET(3);
                } else if (FIELD(short, 0x60) != 0 &&
                           FIELD(short, 0x60) != 3 &&
                           FIELD(short, 0x60) != 10) {
                    RESET(0);
                }
            }
            UPDATE_FACING();
        }
    }
}

#undef UPDATE_FACING
#undef RESET
#undef FIELD
