#include "ScriptResource4205F0.hpp"

signed char ScriptResource4205F0::GetByteField(short sequence, short entry)
{
    return static_cast<signed char>(groups.at(groupIndex[sequence]).records.at(entry).kind);
}

short ScriptResource4205F0::GetWordField(short sequence, short entry)
{
    return groups.at(groupIndex[sequence]).records.at(entry).value;
}

void* ScriptResource4205F0::GetDwordField(short sequence, short entry)
{
    return groups.at(groupIndex[sequence]).records.at(entry).text;
}
