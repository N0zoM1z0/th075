#include "BattleScene.hpp"
#include "ProgressSelectionKeysF954.hpp"
#include "ProgressPauseF174.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"
#include "FighterVirtualActionsF159.hpp"

// Existing unsigned byte view, written from the observed scene pause byte.
extern unsigned char g_RenderByte0067161C;

#define PROGRESS_ARRAY(type, offset) reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + F954_PROGRESS_KEYS(this).fighterAt16AC4 * 0x17F0 + (offset))
#define SELECTED_VALUE(offset) (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + F954_PROGRESS_KEYS(this).fighterAt16AC4 * 0x17F0 + (offset) + F954_PROGRESS_KEYS(this).difficultyAt16AC5 * 0x5FC))
#define HELD_BUTTON reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&g_HeldInputAt00671664) + i * 0x48 + 8)[j]

unsigned int SelectedProgressF174::ReadSelectedWord268(signed char key)
{
    return PROGRESS_ARRAY(unsigned short, 0x268)[key];
}

unsigned int SelectedProgressF174::ReadSelectedWord394(signed char key)
{
    return PROGRESS_ARRAY(unsigned short, 0x394)[key];
}

void SelectedProgressF174::SetSelectedValue8(int value)
{
    SELECTED_VALUE(8) = value;
}

void SelectedProgressF174::SetSelectedValue12(int value)
{
    SELECTED_VALUE(12) = value;
}

int SelectedProgressF174::GetSelectedValue8()
{
    return SELECTED_VALUE(8);
}

int SelectedProgressF174::GetSelectedValue12()
{
    return SELECTED_VALUE(12);
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
                reinterpret_cast<int&>(fighters[i]->inputD) = 0;
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
                reinterpret_cast<int&>(field10C) = 3600;
        }
    }
}

#undef HELD_BUTTON
#undef SELECTED_VALUE
#undef PROGRESS_ARRAY
