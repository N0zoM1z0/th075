#pragma once
#include "InputDevice.hpp"

// This count-only interface does not establish the complete object layout.
// Do not instantiate or embed this reconstructed owner.
class InputResourceClient
{
public:
    InputResourceClient();
    ~InputResourceClient();
};

namespace Input
{
bool InitializeJoysticks();
void PollJoysticks();
BOOL CALLBACK EnumerateJoystickDevice(const DIDEVICEINSTANCEA *instance, void *context);
BOOL CALLBACK ConfigureJoystickAxis(const DIDEVICEOBJECTINSTANCEA *object, void *context);
}
