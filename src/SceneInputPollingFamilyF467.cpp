#include "MusicRoomScene.hpp"
#include "BattleEndScene.hpp"
#include "SequenceScenes.hpp"
#include "PlayerState.hpp"
#include "Fighter.hpp"
#include "SelectionInput4388D0.hpp"
#include "GraphicsDevice.hpp"
#include "InputJoystick.hpp"
// Three separately verified original R102/R036 complete native scene
// input policies. The true hardware fullscreen condition is pressed
// 0x1C AND (pressed 0x38 OR pressed 0xB8), not the earlier incorrect
// !0x38 AND 0xB8; all native branches and physical callbacks match.
// Complete native game input tick policies: two independent 106-byte
// scene entrypoints and a 107-byte battle-end actor-specific variant.
void BattleEndScene::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_BattleFightersAt00671418[0]->UpdateControls();
    if (g_InputMappings[0].IsKeyDown(0x1C)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xB8))
            Graphics::ToggleWindowMode();
    }
}
void MusicRoomScene::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].IsKeyDown(0x1C)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xB8))
            Graphics::ToggleWindowMode();
    }
}
void OpeningScene::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].IsKeyDown(0x1C)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xB8))
            Graphics::ToggleWindowMode();
    }
}
