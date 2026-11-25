#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "replay/ReplayRecords.hpp"
#include "engine/GameSharedState.hpp"
#include "battle/FighterHitResponseF164.hpp"
#include <cstdlib>

#define OPPONENT_X opponent->x

bool Fighter::IsState150To199() {
    return action >= 150 && action < 200;
}

bool Fighter::IsState95To99() {
    return action >= 95 && action <= 99;
}

unsigned char Fighter::SelectHitResponse(unsigned int flags) {
    if (!(savedFrameInfo->flags & 0x10)) return 0;
    if (flags & 0x10) return 0;
    if (field3BC > 0) return 0;
    if (field2CD != 0) {
        if (g_CombatMode == CombatMode::Practice) {
            switch (field52F) {
            case 0:
                return 0;
            case 1:
                if (OPPONENT_X - x > 0.0f) inputX = -1;
                else inputX = 1;
                inputY = 0;
                break;
            case 2:
                if (OPPONENT_X - x > 0.0f) inputX = -1;
                else inputX = 1;
                inputY = 1;
                break;
            case 3:
                if (OPPONENT_X - x > 0.0f) inputX = -1;
                else inputX = 1;
                if (!(flags & 2)) inputY = 1;
                else inputY = 0;
                break;
            }
        } else {
            unsigned char choice = 0;
            if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
                choice = g_ReplayRecords.aiCommandsAndGuardChoices.front();
                g_ReplayRecords.aiCommandsAndGuardChoices.pop_front();
            } else {
                if (g_OptionsModeAt006714D0 == 1) choice = std::rand() % 10 + 9;
                else if (g_OptionsModeAt006714D0 == 0) choice = std::rand() % 10 + 5;
                else choice = 16;
                if (g_ReplayModeAt0066C238 == ReplayMode::Recording) g_ReplayRecords.aiCommandsAndGuardChoices.push_back(choice);
            }
            if (choice < 10) return 0;
            if (OPPONENT_X - x > 0.0f) inputX = -1;
            else inputX = 1;
            if (!(flags & 2)) inputY = 1;
            else inputY = 0;
        }
    }
    if (IsState150To199()) goto classifyResponse;
    if (field465 == 0) {
        if ((OPPONENT_X - x) * inputX > 0.0f || inputX == 0) return 0;
    }
classifyResponse:
    if (y > 0.0f || (savedFrameInfo->flags & 4)) {
        if ((flags & 8) && spirit > 0) return 31;
    } else {
        if (inputY > 0) {
            if (spirit > 0) {
                if (flags & 4) return 21;
                return 22;
            } else {
                if (flags & 4) return 23;
                if (flags & 0x200000) return 41;
                return 0;
            }
        } else {
            if (spirit > 0) {
                if (flags & 2) return 11;
                return 12;
            } else {
                if (flags & 2) return 13;
                if (flags & 0x200000) return 41;
                return 0;
            }
        }
    }
    return 0;
}

#undef OPPONENT_X
