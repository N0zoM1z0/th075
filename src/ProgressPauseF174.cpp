#include "GameProgress.hpp"
#include "BattleScene.hpp"
#include "ProgressPauseF174.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"
#include "FighterVirtualActionsF159.hpp"

// Existing unsigned byte view, written from the observed scene pause byte.
extern unsigned char g_RenderByte0067161C;

#define HELD_BUTTON reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&g_HeldInputAt00671664) + i * 0x48 + 8)[j]

unsigned int GameProgress::ReadSelectedWord268(signed char key)
{
    return characters[selectedFighter].difficulties[0].cardCounters[key];
}

unsigned int GameProgress::ReadSelectedWord394(signed char key)
{
    return characters[selectedFighter].difficulties[0].cardCounters2[key];
}

void GameProgress::SetSelectedValue8(int value)
{
    characters[selectedFighter].difficulties[selectedDifficulty].field008 = value;
}

void GameProgress::SetSelectedValue12(int value)
{
    characters[selectedFighter].difficulties[selectedDifficulty].field00C = value;
}

int GameProgress::GetSelectedValue8()
{
    return characters[selectedFighter].difficulties[selectedDifficulty].field008;
}

int GameProgress::GetSelectedValue12()
{
    return characters[selectedFighter].difficulties[selectedDifficulty].field00C;
}

void BattleScene::PollPauseShortcut()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappingAt00671638.UpdateHeldCounts();
    g_InputMappingAt00671680.UpdateHeldCounts();
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    if (g_InputMappingAt00671638.IsKeyDown(1))
        field114++;
    else
        field114 = 0;
    if ((field114 == 3
            || g_HeldInputAt00671664.counts[6] == 1
            || g_HeldInputAt006716AC.counts[6] == 1)
        && field018 != 5
        && field018 != 0
        && field018 != 7
        && g_CombatMode != 6) {
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
        reinterpret_cast<FighterControlCallsF174*>(fighters[i])->UpdateControls();
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
                reinterpret_cast<FighterControlCallsF174*>(fighters[i])->PackDirectionBits();
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
