#include "Fighter.hpp"
#pragma once

class FighterOpponentGaugeF170 : public Fighter {
public:
    void ApplyOpponentGaugeChange(short base, short multiplier, short count);
};
