#ifndef TH075_FIGHTER_MOVE_SCALAR_HELPERS_HPP
#define TH075_FIGHTER_MOVE_SCALAR_HELPERS_HPP

#include "Fighter.hpp"
class FighterMoveScalarHelpers : public Fighter {
public:
    void SetNonnegativeWord(short value);
    void BeginFadeParameters(unsigned char mode);
};

#endif
