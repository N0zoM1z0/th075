#include "battle/CombatMode.hpp"
#include "engine/GameSharedState.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "ui/CharacterSelectScene.hpp"


void CharacterSelectScene::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    (input[0]) = *reinterpret_cast<SelectInputFrame*>(&g_InputMappings[0].held);
    if (g_CombatMode != CombatMode::Story) {
        g_InputMappings[1].UpdateHeldCounts();
        (input[1]) = *reinterpret_cast<SelectInputFrame*>(&g_InputMappings[1].held);
    }
    if (g_InputMappings[0].IsKeyDown(0x1C)
        && (g_InputMappings[0].IsKeyDown(0x38)
            || g_InputMappings[0].IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    if ((g_CombatMode == CombatMode::Practice || g_CombatMode == CombatMode::DuelCpu || g_CombatMode == CombatMode::Story)
        && (playerState[g_SelectedSideAt006714B8]) >= 4) {
        memcpy(&input[1 - g_SelectedSideAt006714B8], &input[g_SelectedSideAt006714B8], sizeof(SelectInputFrame));
        memset(&input[g_SelectedSideAt006714B8], 0, sizeof(SelectInputFrame));
    }
    if (g_InputMappings[0].IsKeyDown(1))
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
