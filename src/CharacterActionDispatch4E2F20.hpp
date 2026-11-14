#ifndef TH075_CHARACTER_ACTION_DISPATCH_4E2F20_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_4E2F20_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

class CharacterAction4E2F20 : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
public:
    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF12 - 0xF10];
    short fieldF12;
};

#endif
