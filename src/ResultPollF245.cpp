#include "SelectionInput4388D0.hpp"
#include "GraphicsDevice.hpp"
#include "InputJoystick.hpp"
#include "ResultScene.hpp"
// Borrowed controller entries and observed 32-bit button-state globals.
// These pointer-only receiver declarations do not instantiate full owners.
void ResultScene::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    field00C=0;
    field00D=0;
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].held.counts[2]==1 || g_InputMappings[1].held.counts[2]==1)
        field00C=1;
    if (g_InputMappings[0].held.counts[3]==1 || g_InputMappings[1].held.counts[3]==1)
        field00C=1;
    if (g_InputMappings[0].held.counts[4]==1 || g_InputMappings[1].held.counts[4]==1)
        field00C=1;
    if (g_InputMappings[0].held.counts[5]==1 || g_InputMappings[1].held.counts[5]==1)
        field00C=1;
    if (g_InputMappings[0].IsKeyDown(0x1c)) {
        if (g_InputMappings[0].IsKeyDown(0x38) ||
            g_InputMappings[0].IsKeyDown(0xb8))
            Graphics::ToggleWindowMode();
    }
}
