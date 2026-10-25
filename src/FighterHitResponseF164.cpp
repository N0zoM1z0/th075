#include "FighterHitResponseF164.hpp"
#include "BattleCombat.hpp"
#include <cstdlib>

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT_X *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + 0x44)
#define FRAME_FLAGS (*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xAC)) + 0x3C))

bool FighterHitResponseF164::IsState150To199() {
    return FIELD(short, 0x60) >= 150 && FIELD(short, 0x60) < 200;
}

bool FighterHitResponseF164::IsState95To99() {
    return FIELD(short, 0x60) >= 95 && FIELD(short, 0x60) <= 99;
}

unsigned char FighterHitResponseF164::SelectHitResponse(unsigned int flags) {
    if (!(FRAME_FLAGS & 0x10)) return 0;
    if (flags & 0x10) return 0;
    if (FIELD(short, 0x3BC) > 0) return 0;
    if (FIELD(signed char, 0x2CD) != 0) {
        if (g_CombatMode == 5) {
            switch (FIELD(signed char, 0x52F)) {
            case 0:
                return 0;
            case 1:
                if (OPPONENT_X - FLOAT(0x44) > 0.0f) FIELD(int, 0x4DC) = -1;
                else FIELD(int, 0x4DC) = 1;
                FIELD(int, 0x4E0) = 0;
                break;
            case 2:
                if (OPPONENT_X - FLOAT(0x44) > 0.0f) FIELD(int, 0x4DC) = -1;
                else FIELD(int, 0x4DC) = 1;
                FIELD(int, 0x4E0) = 1;
                break;
            case 3:
                if (OPPONENT_X - FLOAT(0x44) > 0.0f) FIELD(int, 0x4DC) = -1;
                else FIELD(int, 0x4DC) = 1;
                if (!(flags & 2)) FIELD(int, 0x4E0) = 1;
                else FIELD(int, 0x4E0) = 0;
                break;
            }
        } else {
            unsigned char choice = 0;
            if (g_InputReplayModeAt0066C238 == 2) {
                choice = g_ReplayChoicesAt006718CC.front();
                g_ReplayChoicesAt006718CC.pop_front();
            } else {
                if (g_StateRepeatLevelAt006714D0 == 1) choice = std::rand() % 10 + 9;
                else if (g_StateRepeatLevelAt006714D0 == 0) choice = std::rand() % 10 + 5;
                else choice = 16;
                if (g_InputReplayModeAt0066C238 == 1) g_ReplayChoicesAt006718CC.push_back(choice);
            }
            if (choice < 10) return 0;
            if (OPPONENT_X - FLOAT(0x44) > 0.0f) FIELD(int, 0x4DC) = -1;
            else FIELD(int, 0x4DC) = 1;
            if (!(flags & 2)) FIELD(int, 0x4E0) = 1;
            else FIELD(int, 0x4E0) = 0;
        }
    }
    if (IsState150To199()) goto classifyResponse;
    if (FIELD(unsigned char, 0x465) == 0) {
        if ((OPPONENT_X - FLOAT(0x44)) * FIELD(int, 0x4DC) > 0.0f || FIELD(int, 0x4DC) == 0) return 0;
    }
classifyResponse:
    if (FLOAT(0x48) > 0.0f || (FRAME_FLAGS & 4)) {
        if ((flags & 8) && FIELD(short, 0x3B0) > 0) return 31;
    } else {
        if (FIELD(int, 0x4E0) > 0) {
            if (FIELD(short, 0x3B0) > 0) {
                if (flags & 4) return 21;
                return 22;
            } else {
                if (flags & 4) return 23;
                if (flags & 0x200000) return 41;
                return 0;
            }
        } else {
            if (FIELD(short, 0x3B0) > 0) {
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

#undef FRAME_FLAGS
#undef OPPONENT_X
#undef FLOAT
#undef FIELD
