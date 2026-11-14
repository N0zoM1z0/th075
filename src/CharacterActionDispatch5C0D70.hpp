#ifndef TH075_CHARACTER_ACTION_DISPATCH_5C0D70_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_5C0D70_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

class CharacterAction5C0D70 : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
