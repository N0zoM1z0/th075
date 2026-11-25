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
        field114++;
    else
        field114 = 0;
    if ((field114 == 3
            || g_InputMappings[0].held.counts[InputControl::Pause] == 1
            || g_InputMappings[1].held.counts[InputControl::Pause] == 1)
        && field018 != 5
        && field018 != 0
        && field018 != 7
        && g_CombatMode != CombatMode::Attract) {
        field0A0 = static_cast<int>(!field0A0);
        if (field0A0 != 0)
            field118 = 0;
        g_SoundBank->Play(48);
    }
    g_RenderByte0067161C = field0A0;
}

void BattleScene::UpdatePlayerEffects()
{
    int i;
    int j;
    for (i = 0; i < 2; i++) {
        fighters[i]->UpdateControls();
        if (field018 != 1) {
            fighters[i]->inputA = 0;
            fighters[i]->inputB = 0;
            fighters[i]->inputC = 0;
            fighters[i]->ClearAuxiliaryWords();
            if (field018 == 13
                || field018 == 11
                || field018 == 10
                || field018 == 3
                || field018 == 2
                || field018 == 0
                || field018 == 5
                || field018 == 7) {
                fighters[i]->inputD = 0;
                fighters[i]->inputX = 0;
                fighters[i]->inputY = 0;
                fighters[i]->PackDirectionBits();
                fighters[i]->aiCommand = 0;
            }
            if (fighters[i]->aiCommand >= 10
                || fighters[i]->field2CD != 0)
                fighters[i]->aiCommand = 0;
        }
        for (j = 0; j < 5; j++) {
            if (HELD_BUTTON != 0)
                field10C = 3600;
        }
    }
}

#undef HELD_BUTTON
