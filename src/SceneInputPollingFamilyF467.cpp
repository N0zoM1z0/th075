#include "SelectionInput4388D0.hpp"
#include "GraphicsDevice.hpp"
#include "InputJoystick.hpp"
// Three separately verified original R102/R036 complete native scene
// input policies. The true hardware fullscreen condition is pressed
// 0x1C AND (pressed 0x38 OR pressed 0xB8), not the earlier incorrect
// !0x38 AND 0xB8; all native branches and physical callbacks match.
// Complete native game input tick policies: two independent 106-byte
// scene entrypoints and a 107-byte battle-end actor-specific variant.
class FighterInputF466 {public:void AdvanceActorInput();};
extern FighterInputF466* g_ActiveFighterAt00671418;
class BattleEndInputF466 {public:void PollInput();};
class SceneTwoInputsF466 {public:void PollInput();};
class OpeningInputF466 {public:void ProcessInput();};
void BattleEndInputF466::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_ActiveFighterAt00671418->AdvanceActorInput();
    if (g_InputMappings[0].IsKeyDown(0x1C)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xB8))
            Graphics::ToggleWindowMode();
    }
}
void SceneTwoInputsF466::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].IsKeyDown(0x1C)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xB8))
            Graphics::ToggleWindowMode();
    }
}
void OpeningInputF466::ProcessInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].IsKeyDown(0x1C)) {
        if (g_InputMappings[0].IsKeyDown(0x38) || g_InputMappings[0].IsKeyDown(0xB8))
            Graphics::ToggleWindowMode();
    }
}
