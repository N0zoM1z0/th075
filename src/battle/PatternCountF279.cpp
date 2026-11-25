#include "assets/ScriptResource4205F0.hpp"

short ScriptResource4205F0::CountCommands(short sequence)
{
    if (groupIndex[sequence] < 0)
        return 0;
    return static_cast<short>(groups.at(groupIndex[sequence]).records.size());
}
