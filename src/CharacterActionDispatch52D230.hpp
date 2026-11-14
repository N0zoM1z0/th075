#ifndef TH075_CHARACTER_ACTION_DISPATCH_52D230_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_52D230_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

// One-byte target view; the original declaration and semantic name are unknown.
extern signed char g_StateRepeatLevelAt006714D0;

class CharacterAction52D230 : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
public:
    // Character-specific fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
};

#endif
