#include "input/InputControl.hpp"
#include "battle/CombatMode.hpp"
#include "battle/BattleResultState.hpp"
#include "engine/GameSharedState.hpp"
#include "battle/BattleScene.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "battle/FighterVirtualActionsF159.hpp"

// Existing unsigned byte view, written from the observed scene pause byte.

#define HELD_BUTTON g_InputMappings[i].held.counts[InputControl::ButtonA + j]

void BattleScene::PollPauseShortcut()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].IsKeyDown(0x1C)
        && (g_InputMappings[0].IsKeyDown(0x38)
            || g_InputMappings[0].IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    if (g_InputMappings[0].IsKeyDown(1))
        escapeKeyHeldFrames++;
    else
        escapeKeyHeldFrames = 0;
    if ((escapeKeyHeldFrames == 3
            || g_InputMappings[0].held.counts[InputControl::Pause] == 1
            || g_InputMappings[1].held.counts[InputControl::Pause] == 1)
        && battlePhase != BattlePhase::VictoryQuote
        && battlePhase != BattlePhase::RoundIntro
        && battlePhase != BattlePhase::StoryDialogue
        && g_CombatMode != CombatMode::Attract) {
        pauseMenuOpen = static_cast<int>(!pauseMenuOpen);
        if (pauseMenuOpen != 0)
            pauseMenuRow = 0;
        g_SoundBank->Play(48);
    }
    g_RenderByte0067161C = pauseMenuOpen;
}

void BattleScene::UpdatePlayerEffects()
{
    int i;
    int j;
    for (i = 0; i < 2; i++) {
        fighters[i]->UpdateControls();
        if (battlePhase != BattlePhase::Fighting) {
            fighters[i]->inputA = 0;
            fighters[i]->inputB = 0;
            fighters[i]->inputC = 0;
            fighters[i]->ClearAuxiliaryWords();
            if (battlePhase == BattlePhase::StoryContinueReset
                || battlePhase == BattlePhase::StoryMatchKnockout
                || battlePhase == BattlePhase::StoryRoundKnockout
                || battlePhase == BattlePhase::VersusMatchKnockout
                || battlePhase == BattlePhase::VersusRoundKnockout
                || battlePhase == BattlePhase::RoundIntro
                || battlePhase == BattlePhase::VictoryQuote
                || battlePhase == BattlePhase::StoryDialogue) {
                fighters[i]->inputD = 0;
                fighters[i]->inputX = 0;
                fighters[i]->inputY = 0;
                fighters[i]->PackDirectionBits();
                fighters[i]->aiCommand = 0;
            }
            if (fighters[i]->aiCommand >= 10
                || fighters[i]->cpuControlled != 0)
                fighters[i]->aiCommand = 0;
        }
        for (j = 0; j < 5; j++) {
            if (HELD_BUTTON != 0)
                attractFrames = 3600;
        }
    }
}

#undef HELD_BUTTON
