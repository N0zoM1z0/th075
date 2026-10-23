#ifndef TH075_CHARACTER_ACTION_DISPATCH_52D230_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_52D230_HPP

#include "ReimuActionDispatch.hpp"

// One-byte target view; the original declaration and semantic name are unknown.
extern signed char g_StateRepeatLevelAt006714D0;

// Pointer-only ABI view. Original character identity and complete owner layout
// remain unknown. Do not instantiate or embed this owner.
class CharacterAction52D230 {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
