#include "assets/ScriptResource4205F0.hpp"

ScriptResource4205F0::ScriptResource4205F0()
{
    groups.clear();
    for (int index = 0; index < 1000; ++index)
        groupIndex[index] = -1;
}

ScriptResource4205F0::~ScriptResource4205F0()
{
    groups.clear();
}
