#ifndef TH075_CHARACTER_ACTION_DISPATCH_597660_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_597660_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

class CharacterAction597660 : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
    void EnableTransform(float x, float y, float z);
public:
    // Character-specific fields after the shared Fighter layout.
    short fieldF10;
};

#endif
