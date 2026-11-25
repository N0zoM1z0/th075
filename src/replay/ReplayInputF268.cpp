#include "input/InputControl.hpp"
#include "replay/ReplayBrowserScene.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "graphics/GraphicsDevice.hpp"
#include "input/InputJoystick.hpp"
#include <windows.h>

void ReplayBrowserScene::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    field04D=0;
    field04E=0;
    field04F=0;
    field050=0;
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].held.counts[InputControl::Vertical]==1 || g_InputMappings[1].held.counts[InputControl::Vertical]==1)
        field04E=1;
    if (g_InputMappings[0].held.counts[InputControl::Vertical]==-1 || g_InputMappings[1].held.counts[InputControl::Vertical]==-1)
        field04E=-1;
    if (g_InputMappings[0].held.counts[InputControl::Horizontal]==1 || g_InputMappings[1].held.counts[InputControl::Horizontal]==1)
        field04D=1;
    if (g_InputMappings[0].held.counts[InputControl::Horizontal]==-1 || g_InputMappings[1].held.counts[InputControl::Horizontal]==-1)
        field04D=-1;
    if (g_InputMappings[0].held.counts[InputControl::ButtonA]==1 || g_InputMappings[1].held.counts[InputControl::ButtonA]==1)
        field04F=1;
    if (g_InputMappings[0].held.counts[InputControl::ButtonB]==1 || g_InputMappings[1].held.counts[InputControl::ButtonB]==1)
        field050=1;
    if (g_InputMappings[0].IsKeyDown(1))
        field050=1;
    if (g_InputMappings[0].IsKeyDown(0x1c)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xb8))
            Graphics::ToggleWindowMode();
    }
}
