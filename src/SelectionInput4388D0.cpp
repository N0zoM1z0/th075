#include "SelectionInput4388D0.hpp"
#include "CharacterSelectScene.hpp"


void CharacterSelectScene::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappingAt00671638.UpdateHeldCounts();
    (input[0]) = *reinterpret_cast<SelectInputFrame*>(&g_HeldInputAt00671664);
    if (g_CombatMode != 3) {
        g_InputMappingAt00671680.UpdateHeldCounts();
        (input[1]) = *reinterpret_cast<SelectInputFrame*>(&g_HeldInputAt006716AC);
    }
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    if ((g_CombatMode == 5 || g_CombatMode == 1 || g_CombatMode == 3)
        && (playerState[g_SelectActiveSideAt006714B8]) >= 4) {
        memcpy(&input[1 - g_SelectActiveSideAt006714B8], &input[g_SelectActiveSideAt006714B8], sizeof(SelectInputFrame));
        memset(&input[g_SelectActiveSideAt006714B8], 0, sizeof(SelectInputFrame));
    }
    if (g_InputMappingAt00671638.IsKeyDown(1))
        cancellationRequested = cancellationRequested + 1;
    else
        cancellationRequested = 0;
}

bool InputMapping4388D0::IsKeyDown(unsigned char key) {
    if (Input::g_KeyboardState[key] & 0x80)
        return true;
    else
        return false;
}
