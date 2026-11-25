#include "input/InputDevice.hpp"
#include <string.h>

namespace Input
{
    HWND g_Window;
    HINSTANCE g_Instance;
    IDirectInput8A *g_DirectInput;
    IDirectInputDevice8A *g_Keyboard;
    unsigned char g_KeyboardState[256];
    extern const char g_CreateDirectInputError[] = "DirectInput" "\x83\x49\x83\x75\x83\x57\x83\x46\x83\x4e\x83\x67\x82\xcc\x8d\xec\x90\xac\x82\xc9\x8e\xb8\x94\x73";
    extern const char g_CreateKeyboardError[] = "\x83\x4c\x81\x5b\x83\x7b\x81\x5b\x83\x68\x82\xcc\x8f\x89\x8a\xfa\x89\xbb\x82\xc9\x8e\xb8\x94\x73";
    extern const char g_KeyboardFormatError[] = "\x83\x66\x81\x5b\x83\x5e\x83\x74\x83\x48\x81\x5b\x83\x7d\x83\x62\x83\x67\x82\xcc\x90\xdd\x92\xe8\x82\xc9\x8e\xb8\x94\x73";
    extern const char g_KeyboardCooperativeLevelError[] = "\x8b\xa6\x92\xb2\x83\x8c\x83\x78\x83\x8b\x82\xcc\x90\xdd\x92\xe8\x82\xc9\x8e\xb8\x94\x73";

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
