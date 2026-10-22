#ifndef TH075_BATTLE_FRAME_HPP
#define TH075_BATTLE_FRAME_HPP
#include "BattleActiveCollision.hpp"
#include "GameLeafHelpers.hpp"
// Partial receiver-only interfaces. Never instantiate or embed these views.
// Slot names preserve observed indices; unused declarations do not establish
// original signatures. Only the observed parameterless slots are invoked.
class FrameActor {
public:
    virtual void Slot0();
    virtual void Advance();
    virtual void Slot2(); virtual void Slot3(); virtual void Slot4();
    virtual void Slot5(); virtual void Slot6(); virtual void Slot7();
    virtual void Slot8(); virtual void Slot9(); virtual void Slot10();
    virtual void Slot11(); virtual void Slot12(); virtual void Slot13();
    virtual void Slot14(); virtual void Slot15();
    virtual void AdvanceMode7();
    virtual void Slot17(); virtual void Slot18();
    virtual void FinishFrame();
    void AdvanceGuardedState();
    void AdvancePosition();
    void UpdateCounters();
    void ChooseAction();
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
