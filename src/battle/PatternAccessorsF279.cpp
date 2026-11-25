#include "assets/ScriptResource4205F0.hpp"

signed char ScriptResource4205F0::GetCommand(short sequence, short entry)
{
    return static_cast<signed char>(groups.at(groupIndex[sequence]).records.at(entry).command);
}

short ScriptResource4205F0::GetArgument(short sequence, short entry)
{
    return groups.at(groupIndex[sequence]).records.at(entry).argument;
}

char* ScriptResource4205F0::GetDialogueText(short sequence, short entry)
{
    return groups.at(groupIndex[sequence]).records.at(entry).dialogue;
}
