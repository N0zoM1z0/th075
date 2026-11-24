#include "CharacterAI5349B0.hpp"

int YoumuFighter::cardCountdown;

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(this) + offset))
#define OPPONENT_GUARD static_cast<Fighter*>(opponent)->IsState50To149()
#define FORWARD_COMMAND (2 - (facing == 1))
#define AIR_FORWARD_COMMAND (2 - (facing == -1))
#define AIR_BACK_COMMAND (1 + (facing == -1))

#define CARD_TYPE field370[field39D]

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AISeparation5349B0 { float x, y; };

void YoumuFighter::ChooseCardAction()
{
    AISeparation5349B0 distance;
    distance.x = AbsFloatAt00412D90(opponent->x - x);
    distance.y = AbsFloatAt00412D90(opponent->y - y);
    --aiWaitTimer;
    if (action > 49 &&
        action < 150) {
        if (aiCardTimer < 0) aiCardTimer = ChooseIntegerRange(30, 90);
        aiStep = 0;
        aiWaitTimer = 0;
        if (ChooseIntegerRange(0, 100) < 50) inputX = 1;
        else inputX = -1;
        if (ChooseIntegerRange(0, 100) < 5) inputA = 1;
        return;
    }
    if (CARD_TYPE == 3 && field3A0 > 0 &&
        --aiCardTimer <= 0 && y == 0.0f) {
        aiCommand = 230;
        return;
    }
    if (CARD_TYPE == 2 && field3A0 > 0) {
        --aiCardTimer;
        if (ChooseIntegerRange(0, 100) < 75 && aiCardTimer <= -180 &&
            y == 0.0f && ChooseIntegerRange(0, 100) < 50) {
            aiCommand = 220;
            return;
        }
    }
    if (CARD_TYPE == 1 && field3A0 > 0 &&
        --aiCardTimer <= 0 && y == 0.0f &&
        distance.x < 240.0f && RecordedRange(0, 100) < 30) {
        aiCommand = 210;
    }
    if (CARD_TYPE == 0 && field3A0 > 0) {
        --aiCardTimer;
        if (ChooseIntegerRange(0, 100) < 75 && aiCardTimer <= 0 && y == 0.0f) {
            if (ChooseIntegerRange(0, 100) < 50 && distance.x < 240.0f) {
                aiCommand = 201;
                return;
            }
            if (ChooseIntegerRange(0, 100) < 50) {
                if (ChooseIntegerRange(0, 100) < 50) {
                    aiCommand = 200;
                    return;
                }
                aiCommand = 202;
                return;
            }
            aiCommand = ChooseIntegerRange(0, 3) + 200;
        }
    }
    if (aiStep == 1) {
        if (aiWaitTimer > 0) {
            inputC = 5;
        } else {
            aiStep = 0;
        }
        return;
    }
    if (aiStep == 2) {
        if (action == 391) {
            aiStep = 0;
            return;
        }
        if (action == 200) {
            inputX = facing;
            inputB = 1;
            return;
        }
        if (action != 200) {
            aiCommand = FORWARD_COMMAND;
            return;
        }
    }
    if (aiStep == 3) {
        if (action == 390) {
            aiStep = 0;
            return;
        }
        if (action == 200) {
            inputX = facing;
            inputA = 1;
            return;
        }
        if (action != 200) {
            aiCommand = FORWARD_COMMAND;
            return;
        }
    }
    if (aiStep == 4) {
        if (action == 392) {
            aiStep = 0;
            return;
        }
        if (action == 200) {
            inputX = facing;
            inputA = 1;
            inputY = 1;
            return;
        }
        if (action != 200) {
            aiCommand = FORWARD_COMMAND;
            return;
        }
    }
    if (aiStep == 5) {
        if (action == 393) {
            aiStep = 0;
            return;
        }
        if (action == 200) {
            inputX = facing;
            inputB = 1;
            inputY = 1;
            return;
        }
        if (action != 200) {
            aiCommand = FORWARD_COMMAND;
            return;
        }
    }
    if ((action > 399 && action < 500) ||
        (action > 599 && action < 700)) {
        if (distance.x > 0.0f) {
            if (y == 0.0f) {
                if (rand() < 4000) {
                    aiCommand = 3;
                    return;
                }
                if (rand() < 4000) {
                    aiCommand = 4;
                    return;
                }
                if (rand() < 4000) {
                    aiCommand = 5;
                    return;
                }
            }
            if (y > 0.0f) {
                if (rand() < 4000) {
                    aiCommand = AIR_BACK_COMMAND;
                    return;
                }
                if (rand() < 4000) {
                    aiCommand = AIR_FORWARD_COMMAND;
                    return;
                }
            }
        }
        if (action > 399 &&
            action < 500 &&
            distance.x < 300.0f &&
            rand() < 4000) {
            aiCommand = 20;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 400.0f &&
            distance.x < 500.0f &&
            rand() < 500) {
            aiCommand = 21;
            return;
        }
    }
    if (OPPONENT_GUARD && (opponent->action < 93 || opponent->action > 99)) {
        if (action == 502 &&
            rand() < 10000 &&
            distance.x < 150.0f) {
            aiCommand = 20;
            return;
        }
        if (action == 503 &&
            rand() < 10000) {
            aiCommand = 20;
            return;
        }
        if (action == 307 &&
            rand() < 10000 &&
            spirit > 250) {
            aiCommand = 20;
            return;
        }
        if (action == 307 &&
            rand() < 5000 &&
            distance.x < 120.0f &&
            field07C == 1) {
            aiCommand = 30;
            if (rand() < 18000) aiCommand = 31;
            return;
        }
        if (action == 307 &&
            rand() < 2000) {
            aiCommand = 100;
            return;
        }
        if (distance.x < 80.0f &&
            action == 307 &&
            rand() < 2000) {
            aiCommand = 101;
            return;
        }
        if (action == 300 &&
            rand() < 10000 &&
            distance.x < 120.0f &&
            field07C == 1) {
            aiCommand = 30;
            if (rand() < 18000) aiCommand = 31;
            return;
        }
        if (action == 300 &&
            rand() < 20000 &&
            distance.x < 80.0f) {
            inputA = 1;
            return;
        }
        if (action == 300 &&
            rand() < 2000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (action == 301 &&
            rand() < 15000) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (action == 301 &&
            rand() < 15000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (action == 301 &&
            rand() < 1500) {
            aiCommand = 100;
            return;
        }
        if (distance.x < 150.0f &&
            action == 301 &&
            rand() < 1500) {
            aiCommand = 101;
            return;
        }
        if (action == 301 &&
            rand() < 3000 &&
            spirit > 350) {
            inputC = 1;
            return;
        }
        if (action == 301 &&
            rand() < 8000) {
            aiStep = 2;
            return;
        }
        if (action == 302 &&
            rand() < 5000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (action == 303 &&
            rand() < 1500) {
            aiCommand = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 303 &&
            rand() < 1500) {
            aiCommand = 101;
            return;
        }
        if (action == 303 &&
            rand() < 10000 &&
            distance.x < 80.0f) {
            inputB = 1;
            inputY = 1;
            return;
        }
        if (action == 303 &&
            rand() < 5000 &&
            field07C == 1) {
            aiCommand = 30;
            if (rand() < 18000) aiCommand = 31;
            return;
        }
        if (action == 308 &&
            rand() < 10000 &&
            spirit > 250) {
            aiCommand = 20;
            return;
        }
        if (action == 308 &&
            rand() < 5000 &&
            distance.x < 120.0f &&
            field07C == 1) {
            aiCommand = 30;
            if (rand() < 18000) aiCommand = 31;
            return;
        }
        if (action == 308 &&
            rand() < 2500) {
            aiCommand = 100;
            return;
        }
        if (distance.x < 80.0f &&
            action == 308 &&
            rand() < 2500) {
            aiCommand = 101;
            return;
        }
        if (distance.x < 60.0f &&
            rand() < 10000) {
            inputA = 1;
            return;
        }
    }
    if (static_cast<float>(rand()) < spirit * 0.8f + 0.0f &&
        distance.x > 200.0f &&
        spirit > 350) {
        inputC = 1;
        if (rand() < 2000) inputX = facing;
        if (rand() < 2000) inputY = 1;
        return;
    }
    if (static_cast<float>(rand()) < spirit * 0.5f + 0.0f &&
        distance.x > 560.0f &&
        spirit > 750 &&
        fieldF12 == 0) {
        inputA = 1;
        if (rand() < 4000) inputX = facing;
        if (rand() < 4000) inputY = 1;
        return;
    }
    if (static_cast<float>(rand()) < spirit * 0.5f + 0.0f &&
        distance.x > 560.0f &&
        spirit > 750 &&
        fieldF12 == 0) {
        inputB = 1;
        if (rand() < 15000) inputX = facing;
        return;
    }
    if (rand() < 50) inputY = -1;
    if (y == 0.0f) {
        if (static_cast<float>(rand()) < distance.x / 2.0f + 100.0f) {
            aiCommand = 3;
            return;
        }
        if (static_cast<float>(rand()) < distance.x / 2.0f + 100.0f) {
            aiCommand = 4;
            return;
        }
        if (distance.x > 400.0f &&
            static_cast<float>(rand()) < 100.0f + distance.x) {
            aiCommand = 5;
            return;
        }
    }
    if (y > 0.0f) {
        if (rand() < 1500) {
            aiCommand = AIR_BACK_COMMAND;
            return;
        }
        if (rand() < 100) {
            aiCommand = AIR_FORWARD_COMMAND;
            return;
        }
    }
    if (distance.x > 120.0f &&
        rand() < 200) {
        inputX = facing;
        if (rand() < 18000) inputX = 0;
        inputY = -1;
        return;
    }
    if (distance.x > 150.0f &&
        y > 0.0f &&
        rand() < 500) {
        aiCommand = aiCommand = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x > 300.0f &&
        y == 0.0f &&
        rand() < 2500) {
        aiCommand = aiCommand = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x < 200.0f &&
        rand() < 100) {
        aiCommand = aiCommand = AIR_FORWARD_COMMAND;
        return;
    }
    if (y == 0.0f && (opponent->action < 93 || opponent->action > 99)) {
        if (distance.x < 70.0f &&
            rand() < 4000) {
            inputA = 1;
            return;
        }
        if (distance.x < 120.0f &&
            rand() < 4000) {
            inputB = 1;
            inputY = 0;
            return;
        }
        if (distance.x < 170.0f &&
            rand() < 4000) {
            inputB = 1;
            inputY = 1;
            return;
        }
        if (distance.x < 80.0f &&
            distance.x > 0.0f &&
            opponent->y == 0.0f &&
            rand() < 2000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (distance.x > 100.0f &&
            distance.x < 400.0f &&
            rand() < 100) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (distance.x > 300.0f &&
            distance.x < 400.0f &&
            rand() < 1000) {
            aiStep = 3;
            return;
        }
        if (distance.x > 200.0f &&
            distance.x < 400.0f &&
            rand() < 2000) {
            aiStep = 2;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 200.0f &&
            distance.x < 400.0f &&
            rand() < 1000) {
            aiStep = 4;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 100.0f &&
            distance.x < 300.0f &&
            rand() < 500) {
            aiStep = 5;
            return;
        }
    }
    if (y > 0.0f && (opponent->action < 93 || opponent->action > 99)) {
        if (distance.x < 150.0f) {
            if (rand() < (opponent->y > 0.0f ? 1 : 0) * 4000 + 4000 &&
                distance.y < 200.0f) {
                inputA = 1;
                return;
            }
        }
        if (distance.x < 150.0f &&
            rand() < 6000 &&
            distance.y < 200.0f &&
            distance.y > 100.0f) {
            inputB = 1;
            inputY = 0;
            return;
        }
    }
    if (distance.y < 150.0f && distance.x < 110.0f) {
        if (rand() < (opponent->y > 0.0f ? 1 : 0) * 2500 + 500 &&
            opponent->action != 93 &&
            opponent->action != 94) {
            aiCommand = 30;
            return;
        }
    }
    if (opponent->y == 0.0f &&
        distance.x < 50.0f &&
        rand() < 500 &&
        !OPPONENT_GUARD) {
        aiCommand = 50;
        if (rand() < 18000) aiCommand = 51;
        return;
    }
    if (distance.x > 100.0f &&
        distance.x < 240.0f &&
        rand() < 200) {
        aiCommand = 100;
        return;
    }
    if (distance.x < 100.0f &&
        opponent->y == 0.0f &&
        rand() < 200) {
        aiCommand = 101;
        return;
    }
    if (distance.x > 250.0f &&
        distance.x < 350.0f &&
        rand() < 300) {
        aiCommand = 21;
        return;
    }
    if (distance.x < 200.0f &&
        distance.x > 100.0f &&
        rand() < 300) {
        aiCommand = 20;
        return;
    }
    if (distance.x > 300.0f &&
        static_cast<float>(rand()) < 200.0f + distance.x &&
        spirit > 350) {
        aiCommand = 10;
        return;
    }
    if (distance.x > 300.0f &&
        static_cast<float>(rand()) < distance.x * 0.3f + 100.0f &&
        spirit > 600) {
        aiCommand = 11;
        return;
    }
    if (cardCountdown > 0) {
        inputX = 1;
        --cardCountdown;
    } else if (cardCountdown < 0) {
        inputX = -1;
        ++cardCountdown;
    } else {
        cardCountdown = (rand() % 90 + 10) * (1 - 2 * (rand() % 2));
    }
}
