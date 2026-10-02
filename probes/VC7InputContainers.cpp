// Origin evidence only. These vendor instantiations earn no authored exact credit.
#include "InputDevice.hpp"
#include <vector>

extern std::vector<IDirectInputDevice8A *> devices;
extern std::vector<DIJOYSTATE> states;

void ProbeContainers(unsigned int index, IDirectInputDevice8A *device, DIJOYSTATE state)
{
    devices.size(); devices.capacity(); devices.empty();
    devices.begin(); devices.end(); devices[index]; devices.back();
    devices.push_back(device); devices.pop_back(); devices.clear();
    states[index]; states.begin(); states.assign(index, state); states.clear();
}
