#ifndef TH075_CHARACTER_ACTION_DISPATCH_5C0D70_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_5C0D70_HPP

#include "ReimuActionDispatch.hpp"

// Pointer-only ABI view. Original character identity and complete owner layout
// remain unknown. Do not instantiate or embed this owner.
class CharacterAction5C0D70 {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
