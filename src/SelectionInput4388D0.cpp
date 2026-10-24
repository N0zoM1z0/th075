#include "SelectionInput4388D0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define SIDE_INPUT(side) (reinterpret_cast<char*>(this) + (side) * 28 + 12)

void SelectionInput4388D0::PollInput() {
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappingAt00671638.UpdateHeldCounts();
    FIELD(HeldInputBlock4388D0, 12) = g_HeldInputAt00671664;
    if (g_CombatMode != 3) {
        g_InputMappingAt00671680.UpdateHeldCounts();
        FIELD(HeldInputBlock4388D0, 40) = g_HeldInputAt006716AC;
    }
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    if ((g_CombatMode == 5 || g_CombatMode == 1 || g_CombatMode == 3)
        && FIELD(signed char, 0x96 + g_SelectActiveSideAt006714B8) >= 4) {
        memcpy(SIDE_INPUT(1 - g_SelectActiveSideAt006714B8), SIDE_INPUT(g_SelectActiveSideAt006714B8), 28);
        memset(SIDE_INPUT(g_SelectActiveSideAt006714B8), 0, 28);
    }
    if (g_InputMappingAt00671638.IsKeyDown(1))
        FIELD(int, 0x4C) = FIELD(int, 0x4C) + 1;
    else
        FIELD(int, 0x4C) = 0;
}

bool InputMapping4388D0::IsKeyDown(unsigned char key) {
    if (Input::g_KeyboardState[key] & 0x80)
        return true;
    else
        return false;
}

#undef SIDE_INPUT
#undef FIELD
