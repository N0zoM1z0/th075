#include "GraphicsDevice.hpp"
#include "InputJoystick.hpp"
// Three separately verified original R102/R036 complete native scene
// input policies. The true hardware fullscreen condition is pressed
// 0x1C AND (pressed 0x38 OR pressed 0xB8), not the earlier incorrect
// !0x38 AND 0xB8; all native branches and physical callbacks match.
// Complete native game input tick policies: two independent 106-byte
// scene entrypoints and a 107-byte battle-end actor-specific variant.
class KeyInputF466 {public:void Advance();unsigned char CheckPressed(int scanCode);};
class FighterInputF466 {public:void AdvanceActorInput();};
extern KeyInputF466 g_MainKeyInputAt00671638;
extern KeyInputF466 g_SecondaryKeyInputAt00671680;
extern FighterInputF466* g_ActiveFighterAt00671418;
class BattleEndInputF466 {public:void PollInput();};
class SceneTwoInputsF466 {public:void PollInput();};
class OpeningInputF466 {public:void ProcessInput();};
void BattleEndInputF466::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_MainKeyInputAt00671638.Advance();
    g_ActiveFighterAt00671418->AdvanceActorInput();
    if (g_MainKeyInputAt00671638.CheckPressed(0x1C)) {
        if (g_MainKeyInputAt00671638.CheckPressed(0x38) || g_MainKeyInputAt00671638.CheckPressed(0xB8))
            Graphics::ToggleWindowMode();
    }
}
void SceneTwoInputsF466::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_MainKeyInputAt00671638.Advance();
    g_SecondaryKeyInputAt00671680.Advance();
    if (g_MainKeyInputAt00671638.CheckPressed(0x1C)) {
        if (g_MainKeyInputAt00671638.CheckPressed(0x38) || g_MainKeyInputAt00671638.CheckPressed(0xB8))
            Graphics::ToggleWindowMode();
    }
}
void OpeningInputF466::ProcessInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_MainKeyInputAt00671638.Advance();
    g_SecondaryKeyInputAt00671680.Advance();
    if (g_MainKeyInputAt00671638.CheckPressed(0x1C)) {
        if (g_MainKeyInputAt00671638.CheckPressed(0x38) || g_MainKeyInputAt00671638.CheckPressed(0xB8))
            Graphics::ToggleWindowMode();
    }
}
