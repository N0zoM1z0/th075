#include "characters/CharacterAI4C8CD0.hpp"

int SakuyaFighter::cardCountdown;

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(this) + offset))
#define OPPONENT_GUARD static_cast<Fighter*>(opponent)->IsState50To149()
#define FORWARD_COMMAND (2 - (facing == 1))
#define AIR_FORWARD_COMMAND (2 - (facing == -1))
#define AIR_BACK_COMMAND (1 + (facing == -1))

#define CARD_TYPE field370[field39D]

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AISeparation4C8CD0 { float x, y; };

void SakuyaFighter::ChooseCardAction()
{
    AISeparation4C8CD0 distance;
    distance.x = AbsFloatAt00412D90(opponent->x - x);
    distance.y = AbsFloatAt00412D90(opponent->y - y);
    --aiWaitTimer;
    if (action > 49 && action < 150) {
        if (aiCardTimer < 0) aiCardTimer = ChooseIntegerRange(0, 60);
        aiStep = 0;
        aiWaitTimer = 0;
    }
    if (CARD_TYPE == 2 && spellTimer > 0 &&
        --aiCardTimer <= 0 && y == 0.0f) {
        if (ChooseIntegerRange(0, 100) < 50) {
            aiCommand = 221;
            return;
        }
        aiCommand = 220;
        return;
    }
    if (CARD_TYPE == 1 && spellTimer > 0 &&
        --aiCardTimer <= 0 && y == 0.0f) {
        aiCommand = 211;
        return;
    }
    if (CARD_TYPE == 0 && spellTimer > 0 &&
        --aiCardTimer <= 0 && y == 0.0f) {
        if (ChooseIntegerRange(0, 100) < 50) {
            aiCommand = 201;
            return;
        }
        aiCommand = 200;
        return;
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
            spirit > 350 &&
            rand() < 500) {
            aiCommand = 20;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 300.0f &&
            distance.x < 900.0f &&
            spirit > 350 &&
            rand() < 500) {
            aiCommand = 21;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x < 450.0f &&
            rand() < 100) {
            aiCommand = 10;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 300.0f &&
            distance.x < 700.0f &&
            rand() < 100) {
            aiCommand = 11;
            return;
        }
    }
    if (OPPONENT_GUARD && (opponent->action < 93 || opponent->action > 99)) {
        if (distance.x < 60.0f &&
            rand() < 10000) {
            inputA = 1;
            return;
        }
        if (action == 307 &&
            rand() < 10000 &&
            spirit > 250) {
            inputC = 1;
            return;
        }
        if (action == 307 &&
            rand() < 5000 &&
            distance.x < 120.0f) {
            aiCommand = 30;
            return;
        }
        if (action == 300 &&
            rand() < 20000 &&
            distance.x < 80.0f) {
            inputA = 1;
            return;
        }
        if (action == 300 &&
            rand() < 5000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (action == 300 &&
            rand() < 10000) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (action == 301 &&
            rand() < 10000) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (distance.x < 150.0f &&
            action == 301 &&
            rand() < 10000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (action == 301 &&
            rand() < 500) {
            aiCommand = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 301 &&
            rand() < 500) {
            aiCommand = 101;
            return;
        }
        if (action == 301 &&
            rand() < 10000 &&
            spirit > 350) {
            if (rand() < 2000) aiCommand = 10;
            if (rand() < 2000) aiCommand = 11;
            if (rand() < 2000) aiCommand = 20;
            if (rand() < 2000) aiCommand = 21;
            if (rand() < 2000) inputC = 1;
            return;
        }
        if (action == 301 &&
            rand() < 3000) {
            aiStep = 3;
            return;
        }
        if (action == 301 &&
            rand() < 3000) {
            aiStep = 5;
            return;
        }
        if (action == 301 &&
            rand() < 1000) {
            aiCommand = 30;
            return;
        }
        if (distance.x < 120.0f &&
            action == 303 &&
            rand() < 5000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (action == 303 &&
            rand() < 500) {
            aiCommand = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 303 &&
            rand() < 500) {
            aiCommand = 101;
            return;
        }
        if (action == 303 &&
            rand() < 1000) {
            aiCommand = 30;
            return;
        }
        if (action == 303 &&
            rand() < 10000 &&
            spirit > 350) {
            if (rand() < 2000) aiCommand = 10;
            if (rand() < 2000) aiCommand = 11;
            if (rand() < 2000) aiCommand = 20;
            if (rand() < 2000) aiCommand = 21;
            if (rand() < 2000) inputC = 1;
            return;
        }
        if (action == 308 &&
            rand() < 10000 &&
            spirit > 300) {
            aiWaitTimer = ChooseIntegerRange(0, 30);
            aiStep = 1;
            inputC = 1;
            return;
        }
        if (action == 308 &&
            rand() < 1000) {
            aiCommand = 30;
            return;
        }
        if (action == 307 &&
            distance.x < 150.0f &&
            rand() < 500) {
            aiCommand = 30;
            return;
        }
        if (action == 307 &&
            rand() < 10000 &&
            spirit > 350) {
            if (rand() < 2000) aiCommand = 10;
            if (rand() < 2000) aiCommand = 11;
            if (rand() < 2000) aiCommand = 20;
            if (rand() < 2000) aiCommand = 21;
            if (rand() < 2000) inputC = 1;
            return;
        }
        if (action == 307 &&
            rand() < 500) {
            aiCommand = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 307 &&
            rand() < 500) {
            aiCommand = 101;
            return;
        }
    }
    if (static_cast<float>(rand()) < spirit * 0.8f + 0.0f &&
        distance.x > 200.0f &&
        spirit > 350) {
        inputC = 1;
        if (rand() < 4000) inputX = facing;
        if (rand() < 4000) inputY = 1;
        return;
    }
    if (static_cast<float>(rand()) < spirit * 1.0f + 0.0f &&
        distance.x > 560.0f &&
        spirit > 250) {
        inputA = 1;
        if (rand() < 4000) inputX = facing;
        if (rand() < 4000) inputY = 1;
        return;
    }
    if (static_cast<float>(rand()) < spirit * 0.4f + 0.0f &&
        distance.x > 560.0f &&
        spirit > 350) {
        inputB = 1;
        if (rand() < 15000) inputX = facing;
        return;
    }
    if (rand() < 50) inputY = -1;
    if (y == 0.0f) {
        if (rand() < 400) {
            aiCommand = 3;
            return;
        }
        if (rand() < 400) {
            aiCommand = 4;
            return;
        }
        if (distance.x > 400.0f &&
            rand() < 400) {
            aiCommand = 5;
            return;
        }
    }
    if (y > 0.0f) {
        if (rand() < 1300) {
            aiCommand = AIR_BACK_COMMAND;
            return;
        }
        if (rand() < 1300) {
            aiCommand = AIR_FORWARD_COMMAND;
            return;
        }
    }
    if (distance.x > 120.0f &&
        rand() < 150) {
        inputX = facing;
        if (rand() < 18000) inputX = 0;
        inputY = -1;
        return;
    }
    if (distance.x > 150.0f &&
        y > 0.0f &&
        rand() < 200) {
        aiCommand = aiCommand = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x > 300.0f &&
        y == 0.0f &&
        rand() < 150) {
        aiCommand = aiCommand = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x < 150.0f &&
        rand() < 100) {
        aiCommand = aiCommand = AIR_FORWARD_COMMAND;
        return;
    }
    if (y == 0.0f && (opponent->action < 93 || opponent->action > 99)) {
        if (distance.x < 70.0f &&
            rand() < 5000) {
            inputA = 1;
            return;
        }
        if (distance.x < 150.0f &&
            rand() < 2000) {
            inputB = 1;
            inputY = 0;
            return;
        }
        if (distance.x < 170.0f &&
            rand() < 2000) {
            inputB = 1;
            inputY = 1;
            return;
        }
        if (distance.x < 120.0f &&
            distance.x > 60.0f &&
            opponent->y == 0.0f &&
            rand() < 200) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (distance.x > 60.0f &&
            distance.x < 1000.0f &&
            rand() < 400) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (distance.x > 150.0f &&
            distance.x < 250.0f &&
            rand() < 600) {
            aiStep = 3;
            return;
        }
        if (distance.x > 350.0f &&
            distance.x < 500.0f &&
            rand() < 200) {
            aiStep = 2;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 300.0f &&
            distance.x < 400.0f &&
            rand() < 100) {
            aiStep = 4;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 100.0f &&
            distance.x < 500.0f &&
            rand() < 600) {
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
            distance.y > 80.0f) {
            inputB = 1;
            inputY = 0;
            return;
        }
    }
    if (y == 0.0f &&
        distance.y < 150.0f &&
        opponent->y > 0.0f &&
        rand() < 1000 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        aiCommand = 42;
        return;
    }
    if (distance.x > 100.0f &&
        distance.x < 240.0f &&
        rand() < 200) {
        aiCommand = 100;
        return;
    }
    if (distance.x > 100.0f &&
        distance.x < 250.0f &&
        opponent->y == 0.0f &&
        rand() < 200) {
        aiCommand = 101;
        return;
    }
    if (distance.x > 200.0f &&
        rand() < 300 &&
        spirit > 350) {
        aiCommand = 21;
        return;
    }
    if (distance.x < 200.0f &&
        rand() < 300 &&
        spirit > 350) {
        aiCommand = 20;
        return;
    }
    if (distance.x > 200.0f &&
        rand() < 200 &&
        spirit > 350) {
        aiCommand = 10;
        if (rand() > 25000) aiCommand = 11;
        return;
    }
    if (distance.x < 400.0f &&
        rand() < 100 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        aiCommand = 31;
        return;
    }
    if (rand() < 200) {
        aiCommand = 40;
        if (rand() < 12000) aiCommand = 41;
        if (rand() < 12000) aiCommand = 42;
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
