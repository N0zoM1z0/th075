#include "input/InputControl.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "graphics/GraphicsDevice.hpp"
#include "input/InputJoystick.hpp"
#include "ui/ResultScene.hpp"
// Borrowed controller entries and observed 32-bit button-state globals.
// These pointer-only receiver declarations do not instantiate full owners.
void ResultScene::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    advanceInput=0;
    field00D=0;
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].held.counts[InputControl::ButtonA]==1 || g_InputMappings[1].held.counts[InputControl::ButtonA]==1)
        advanceInput=1;
    if (g_InputMappings[0].held.counts[InputControl::ButtonB]==1 || g_InputMappings[1].held.counts[InputControl::ButtonB]==1)
        advanceInput=1;
    if (g_InputMappings[0].held.counts[InputControl::ButtonC]==1 || g_InputMappings[1].held.counts[InputControl::ButtonC]==1)
        advanceInput=1;
    if (g_InputMappings[0].held.counts[InputControl::ButtonD]==1 || g_InputMappings[1].held.counts[InputControl::ButtonD]==1)
        advanceInput=1;
    if (g_InputMappings[0].IsKeyDown(0x1c)) {
        if (g_InputMappings[0].IsKeyDown(0x38) ||
            g_InputMappings[0].IsKeyDown(0xb8))
            Graphics::ToggleWindowMode();
    }
}
