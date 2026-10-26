#include "NameEntryInputF182.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define HELD(button) reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&g_HeldInputAt00671664) + i * 0x48)[button]

void NameEntryInputF182::PollPlayerInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappingAt00671638.UpdateHeldCounts();
    g_InputMappingAt00671680.UpdateHeldCounts();
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    for (int i = 0; i < 2; i++) {
        if (HELD(0) == 1 || (HELD(0) % 6 == 1 && HELD(0) > 30)) {
            g_SoundBank->Play(39);
            FIELD(short, 0x10)++;
        }
        if (HELD(0) == -1 || (HELD(0) % 6 == -1 && HELD(0) < -30)) {
            g_SoundBank->Play(39);
            FIELD(short, 0x10)--;
        }
        if (HELD(1) == 1 || (HELD(1) % 6 == 1 && HELD(1) > 30)) {
            g_SoundBank->Play(39);
            FIELD(short, 0x12)++;
        }
        if (HELD(1) == -1 || (HELD(1) % 6 == -1 && HELD(1) < -30)) {
            g_SoundBank->Play(39);
            FIELD(short, 0x12)--;
        }
        if (HELD(6) == 1) {
            FIELD(short, 0x10) = 14;
            FIELD(short, 0x12) = 3;
        }
    }
    if (g_HeldInputAt00671664.counts[2] == 1 || g_HeldInputAt006716AC.counts[2] == 1)
        FIELD(short, 0x16) = 1;
    else if (g_HeldInputAt00671664.counts[3] == 1 || g_HeldInputAt006716AC.counts[3] == 1)
        FIELD(short, 0x16) = 2;
    else
        FIELD(short, 0x16) = 0;
    if (FIELD(short, 0x12) < 0)
        FIELD(short, 0x12) = 3;
    if (FIELD(short, 0x12) > 3)
        FIELD(short, 0x12) = 0;
    if (FIELD(short, 0x12) < 3) {
        if (FIELD(short, 0x10) < 0)
            FIELD(short, 0x10) = 25;
        if (FIELD(short, 0x10) > 25)
            FIELD(short, 0x10) = 0;
    } else {
        if (FIELD(short, 0x10) < 0)
            FIELD(short, 0x10) = 14;
        if (FIELD(short, 0x10) > 14)
            FIELD(short, 0x10) = 14;
    }
}

void NameEntryInputF182::PollSharedInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappingAt00671638.UpdateHeldCounts();
    g_InputMappingAt00671680.UpdateHeldCounts();
    if (g_InputMappingAt00671638.IsKeyDown(0x1C)
        && (g_InputMappingAt00671638.IsKeyDown(0x38)
            || g_InputMappingAt00671638.IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    for (int i = 0; i < 2; i++) {
        if (HELD(0) == 1 || (HELD(0) % 6 == 1 && HELD(0) > 30)) {
            g_SoundBank->Play(39);
            FIELD(short, 0x0E)++;
            FIELD(short, 0x14) = 1 - FIELD(short, 0x14);
        }
        if (HELD(0) == -1 || (HELD(0) % 6 == -1 && HELD(0) < -30)) {
            g_SoundBank->Play(39);
            FIELD(short, 0x0E)--;
            FIELD(short, 0x14) = 1 - FIELD(short, 0x14);
        }
        if (HELD(1) == 1 || (HELD(1) % 6 == 1 && HELD(1) > 30)) {
            g_SoundBank->Play(39);
            FIELD(short, 0x10)++;
        }
        if (HELD(1) == -1 || (HELD(1) % 6 == -1 && HELD(1) < -30)) {
            g_SoundBank->Play(39);
            FIELD(short, 0x10)--;
        }
        if (HELD(6) == 1) {
            FIELD(short, 0x0E) = 14;
            FIELD(short, 0x10) = 3;
        }
    }
    if (g_HeldInputAt00671664.counts[2] == 1 || g_HeldInputAt006716AC.counts[2] == 1)
        FIELD(short, 0x16) = 1;
    else if (g_HeldInputAt00671664.counts[3] == 1 || g_HeldInputAt006716AC.counts[3] == 1)
        FIELD(short, 0x16) = 2;
    else
        FIELD(short, 0x16) = 0;
    if (FIELD(short, 0x10) < 0)
        FIELD(short, 0x10) = 3;
    if (FIELD(short, 0x10) > 3)
        FIELD(short, 0x10) = 0;
    if (FIELD(short, 0x10) < 3) {
        if (FIELD(short, 0x0E) < 0)
            FIELD(short, 0x0E) = 25;
        if (FIELD(short, 0x0E) > 25)
            FIELD(short, 0x0E) = 0;
    } else {
        if (FIELD(short, 0x0E) < 0)
            FIELD(short, 0x0E) = 14;
        if (FIELD(short, 0x0E) > 14)
            FIELD(short, 0x0E) = 14;
    }
}

#undef HELD
#undef FIELD
