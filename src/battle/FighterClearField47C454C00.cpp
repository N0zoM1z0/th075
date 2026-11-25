#include "battle/Fighter.hpp"

// Native leaf at 00454C00: clear the command-selection state word.
void Fighter::ClearField47CAt00454C00()
{
    spriteHistoryRetentionFrames = 0;
}
