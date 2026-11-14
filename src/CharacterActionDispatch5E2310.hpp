#ifndef TH075_CHARACTER_ACTION_DISPATCH_5E2310_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_5E2310_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

class CharacterAction5E2310 : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
