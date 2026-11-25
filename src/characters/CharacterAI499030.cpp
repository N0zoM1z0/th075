#include "characters/CharacterAI499030.hpp"

int MarisaFighter::actionCountdown;

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(this) + offset))
#define OPPONENT_GUARD static_cast<Fighter*>(opponent)->IsState50To149()
#define FORWARD_COMMAND (2 - (facing == 1))
#define AIR_FORWARD_COMMAND (2 - (facing == -1))
#define AIR_BACK_COMMAND (1 + (facing == -1))

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AISeparation499030 { float x, y; };

void MarisaFighter::ChooseAction()
{
    AISeparation499030 distance;
    distance.x = AbsFloatAt00412D90(opponent->x - x);
    distance.y = AbsFloatAt00412D90(opponent->y - y);
    --aiWaitTimer;
    if (action > 49 && action < 150) {
        aiStep = 0;
        aiWaitTimer = 0;
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
    if (spellPower > 300.0f) {
        if (distance.x > 560.0f &&
            rand() < 3 &&
            spellDeclarationExpired == 0 &&
            spellTimer <= 0) {
            aiCommand = 103;
            return;
        }
        if (opponent->action == 98 &&
            rand() < 20 &&
            spellDeclarationExpired == 0 &&
            spellTimer <= 0) {
            aiCommand = 103;
            return;
        }
    }
    if (spellPower > 100.0f) {
        if (health < 4000 &&
            distance.x > 560.0f &&
            rand() < 50 &&
            spellDeclarationExpired == 0 &&
            spellTimer <= 0) {
            aiCommand = 103;
            return;
        }
        if (health < 4000 &&
            rand() < 5 &&
            spellDeclarationExpired == 0 &&
            spellTimer <= 0) {
            aiCommand = 103;
            return;
        }
        if (OPPONENT_GUARD &&
            health < 3000 &&
            spellDeclarationExpired == 0 &&
            spellTimer <= 0) {
            aiCommand = 103;
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
            spirit > 500 &&
            rand() < 100) {
            aiCommand = 50;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 600.0f &&
            distance.x < 900.0f &&
            spirit > 500 &&
            rand() < 100) {
            aiCommand = 51;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x < 450.0f &&
            rand() < 200) {
            aiCommand = 20;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 300.0f &&
            distance.x < 700.0f &&
            rand() < 100) {
            aiCommand = 21;
            return;
        }
    }
    if (OPPONENT_GUARD && (opponent->action < 93 || opponent->action > 99)) {
        if ((action == 500 || action == 501 || action == 309) &&
            rand() < 10000 &&
            spellTimer > 0 &&
            spellPower >= 100.0f &&
            selectedSpellCards[1] == 1 &&
            roundsRemaining == 1) {
            aiCommand = 13;
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 308 || action == 307 || action == 522 || action == 523 || action == 524 || action == 525) &&
            rand() < 10000 &&
            spellTimer > 0 &&
            spellPower >= 100.0f &&
            selectedSpellCards[1] == 1 &&
            roundsRemaining == 2) {
            aiCommand = 13;
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 310 || action == 390 || action == 392) &&
            rand() < 10000 &&
            spellTimer > 0 &&
            spellPower >= 100.0f &&
            selectedSpellCards[1] == 2 &&
            roundsRemaining == 1) {
            if (fieldF14 == 0) {
                aiCommand = 13;
            } else {
                if (rand() < 15000) aiCommand = 13;
                if (rand() < 15000) aiCommand = 23;
            }
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 310 || action == 390 || action == 392) &&
            rand() < 10000 &&
            spellTimer > 0 &&
            spellPower >= 100.0f &&
            selectedSpellCards[1] == 2 &&
            roundsRemaining == 2) {
            if (fieldF14 == 0) {
                aiCommand = 13;
            } else {
                if (rand() < 15000) aiCommand = 13;
                if (rand() < 15000) aiCommand = 23;
            }
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 308) &&
            rand() < 10000 &&
            spellTimer > 0 &&
            spellPower >= 100.0f &&
            selectedSpellCards[1] == 0 &&
            roundsRemaining == 1) {
            aiCommand = 13;
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 308) &&
            rand() < 10000 &&
            spellTimer > 0 &&
            spellPower >= 100.0f &&
            selectedSpellCards[1] == 0 &&
            roundsRemaining == 2) {
            aiCommand = 13;
            return;
        }
        if (distance.x < 60.0f &&
            rand() < 10000) {
            inputA = 1;
            return;
        }
        if (action == 307 &&
            rand() < 10000 &&
            spirit > 250) {
            aiWaitTimer = ChooseIntegerRange(0, 45);
            aiStep = 1;
            inputC = 1;
            return;
        }
        if (action == 307 &&
            rand() < 10000) {
            aiCommand = 20;
            return;
        }
        if (distance.x < 200.0f &&
            (action == 301 || action == 308) &&
            rand() < 20000) {
            aiCommand = 20;
            return;
        }
        if (distance.x < 100.0f &&
            (action == 301 || action == 308) &&
            rand() < 5000 &&
            collisionResult == 1) {
            aiCommand = 31;
            return;
        }
        if (action == 300 &&
            rand() < 20000 &&
            distance.x < 80.0f) {
            inputA = 1;
            return;
        }
        if (action == 300 &&
            rand() < 20000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (action == 300 &&
            rand() < 1000) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (action == 301 &&
            rand() < 1000) {
            inputA = 1;
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
        if (distance.x < 150.0f &&
            action == 301 &&
            rand() < 10000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (action == 301 &&
            rand() < 3000) {
            aiStep = 2;
            return;
        }
        if (distance.x < 100.0f &&
            action == 303 &&
            rand() < 15000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (distance.x < 100.0f &&
            action == 303 &&
            rand() < 5000 &&
            spirit > 300) {
            aiWaitTimer = ChooseIntegerRange(0, 30);
            aiStep = 1;
            inputC = 1;
            return;
        }
        if (action == 303 &&
            rand() < 500) {
            aiCommand = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 303 &&
            rand() < 300) {
            aiCommand = 101;
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
            rand() < 600) {
            aiCommand = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 308 &&
            rand() < 600) {
            aiCommand = 101;
            return;
        }
        if (action == 308 &&
            rand() < 10000 &&
            spirit > 300) {
            aiCommand = 50;
            return;
        }
        if (action == 308 &&
            rand() < 500) {
            aiCommand = 20;
            return;
        }
    }
    if (static_cast<float>(rand()) < spirit * 0.8f + 0.0f &&
        distance.x > 320.0f &&
        spirit > 350) {
        aiWaitTimer = ChooseIntegerRange(0, 45);
        aiStep = 1;
        inputC = 1;
        if (rand() < 16000) inputX = facing;
        if (rand() < 16000) inputY = 1;
        return;
    }
    if (static_cast<float>(rand()) < spirit * 0.5f + 0.0f &&
        distance.x > 560.0f &&
        spirit > 250 &&
        distance.y < 100.0f) {
        inputA = 1;
        return;
    }
    if (static_cast<float>(rand()) < spirit * 0.1f + 0.0f &&
        distance.x > 560.0f &&
        spirit > 250) {
        inputB = 1;
        if (rand() < 10000) inputX = facing;
        return;
    }
    if (rand() < 50) inputY = -1;
    if (y == 0.0f) {
        if (rand() < 500) {
            aiCommand = 3;
            return;
        }
        if (rand() < 500) {
            aiCommand = 4;
            return;
        }
        if (distance.x > 400.0f &&
            rand() < 500) {
            aiCommand = 5;
            return;
        }
    }
    if (y > 0.0f) {
        if (rand() < 1000) {
            aiCommand = AIR_BACK_COMMAND;
            return;
        }
        if (rand() < 1000) {
            aiCommand = AIR_FORWARD_COMMAND;
            return;
        }
    }
    if (distance.x > 120.0f &&
        rand() < 100) {
        inputX = facing;
        if (rand() < 18000) inputX = 0;
        inputY = -1;
        return;
    }
    if (distance.x > 120.0f &&
        y > 0.0f &&
        rand() < 300) {
        aiCommand = aiCommand = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x > 350.0f &&
        y == 0.0f &&
        rand() < 100) {
        aiCommand = aiCommand = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x < 100.0f &&
        rand() < 10) {
        aiCommand = aiCommand = AIR_FORWARD_COMMAND;
        return;
    }
    if (y == 0.0f && (opponent->action < 93 || opponent->action > 99)) {
        if (distance.x < 80.0f &&
            rand() < 5000) {
            inputA = 1;
            inputY = rand() > 20000;
            if (opponent->y > 0.0f) inputY = 0;
            return;
        }
        if (distance.x < 80.0f &&
            rand() < 2000) {
            inputB = 1;
            inputY = 0;
            return;
        }
        if (distance.x < 140.0f &&
            rand() < 2000) {
            inputB = 1;
            inputY = rand() > 20000;
            if (opponent->y > 0.0f) inputY = 0;
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
            distance.x < 240.0f &&
            rand() < 400) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (distance.x > 200.0f &&
            distance.x < 400.0f &&
            rand() < 400) {
            aiStep = 3;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 200.0f &&
            distance.x < 400.0f &&
            rand() < 400) {
            aiStep = 4;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 300.0f &&
            distance.x < 500.0f &&
            rand() < 100) {
            aiStep = 5;
            return;
        }
    }
    if (y > 0.0f && (opponent->action < 93 || opponent->action > 99)) {
        if (distance.x < 150.0f &&
            rand() < 2000 &&
            distance.y < 300.0f &&
            distance.y > 100.0f &&
            y > opponent->y) {
            inputA = 1;
            return;
        }
        if (distance.x < 200.0f &&
            rand() < 6000 &&
            distance.y < 250.0f &&
            distance.y > 80.0f) {
            inputB = 1;
            inputY = 0;
            return;
        }
    }
    if (rand() < 3000 &&
        distance.x > 200.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 2 &&
        roundsRemaining == 1 &&
        fieldF14 == 0) {
        aiCommand = 13;
        return;
    }
    if (rand() < 1000 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 2 &&
        roundsRemaining == 1) {
        aiCommand = 13;
        return;
    }
    if (rand() < 1000 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 2 &&
        roundsRemaining == 1) {
        aiCommand = 23;
        return;
    }
    if (rand() < 1000 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 1 &&
        roundsRemaining == 1) {
        aiCommand = 13;
        return;
    }
    if (rand() < (opponent->action > 299) * 500 + 50 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 0 &&
        roundsRemaining == 1) {
        aiCommand = 13;
        return;
    }
    if (rand() < 2000 &&
        distance.x > 200.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[0] == 2 &&
        roundsRemaining == 2 &&
        fieldF14 == 0) {
        aiCommand = 13;
        return;
    }
    if (rand() < 2000 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 2 &&
        roundsRemaining == 2) {
        aiCommand = 13;
        return;
    }
    if (rand() < 2000 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 2 &&
        roundsRemaining == 2) {
        aiCommand = 23;
        return;
    }
    if (rand() < (opponent->action > 299) * 500 + 50 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[0] == 0 &&
        roundsRemaining == 2) {
        aiCommand = 13;
        return;
    }
    if (rand() < 500 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[0] == 1 &&
        roundsRemaining == 2 &&
        distance.y < 100.0f) {
        aiCommand = 13;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x < 110.0f &&
        rand() < 600 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        aiCommand = 30;
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
    if (distance.x > 560.0f &&
        rand() < 200 &&
        spirit > 350) {
        aiCommand = 51;
        return;
    }
    if (distance.y < 250.0f &&
        distance.y > 100.0f &&
        distance.x < 200.0f &&
        rand() < 100 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        aiCommand = 31;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x > 200.0f &&
        rand() < 1000) {
        aiCommand = 20;
        return;
    }
    if (actionCountdown > 0) {
        inputX = 1;
        --actionCountdown;
    } else if (actionCountdown < 0) {
        inputX = -1;
        ++actionCountdown;
    } else {
        actionCountdown = (rand() % 90 + 10) * (1 - 2 * (rand() % 2));
    }
}
