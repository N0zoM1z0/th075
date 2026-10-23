#ifndef TH075_CHARACTER_ACTION_DISPATCH_597660_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_597660_HPP

#include "ReimuActionDispatch.hpp"

// Pointer-only ABI view. Original character identity and complete owner layout
// remain unknown. Do not instantiate or embed this owner.
class CharacterAction597660 {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
    void EnableTransform(float x, float y, float z);
};

#endif
