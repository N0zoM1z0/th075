#include "battle/Fighter.hpp"

void Fighter::SetNoticeMode(unsigned char mode)
{
    sequencePhase = static_cast<signed char>(mode);
}
