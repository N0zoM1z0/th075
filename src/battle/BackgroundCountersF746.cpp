#include "battle/BackgroundStages.hpp"

void BackgroundBG05bF377::Advance() {
    --field68;
    if (field68 < 0) field68 = 0xF00;
    ++field6C;
    if (field6C >= 42) field6C = 0;
    ++field70;
}
