#pragma once
#include "InputDevice.hpp"

#include "InputResourceClient.hpp"

namespace Input
{
bool InitializeJoysticks();
void PollJoysticks();
BOOL CALLBACK EnumerateJoystickDevice(const DIDEVICEINSTANCEA *instance, void *context);
BOOL CALLBACK ConfigureJoystickAxis(const DIDEVICEOBJECTINSTANCEA *object, void *context);
}
