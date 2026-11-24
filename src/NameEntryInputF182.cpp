#include "NameEntryScenes.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"

#define HELD(button) g_InputMappings[i].held.counts[button]

void PlayerNameEntryScene::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].IsKeyDown(0x1C)
        && (g_InputMappings[0].IsKeyDown(0x38)
            || g_InputMappings[0].IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    for (int i = 0; i < 2; i++) {
        if (HELD(0) == 1 || (HELD(0) % 6 == 1 && HELD(0) > 30)) {
            g_SoundBank->Play(39);
            field010++;
        }
        if (HELD(0) == -1 || (HELD(0) % 6 == -1 && HELD(0) < -30)) {
            g_SoundBank->Play(39);
            field010--;
        }
        if (HELD(1) == 1 || (HELD(1) % 6 == 1 && HELD(1) > 30)) {
            g_SoundBank->Play(39);
            field012++;
        }
        if (HELD(1) == -1 || (HELD(1) % 6 == -1 && HELD(1) < -30)) {
            g_SoundBank->Play(39);
            field012--;
        }
        if (HELD(6) == 1) {
            field010 = 14;
            field012 = 3;
        }
    }
    if (g_InputMappings[0].held.counts[2] == 1 || g_InputMappings[1].held.counts[2] == 1)
        field016 = 1;
    else if (g_InputMappings[0].held.counts[3] == 1 || g_InputMappings[1].held.counts[3] == 1)
        field016 = 2;
    else
        field016 = 0;
    if (field012 < 0)
        field012 = 3;
    if (field012 > 3)
        field012 = 0;
    if (field012 < 3) {
        if (field010 < 0)
            field010 = 25;
        if (field010 > 25)
            field010 = 0;
    } else {
        if (field010 < 0)
            field010 = 14;
        if (field010 > 14)
            field010 = 14;
    }
}

void SharedNameEntryScene::PollInput()
{
    Input::PollKeyboard();
    Input::PollJoysticks();
    g_InputMappings[0].UpdateHeldCounts();
    g_InputMappings[1].UpdateHeldCounts();
    if (g_InputMappings[0].IsKeyDown(0x1C)
        && (g_InputMappings[0].IsKeyDown(0x38)
            || g_InputMappings[0].IsKeyDown(0xB8)))
        Graphics::ToggleWindowMode();
    for (int i = 0; i < 2; i++) {
        if (HELD(0) == 1 || (HELD(0) % 6 == 1 && HELD(0) > 30)) {
            g_SoundBank->Play(39);
            field00E++;
            field014 = 1 - field014;
        }
        if (HELD(0) == -1 || (HELD(0) % 6 == -1 && HELD(0) < -30)) {
            g_SoundBank->Play(39);
            field00E--;
            field014 = 1 - field014;
        }
        if (HELD(1) == 1 || (HELD(1) % 6 == 1 && HELD(1) > 30)) {
            g_SoundBank->Play(39);
            field010++;
        }
        if (HELD(1) == -1 || (HELD(1) % 6 == -1 && HELD(1) < -30)) {
            g_SoundBank->Play(39);
            field010--;
        }
        if (HELD(6) == 1) {
            field00E = 14;
            field010 = 3;
        }
    }
    if (g_InputMappings[0].held.counts[2] == 1 || g_InputMappings[1].held.counts[2] == 1)
        field016 = 1;
    else if (g_InputMappings[0].held.counts[3] == 1 || g_InputMappings[1].held.counts[3] == 1)
        field016 = 2;
    else
        field016 = 0;
    if (field010 < 0)
        field010 = 3;
    if (field010 > 3)
        field010 = 0;
    if (field010 < 3) {
        if (field00E < 0)
            field00E = 25;
        if (field00E > 25)
            field00E = 0;
    } else {
        if (field00E < 0)
            field00E = 14;
        if (field00E > 14)
            field00E = 14;
    }
}

#undef HELD
