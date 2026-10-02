#include "InputDevice.hpp"
#include <string.h>

namespace Input
{
    extern HWND g_Window;
    extern HINSTANCE g_Instance;
    extern IDirectInput8A *g_DirectInput;
    extern IDirectInputDevice8A *g_Keyboard;
    extern unsigned char g_KeyboardState[256];
    extern const char g_CreateDirectInputError[];
    extern const char g_CreateKeyboardError[];
    extern const char g_KeyboardFormatError[];
    extern const char g_KeyboardCooperativeLevelError[];

    bool Initialize(HWND window, HINSTANCE instance)
    {
        g_Window = window;
        g_Instance = instance;
        if (g_DirectInput) return true;
        HRESULT result = DirectInput8Create(g_Instance, DIRECTINPUT_VERSION,
            IID_IDirectInput8A, reinterpret_cast<void **>(&g_DirectInput), 0);
        if (FAILED(result))
        {
            ShowError(g_CreateDirectInputError);
            return false;
        }
        return true;
    }

    bool CreateKeyboard()
    {
        if (g_Keyboard) return true;
        HRESULT result = g_DirectInput->CreateDevice(GUID_SysKeyboard,
            &g_Keyboard, 0);
        if (FAILED(result))
        {
            ShowError(g_CreateKeyboardError);
            return false;
        }
        result = g_Keyboard->SetDataFormat(&c_dfDIKeyboard);
        if (FAILED(result))
        {
            ShowError(g_KeyboardFormatError);
            return false;
        }
        result = g_Keyboard->SetCooperativeLevel(g_Window,
            DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY);
        if (FAILED(result))
        {
            ShowError(g_KeyboardCooperativeLevelError);
            return false;
        }
        g_Keyboard->Acquire();
        return true;
    }

    void PollKeyboard()
    {
        if (g_Keyboard)
        {
            HRESULT result = g_Keyboard->GetDeviceState(sizeof(g_KeyboardState),
                g_KeyboardState);
            if (FAILED(result))
            {
                g_Keyboard->Acquire();
                memset(g_KeyboardState, 0, sizeof(g_KeyboardState));
            }
        }
    }
}
