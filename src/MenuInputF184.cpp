// Two independent call-only scene views; their full layouts are unknown.
#include "MenuInputF184.hpp"
#include "SelectionInput4388D0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void TitleMenuInputF184::PollMenuInput()
{
    FIELD(int, 0x14) = 0;
    FIELD(int, 0x18) = 0;
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappingAt00671638.UpdateHeldCounts();
    g_InputMappingAt00671680.UpdateHeldCounts();
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    if (g_HeldInputAt00671664.counts[1] == 1 || g_HeldInputAt006716AC.counts[1] == 1)
        FIELD(int, 0x18) = 1;
    if (g_HeldInputAt00671664.counts[1] == -1 || g_HeldInputAt006716AC.counts[1] == -1)
        FIELD(int, 0x18) = -1;
    if (g_InputMappingAt00671638.IsKeyDown(1))
        FIELD(int, 0x1C)++;
    else
        FIELD(int, 0x1C) = 0;
}

void ReplayMenuInputF184::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    FIELD(signed char, 0x15) = 0;
    FIELD(signed char, 0x16) = 0;
    FIELD(signed char, 0x17) = 0;
    FIELD(signed char, 0x18) = 0;
    g_InputMappingAt00671638.UpdateHeldCounts();
    g_InputMappingAt00671680.UpdateHeldCounts();
    if (g_HeldInputAt00671664.counts[1] == 1 || g_HeldInputAt006716AC.counts[1] == 1)
        FIELD(signed char, 0x16) = 1;
    if (g_HeldInputAt00671664.counts[1] == -1 || g_HeldInputAt006716AC.counts[1] == -1)
        FIELD(signed char, 0x16) = -1;
    if (g_HeldInputAt00671664.counts[0] == 1 || g_HeldInputAt006716AC.counts[0] == 1)
        FIELD(signed char, 0x15) = 1;
    if (g_HeldInputAt00671664.counts[0] == -1 || g_HeldInputAt006716AC.counts[0] == -1)
        FIELD(signed char, 0x15) = -1;
    if (g_HeldInputAt00671664.counts[2] == 1 || g_HeldInputAt006716AC.counts[2] == 1)
        FIELD(signed char, 0x17) = 1;
    if (g_HeldInputAt00671664.counts[3] == 1 || g_HeldInputAt006716AC.counts[3] == 1)
        FIELD(signed char, 0x18) = 1;
    if (g_InputMappingAt00671638.IsKeyDown(1))
        FIELD(signed char, 0x18) = 1;
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
}

#undef FIELD
