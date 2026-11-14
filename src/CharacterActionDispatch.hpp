#ifndef TH075_CHARACTER_ACTION_DISPATCH_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

class CharacterAction : public Fighter {
public:
    void DispatchAt004C0AD0();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
public:
    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    short fieldF14;
};

#endif
