#ifndef TH075_FIGHTER_MOVE_SCALAR_HELPERS_HPP
#define TH075_FIGHTER_MOVE_SCALAR_HELPERS_HPP

// Declaration-only receiver view. Names are provisional and the complete owner
// layout is unknown. Never instantiate, copy, allocate or embed this view.
class FighterMoveScalarHelpers {
public:
    void SetNonnegativeWord(short value);
    void BeginFadeParameters(unsigned char mode);
};

#endif
