#include "input/InputControl.hpp"
#include "replay/ReplayMode.hpp"
#include "battle/CombatMode.hpp"
#include "battle/BattleResultState.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "battle/BattleScene.hpp"
#include "battle/PauseDebugF175.hpp"
#include "battle/BattleMode5OptionsF168.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "battle/FighterHitResponseF164.hpp"

// Reference-only byte views from complete native accesses; no allocation or
// original global identity is established by these provisional names.
// The dword lies in the PE's uninitialized virtual data tail. No file payload
// is asserted; native comparisons/increments/stores establish this used view.
unsigned int g_DebugKeyRepeatAt0068D618;


void BattleScene::HandlePauseMenu()
{
    if (g_CombatMode == CombatMode::Practice) {
        HandleMode5Options();
    } else {
        if (g_InputMappings[0].held.counts[InputControl::ButtonA] == 1
            || g_InputMappings[1].held.counts[InputControl::ButtonA] == 1) {
            pauseMenuOpen = 0;
            g_SoundBank->Play(45);
            switch (pauseMenuRow) {
            case 0:
                if (battlePhase == BattlePhase::StoryContinuePrompt && g_ContinueCountAt00671623 > 0) {
                    fighters[0]->roundsRemaining = 2;
                    fighters[0]->score = 0;
                    g_ContinueCountAt00671623--;
                    g_ContinueUsedAt00671624 = 1;
                    g_SequenceCounterAt00671622 = 2;
                    battlePhase = BattlePhase::StoryContinueReset;
                    phaseFrames = 299;
                }
                break;
            case 1:
                if (battlePhase == BattlePhase::StoryContinuePrompt) {
                    g_StateReturnFlag = 0;
                    battlePhase = BattlePhase::LeaveStory;
                    break;
                }
                battlePhase = BattlePhase::LeaveBattle;
                break;
            case 2:
                if (battlePhase == BattlePhase::StoryContinuePrompt) {
                    g_StateReturnFlag = 1;
                    battlePhase = BattlePhase::LeaveStory;
                } else {
                    battlePhase = BattlePhase::LeaveAndSaveReplay;
                }
                break;
            }
        }
        if (battlePhase != BattlePhase::VictoryQuote && battlePhase != BattlePhase::StoryContinuePrompt
            && (g_InputMappings[0].held.counts[InputControl::ButtonB] == 1
                || g_InputMappings[1].held.counts[InputControl::ButtonB] == 1))
            pauseMenuOpen = 0;
        if (g_InputMappings[0].held.counts[InputControl::Vertical] == 1
            || g_InputMappings[1].held.counts[InputControl::Vertical] == 1) {
            g_SoundBank->Play(39);
            pauseMenuRow++;
        }
        if (g_InputMappings[0].held.counts[InputControl::Vertical] == -1
            || g_InputMappings[1].held.counts[InputControl::Vertical] == -1) {
            g_SoundBank->Play(39);
            pauseMenuRow--;
        }
        if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
            if (pauseMenuRow < 0)
                pauseMenuRow = 1;
            if (pauseMenuRow > 1)
                pauseMenuRow = 0;
        }
        if (battlePhase == BattlePhase::VictoryQuote) {
            if (pauseMenuRow < 1)
                pauseMenuRow = 2;
            if (pauseMenuRow > 2)
                pauseMenuRow = 1;
        } else if (battlePhase == BattlePhase::StoryContinuePrompt && g_ContinueCountAt00671623 == 0) {
            pauseMenuRow = 1;
        } else if (g_CombatMode == CombatMode::Story
            && (g_ContinueUsedAt00671624 != 0 || battlePhase == BattlePhase::StoryDialogue)) {
            if (pauseMenuRow < 0)
                pauseMenuRow = 1;
            if (pauseMenuRow > 1)
                pauseMenuRow = 0;
        } else {
            if (pauseMenuRow < 0)
                pauseMenuRow = 2;
            if (pauseMenuRow > 2)
                pauseMenuRow = 0;
        }
    }
}

void BattleScene::ProcessDebugKeys()
{
    if (g_InputMappings[0].IsKeyDown(0x3B)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->practiceSpellSelection = (fighters[1]->practiceSpellSelection + 1) % 6;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x3C)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->practiceSpellStock = (fighters[1]->practiceSpellStock + 9) % 10;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x3D)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->practiceSpellStock = (fighters[1]->practiceSpellStock + 1) % 10;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x3E)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->practiceGuardMode = (fighters[1]->practiceGuardMode + 1) % 4;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x3F)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->practiceManualAirRecovery = (fighters[1]->practiceManualAirRecovery + 1) % 2;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x40)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->practiceActionMode = (fighters[1]->practiceActionMode + 1) % 4;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x41)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->practiceCenterPosition = (fighters[1]->practiceCenterPosition + 1) % 2;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x42)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[0]->spellTimer = 1;
        g_DebugKeyRepeatAt0068D618++;
    } else {
        g_DebugKeyRepeatAt0068D618 = 0;
    }
    fighters[0]->roundsRemaining = 2 - fighters[1]->practiceSpellSelection / 3;
    fighters[0]->selectedSpellCards[0] = fighters[1]->practiceSpellSelection % 3;
    fighters[0]->selectedSpellCards[1] = fighters[1]->practiceSpellSelection % 3;
}
