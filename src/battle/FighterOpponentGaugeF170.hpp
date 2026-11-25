#pragma once

#include "battle/Fighter.hpp"
class FighterOpponentGaugeF170 : public Fighter {
public:
    void ApplyOpponentGaugeChange(short base, short multiplier, short count);
};
