#ifndef TH075_YUYUKO_FIGHTER_HPP
#define TH075_YUYUKO_FIGHTER_HPP
#include "battle/Fighter.hpp"

// Yuyuko's fighter: vtable Yuyuko ctor F311 at 0x00659B80.
// Slot overrides use the Fighter slot names; the rest are helpers.
class YuyukoFighter : public Fighter {
public:
    YuyukoFighter();
    void ChooseAction();
    static int actionCountdown;
    void RenderStage(signed char stage);
    virtual void Advance(); // slot 1: partial native move-state reconstruction at 00564BE0
    void ConfigureStage();
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void PollCommands();
    void AdvanceSequence();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(CharacterObject** out);
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    short longRangeFrames;  // +0xF10
    unsigned char unknownF12[0xF14 - 0xF12];
    float stageLayerX[4];  // +0xF14
    unsigned char unknownF24[0xF3C - 0xF24];
    float stageLayerY[4];  // +0xF3C
    unsigned char unknownF4C[0xFDC - 0xF4C];
    unsigned char stageLayerAlpha[4];  // +0xFDC
    unsigned char unknownFE0[0xFE8 - 0xFE0];
};

#endif
