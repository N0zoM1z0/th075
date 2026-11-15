#include "SelectionInput4388D0.hpp"
#include <vector>

namespace Input { extern std::vector<DIJOYSTATE> g_JoystickStates; }

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define DEVICE field004
#define X field02C
#define Y field030
#define BUTTON(type, base, index) FIELD(type, (base) + (index) * 4)

void InputMapping4388D0::UpdateHeldCounts() {
    if (DEVICE >= 0) {
        if (Input::g_JoystickStates[DEVICE].lX < -500) {
            if (X > 0)
                X = 0;
            X = X - 1;
        } else if (Input::g_JoystickStates[DEVICE].lX > 500) {
            if (X < 0)
                X = 0;
            X = X + 1;
        } else {
            X = 0;
        }
        if (Input::g_JoystickStates[DEVICE].lY < -500) {
            if (Y > 0)
                Y = 0;
            Y = Y - 1;
        } else if (Input::g_JoystickStates[DEVICE].lY > 500) {
            if (Y < 0)
                Y = 0;
            Y = Y + 1;
        } else {
            Y = 0;
        }
        for (int joystickButton = 0; joystickButton < 5; joystickButton = joystickButton + 1) {
            if (Input::g_JoystickStates[DEVICE].rgbButtons[BUTTON(int, 0x18, joystickButton)])
                BUTTON(int, 0x34, joystickButton) = BUTTON(int, 0x34, joystickButton) + 1;
            else
                BUTTON(int, 0x34, joystickButton) = 0;
        }
    } else {
        if (Input::g_KeyboardState[field008] & 0x80) {
            if (X > 0)
                X = 0;
            X = X - 1;
        } else if (Input::g_KeyboardState[field00C] & 0x80) {
            if (X < 0)
                X = 0;
            X = X + 1;
        } else {
            X = 0;
        }
        if (Input::g_KeyboardState[field010] & 0x80) {
            if (Y > 0)
                Y = 0;
            Y = Y - 1;
        } else if (Input::g_KeyboardState[field014] & 0x80) {
            if (Y < 0)
                Y = 0;
            Y = Y + 1;
        } else {
            Y = 0;
        }
        for (int keyboardButton = 0; keyboardButton < 5; keyboardButton = keyboardButton + 1) {
            if (Input::g_KeyboardState[BUTTON(int, 0x18, keyboardButton)] & 0x80)
                BUTTON(int, 0x34, keyboardButton) = BUTTON(int, 0x34, keyboardButton) + 1;
            else
                BUTTON(int, 0x34, keyboardButton) = 0;
        }
    }
}

#undef BUTTON
#undef Y
#undef X
#undef DEVICE
#undef FIELD
