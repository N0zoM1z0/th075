#include "InputJoystick.hpp"
#include <vector>
#include <string.h>

extern int g_InputResourceClientCount;

namespace Input
{
    extern HWND g_Window;
    extern IDirectInput8A *g_DirectInput;
    extern IDirectInputDevice8A *g_Keyboard;
    extern std::vector<IDirectInputDevice8A *> g_Joysticks;
    extern std::vector<DIJOYSTATE> g_JoystickStates;
    extern unsigned char g_JoystickCount;
    extern const char g_EnumerateJoysticksError[];

    bool InitializeJoysticks()
    {
        if (g_DirectInput)
        {
            if (g_DirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
                EnumerateJoystickDevice, 0, DIEDFL_ATTACHEDONLY) != DI_OK)
            {
                ShowError(g_EnumerateJoysticksError);
                return false;
            }
            g_JoystickCount = static_cast<unsigned char>(g_Joysticks.size());
            DIJOYSTATE state;
            memset(&state, 0, sizeof(state));
            g_JoystickStates.assign(g_JoystickCount, state);
        }
        return true;
    }

    void PollJoysticks()
    {
        HRESULT result;
        if (g_DirectInput)
        {
            for (int index = 0; index < g_JoystickCount; ++index)
            {
                if (g_Joysticks[index])
                {
                    result = g_Joysticks[index]->Poll();
                    if (FAILED(result)) g_Joysticks[index]->Acquire();
                    g_Joysticks[index]->GetDeviceState(sizeof(DIJOYSTATE),
                        &g_JoystickStates[index]);
                }
            }
        }
    }

    BOOL CALLBACK EnumerateJoystickDevice(const DIDEVICEINSTANCEA *instance, void *context)
    {
        HRESULT result;
        if (!g_DirectInput) return DIENUM_STOP;
        else
        {
            DIDEVCAPS capabilities;
            g_Joysticks.push_back(0);
            result = g_DirectInput->CreateDevice(instance->guidInstance,
                &g_Joysticks.back(), 0);
            if (FAILED(result))
            {
                g_Joysticks.pop_back();
                return DIENUM_STOP;
            }
            g_Joysticks.back()->SetDataFormat(&c_dfDIJoystick);
            g_Joysticks.back()->SetCooperativeLevel(g_Window,
                DISCL_EXCLUSIVE | DISCL_FOREGROUND);
            capabilities.dwSize = sizeof(capabilities);
            g_Joysticks.back()->GetCapabilities(&capabilities);
            g_Joysticks.back()->EnumObjects(ConfigureJoystickAxis, 0, DIDFT_AXIS);
            return DIENUM_CONTINUE;
        }
    }

    BOOL CALLBACK ConfigureJoystickAxis(const DIDEVICEOBJECTINSTANCEA *object, void *context)
    {
        DIPROPRANGE range;
        range.diph.dwSize = sizeof(range);
        range.diph.dwHeaderSize = sizeof(range.diph);
        range.diph.dwHow = DIPH_BYID;
        range.diph.dwObj = object->dwType;
        range.lMin = -1000;
        range.lMax = 1000;
        HRESULT result = g_Joysticks.back()->SetProperty(DIPROP_RANGE, &range.diph);
        if (FAILED(result)) return DIENUM_STOP;
        return DIENUM_CONTINUE;
    }
}

InputResourceClient::InputResourceClient()
{
    if (g_InputResourceClientCount == 0)
    {
        Input::g_DirectInput = 0;
        Input::g_Keyboard = 0;
        Input::g_Joysticks.clear();
        Input::g_JoystickStates.clear();
    }
    ++g_InputResourceClientCount;
}

InputResourceClient::~InputResourceClient()
{
    if (--g_InputResourceClientCount == 0)
    {
        if (Input::g_Keyboard)
        {
            Input::g_Keyboard->Unacquire();
            Input::g_Keyboard->Release();
            Input::g_Keyboard = 0;
        }
        for (unsigned int index = 0; index < Input::g_Joysticks.size(); ++index)
        {
            if (Input::g_Joysticks[index])
            {
                Input::g_Joysticks[index]->Unacquire();
                Input::g_Joysticks[index]->Release();
                Input::g_Joysticks[index] = 0;
            }
        }
        Input::g_Joysticks.clear();
        Input::g_JoystickStates.clear();
        if (Input::g_DirectInput)
        {
            Input::g_DirectInput->Release();
            Input::g_DirectInput = 0;
        }
    }
}
