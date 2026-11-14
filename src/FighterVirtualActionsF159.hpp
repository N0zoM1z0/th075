#pragma once

#include "AliceFighter.hpp"
#include "Fighter.hpp"
class FighterBaseActionsF159 : public Fighter {
public:
    void SelectMovementAnimation();
    void ClearAuxiliaryWords();
    void ResetRound();
};

class ReimuFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
};
class MarisaFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot18();
};
class SakuyaFighterActionsF159 : public Fighter {
public:
    void ResetRound();
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
public:
    // Fields after the shared Fighter layout.
    unsigned short fieldF10;
    unsigned short fieldF12;
    unsigned short fieldF14;
    unsigned short fieldF16;
};
class PatchouliFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
};
class YoumuFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
};
class RemiliaFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
};
class YuyukoFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
};
class YukariFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
};
class SuikaFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
};
class MeilingFighterActionsF159 {
public:
    void ForwardBaseAction();
    void NoOpSlot9();
    void NoOpSlot18();
};

class RoundResetInputCountsF159 {
public:
    void ClearHeldCounts();
};
class RoundResetEffectsF159 {
public:
    void DeleteFourLists();
};
