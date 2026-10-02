// Compiler-origin fixtures only; these bodies grant no authored exact credit.
#include "InputDevice.hpp"
#include <string>
#include <vector>
#include <new>

void ProbeCompilerStringParameter(std::string value)
{
    std::vector<unsigned int> lengths;
    lengths.push_back(value.size());
}

void ProbeCompilerPlacementCleanup(void *memory, const std::string &value)
{
    new (memory) std::string(value);
}
