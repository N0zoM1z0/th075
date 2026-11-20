#ifndef TH075_BATTLE_FRAME_HPP
#define TH075_BATTLE_FRAME_HPP
#include "Fighter.hpp"
#include "BattleScene.hpp"
#include "GameLeafHelpers.hpp"
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
class FrameAuxEffects { public: void AdvanceAndPrune(); };
// Bounded copied value: seven observed dwords, no enclosing owner layout.
extern signed char g_FrameClockMode;
extern unsigned char g_FramePresentToggle;
extern unsigned char g_FramePresentEveryTick;
#endif
