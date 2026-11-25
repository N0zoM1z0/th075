#include "engine/SceneTransition.hpp"
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
#define MAX_HEALTH fighters[1]->healthLimits[fighters[1]->field39D]
short BattleScene::AdvanceState()
{
    int i, j, k, resetPlayer;
    if (fighters[0]->score > g_MaxCombatScore) g_MaxCombatScore = fighters[0]->score;
    switch (battlePhase) {
    case BattlePhase::RoundIntro:
        if (hudOffsetY < 0.0f) hudOffsetY += 5.0f;
        if (phaseFrames == 150) {
            if (g_CombatMode != CombatMode::Story) MusicF205::ScheduleTransitionFade();
            SetNotice(0);
        }
        if (phaseFrames == 20) battlePhase = BattlePhase::Fighting;
        break;
    case BattlePhase::VersusRoundKnockout:
        if (phaseFrames == 300) SetNotice(1);
        if (phaseFrames == 10) { battlePhase = BattlePhase::VersusRoundRecovery; phaseFrames = 160; }
        break;
    case BattlePhase::VersusMatchKnockout:
        if (phaseFrames == 180) SetNotice(1);
        if (phaseFrames == 10) {
            fighters[0]->spellTimer = 0; fighters[1]->spellTimer = 0;
            fighters[0]->spellDeclarationExpired = 0; fighters[1]->spellDeclarationExpired = 0;
            if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
                if (g_StageAt0067161E == g_ReplayRecords.fileHeader.recordCount || g_CombatMode == CombatMode::DuelCpu || g_CombatMode == CombatMode::DuelHuman) { battlePhase = BattlePhase::LeaveBattle; break; }
                AudioControl407CA0::ScheduleFade(-10000, -200, true, false);
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::LoadBattle;
            } else {
                victoryQuoteLine = 0;
                g_TextRenderer->ConfigureText(35.0f, 360.0f, 1);
                fighters[matchWinnerSide]->ChoosePatternSequence();
                g_TextRenderer->RenderTextToTexture(fighters[matchWinnerSide]->quoteLines[victoryQuoteLine], 120, 120, 255, 24, 2, false);
                fighters[matchWinnerSide]->noticeBadge = fighters[matchWinnerSide]->quoteBadges[victoryQuoteLine];
                g_GameProgress.RecordMatchWin(g_PlayerIdAt006714C8[matchWinnerSide], g_PlayerIdAt006714C8[1 - matchWinnerSide]);
                battlePhase = BattlePhase::VictoryQuote; phaseFrames = 160;
            }
        }
        break;
    case BattlePhase::VersusRoundRecovery:
        if (fighters[0]->field3CF == 0 || fighters[1]->field3CF == 0) ++phaseFrames;
        if (phaseFrames == 150) {
            fighters[0]->spellTimer = 0; fighters[1]->spellTimer = 0;
            fighters[0]->spellDeclarationExpired = 0; fighters[1]->spellDeclarationExpired = 0;
            SetNotice(0);
        }
        if (phaseFrames <= 145) {
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
        if (phaseFrames <= 20) { fighters[0]->field3CE.unsignedAt3CE = 0; fighters[1]->field3CE.unsignedAt3CE = 0; battlePhase = BattlePhase::Fighting; }
        break;
    case BattlePhase::VictoryQuote:
        if (hudOffsetY > -200.0f) hudOffsetY -= 5.0f;
        if (victoryBadgeX < 0.0f) victoryBadgeX += 10.0f;
        if (fighters[0]->field4E4 == 1 || fighters[1]->field4E4 == 1) {
            ++victoryQuoteLine;
            if (victoryQuoteLine < fighters[matchWinnerSide]->quoteLineCount) {
                g_TextRenderer->RenderTextToTexture(fighters[matchWinnerSide]->quoteLines[victoryQuoteLine], 120, 120, 255, 24, 2, false);
                fighters[matchWinnerSide]->noticeBadge = fighters[matchWinnerSide]->quoteBadges[victoryQuoteLine];
            } else if (g_CombatMode == CombatMode::Arcade) {
                if (fighters[0]->field3CE.signedAt3CE != 0) {
                    if (g_ReplayModeAt0066C238 == ReplayMode::Playback) battlePhase = BattlePhase::LeaveBattle;
                    else { pauseMenuOpen = 1; pauseMenuRow = 1; break; }
                } else {
                    if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
                        if (g_StageAt0067161E == g_ReplayRecords.fileHeader.recordCount) { battlePhase = BattlePhase::LeaveBattle; break; }
                        AudioControl407CA0::ScheduleFade(-10000, -200, true, false); return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::LoadBattle;
                    } else {
                        g_ReplayRecords.AppendRecord();
                        if (g_StageAt0067161E == g_CharacterCountAt0067161F) {
                            MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true);
                            g_StateReturnFlag = -1; return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayNameEntry;
                        }
                        AudioControl407CA0::ScheduleFade(-10000, -200, true, false); return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::LoadBattle;
                    }
                }
            } else {
                if (g_ReplayModeAt0066C238 == ReplayMode::Playback) battlePhase = BattlePhase::LeaveBattle;
                else { pauseMenuOpen = 1; pauseMenuRow = 1; }
            }
        }
        break;
    case BattlePhase::LeaveBattle:
        MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true);
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback || g_ReplayModeAt0066C238 == ReplayMode::ReplayDialogue) return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayBrowser;
        return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::CharacterSelect;
    case BattlePhase::StoryDialogue:
        if (fighters[0]->field6EF) {
            fighters[0]->field6EF = 0; ++storyDialogueEnds;
            if (storyDialogueEnds == 1) {
                phaseFrames = 200; battlePhase = BattlePhase::RoundIntro;
                if (g_ReplayModeAt0066C238 == ReplayMode::ReplayDialogue) { g_ReplayModeAt0066C238 = ReplayMode::Playback; g_InputCanCancelAt00671632 = 1; }
                if (g_ReplayModeAt0066C238 == ReplayMode::LiveDialogue) g_ReplayModeAt0066C238 = ReplayMode::Recording;
            } else if (storyDialogueEnds == 2) {
                AudioControl407CA0::ScheduleFade(-10000, -160, true, false);
                g_WindowOverlayAt006714C4->InstallPresentCallback();
                Render();
                g_WindowOverlayAt006714C4->EnableDirectDraw();
                g_WindowOverlayAt006714C4->CapturePrimary();
                if (g_ReplayModeAt0066C238 == ReplayMode::ReplayDialogue) { g_ReplayModeAt0066C238 = ReplayMode::Playback; g_InputCanCancelAt00671632 = 1; }
                else if (g_ReplayModeAt0066C238 == ReplayMode::LiveDialogue) g_ReplayModeAt0066C238 = ReplayMode::Recording;
                if (g_ReplayModeAt0066C238 == ReplayMode::Recording) g_ReplayRecords.AppendRecord();
                return static_cast<short>(SceneTransition::SkipInAnimation | SceneTransition::SkipOutAnimation | SceneId::BattleResult);
            }
        }
        break;
    case BattlePhase::LeaveAndSaveReplay:
        MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true); g_ReplayRecords.AppendRecord(); return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayNameEntry;
    case BattlePhase::LeaveStory:
        MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true);
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback || g_ReplayModeAt0066C238 == ReplayMode::ReplayDialogue) return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayBrowser;
        if (g_StateReturnFlag) g_ReplayRecords.AppendRecord();
        if (g_CombatMode == CombatMode::Story && fighters[0]->score > g_StateScoreThreshold) return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ScoreNameEntry;
        return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::CharacterSelect;
    case BattlePhase::StoryRoundRecovery:
        if ((fighters[0]->field3CF == 0 || fighters[1]->field3CF == 0) && phaseFrames < 25) ++phaseFrames;
        if (phaseFrames == 150) SetNotice(0);
        if (phaseFrames <= 145) {
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
        if (phaseFrames <= 20) { fighters[0]->field3CE.unsignedAt3CE = 0; fighters[1]->field3CE.unsignedAt3CE = 0; battlePhase = BattlePhase::Fighting; }
        break;
    case BattlePhase::StoryRoundKnockout:
        if (phaseFrames == 300) SetNotice(1);
        if (phaseFrames == 10) { battlePhase = BattlePhase::StoryRoundRecovery; phaseFrames = 160; }
        break;
    case BattlePhase::StoryMatchKnockout:
        if (phaseFrames == 180) SetNotice(1);
        if (phaseFrames == 10) {
            fighters[0]->spellTimer = 0; fighters[1]->spellTimer = 0;
            fighters[0]->spellDeclarationExpired = 0; fighters[1]->spellDeclarationExpired = 0;
            if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
                if (fighters[0]->field3CE.signedAt3CE) battlePhase = BattlePhase::LeaveBattle;
                else { battlePhase = BattlePhase::StoryDialogue; g_ReplayModeAt0066C238 = ReplayMode::ReplayDialogue; g_InputCanCancelAt00671632 = 1; }
            } else if (fighters[0]->field3CE.signedAt3CE) {
                battlePhase = BattlePhase::StoryContinuePrompt;
                if (g_ContinueCountAt00671623 > 0) pauseMenuRow = 0;
                else pauseMenuRow = 1;
                phaseFrames = 100;
            } else {
                battlePhase = BattlePhase::StoryDialogue;
                if (g_ReplayModeAt0066C238 == ReplayMode::Recording) g_ReplayModeAt0066C238 = ReplayMode::LiveDialogue;
            }
        }
        break;
    case BattlePhase::StoryContinuePrompt:
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback) battlePhase = BattlePhase::LeaveBattle;
        else if (phaseFrames <= 1) pauseMenuOpen = 1;
        break;
    case BattlePhase::StoryContinueReset:
        if (phaseFrames == 300) SetNotice(1);
        else if (phaseFrames < 200 && phaseFrames >= 150) {
            g_StateFadeAlpha = static_cast<unsigned char>(255.0f - (phaseFrames - 150) * 5.1f);
            g_StateResetCounter = 0;
            if (phaseFrames == 150) {
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
        } else if (phaseFrames < 50) {
            g_StateFadeAlpha = static_cast<unsigned char>(phaseFrames * 5.1f);
            if (phaseFrames == 0) { g_StateFadeAlpha = 0; battlePhase = BattlePhase::StoryRoundRecovery; phaseFrames = 160; }
        }
        break;
    }
    if (noticeFrames > 0) AdvanceOverlay();
    UpdateTransition();
    if (restoreResources) {
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
        ++attractFrames;
        if (attractFrames > 3600) { MusicF204::PlayTrackByIndex(40); AudioControl407CA0::ScheduleFade(-10000, -160, true, true); return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title; }
    }
    if (phaseFrames > 0) --phaseFrames;
    if (spellBonusBannerFrames > 0) --spellBonusBannerFrames;
    if (g_StateFadeValue > 0.0f) { g_StateFadeValue -= 0.01f; if (g_StateFadeValue < 0.0f) g_StateFadeValue = 0.0f; }
    if (fighters[0]->field39D == 2) healthBarTint[0] = 128;
    else if (healthBarTint[0] < 255) ++healthBarTint[0];
    if (g_CombatMode != CombatMode::Story) {
        if (fighters[1]->field39D == 2) healthBarTint[1] = 128;
        else if (healthBarTint[1] < 255) ++healthBarTint[1];
    }
    if (g_ReplayModeAt0066C238 == ReplayMode::Playback && g_ReplayRecords.IsPrimaryInputQueueEmpty()) {
        if (g_CombatMode != CombatMode::Story && g_CombatMode != CombatMode::Arcade) battlePhase = BattlePhase::LeaveBattle;
        else if (g_StageAt0067161E >= g_ReplayRecords.fileHeader.recordCount) battlePhase = BattlePhase::LeaveBattle;
    }
    if (pauseMenuOpen || pauseOverlayAlpha) {
        inputSnapshots[0] = fighters[0]->inputBindings.held;
        inputSnapshots[1] = fighters[1]->inputBindings.held;
    }
    return 0;
}
