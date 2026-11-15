#include "FighterVirtualActionsF159.hpp"
#include "GameLeafHelpers.hpp"
#include "BattleCombat.hpp"

#define RESET(state) reinterpret_cast<AnimationState*>(this)->ResetPrimaryCounters(state)
#define UPDATE_FACING() reinterpret_cast<CombatActor*>(this)->UpdateFacingFromOpponent()

void Fighter::ForwardBaseAction()
{
    if (y <= 0.0f) {
        reinterpret_cast<unsigned char&>(field3AD) = 0;
        field3AE = 0;
    }
    if (y <= 0.0f &&
        action != 6 &&
        action != 7 &&
        action != 8) {
        if (inputY < 0) {
            UPDATE_FACING();
            if (inputX == 0) {
                if (reinterpret_cast<unsigned int&>(inputD) > 0) {
                    if (action != 204)
                        RESET(204);
                } else if (action != 6) {
                    RESET(6);
                }
            } else if (facing * inputX > 0) {
                if (reinterpret_cast<unsigned int&>(inputD) > 0) {
                    if (action != 205)
                        RESET(205);
                } else if (action != 7) {
                    RESET(7);
                }
            } else if (facing * inputX < 0) {
                if (reinterpret_cast<unsigned int&>(inputD) > 0) {
                    if (action != 206)
                        RESET(206);
                } else if (action != 8) {
                    RESET(8);
                }
            }
        } else {
            if (inputY > 0) {
                if (action != 2 && action != 1) {
                    RESET(1);
                } else if (action != 1) {
                    RESET(2);
                }
            } else if (inputX != 0) {
                UPDATE_FACING();
                if (facing * inputX > 0) {
                    if (reinterpret_cast<unsigned int&>(inputD) > 0) {
                        if (action != 200)
                            RESET(200);
                    } else if (action != 4) {
                        RESET(4);
                    }
                } else {
                    if (reinterpret_cast<unsigned int&>(inputD) > 0) {
                        if (action != 201)
                            RESET(201);
                    } else if (action != 5) {
                        RESET(5);
                    }
                }
            } else {
                if (action == 1 || action == 2) {
                    RESET(3);
                } else if (action != 0 &&
                           action != 3 &&
                           action != 10) {
                    RESET(0);
                }
            }
            UPDATE_FACING();
        }
    }
}

#undef UPDATE_FACING
#undef RESET
