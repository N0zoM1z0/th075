#include "FighterVirtualActionsF159.hpp"
#include "GameLeafHelpers.hpp"


void Fighter::ForwardBaseAction()
{
    if (y <= 0.0f) {
        field3AD = 0;
        field3AE = 0;
    }
    if (y <= 0.0f &&
        action != 6 &&
        action != 7 &&
        action != 8) {
        if (inputY < 0) {
            UpdateFacingFromOpponent();
            if (inputX == 0) {
                if (static_cast<unsigned int>(inputD) > 0) {
                    if (action != 204)
                        ResetPrimaryCounters(204);
                } else if (action != 6) {
                    ResetPrimaryCounters(6);
                }
            } else if (facing * inputX > 0) {
                if (static_cast<unsigned int>(inputD) > 0) {
                    if (action != 205)
                        ResetPrimaryCounters(205);
                } else if (action != 7) {
                    ResetPrimaryCounters(7);
                }
            } else if (facing * inputX < 0) {
                if (static_cast<unsigned int>(inputD) > 0) {
                    if (action != 206)
                        ResetPrimaryCounters(206);
                } else if (action != 8) {
                    ResetPrimaryCounters(8);
                }
            }
        } else {
            if (inputY > 0) {
                if (action != 2 && action != 1) {
                    ResetPrimaryCounters(1);
                } else if (action != 1) {
                    ResetPrimaryCounters(2);
                }
            } else if (inputX != 0) {
                UpdateFacingFromOpponent();
                if (facing * inputX > 0) {
                    if (static_cast<unsigned int>(inputD) > 0) {
                        if (action != 200)
                            ResetPrimaryCounters(200);
                    } else if (action != 4) {
                        ResetPrimaryCounters(4);
                    }
                } else {
                    if (static_cast<unsigned int>(inputD) > 0) {
                        if (action != 201)
                            ResetPrimaryCounters(201);
                    } else if (action != 5) {
                        ResetPrimaryCounters(5);
                    }
                }
            } else {
                if (action == 1 || action == 2) {
                    ResetPrimaryCounters(3);
                } else if (action != 0 &&
                           action != 3 &&
                           action != 10) {
                    ResetPrimaryCounters(0);
                }
            }
            UpdateFacingFromOpponent();
        }
    }
}
