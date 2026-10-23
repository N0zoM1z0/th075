#ifndef TH075_CHARACTER_ACTION_DISPATCH_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_HPP

#include "ReimuActionDispatch.hpp"

// Pointer-only dispatch interface and shared slot-reference ABI view. Neither
// original character identity nor complete owner layout is established here.
// Do not instantiate or embed these partial owners.
class CharacterAction {
public:
    void DispatchAt004C0AD0();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
