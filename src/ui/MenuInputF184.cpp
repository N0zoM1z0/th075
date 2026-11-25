#include "input/InputControl.hpp"
#include "ui/OptionsScene.hpp"
#include "ui/TitleScene.hpp"
// Two independent call-only scene views; their full layouts are unknown.
#include "ui/MenuInputF184.hpp"
#include "ui/SelectionInput4388D0.hpp"


void TitleScene::PollMenuInput()
{
    field014 = 0;
    field018 = 0;
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].IsKeyDown(0x1C)
        && (g_InputMappings[0].IsKeyDown(0x38)
            || g_InputMappings[0].IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    if (g_InputMappings[0].held.counts[InputControl::Vertical] == 1 || g_InputMappings[1].held.counts[InputControl::Vertical] == 1)
        field018 = 1;
    if (g_InputMappings[0].held.counts[InputControl::Vertical] == -1 || g_InputMappings[1].held.counts[InputControl::Vertical] == -1)
        field018 = -1;
    if (g_InputMappings[0].IsKeyDown(1))
        field01C++;
    else
        field01C = 0;
}

void OptionsScene::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    field015 = 0;
    field016 = 0;
    field017 = 0;
    field018 = 0;
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].held.counts[InputControl::Vertical] == 1 || g_InputMappings[1].held.counts[InputControl::Vertical] == 1)
        field016 = 1;
    if (g_InputMappings[0].held.counts[InputControl::Vertical] == -1 || g_InputMappings[1].held.counts[InputControl::Vertical] == -1)
        field016 = -1;
    if (g_InputMappings[0].held.counts[InputControl::Horizontal] == 1 || g_InputMappings[1].held.counts[InputControl::Horizontal] == 1)
        field015 = 1;
    if (g_InputMappings[0].held.counts[InputControl::Horizontal] == -1 || g_InputMappings[1].held.counts[InputControl::Horizontal] == -1)
        field015 = -1;
    if (g_InputMappings[0].held.counts[InputControl::ButtonA] == 1 || g_InputMappings[1].held.counts[InputControl::ButtonA] == 1)
        field017 = 1;
    if (g_InputMappings[0].held.counts[InputControl::ButtonB] == 1 || g_InputMappings[1].held.counts[InputControl::ButtonB] == 1)
        field018 = 1;
    if (g_InputMappings[0].IsKeyDown(1))
        field018 = 1;
    if (g_InputMappings[0].IsKeyDown(0x1C)
        && (g_InputMappings[0].IsKeyDown(0x38)
            || g_InputMappings[0].IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
}
