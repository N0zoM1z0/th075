#ifndef TH075_BATTLE_FRAME_HPP
#define TH075_BATTLE_FRAME_HPP
#include "battle/BattleSessionState.hpp"
#include "battle/Fighter.hpp"
#include "battle/BattleScene.hpp"
#include "engine/GameLeafHelpers.hpp"
// Partial receiver-only interfaces. Never instantiate or embed these views.
// Slot names preserve observed indices; unused declarations do not establish
// original signatures. Only the observed parameterless slots are invoked.
class FrameActor : public Fighter {
public:
    void AdvanceGuardedState();
    void AdvancePosition();
    void UpdateCounters();
    void ChooseFrameAction();
    signed char CheckHorizontalLimits();
};
// Bounded copied value: seven observed dwords, no enclosing owner layout.
extern unsigned char g_OptionsFlagAt00671430;
#endif
