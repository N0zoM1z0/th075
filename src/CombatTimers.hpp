#ifndef TH075_COMBAT_TIMERS_HPP
#define TH075_COMBAT_TIMERS_HPP
#include "BattleFrame.hpp"
// Partial interfaces used only on existing actor receivers.
class CombatTimerActor {
public:
    bool IsState150To199();
    void PlaySharedSound(short sound);
};
extern float g_CombatViewOffsetX;
extern float g_CombatViewSpan;
extern float g_CombatViewOffsetY;
#endif
