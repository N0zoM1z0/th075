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
class FrameEffectOwner { public: void AdvanceAll(); };
class FrameAuxEffects { public: void AdvanceAndPrune(); };
class BattleFrame {
public:
    virtual void Slot0(); virtual void Slot1(); virtual void OnFrameStart();
    short UpdateFrame();
    void PollPauseShortcut();
    void UpdatePlayerEffects();
    void ApplySequence();
    void ResolveBodySeparation();
    void ResolveRoundEndMode();
    void UpdatePlayerCounters();
    void Present();
    short AdvanceState();
    void HandlePauseMenu();
    void ResolveSpecialRoundEnd();
    void ResolveNormalRoundEnd();
};
// Bounded copied value: seven observed dwords, no enclosing owner layout.
struct FrameInputSnapshot { unsigned long words[7]; };
extern signed char g_FrameClockMode;
extern unsigned char g_FramePresentToggle;
extern unsigned char g_FramePresentEveryTick;
#endif
