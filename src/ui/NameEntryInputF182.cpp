#include "input/InputControl.hpp"
#include "ui/NameEntryScenes.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "engine/GameLeafHelpers.hpp"

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
        if (HELD(InputControl::Horizontal) == 1 || (HELD(InputControl::Horizontal) % 6 == 1 && HELD(InputControl::Horizontal) > 30)) {
            g_SoundBank->Play(39);
            glyphColumn++;
        }
        if (HELD(InputControl::Horizontal) == -1 || (HELD(InputControl::Horizontal) % 6 == -1 && HELD(InputControl::Horizontal) < -30)) {
            g_SoundBank->Play(39);
            glyphColumn--;
        }
        if (HELD(InputControl::Vertical) == 1 || (HELD(InputControl::Vertical) % 6 == 1 && HELD(InputControl::Vertical) > 30)) {
            g_SoundBank->Play(39);
            glyphRow++;
        }
        if (HELD(InputControl::Vertical) == -1 || (HELD(InputControl::Vertical) % 6 == -1 && HELD(InputControl::Vertical) < -30)) {
            g_SoundBank->Play(39);
            glyphRow--;
        }
        if (HELD(InputControl::Pause) == 1) {
            glyphColumn = 14;
            glyphRow = 3;
        }
    }
    if (g_InputMappings[0].held.counts[InputControl::ButtonA] == 1 || g_InputMappings[1].held.counts[InputControl::ButtonA] == 1)
        editInput = 1;
    else if (g_InputMappings[0].held.counts[InputControl::ButtonB] == 1 || g_InputMappings[1].held.counts[InputControl::ButtonB] == 1)
        editInput = 2;
    else
        editInput = 0;
    if (glyphRow < 0)
        glyphRow = 3;
    if (glyphRow > 3)
        glyphRow = 0;
    if (glyphRow < 3) {
        if (glyphColumn < 0)
            glyphColumn = 25;
        if (glyphColumn > 25)
            glyphColumn = 0;
    } else {
        if (glyphColumn < 0)
            glyphColumn = 14;
        if (glyphColumn > 14)
            glyphColumn = 14;
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
        if (HELD(InputControl::Horizontal) == 1 || (HELD(InputControl::Horizontal) % 6 == 1 && HELD(InputControl::Horizontal) > 30)) {
            g_SoundBank->Play(39);
            glyphColumn++;
            cancelChoice = 1 - cancelChoice;
        }
        if (HELD(InputControl::Horizontal) == -1 || (HELD(InputControl::Horizontal) % 6 == -1 && HELD(InputControl::Horizontal) < -30)) {
            g_SoundBank->Play(39);
            glyphColumn--;
            cancelChoice = 1 - cancelChoice;
        }
        if (HELD(InputControl::Vertical) == 1 || (HELD(InputControl::Vertical) % 6 == 1 && HELD(InputControl::Vertical) > 30)) {
            g_SoundBank->Play(39);
            glyphRow++;
        }
        if (HELD(InputControl::Vertical) == -1 || (HELD(InputControl::Vertical) % 6 == -1 && HELD(InputControl::Vertical) < -30)) {
            g_SoundBank->Play(39);
            glyphRow--;
        }
        if (HELD(InputControl::Pause) == 1) {
            glyphColumn = 14;
            glyphRow = 3;
        }
    }
    if (g_InputMappings[0].held.counts[InputControl::ButtonA] == 1 || g_InputMappings[1].held.counts[InputControl::ButtonA] == 1)
        editInput = 1;
    else if (g_InputMappings[0].held.counts[InputControl::ButtonB] == 1 || g_InputMappings[1].held.counts[InputControl::ButtonB] == 1)
        editInput = 2;
    else
        editInput = 0;
    if (glyphRow < 0)
        glyphRow = 3;
    if (glyphRow > 3)
        glyphRow = 0;
    if (glyphRow < 3) {
        if (glyphColumn < 0)
            glyphColumn = 25;
        if (glyphColumn > 25)
            glyphColumn = 0;
    } else {
        if (glyphColumn < 0)
            glyphColumn = 14;
        if (glyphColumn > 14)
            glyphColumn = 14;
    }
}

#undef HELD
