#include "ui/SelectionInput4388D0.hpp"
#include <vector>

namespace Input { extern std::vector<DIJOYSTATE> g_JoystickStates; }


void InputMapping4388D0::UpdateHeldCounts() {
    if (keys.device >= 0) {
        if (Input::g_JoystickStates[keys.device].lX < -500) {
            if (held.counts[0] > 0)
                held.counts[0] = 0;
            held.counts[0] = held.counts[0] - 1;
        } else if (Input::g_JoystickStates[keys.device].lX > 500) {
            if (held.counts[0] < 0)
                held.counts[0] = 0;
            held.counts[0] = held.counts[0] + 1;
        } else {
            held.counts[0] = 0;
        }
        if (Input::g_JoystickStates[keys.device].lY < -500) {
            if (held.counts[1] > 0)
                held.counts[1] = 0;
            held.counts[1] = held.counts[1] - 1;
        } else if (Input::g_JoystickStates[keys.device].lY > 500) {
            if (held.counts[1] < 0)
                held.counts[1] = 0;
            held.counts[1] = held.counts[1] + 1;
        } else {
            held.counts[1] = 0;
        }
        for (int joystickButton = 0; joystickButton < 5; joystickButton = joystickButton + 1) {
            if (Input::g_JoystickStates[keys.device].rgbButtons[keys.buttons[joystickButton]])
                held.counts[2 + joystickButton] = held.counts[2 + joystickButton] + 1;
            else
                held.counts[2 + joystickButton] = 0;
        }
    } else {
        if (Input::g_KeyboardState[keys.left] & 0x80) {
            if (held.counts[0] > 0)
                held.counts[0] = 0;
            held.counts[0] = held.counts[0] - 1;
        } else if (Input::g_KeyboardState[keys.right] & 0x80) {
            if (held.counts[0] < 0)
                held.counts[0] = 0;
            held.counts[0] = held.counts[0] + 1;
        } else {
            held.counts[0] = 0;
        }
        if (Input::g_KeyboardState[keys.up] & 0x80) {
            if (held.counts[1] > 0)
                held.counts[1] = 0;
            held.counts[1] = held.counts[1] - 1;
        } else if (Input::g_KeyboardState[keys.down] & 0x80) {
            if (held.counts[1] < 0)
                held.counts[1] = 0;
            held.counts[1] = held.counts[1] + 1;
        } else {
            held.counts[1] = 0;
        }
        for (int keyboardButton = 0; keyboardButton < 5; keyboardButton = keyboardButton + 1) {
            if (Input::g_KeyboardState[keys.buttons[keyboardButton]] & 0x80)
                held.counts[2 + keyboardButton] = held.counts[2 + keyboardButton] + 1;
            else
                held.counts[2 + keyboardButton] = 0;
        }
    }
}
