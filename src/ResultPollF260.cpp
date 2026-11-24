#include "SelectionInput4388D0.hpp"
#include "GraphicsDevice.hpp"
#include "InputJoystick.hpp"
#include <windows.h>
#include "ResultListScene.hpp"

// Only borrowed physical input interfaces are exposed: the original
// input frames, scene layout, and notification types remain unproven.
void ResultListScene::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    horizontalInput=0;
    verticalInput=0;
    confirmInput=0;
    cancelInput=0;
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].held.counts[1]==1 || g_InputMappings[1].held.counts[1]==1)
        verticalInput=1;
    if (g_InputMappings[0].held.counts[1]==-1 || g_InputMappings[1].held.counts[1]==-1)
        verticalInput=-1;
    if (g_InputMappings[0].held.counts[0]==1 || g_InputMappings[1].held.counts[0]==1)
        horizontalInput=1;
    if (g_InputMappings[0].held.counts[0]==-1 || g_InputMappings[1].held.counts[0]==-1)
        horizontalInput=-1;
    if (g_InputMappings[0].held.counts[2]==1 || g_InputMappings[1].held.counts[2]==1)
        confirmInput=1;
    if (g_InputMappings[0].held.counts[3]==1 || g_InputMappings[1].held.counts[3]==1)
        cancelInput=1;
    if (g_InputMappings[0].IsKeyDown(1))
        cancelInput=1;
    if (g_InputMappings[0].IsKeyDown(0x1c)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xb8))
            Graphics::ToggleWindowMode();
    }
}
