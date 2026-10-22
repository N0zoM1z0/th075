#include "BattleStateMachine.hpp"
#define FIELD(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define SELF(type, offset) FIELD(type, this, offset)
#define PLAYER(i) (reinterpret_cast<FrameActor **>(reinterpret_cast<unsigned char *>(this) + 0x44)[i])
#define ACTOR(type, i, offset) FIELD(type, PLAYER(i), offset)
#define STATE SELF(signed char, 0x18)
#define TIMER SELF(unsigned long, 0x0C)
#define NOTICE reinterpret_cast<StateFramePolicies *>(this)
#define WINNER SELF(signed char, 0x5D)
#define LINE SELF(signed char, 0x5E)
#define STATE_TEXT (reinterpret_cast<const char *>(PLAYER(WINNER)) + 0x53B + LINE * 200)
#define MAX_HEALTH (reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(PLAYER(1)) + 0x33E)[ACTOR(signed char, 1, 0x39D)])
short BattleFrame::AdvanceState()
{
    int i, j, k, resetPlayer;
    if (ACTOR(unsigned long, 0, 0x2D0) > g_MaxCombatScore) g_MaxCombatScore = ACTOR(unsigned long, 0, 0x2D0);
    switch (STATE) {
    case 0:
        if (SELF(float, 0x8C) < 0.0f) SELF(float, 0x8C) += 5.0f;
        if (TIMER == 150) {
            if (g_CombatMode != 3) StateAudio::TransitionFade();
            NOTICE->SetNotice(0);
        }
        if (TIMER == 20) STATE = 1;
        break;
    case 2:
        if (TIMER == 300) NOTICE->SetNotice(1);
        if (TIMER == 10) { STATE = 4; TIMER = 160; }
        break;
    case 3:
        if (TIMER == 180) NOTICE->SetNotice(1);
        if (TIMER == 10) {
            ACTOR(short, 0, 0x3A0) = 0; ACTOR(short, 1, 0x3A0) = 0;
            ACTOR(unsigned char, 0, 0x39C) = 0; ACTOR(unsigned char, 1, 0x39C) = 0;
            if (g_FrameClockMode == 2) {
                if (g_NoticeSelection == g_StateReplayLimit || g_CombatMode == 1 || g_CombatMode == 2) { STATE = 6; break; }
                StateAudio::Fade(-10000, -200, true, false);
                return 0x2201;
            } else {
                LINE = 0;
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Configure(35.0f, 360.0f, 1);
                reinterpret_cast<StatePatternActor *>(PLAYER(WINNER))->ChoosePattern();
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Render(STATE_TEXT, 120, 120, 255, 24, 2, false);
                ACTOR(signed char, WINNER, 0x6E7) = reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(PLAYER(WINNER)) + 0x6CB)[LINE];
                reinterpret_cast<StateRecords *>(&g_BattleRecords)->IncrementCounter(g_StatePlayerIds[WINNER], g_StatePlayerIds[1 - WINNER]);
                STATE = 5; TIMER = 160;
            }
        }
        break;
    case 4:
        if (ACTOR(unsigned char, 0, 0x3CF) == 0 || ACTOR(unsigned char, 1, 0x3CF) == 0) ++TIMER;
        if (TIMER == 150) {
            ACTOR(short, 0, 0x3A0) = 0; ACTOR(short, 1, 0x3A0) = 0;
            ACTOR(unsigned char, 0, 0x39C) = 0; ACTOR(unsigned char, 1, 0x39C) = 0;
            NOTICE->SetNotice(0);
        }
        if (TIMER <= 145) {
            for (i = 0; i < 2; ++i) {
                ACTOR(short, i, 0x326) += 600;
                if (ACTOR(short, i, 0x326) >= 10000) {
                    ACTOR(short, i, 0x326) = 10000;
                    ACTOR(short, i, 0x324) += 200;
                    if (ACTOR(short, i, 0x324) >= 10000) ACTOR(short, i, 0x324) = 10000;
                }
                ACTOR(float, i, 0x368) = 0.0f; ACTOR(float, i, 0x36C) = 0.0f;
                ACTOR(short, i, 0x3B0) = 1000; ACTOR(short, i, 0x3B6) = 0;
            }
        }
        if (TIMER <= 20) { ACTOR(signed char, 0, 0x3CE) = 0; ACTOR(signed char, 1, 0x3CE) = 0; STATE = 1; }
        break;
    case 5:
        if (SELF(float, 0x8C) > -200.0f) SELF(float, 0x8C) -= 5.0f;
        if (SELF(float, 0x90) < 0.0f) SELF(float, 0x90) += 10.0f;
        if (ACTOR(int, 0, 0x4E4) == 1 || ACTOR(int, 1, 0x4E4) == 1) {
            ++LINE;
            if (LINE < ACTOR(signed char, WINNER, 0x53A)) {
                reinterpret_cast<StateTextSurface *>(g_TextRenderer)->Render(STATE_TEXT, 120, 120, 255, 24, 2, false);
                ACTOR(signed char, WINNER, 0x6E7) = reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(PLAYER(WINNER)) + 0x6CB)[LINE];
            } else if (g_CombatMode == 4) {
                if (ACTOR(signed char, 0, 0x3CE) != 0) {
                    if (g_FrameClockMode == 2) STATE = 6;
                    else { SELF(unsigned char, 0xA0) = 1; SELF(unsigned char, 0x118) = 1; break; }
                } else {
                    if (g_FrameClockMode == 2) {
                        if (g_NoticeSelection == g_StateReplayLimit) { STATE = 6; break; }
                        StateAudio::Fade(-10000, -200, true, false); return 0x2201;
                    } else {
                        g_StateReplay.AppendRecord();
                        if (g_NoticeSelection == g_StateRecordLimit) {
                            StateAudio::PlayTrack(40); StateAudio::Fade(-10000, -160, true, true);
                            g_StateReturnFlag = -1; return 0x2207;
                        }
                        StateAudio::Fade(-10000, -200, true, false); return 0x2201;
                    }
                }
            } else {
                if (g_FrameClockMode == 2) STATE = 6;
                else { SELF(unsigned char, 0xA0) = 1; SELF(unsigned char, 0x118) = 1; }
            }
        }
        break;
    case 6:
        StateAudio::PlayTrack(40); StateAudio::Fade(-10000, -160, true, true);
        if (g_FrameClockMode == 2 || g_FrameClockMode == 4) return 0x2205;
        return 0x2203;
    case 7:
        if (ACTOR(unsigned char, 0, 0x6EF)) {
            ACTOR(unsigned char, 0, 0x6EF) = 0; ++SELF(signed char, 0x5C);
            if (SELF(signed char, 0x5C) == 1) {
                TIMER = 200; STATE = 0;
                if (g_FrameClockMode == 4) { g_FrameClockMode = 2; g_StateReplayChanged = 1; }
                if (g_FrameClockMode == 3) g_FrameClockMode = 1;
            } else if (SELF(signed char, 0x5C) == 2) {
                StateAudio::Fade(-10000, -160, true, false);
                g_StateCapture->InstallCallback(); OnFrameStart(); g_StateCapture->EnableDirectDraw(); g_StateCapture->CapturePrimary();
                if (g_FrameClockMode == 4) { g_FrameClockMode = 2; g_StateReplayChanged = 1; }
                else if (g_FrameClockMode == 3) g_FrameClockMode = 1;
                if (g_FrameClockMode == 1) g_StateReplay.AppendRecord();
                return static_cast<short>(0xFF06);
            }
        }
        break;
    case 8:
        StateAudio::PlayTrack(40); StateAudio::Fade(-10000, -160, true, true); g_StateReplay.AppendRecord(); return 0x2207;
    case 14:
        StateAudio::PlayTrack(40); StateAudio::Fade(-10000, -160, true, true);
        if (g_FrameClockMode == 2 || g_FrameClockMode == 4) return 0x2205;
        if (g_StateReturnFlag) g_StateReplay.AppendRecord();
        if (g_CombatMode == 3 && ACTOR(unsigned long, 0, 0x2D0) > g_StateScoreThreshold) return 0x220A;
        return 0x2203;
    case 9:
        if ((ACTOR(unsigned char, 0, 0x3CF) == 0 || ACTOR(unsigned char, 1, 0x3CF) == 0) && TIMER < 25) ++TIMER;
        if (TIMER == 150) NOTICE->SetNotice(0);
        if (TIMER <= 145) {
            if (ACTOR(signed char, 0, 0x3CE)) {
                ACTOR(short, 0, 0x326) += 600; ACTOR(short, 0, 0x324) += 200;
                if (ACTOR(short, 0, 0x326) > 10000) ACTOR(short, 0, 0x326) = 10000;
                if (ACTOR(short, 0, 0x324) > 10000) ACTOR(short, 0, 0x324) = 10000;
                ACTOR(float, 0, 0x368) = 0.0f; ACTOR(short, 0, 0x3B0) = 1000; ACTOR(short, 0, 0x3B6) = 0; ACTOR(signed char, 0, 0x366) = 2;
            }
            if (ACTOR(signed char, 1, 0x3CE)) {
                ACTOR(short, 1, 0x326) += 600;
                if (ACTOR(short, 1, 0x326) >= MAX_HEALTH) {
                    ACTOR(short, 1, 0x326) = MAX_HEALTH;
                    ACTOR(short, 1, 0x324) += 200;
                    if (ACTOR(short, 1, 0x324) > MAX_HEALTH) ACTOR(short, 1, 0x324) = MAX_HEALTH;
                }
                ACTOR(float, 1, 0x368) = 0.0f; ACTOR(float, 1, 0x36C) = 900.0f;
                ACTOR(short, 1, 0x3B0) = 1000; ACTOR(short, 1, 0x3B6) = 0; ACTOR(signed char, 0, 0x39C) = 0;
            }
        }
        if (TIMER <= 20) { ACTOR(signed char, 0, 0x3CE) = 0; ACTOR(signed char, 1, 0x3CE) = 0; STATE = 1; }
        break;
    case 10:
        if (TIMER == 300) NOTICE->SetNotice(1);
        if (TIMER == 10) { STATE = 9; TIMER = 160; }
        break;
    case 11:
        if (TIMER == 180) NOTICE->SetNotice(1);
        if (TIMER == 10) {
            ACTOR(short, 0, 0x3A0) = 0; ACTOR(short, 1, 0x3A0) = 0;
            ACTOR(unsigned char, 0, 0x39C) = 0; ACTOR(unsigned char, 1, 0x39C) = 0;
            if (g_FrameClockMode == 2) {
                if (ACTOR(signed char, 0, 0x3CE)) STATE = 6;
                else { STATE = 7; g_FrameClockMode = 4; g_StateReplayChanged = 1; }
            } else if (ACTOR(signed char, 0, 0x3CE)) {
                STATE = 12;
                if (g_StateContinueCount > 0) SELF(unsigned char, 0x118) = 0;
                else SELF(unsigned char, 0x118) = 1;
                TIMER = 100;
            } else {
                STATE = 7;
                if (g_FrameClockMode == 1) g_FrameClockMode = 3;
            }
        }
        break;
    case 12:
        if (g_FrameClockMode == 2) STATE = 6;
        else if (TIMER <= 1) SELF(unsigned char, 0xA0) = 1;
        break;
    case 13:
        if (TIMER == 300) NOTICE->SetNotice(1);
        else if (TIMER < 200 && TIMER >= 150) {
            g_StateFadeAlpha = static_cast<unsigned char>(255.0f - (TIMER - 150) * 5.1f);
            g_StateResetCounter = 0;
            if (TIMER == 150) {
                ACTOR(int, 1, 0x3A4) = 0; ACTOR(int, 1, 0x3A8) = 0;
                ACTOR(short, 1, 0x3A0) = 0; ACTOR(signed char, 1, 0x39C) = 0;
                for (resetPlayer = 0; resetPlayer < 2; ++resetPlayer) {
                    PLAYER(resetPlayer)->Slot6();
                    ACTOR(signed char, resetPlayer, 0x3CE) = 1;
                    ACTOR(float, resetPlayer, 0x44) = static_cast<float>(resetPlayer * 320 + 480);
                    ACTOR(float, resetPlayer, 0x48) = 0.0f;
                }
                ACTOR(signed char, 0, 0x39D) = 2; ACTOR(signed char, 1, 0x39D) = ACTOR(signed char, 1, 0x39E);
                ACTOR(short, 1, 0x326) = 1;
                ACTOR(short, 1, 0x326) = MAX_HEALTH;
                reinterpret_cast<StateEffects *>(&g_CombatEffects)->ReleaseEntries();
                g_StateStageTotal = 0;
                for (resetPlayer = 1; resetPlayer <= ACTOR(signed char, 1, 0x39E); ++resetPlayer)
                    g_StateStageTotal += reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(PLAYER(1)) + 0x400)[resetPlayer];
            }
        } else if (TIMER < 50) {
            g_StateFadeAlpha = static_cast<unsigned char>(TIMER * 5.1f);
            if (TIMER == 0) { g_StateFadeAlpha = 0; STATE = 9; TIMER = 160; }
        }
        break;
    }
    if (SELF(int, 0x60) > 0) NOTICE->AdvanceOverlay();
    NOTICE->UpdateTransition();
    if (SELF(unsigned char, 0x1C)) {
        for (k = 0; k < 2; ++k) {
            if (ACTOR(short, k, 0x60) < 50) {
                ACTOR(short, k, 0x324) = 10000; ACTOR(short, k, 0x326) = 10000;
                ACTOR(float, k, 0x368) = 1000.0f; ACTOR(signed char, k, 0x39C) = 0; ACTOR(signed char, k, 0x366) = 2;
            }
        }
    }
    if (g_CombatMode == 5) {
        for (j = 0; j < 2; ++j) {
            if (ACTOR(short, j, 0x60) < 50) {
                ACTOR(short, j, 0x324) = 10000; ACTOR(short, j, 0x326) = 10000;
                ACTOR(float, j, 0x36C) = static_cast<float>(ACTOR(signed char, 1, 0x52D) * 100);
                ACTOR(signed char, j, 0x39C) = 0; ACTOR(signed char, j, 0x366) = 2;
            }
        }
    }
    if (g_CombatMode == 6) {
        ++SELF(unsigned long, 0x10C);
        if (SELF(unsigned long, 0x10C) > 3600) { StateAudio::PlayTrack(40); StateAudio::Fade(-10000, -160, true, true); return 0x2202; }
    }
    if (TIMER > 0) --TIMER;
    if (SELF(int, 0x6C) > 0) --SELF(int, 0x6C);
    if (g_StateFadeValue > 0.0f) { g_StateFadeValue -= 0.01f; if (g_StateFadeValue < 0.0f) g_StateFadeValue = 0.0f; }
    if (ACTOR(signed char, 0, 0x39D) == 2) SELF(unsigned char, 0x98) = 128;
    else if (SELF(unsigned char, 0x98) < 255) ++SELF(unsigned char, 0x98);
    if (g_CombatMode != 3) {
        if (ACTOR(signed char, 1, 0x39D) == 2) SELF(unsigned char, 0x99) = 128;
        else if (SELF(unsigned char, 0x99) < 255) ++SELF(unsigned char, 0x99);
    }
    if (g_FrameClockMode == 2 && g_StateReplay.IsInputEmpty()) {
        if (g_CombatMode != 3 && g_CombatMode != 4) STATE = 6;
        else if (g_NoticeSelection >= g_StateReplayLimit) STATE = 6;
    }
    if (SELF(unsigned char, 0xA0) || SELF(unsigned char, 0xA1)) {
        SELF(FrameInputSnapshot, 0xA4) = ACTOR(FrameInputSnapshot, 0, 0x4C0);
        SELF(FrameInputSnapshot, 0xC0) = ACTOR(FrameInputSnapshot, 1, 0x4C0);
    }
    return 0;
}
