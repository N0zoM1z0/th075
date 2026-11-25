#ifndef TH075_SUIKA_FIGHTER_HPP
#define TH075_SUIKA_FIGHTER_HPP
#include "battle/Fighter.hpp"

// Suika's fighter: vtable Suika ctor F309 at 0x00659E30.
// Slot overrides use the Fighter slot names; the rest are helpers.
class SuikaFighter : public Fighter {
public:
    SuikaFighter();
    void ChooseAction();
    static int actionCountdown;
    void RenderStage(signed char stage);
    virtual void Advance(); // Slot 1 at 005AEEC0.
    void SpawnTrackedEffectWithFlags(short effect, float x, float y,
                                     signed char facing, signed char layer,
                                     unsigned char flagA, unsigned char flagB,
                                     unsigned char linked);
    void ConfigureStage();
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void PollCommands();
    void AdvanceSequence();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(CharacterObject** out);
    void SelectVariant();
    void ResetRound();
    void AdvanceAuxiliary();

    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF1C - 0xF10];
    short opponentSpiritDrainFrames;  // +0xF1C
    short selfSpiritDrainMode;  // +0xF1E
    short fieldF20;
    short spellAnchorX;  // +0xF22
    short spellAnchorY;  // +0xF24
    short longRangeFrames;  // +0xF26
    short fieldF28;
    short suikaStageBannerHoldFrames;
    float stageLayerX[4];  // +0xF2C
    unsigned char unknownF3C[0xF54 - 0xF3C];
    float stageLayerY[4];  // +0xF54
    unsigned char unknownF64[0xFF4 - 0xF64];
    unsigned char stageLayerAlpha[4];  // +0xFF4
    unsigned char unknownFF8[0x1000 - 0xFF8];
};

#endif
