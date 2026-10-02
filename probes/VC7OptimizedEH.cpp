// Ordinary optimized allocation fixtures; origin evidence only.
#include "InputDevice.hpp"
#include <string>

std::string *ProbeCompilerAllocateString(const std::string &value)
{
    return new std::string(value);
}

std::string *ProbeCompilerSelectString(const std::string *value, int selector)
{
    if (selector != 0)
        return new std::string(*value);
    return new std::string(10, 'x');
}
