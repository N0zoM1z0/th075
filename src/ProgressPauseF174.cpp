#include "ProgressPauseF174.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"
#include "FighterVirtualActionsF159.hpp"

// Existing unsigned byte view, written from the observed scene pause byte.
extern unsigned char g_RenderByte0067161C;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define PROGRESS_ARRAY(type, offset) reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + FIELD(signed char, 0x16AC4) * 0x17F0 + (offset))
#define SELECTED_VALUE(offset) (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + FIELD(signed char, 0x16AC4) * 0x17F0 + (offset) + FIELD(signed char, 0x16AC5) * 0x5FC))
#define PLAYER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char**>(reinterpret_cast<unsigned char*>(this) + 0x44)[i] + (offset)))
#define CONTROL_PLAYER reinterpret_cast<FighterControlCallsF174*>(reinterpret_cast<unsigned char**>(reinterpret_cast<unsigned char*>(this) + 0x44)[i])
#define BASE_PLAYER reinterpret_cast<FighterBaseActionsF159*>(reinterpret_cast<unsigned char**>(reinterpret_cast<unsigned char*>(this) + 0x44)[i])
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

void BattleInputF174::PollPauseShortcut()
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
        FIELD(int, 0x114)++;
    else
        FIELD(int, 0x114) = 0;
    if ((FIELD(int, 0x114) == 3
            || g_HeldInputAt00671664.counts[6] == 1
            || g_HeldInputAt006716AC.counts[6] == 1)
        && FIELD(signed char, 0x18) != 5
        && FIELD(signed char, 0x18) != 0
        && FIELD(signed char, 0x18) != 7
        && g_CombatMode != 6) {
        FIELD(unsigned char, 0xA0) = static_cast<int>(!FIELD(unsigned char, 0xA0));
        if (FIELD(unsigned char, 0xA0) != 0)
            FIELD(unsigned char, 0x118) = 0;
        g_SoundBank->Play(48);
    }
    g_RenderByte0067161C = FIELD(unsigned char, 0xA0);
}

void BattleInputF174::UpdatePlayerEffects()
{
    int i;
    int j;
    for (i = 0; i < 2; i++) {
        CONTROL_PLAYER->UpdateControls();
        if (FIELD(signed char, 0x18) != 1) {
            PLAYER(int, 0x4E8) = 0;
            PLAYER(int, 0x4EC) = 0;
            PLAYER(int, 0x4F0) = 0;
            BASE_PLAYER->ClearAuxiliaryWords();
            if (FIELD(signed char, 0x18) == 13
                || FIELD(signed char, 0x18) == 11
                || FIELD(signed char, 0x18) == 10
                || FIELD(signed char, 0x18) == 3
                || FIELD(signed char, 0x18) == 2
                || FIELD(signed char, 0x18) == 0
                || FIELD(signed char, 0x18) == 5
                || FIELD(signed char, 0x18) == 7) {
                PLAYER(int, 0x4F4) = 0;
                PLAYER(int, 0x4DC) = 0;
                PLAYER(int, 0x4E0) = 0;
                CONTROL_PLAYER->PackDirectionBits();
                PLAYER(unsigned char, 0x511) = 0;
            }
            if (PLAYER(unsigned char, 0x511) >= 10
                || PLAYER(signed char, 0x2CD) != 0)
                PLAYER(unsigned char, 0x511) = 0;
        }
        for (j = 0; j < 5; j++) {
            if (HELD_BUTTON != 0)
                FIELD(int, 0x10C) = 3600;
        }
    }
}

#undef HELD_BUTTON
#undef BASE_PLAYER
#undef CONTROL_PLAYER
#undef PLAYER
#undef SELECTED_VALUE
#undef PROGRESS_ARRAY
#undef FIELD
