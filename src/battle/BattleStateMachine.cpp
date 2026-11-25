#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "replay/ReplayRecords.hpp"
#include "engine/GameSharedState.hpp"
#include "graphics/TextOverlay.hpp"
#include "audio/AudioControl.hpp"
#include "battle/BattleScene.hpp"
#include "battle/CombatEffects.hpp"
#include "battle/BattleStateMachine.hpp"
#include "engine/GameProgress.hpp"
#include "ui/WindowOverlayF212.hpp"
#define STATE field018
#define TIMER field00C
#define WINNER field05D
#define LINE field05E
#define STATE_TEXT fighters[WINNER]->quoteLines[LINE]
#define MAX_HEALTH fighters[1]->healthLimits[fighters[1]->field39D]
short BattleScene::AdvanceState()
{
    int i, j, k, resetPlayer;
    if (fighters[0]->score > g_MaxCombatScore) g_MaxCombatScore = fighters[0]->score;
    switch (STATE) {
    case 0:
        if (field08C < 0.0f) field08C += 5.0f;
        if (TIMER == 150) {
            if (g_CombatMode != CombatMode::Story) MusicF205::ScheduleTransitionFade();
            SetNotice(0);
        }
        if (TIMER == 20) STATE = 1;
        break;
    case 2:
        if (TIMER == 300) SetNotice(1);
        if (TIMER == 10) { STATE = 4; TIMER = 160; }
        break;
    case 3:
        if (TIMER == 180) SetNotice(1);
        if (TIMER == 10) {
            fighters[0]->spellTimer = 0; fighters[1]->spellTimer = 0;
            fighters[0]->spellDeclarationExpired = 0; fighters[1]->spellDeclarationExpired = 0;
            if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
                if (g_StageAt0067161E == g_ReplayRecords.fileHeader.recordCount || g_CombatMode == CombatMode::DuelCpu || g_CombatMode == CombatMode::DuelHuman) { STATE = 6; break; }
                AudioControl407CA0::ScheduleFade(-10000, -200, true, false);
                return 0x2201;
            } else {
                LINE = 0;
                g_TextRenderer->ConfigureText(35.0f, 360.0f, 1);
                fighters[WINNER]->ChoosePatternSequence();
                g_TextRenderer->RenderTextToTexture(STATE_TEXT, 120, 120, 255, 24, 2, false);
                fighters[WINNER]->noticeBadge = fighters[WINNER]->quoteBadges[LINE];
                g_GameProgress.RecordMatchWin(g_PlayerIdAt006714C8[WINNER], g_PlayerIdAt006714C8[1 - WINNER]);
                STATE = 5; TIMER = 160;
            }
        }
        break;
    case 4:
        if (fighters[0]->field3CF == 0 || fighters[1]->field3CF == 0) ++TIMER;
        if (TIMER == 150) {
            fighters[0]->spellTimer = 0; fighters[1]->spellTimer = 0;
            fighters[0]->spellDeclarationExpired = 0; fighters[1]->spellDeclarationExpired = 0;
            SetNotice(0);
        }
        if (TIMER <= 145) {
            for (i = 0; i < 2; ++i) {
                fighters[i]->recoverableHealth += 600;
                if (fighters[i]->recoverableHealth >= 10000) {
                    fighters[i]->recoverableHealth = 10000;
                    fighters[i]->health += 200;
                    if (fighters[i]->health >= 10000) fighters[i]->health = 10000;
                }
                fighters[i]->pendingSpellCharge = 0.0f; fighters[i]->spellPower = 0.0f;
                fighters[i]->spirit = 1000; fighters[i]->spiritCooldown = 0;
            }
        }
        if (TIMER <= 20) { fighters[0]->field3CE.unsignedAt3CE = 0; fighters[1]->field3CE.unsignedAt3CE = 0; STATE = 1; }
        break;
    case 5:
        if (field08C > -200.0f) field08C -= 5.0f;
        if (field090 < 0.0f) field090 += 10.0f;
        if (fighters[0]->field4E4 == 1 || fighters[1]->field4E4 == 1) {
            ++LINE;
            if (LINE < fighters[WINNER]->quoteLineCount) {
                g_TextRenderer->RenderTextToTexture(STATE_TEXT, 120, 120, 255, 24, 2, false);
                fighters[WINNER]->noticeBadge = fighters[WINNER]->quoteBadges[LINE];
            } else if (g_CombatMode == CombatMode::Arcade) {
                if (fighters[0]->field3CE.signedAt3CE != 0) {
                    if (g_ReplayModeAt0066C238 == ReplayMode::Playback) STATE = 6;
                    else { field0A0 = 1; field118 = 1; break; }
                } else {
                    if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
                        if (g_StageAt0067161E == g_ReplayRecords.fileHeader.recordCount) { STATE = 6; break; }
                        AudioControl407CA0::ScheduleFade(-10000, -200, true, false); return 0x2201;
                    } else {
                        g_ReplayRecords.AppendRecord();
                        if (g_StageAt0067161E == g_CharacterCountAt0067161F) {
                            MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true);
                            g_StateReturnFlag = -1; return 0x2207;
                        }
                        AudioControl407CA0::ScheduleFade(-10000, -200, true, false); return 0x2201;
                    }
                }
            } else {
                if (g_ReplayModeAt0066C238 == ReplayMode::Playback) STATE = 6;
                else { field0A0 = 1; field118 = 1; }
            }
        }
        break;
    case 6:
        MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true);
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback || g_ReplayModeAt0066C238 == ReplayMode::ReplayDialogue) return 0x2205;
        return 0x2203;
    case 7:
        if (fighters[0]->field6EF) {
            fighters[0]->field6EF = 0; ++field05C;
            if (field05C == 1) {
                TIMER = 200; STATE = 0;
                if (g_ReplayModeAt0066C238 == ReplayMode::ReplayDialogue) { g_ReplayModeAt0066C238 = ReplayMode::Playback; g_InputCanCancelAt00671632 = 1; }
                if (g_ReplayModeAt0066C238 == ReplayMode::LiveDialogue) g_ReplayModeAt0066C238 = ReplayMode::Recording;
            } else if (field05C == 2) {
                AudioControl407CA0::ScheduleFade(-10000, -160, true, false);
                g_WindowOverlayAt006714C4->InstallPresentCallback();
                Render();
                g_WindowOverlayAt006714C4->EnableDirectDraw();
                g_WindowOverlayAt006714C4->CapturePrimary();
                if (g_ReplayModeAt0066C238 == ReplayMode::ReplayDialogue) { g_ReplayModeAt0066C238 = ReplayMode::Playback; g_InputCanCancelAt00671632 = 1; }
                else if (g_ReplayModeAt0066C238 == ReplayMode::LiveDialogue) g_ReplayModeAt0066C238 = ReplayMode::Recording;
                if (g_ReplayModeAt0066C238 == ReplayMode::Recording) g_ReplayRecords.AppendRecord();
                return static_cast<short>(0xFF06);
            }
        }
        break;
    case 8:
        MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true); g_ReplayRecords.AppendRecord(); return 0x2207;
    case 14:
        MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true);
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback || g_ReplayModeAt0066C238 == ReplayMode::ReplayDialogue) return 0x2205;
        if (g_StateReturnFlag) g_ReplayRecords.AppendRecord();
        if (g_CombatMode == CombatMode::Story && fighters[0]->score > g_StateScoreThreshold) return 0x220A;
        return 0x2203;
    case 9:
        if ((fighters[0]->field3CF == 0 || fighters[1]->field3CF == 0) && TIMER < 25) ++TIMER;
        if (TIMER == 150) SetNotice(0);
        if (TIMER <= 145) {
            if (fighters[0]->field3CE.signedAt3CE) {
                fighters[0]->recoverableHealth += 600; fighters[0]->health += 200;
                if (fighters[0]->recoverableHealth > 10000) fighters[0]->recoverableHealth = 10000;
                if (fighters[0]->health > 10000) fighters[0]->health = 10000;
                fighters[0]->pendingSpellCharge = 0.0f; fighters[0]->spirit = 1000; fighters[0]->spiritCooldown = 0; fighters[0]->bombCount = 2;
            }
            if (fighters[1]->field3CE.signedAt3CE) {
                fighters[1]->recoverableHealth += 600;
                if (fighters[1]->recoverableHealth >= MAX_HEALTH) {
                    fighters[1]->recoverableHealth = MAX_HEALTH;
                    fighters[1]->health += 200;
                    if (fighters[1]->health > MAX_HEALTH) fighters[1]->health = MAX_HEALTH;
                }
                fighters[1]->pendingSpellCharge = 0.0f; fighters[1]->spellPower = 900.0f;
                fighters[1]->spirit = 1000; fighters[1]->spiritCooldown = 0; fighters[0]->spellDeclarationExpired = 0;
            }
        }
        if (TIMER <= 20) { fighters[0]->field3CE.unsignedAt3CE = 0; fighters[1]->field3CE.unsignedAt3CE = 0; STATE = 1; }
        break;
    case 10:
        if (TIMER == 300) SetNotice(1);
        if (TIMER == 10) { STATE = 9; TIMER = 160; }
        break;
    case 11:
        if (TIMER == 180) SetNotice(1);
        if (TIMER == 10) {
            fighters[0]->spellTimer = 0; fighters[1]->spellTimer = 0;
            fighters[0]->spellDeclarationExpired = 0; fighters[1]->spellDeclarationExpired = 0;
            if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
                if (fighters[0]->field3CE.signedAt3CE) STATE = 6;
                else { STATE = 7; g_ReplayModeAt0066C238 = ReplayMode::ReplayDialogue; g_InputCanCancelAt00671632 = 1; }
            } else if (fighters[0]->field3CE.signedAt3CE) {
                STATE = 12;
                if (g_ContinueCountAt00671623 > 0) field118 = 0;
                else field118 = 1;
                TIMER = 100;
            } else {
                STATE = 7;
                if (g_ReplayModeAt0066C238 == ReplayMode::Recording) g_ReplayModeAt0066C238 = ReplayMode::LiveDialogue;
            }
        }
        break;
    case 12:
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback) STATE = 6;
        else if (TIMER <= 1) field0A0 = 1;
        break;
    case 13:
        if (TIMER == 300) SetNotice(1);
        else if (TIMER < 200 && TIMER >= 150) {
            g_StateFadeAlpha = static_cast<unsigned char>(255.0f - (TIMER - 150) * 5.1f);
            g_StateResetCounter = 0;
            if (TIMER == 150) {
                fighters[1]->field3A4 = 0; fighters[1]->field3A8 = 0;
                fighters[1]->spellTimer = 0; fighters[1]->spellDeclarationExpired = 0;
                for (resetPlayer = 0; resetPlayer < 2; ++resetPlayer) {
                    fighters[resetPlayer]->ResetRound();
                    fighters[resetPlayer]->field3CE.unsignedAt3CE = 1;
                    fighters[resetPlayer]->x = static_cast<float>(resetPlayer * 320 + 480);
                    fighters[resetPlayer]->y = 0.0f;
                }
                fighters[0]->field39D = 2; fighters[1]->field39D = fighters[1]->field39E;
                fighters[1]->recoverableHealth = 1;
                fighters[1]->recoverableHealth = MAX_HEALTH;
                g_CombatEffects.ReleaseEntries();
                g_CumulativeScoreAt006714BC = 0;
                for (resetPlayer = 1; resetPlayer <= fighters[1]->field39E; ++resetPlayer)
                    g_CumulativeScoreAt006714BC += static_cast<int>(fighters[1]->field400[resetPlayer]);
            }
        } else if (TIMER < 50) {
            g_StateFadeAlpha = static_cast<unsigned char>(TIMER * 5.1f);
            if (TIMER == 0) { g_StateFadeAlpha = 0; STATE = 9; TIMER = 160; }
        }
        break;
    }
    if (field060 > 0) AdvanceOverlay();
    UpdateTransition();
    if (field01C) {
        for (k = 0; k < 2; ++k) {
            if (fighters[k]->action < 50) {
                fighters[k]->health = 10000; fighters[k]->recoverableHealth = 10000;
                fighters[k]->pendingSpellCharge = 1000.0f; fighters[k]->spellDeclarationExpired = 0; fighters[k]->bombCount = 2;
            }
        }
    }
    if (g_CombatMode == CombatMode::Practice) {
        for (j = 0; j < 2; ++j) {
            if (fighters[j]->action < 50) {
                fighters[j]->health = 10000; fighters[j]->recoverableHealth = 10000;
                fighters[j]->spellPower = static_cast<float>(fighters[1]->practiceSpellStock * 100);
                fighters[j]->spellDeclarationExpired = 0; fighters[j]->bombCount = 2;
            }
        }
    }
    if (g_CombatMode == CombatMode::Attract) {
        ++field10C;
        if (field10C > 3600) { MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true); return 0x2202; }
    }
    if (TIMER > 0) --TIMER;
    if (field06C > 0) --field06C;
    if (g_StateFadeValue > 0.0f) { g_StateFadeValue -= 0.01f; if (g_StateFadeValue < 0.0f) g_StateFadeValue = 0.0f; }
    if (fighters[0]->field39D == 2) field098 = 128;
    else if (field098 < 255) ++field098;
    if (g_CombatMode != CombatMode::Story) {
        if (fighters[1]->field39D == 2) field099 = 128;
        else if (field099 < 255) ++field099;
    }
    if (g_ReplayModeAt0066C238 == ReplayMode::Playback && g_ReplayRecords.IsPrimaryInputQueueEmpty()) {
        if (g_CombatMode != CombatMode::Story && g_CombatMode != CombatMode::Arcade) STATE = 6;
        else if (g_StageAt0067161E >= g_ReplayRecords.fileHeader.recordCount) STATE = 6;
    }
    if (field0A0 || field0A1) {
        inputSnapshots[0] = fighters[0]->inputBindings.held;
        inputSnapshots[1] = fighters[1]->inputBindings.held;
    }
    return 0;
}
#undef F1112_LIFE_CURRENT
#undef F1112_LIFE_RECOVERABLE
#undef F1112_ROUND_FIRST
#undef F1112_ROUND_SECOND
#undef F1112_ACTOR_X
#undef F1112_ACTOR_Y
