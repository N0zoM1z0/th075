#include "CommandListF283.hpp"

CommandListF283::CommandListF283(TextureManagerF198* source)
{
    texture=source;
    capacity=15;
    mode=5;
    Reset();
}

void CommandListF283::SetCapacityAt00410FC0(short maximumEntries)
{
    capacity = maximumEntries;
}
