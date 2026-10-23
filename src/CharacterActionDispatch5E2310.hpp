#ifndef TH075_CHARACTER_ACTION_DISPATCH_5E2310_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_5E2310_HPP

#include "ReimuActionDispatch.hpp"

// Pointer-only ABI view. Original character identity and complete owner layout
// remain unknown. Do not instantiate or embed this owner.
class CharacterAction5E2310 {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
