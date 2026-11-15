#include "TitleScene.hpp"
// Two independent call-only scene views; their full layouts are unknown.
#include "MenuInputF184.hpp"
#include "SelectionInput4388D0.hpp"


void TitleScene::PollMenuInput()
{
    field014 = 0;
    field018 = 0;
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappingAt00671638.UpdateHeldCounts();
    g_InputMappingAt00671680.UpdateHeldCounts();
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    if (g_HeldInputAt00671664.counts[1] == 1 || g_HeldInputAt006716AC.counts[1] == 1)
        field018 = 1;
    if (g_HeldInputAt00671664.counts[1] == -1 || g_HeldInputAt006716AC.counts[1] == -1)
        field018 = -1;
    if (g_InputMappingAt00671638.IsKeyDown(1))
        field01C++;
    else
        field01C = 0;
}

void ReplayMenuInputF184::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    field015 = 0;
    field016 = 0;
    field017 = 0;
    field018 = 0;
    g_InputMappingAt00671638.UpdateHeldCounts();
    g_InputMappingAt00671680.UpdateHeldCounts();
    if (g_HeldInputAt00671664.counts[1] == 1 || g_HeldInputAt006716AC.counts[1] == 1)
        field016 = 1;
    if (g_HeldInputAt00671664.counts[1] == -1 || g_HeldInputAt006716AC.counts[1] == -1)
        field016 = -1;
    if (g_HeldInputAt00671664.counts[0] == 1 || g_HeldInputAt006716AC.counts[0] == 1)
        field015 = 1;
    if (g_HeldInputAt00671664.counts[0] == -1 || g_HeldInputAt006716AC.counts[0] == -1)
        field015 = -1;
    if (g_HeldInputAt00671664.counts[2] == 1 || g_HeldInputAt006716AC.counts[2] == 1)
        field017 = 1;
    if (g_HeldInputAt00671664.counts[3] == 1 || g_HeldInputAt006716AC.counts[3] == 1)
        field018 = 1;
    if (g_InputMappingAt00671638.IsKeyDown(1))
        field018 = 1;
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
}
