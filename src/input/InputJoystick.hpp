#pragma once
#include "input/InputDevice.hpp"

#include "input/InputResourceClient.hpp"

namespace Input
{
bool InitializeJoysticks();
void PollJoysticks();
BOOL CALLBACK EnumerateJoystickDevice(const DIDEVICEINSTANCEA *instance, void *context);
BOOL CALLBACK ConfigureJoystickAxis(const DIDEVICEOBJECTINSTANCEA *object, void *context);
}
