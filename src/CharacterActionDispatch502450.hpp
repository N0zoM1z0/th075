#ifndef TH075_CHARACTER_ACTION_DISPATCH_502450_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_502450_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

class CharacterAction502450 : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
