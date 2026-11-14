#pragma once

#include "MeilingFighter.hpp"
#include "SuikaFighter.hpp"
#include "YukariFighter.hpp"
#include "YuyukoFighter.hpp"
#include "RemiliaFighter.hpp"
#include "YoumuFighter.hpp"
#include "PatchouliFighter.hpp"
#include "SakuyaFighter.hpp"
#include "MarisaFighter.hpp"
#include "ReimuFighter.hpp"
#include "AliceFighter.hpp"
#include "Fighter.hpp"
class FighterBaseActionsF159 : public Fighter {
public:
    void SelectMovementAnimation();
    void ClearAuxiliaryWords();
    void ResetRound();
};


class RoundResetInputCountsF159 {
public:
    void ClearHeldCounts();
};
class RoundResetEffectsF159 {
public:
    void DeleteFourLists();
};
