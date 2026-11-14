#ifndef TH075_CHARACTER_ACTION_DISPATCH_551C00_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_551C00_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

class CharacterAction551C00 : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
