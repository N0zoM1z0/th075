#ifndef TH075_CHARACTER_ACTION_DISPATCH_574370_HPP
#define TH075_CHARACTER_ACTION_DISPATCH_574370_HPP

#include "Fighter.hpp"
#include "ReimuActionDispatch.hpp"

class CharacterAction574370 : public Fighter {
public:
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
};

#endif
