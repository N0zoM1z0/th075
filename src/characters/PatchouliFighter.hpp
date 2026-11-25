#ifndef TH075_PATCHOULI_FIGHTER_HPP
#define TH075_PATCHOULI_FIGHTER_HPP
#include "battle/Fighter.hpp"

// Patchouli's fighter: vtable Patchouli ctor F309 at 0x00659768.
// Slot overrides use the Fighter slot names; the rest are helpers.
class PatchouliFighter : public Fighter {
public:
    PatchouliFighter();
    virtual void Advance(); // Slot 1 at 004F7130.
    void ConfigureStage();
    void ChooseAction();
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void PollCommands();
    void AdvanceSequence();
    void RenderStage(signed char stage);
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(CharacterObject** out);
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    float stageLayerX[4];  // +0xF14
    unsigned char unknownF24[0xF3C - 0xF24];
    float stageLayerY[4];  // +0xF3C
    unsigned char unknownF4C[0xFDC - 0xF4C];
    unsigned char stageLayerAlpha[4];  // +0xFDC
    unsigned char unknownFE0[0xFE8 - 0xFE0];
};

#endif
