void AI_FIGHTER::ChooseAction()
{
    AISeparation distance;
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
    if (aiStep == 6) {
        if (aiWaitTimer > 0) {
            inputA = 5;
        } else {
            aiStep = 0;
        }
        return;
    }
    if (field36C > 300.0f) {
        if (distance.x > 560.0f &&
            rand() < 3 &&
            field39C == 0 &&
            field3A0 <= 0) {
            aiCommand = 103;
            return;
        }
        if (opponent->action == 98 &&
            rand() < 20 &&
            field39C == 0 &&
            field3A0 <= 0) {
            aiCommand = 103;
            return;
        }
    }
    if (field36C > 100.0f) {
        if (health < 4000 &&
            distance.x > 560.0f &&
            rand() < 50 &&
            field39C == 0 &&
            field3A0 <= 0) {
            aiCommand = 103;
            return;
        }
        if (health < 4000 &&
            rand() < 5 &&
            field39C == 0 &&
            field3A0 <= 0) {
            aiCommand = 103;
            return;
        }
        if (OPPONENT_GUARD &&
            health < 3000 &&
            field39C == 0 &&
            field3A0 <= 0) {
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
            aiCommand = 20;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 600.0f &&
            spirit > 500 &&
            rand() < 100) {
            aiCommand = 21;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x < 300.0f &&
            spirit > 500 &&
            rand() < 100) {
            aiCommand = 10;
            return;
        }
        if (action > 399 &&
            action < 500 &&
            distance.x > 600.0f &&
            spirit > 500 &&
            rand() < 100) {
            aiCommand = 11;
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
        if ((action == 501 || action == 309 || action == 393) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            field398[AI_POLICY::firstSelector] == 1 &&
            field39D == AI_POLICY::firstMode) {
            aiCommand = 13;
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 308 || action == 307 || action == 390 || action == 392 || action == 393) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            field398[AI_POLICY::secondSelector] == 1 &&
            field39D == 2) {
            aiCommand = 13;
            return;
        }
        if ((action == 500 || action == 501 || action == 309 || action == 310 || action == 390 || action == 393) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            field398[1] == 2 &&
            field39D == 1) {
            aiCommand = 13;
            return;
        }
        if ((action == 393 || action == 392 || action == 506 || action == 301 || action == 308 || action == 307) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            field398[AI_POLICY::cancelSelector] == 2 &&
            field39D == 2) {
            aiCommand = 13;
            return;
        }
        if ((action == 393 || action == 392 || action == 506 || action == 301 || action == 303) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            field398[1] == 0 &&
            field39D == 1) {
            aiCommand = 13;
            return;
        }
        if ((action == 393 || action == 392 || action == 506 || action == 301 || action == 303) &&
            rand() < 10000 &&
            field3A0 > 0 &&
            field36C >= 100.0f &&
            field398[AI_POLICY::cancelSelector] == 0 &&
            field39D == 2) {
            aiCommand = 13;
            return;
        }
        if (action == 307 &&
            rand() < 10000 &&
            spirit > 250) {
            aiWaitTimer = this->ChooseIntegerRange(0, 45);
            aiStep = 6;
            inputC = 1;
            return;
        }
        if (action == 307 &&
            rand() < 1000 &&
            spirit > 500) {
            aiCommand = 20;
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
        if (action == 307 &&
            rand() < 500) {
            aiCommand = 40;
            return;
        }
        if (action == 307 &&
            rand() < 200) {
            aiCommand = 41;
            return;
        }
        if (distance.x < 100.0f &&
            action == 307 &&
            rand() < 5000 &&
            spirit > 300) {
            aiWaitTimer = this->ChooseIntegerRange(0, 30);
            aiStep = 1;
            inputC = 1;
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
            field07C == 1) {
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
            aiCommand = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 303 &&
            rand() < 300) {
            aiCommand = 101;
            return;
        }
        if (distance.x < 100.0f &&
            action == 301 &&
            rand() < 1000) {
            aiCommand = 30;
            return;
        }
        if (action == 303 &&
            rand() < 200) {
            aiCommand = 100;
            return;
        }
        if (distance.x > 150.0f &&
            action == 303 &&
            rand() < 200) {
            aiCommand = 101;
            return;
        }
        if (action == 301 &&
            rand() < 1000) {
            aiStep = 3;
            return;
        }
        if (action == 301 &&
            rand() < 1000) {
            aiStep = 5;
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
            aiStep = 3;
            return;
        }
        if (action == 302 &&
            rand() < 1000) {
            aiStep = 5;
            return;
        }
        if (action == 302 &&
            rand() < 1000) {
            aiStep = 4;
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
            aiWaitTimer = this->ChooseIntegerRange(0, 30);
            aiStep = 1;
            inputC = 1;
            return;
        }
        if (action == 308 &&
            rand() < 10000 &&
            spirit > 300) {
            aiWaitTimer = this->ChooseIntegerRange(0, 30);
            aiStep = 1;
            inputC = 1;
            return;
        }
        if (action == 308 &&
            rand() < 10000 &&
            spirit > 300) {
            aiCommand = 10;
            return;
        }
        if (action == 308 &&
            rand() < 200) {
            aiCommand = 20;
            return;
        }
        if (distance.x < 60.0f &&
            rand() < 10000) {
            inputA = 1;
            return;
        }
    }
    if (rand() < spirit * 0.8f + 0.0f &&
        distance.x > 320.0f &&
        spirit > 350) {
        aiWaitTimer = this->ChooseIntegerRange(0, 45);
        aiStep = 1;
        inputC = 1;
        if (rand() < 1000) inputX = facing;
        if (rand() < 1000) inputY = 1;
        return;
    }
    if (rand() < spirit * 1.0f + 0.0f &&
        distance.x > 560.0f &&
        spirit > 250 &&
        distance.y < 100.0f) {
        aiStep = 6;
        aiWaitTimer = this->ChooseIntegerRange(0, 45);
        inputA = 1;
        if (rand() < 2000) inputX = facing;
        if (rand() < 2000) inputY = 1;
        return;
    }
    if (rand() < spirit * 0.5f + 0.0f &&
        distance.x > 560.0f &&
        spirit > 250) {
        inputB = 1;
        return;
    }
    if (rand() < 50) inputY = -1;
    if (y == 0.0f) {
        if (rand() < 1000) {
            aiCommand = 3;
            return;
        }
        if (rand() < 1000) {
            aiCommand = 4;
            return;
        }
        if (distance.x > 400.0f &&
            rand() < 1000) {
            aiCommand = 5;
            return;
        }
    }
    if (y > 0.0f) {
        if (rand() < 1100) {
            aiCommand = AIR_BACK_COMMAND;
            return;
        }
        if (rand() < 1100) {
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
    if (distance.x > 200.0f &&
        y > 0.0f &&
        rand() < 80) {
        aiCommand = aiCommand = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x > 350.0f &&
        y == 0.0f &&
        rand() < 50) {
        aiCommand = aiCommand = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x < 400.0f &&
        rand() < 100) {
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
            aiStep = 3;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 100.0f &&
            distance.x < 500.0f &&
            rand() < 100) {
            aiStep = 2;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 200.0f &&
            distance.x < 500.0f &&
            rand() < 600) {
            aiStep = 4;
            return;
        }
        if (opponent->y == 0.0f &&
            distance.x > 300.0f &&
            distance.x < 500.0f &&
            rand() < 250) {
            aiStep = 5;
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
        field398[1] == 2 &&
        field39D == 1) {
        aiCommand = 13;
        return;
    }
    if (rand() < (opponent->y > 0.0f ? 1 : 0) * 1500 + 1000 &&
        distance.x < 350.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        field398[1] == 1 &&
        field39D == 1) {
        aiCommand = 13;
        return;
    }
    if (rand() < 1500 &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        field398[1] == 0 &&
        field39D == 1) {
        aiCommand = 13;
        return;
    }
    if (rand() < 500 &&
        distance.x < 300.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        field398[AI_POLICY::lateSelector] == 2 &&
        field39D == 2) {
        aiCommand = 13;
        return;
    }
    if (rand() < 1500 &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        field398[0] == 0 &&
        field39D == 2) {
        aiCommand = 13;
        return;
    }
    if (rand() < (opponent->y > 0.0f ? 1 : 0) * 1500 + 500 &&
        distance.x < 200.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        field398[0] == 1 &&
        field39D == 2) {
        aiCommand = 13;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x < 100.0f &&
        rand() < 600 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        aiCommand = 30;
        return;
    }
    if (distance.x > 100.0f &&
        distance.x < 300.0f &&
        rand() < 200) {
        aiCommand = 100;
        return;
    }
    if (distance.x > 400.0f &&
        distance.x < 500.0f &&
        opponent->y == 0.0f &&
        rand() < 200) {
        aiCommand = 101;
        return;
    }
    if (distance.x > 350.0f &&
        rand() < 200 &&
        spirit > 350) {
        aiCommand = 10;
        return;
    }
    if (distance.x > 350.0f &&
        rand() < 200 &&
        spirit > 350) {
        aiCommand = 11;
        return;
    }
    if (rand() < 250 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        aiCommand = 40;
        return;
    }
    if (rand() < 100 &&
        opponent->action != 93 &&
        opponent->action != 94) {
        aiCommand = 41;
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
        rand() < spirit * 0.1f) {
        aiCommand = 20;
        return;
    }
    if (distance.y < 150.0f &&
        distance.x > 400.0f &&
        rand() < spirit * 0.1f) {
        aiCommand = 21;
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
