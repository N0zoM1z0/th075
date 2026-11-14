#include "FighterCommandByteF940.hpp"
#include "FighterAIShortFieldsF946.hpp"
#include "CharacterAIPolicy.hpp"

#define OPPONENT_GUARD reinterpret_cast<FighterState *>(opponent)->IsState50To149()
#define FORWARD_COMMAND (2 - (facing == 1))
#define AIR_FORWARD_COMMAND (2 - (facing == -1))
#define AIR_BACK_COMMAND (1 + (facing == -1))

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AISeparation { float x, y; };

template<class Policy> void CharacterAIPolicy<Policy>::ChooseAction()
{
    AISeparation distance;
    distance.x = AbsFloatAt00412D90(opponent->x - x);
    distance.y = AbsFloatAt00412D90(opponent->y - y);
    --F946_AI_FIELDS_AT512(this).countdownAt512;
    if (action > 49 && action < 150) {
        F946_AI_FIELDS_AT512(this).modeAt514 = 0;
        F946_AI_FIELDS_AT512(this).countdownAt512 = 0;
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 1) {
        if (F946_AI_FIELDS_AT512(this).countdownAt512 > 0) {
            inputC = 5;
        } else {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
        }
        return;
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 2) {
        if (action == 391) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
            return;
        }
        if (action == 200) {
            inputX = facing;
            inputB = 1;
            return;
        }
        if (action != 200) {
            F940_COMMAND_AT511(this) = FORWARD_COMMAND;
            return;
        }
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 3) {
        if (action == 390) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
            return;
        }
        if (action == 200) {
            inputX = facing;
            inputA = 1;
            return;
        }
        if (action != 200) {
            F940_COMMAND_AT511(this) = FORWARD_COMMAND;
            return;
        }
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 4) {
        if (action == 392) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
            return;
        }
        if (action == 200) {
            inputX = facing;
            inputA = 1;
            inputY = 1;
            return;
        }
        if (action != 200) {
            F940_COMMAND_AT511(this) = FORWARD_COMMAND;
            return;
        }
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 5) {
        if (action == 393) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
            return;
        }
        if (action == 200) {
            inputX = facing;
            inputB = 1;
            inputY = 1;
            return;
        }
        if (action != 200) {
            F940_COMMAND_AT511(this) = FORWARD_COMMAND;
            return;
        }
    }
    if (F946_AI_FIELDS_AT512(this).modeAt514 == 6) {
        if (F946_AI_FIELDS_AT512(this).countdownAt512 > 0) {
            inputA = 5;
        } else {
            F946_AI_FIELDS_AT512(this).modeAt514 = 0;
        }
        return;
    }
    if (field36C > 300.0f) {
        if (distance.x > 560.0f &&
            rand() < 3 &&
            field39C == 0 &&
            field3A0 <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
        if (opponent->action == 98 &&
            rand() < 20 &&
            field39C == 0 &&
            field3A0 <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
    }
    if (field36C > 100.0f) {
        if (field324 < 4000 &&
            distance.x > 560.0f &&
            rand() < 50 &&
            field39C == 0 &&
            field3A0 <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
        if (field324 < 4000 &&
            rand() < 5 &&
            field39C == 0 &&
            field3A0 <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
        if (OPPONENT_GUARD &&
            field324 < 3000 &&
            field39C == 0 &&
            field3A0 <= 0) {
            F940_COMMAND_AT511(this) = 103;
            return;
        }
    }
    if ((action > 399 && action < 500) ||
        (action > 599 && action < 700)) {
        if (distance.x > 0.0f) {
            if (y == 0.0f) {
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = 3;
                    return;
                }
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = 4;
                    return;
                }
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = 5;
                    return;
                }
            }
            if (y > 0.0f) {
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = AIR_BACK_COMMAND;
                    return;
                }
                if (rand() < 4000) {
                    F940_COMMAND_AT511(this) = AIR_FORWARD_COMMAND;
                    return;
                }
            }
        }
        if (action > 399 &&
            action < 500 &&
            distance.x < 300.0f &&
            meter > 500 &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 600.0f &&
            meter > 500 &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 21;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x < 300.0f &&
            meter > 500 &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 10;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 600.0f &&
            meter > 500 &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 11;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x < 450.0f &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 300.0f &&
            distance.x < 700.0f &&
            rand() < 100) {
            F940_COMMAND_AT511(this) = 21;
            return;
        }
    }
    if (OPPONENT_GUARD && (opponent->action < 93 || opponent->action > 99)) {
        if ((action == 501 || action == 309 || action == 393) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            aiSelectors[Policy::firstSelector] == 1 &&
            field39D == Policy::firstMode) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 308 || action == 307 || action == 390 || action == 392 || action == 393) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            aiSelectors[Policy::secondSelector] == 1 &&
            field39D == 2) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 310 || action == 390 || action == 393) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            aiSelectors[1] == 2 &&
            field39D == 1) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((action == 393 || action == 392 || action == 506 || action == 301 || action == 308 || action == 307) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            aiSelectors[Policy::cancelSelector] == 2 &&
            field39D == 2) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((action == 393 || action == 392 || action == 506 || action == 301 || action == 303) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            aiSelectors[1] == 0 &&
            field39D == 1) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if ((action == 393 || action == 392 || action == 506 || action == 301 || action == 303) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            aiSelectors[Policy::cancelSelector] == 0 &&
            field39D == 2) {
            F940_COMMAND_AT511(this) = 13;
            return;
        }
        if (action == 307 &&
            rand() < 10000 &&
            meter > 250) {
            F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 45);
            F946_AI_FIELDS_AT512(this).modeAt514 = 6;
            inputC = 1;
            return;
        }
        if (action == 307 &&
            rand() < 1000 &&
            meter > 500) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (action == 307 &&
            rand() < 500) {
            F940_COMMAND_AT511(this) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 307 &&
            rand() < 500) {
            F940_COMMAND_AT511(this) = 101;
            return;
        }
        if (action == 307 &&
            rand() < 500) {
            F940_COMMAND_AT511(this) = 40;
            return;
        }
        if (action == 307 &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 41;
            return;
        }
        if (distance.x < 100.0f &&
            action == 307 &&
            rand() < 5000 &&
            meter > 300) {
            F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 30);
            F946_AI_FIELDS_AT512(this).modeAt514 = 1;
            inputC = 1;
            return;
        }
        if (distance.x < 200.0f &&
            (action == 301 || action == 308) &&
            rand() < 20000) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (distance.x < 100.0f &&
            (action == 301 || action == 308) &&
            rand() < 5000 &&
            field07C == 1) {
            F940_COMMAND_AT511(this) = 31;
            return;
        }
        if (action == 300 &&
            rand() < 20000 &&
            distance.x < 80.0f) {
            inputA = 1;
            return;
        }
        if (action == 300 &&
            rand() < 100) {
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
            rand() < 15000) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (action == 303 &&
            rand() < 550) {
            F940_COMMAND_AT511(this) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 303 &&
            rand() < 300) {
            F940_COMMAND_AT511(this) = 101;
            return;
        }
        if (distance.x < 100.0f &&
            action == 301 &&
            rand() < 1000) {
            F940_COMMAND_AT511(this) = 30;
            return;
        }
        if (action == 303 &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 303 &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 101;
            return;
        }
        if (action == 301 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 3;
            return;
        }
        if (action == 301 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 5;
            return;
        }
        if (action == 302 &&
            rand() < 15000) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (action == 302 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 3;
            return;
        }
        if (action == 302 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 5;
            return;
        }
        if (action == 302 &&
            rand() < 1000) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 4;
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
            meter > 300) {
            F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 30);
            F946_AI_FIELDS_AT512(this).modeAt514 = 1;
            inputC = 1;
            return;
        }
        if (action == 308 &&
            rand() < 10000 &&
            meter > 300) {
            F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 30);
            F946_AI_FIELDS_AT512(this).modeAt514 = 1;
            inputC = 1;
            return;
        }
        if (action == 308 &&
            rand() < 10000 &&
            meter > 300) {
            F940_COMMAND_AT511(this) = 10;
            return;
        }
        if (action == 308 &&
            rand() < 200) {
            F940_COMMAND_AT511(this) = 20;
            return;
        }
        if (distance.x < 60.0f &&
            rand() < 10000) {
            inputA = 1;
            return;
        }
    }
    if (static_cast<float>(rand()) < meter * 0.8f + 0.0f &&
        distance.x > 320.0f &&
        meter > 350) {
        F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 45);
        F946_AI_FIELDS_AT512(this).modeAt514 = 1;
        inputC = 1;
        if (rand() < 1000) inputX = facing;
        if (rand() < 1000) inputY = 1;
        return;
    }
    if (static_cast<float>(rand()) < meter * 1.0f + 0.0f &&
        distance.x > 560.0f &&
        meter > 250 &&
        distance.y < 100.0f) {
        F946_AI_FIELDS_AT512(this).modeAt514 = 6;
        F946_AI_FIELDS_AT512(this).countdownAt512 = ChooseIntegerRange(0, 45);
        inputA = 1;
        if (rand() < 2000) inputX = facing;
        if (rand() < 2000) inputY = 1;
        return;
    }
    if (static_cast<float>(rand()) < meter * 0.5f + 0.0f &&
        distance.x > 560.0f &&
        meter > 250) {
        inputB = 1;
        return;
    }
    if (rand() < 50) inputY = -1;
    if (y == 0.0f) {
        if (rand() < 1000) {
            F940_COMMAND_AT511(this) = 3;
            return;
        }
        if (rand() < 1000) {
            F940_COMMAND_AT511(this) = 4;
            return;
        }
        if (distance.x > 400.0f &&
            rand() < 1000) {
            F940_COMMAND_AT511(this) = 5;
            return;
        }
    }
    if (y > 0.0f) {
        if (rand() < 1100) {
            F940_COMMAND_AT511(this) = AIR_BACK_COMMAND;
            return;
        }
        if (rand() < 1100) {
            F940_COMMAND_AT511(this) = AIR_FORWARD_COMMAND;
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
    if (distance.x > 200.0f &&
        y > 0.0f &&
        rand() < 80) {
        F940_COMMAND_AT511(this) = F940_COMMAND_AT511(this) = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x > 350.0f &&
        y == 0.0f &&
        rand() < 50) {
        F940_COMMAND_AT511(this) = F940_COMMAND_AT511(this) = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x < 400.0f &&
        rand() < 100) {
        F940_COMMAND_AT511(this) = F940_COMMAND_AT511(this) = AIR_FORWARD_COMMAND;
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
        if (distance.x < 120.0f &&
            rand() < 2000) {
            inputB = 1;
            inputY = 0;
            return;
        }
        if (distance.x < 140.0f) {
            if (rand() < (distance.x > 0.0f && distance.x < 200.0f ? 1 : 0) * 900 + 100) {
                inputB = 1;
                inputY = 1;
                return;
            }
        }
        if (distance.x < 120.0f &&
            distance.x > 60.0f &&
            opponent->y == 0.0f &&
            rand() < 100) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (distance.x > 60.0f &&
            distance.x < 300.0f &&
            rand() < 400) {
            inputA = 1;
            inputX = facing;
            return;
        }
        if (distance.x > 200.0f &&
            distance.x < 400.0f &&
            rand() < 600) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 3;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 100.0f &&
            distance.x < 500.0f &&
            rand() < 100) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 2;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 200.0f &&
            distance.x < 500.0f &&
            rand() < 600) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 4;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 300.0f &&
            distance.x < 500.0f &&
            rand() < 250) {
            F946_AI_FIELDS_AT512(this).modeAt514 = 5;
            return;
        }
    }
    if (y > 0.0f && (opponent->action < 93 || opponent->action > 99)) {
        if (distance.x < 300.0f &&
            rand() < 6000 &&
            distance.y < 200.0f &&
            distance.y > 0.0f) {
            inputA = 1;
            return;
        }
        if (distance.x < 200.0f &&
            rand() < 4000 &&
            distance.y < 250.0f &&
            distance.y > 80.0f) {
            inputB = 1;
            inputY = 0;
            return;
        }
    }
    if (rand() < 1500 &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[1] == 2 &&
        field39D == 1) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < (opponent->y > 0.0f ? 1 : 0) * 1500 + 1000 &&
        distance.x < 350.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[1] == 1 &&
        field39D == 1) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < 1500 &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[1] == 0 &&
        field39D == 1) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < 500 &&
        distance.x < 300.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[Policy::lateSelector] == 2 &&
        field39D == 2) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < 1500 &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[0] == 0 &&
        field39D == 2) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (rand() < (opponent->y > 0.0f ? 1 : 0) * 1500 + 500 &&
        distance.x < 200.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[0] == 1 &&
        field39D == 2) {
        F940_COMMAND_AT511(this) = 13;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x < 100.0f &&
        rand() < 600 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        F940_COMMAND_AT511(this) = 30;
        return;
    }
    if (distance.x > 100.0f &&
        distance.x < 300.0f &&
        rand() < 200) {
        F940_COMMAND_AT511(this) = 100;
        return;
    }
    if (distance.x > 400.0f &&
        distance.x < 500.0f &&
        opponent->y == 0.0f &&
        rand() < 200) {
        F940_COMMAND_AT511(this) = 101;
        return;
    }
    if (distance.x > 350.0f &&
        rand() < 200 &&
        meter > 350) {
        F940_COMMAND_AT511(this) = 10;
        return;
    }
    if (distance.x > 350.0f &&
        rand() < 200 &&
        meter > 350) {
        F940_COMMAND_AT511(this) = 11;
        return;
    }
    if (rand() < 250 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        F940_COMMAND_AT511(this) = 40;
        return;
    }
    if (rand() < 100 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        F940_COMMAND_AT511(this) = 41;
        return;
    }
    if (distance.y < 250.0f &&
        distance.y > 100.0f &&
        distance.x < 200.0f &&
        rand() < 100 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        F940_COMMAND_AT511(this) = 31;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x > 200.0f &&
        static_cast<float>(rand()) < meter * 0.1f) {
        F940_COMMAND_AT511(this) = 20;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x > 400.0f &&
        static_cast<float>(rand()) < meter * 0.1f) {
        F940_COMMAND_AT511(this) = 21;
        return;
    }
    if (Policy::countdown > 0) {
        inputX = 1;
        --Policy::countdown;
    } else if (Policy::countdown < 0) {
        inputX = -1;
        ++Policy::countdown;
    } else {
        Policy::countdown = (rand() % 90 + 10) * (1 - 2 * (rand() % 2));
    }
}

template void CharacterAIPolicy<AI472890Policy>::ChooseAction();
template void CharacterAIPolicy<AI4E7DE0Policy>::ChooseAction();
template void CharacterAIPolicy<AI579650Policy>::ChooseAction();
template void CharacterAIPolicy<AI59D240Policy>::ChooseAction();
template void CharacterAIPolicy<AI5C5D10Policy>::ChooseAction();
template void CharacterAIPolicy<AI5E7370Policy>::ChooseAction();

