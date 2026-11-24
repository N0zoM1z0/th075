#ifndef TH075_YUKARI_FIGHTER_HPP
#define TH075_YUKARI_FIGHTER_HPP
#include "Fighter.hpp"

// Yukari's fighter: vtable Yukari ctor F309 at 0x00659CC0.
// Slot overrides use the Fighter slot names; the rest are helpers.
class YukariFighter : public Fighter {
public:
    YukariFighter();
    void ChooseAction();
    static int actionCountdown;
    void RenderStage(signed char stage);
    virtual void Advance(); // Slot 1 at 0058AF60.
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
    void ResetBaseRound();
    void ResetRound();
    void AdvanceAuxiliary();

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    short fieldF14;
    short fieldF16;
    short fieldF18;
    short fieldF1A;
    unsigned char unknownF1C[0xF30 - 0xF1C];
    short fieldF30;
    short fieldF32;
    float fieldF34;
    float fieldF38;
    float fieldF3C;
    float fieldF40;
    unsigned char unknownF44[0xF5C - 0xF44];
    float fieldF5C;
    float fieldF60;
    float fieldF64;
    float fieldF68;
    unsigned char unknownF6C[0xFFC - 0xF6C];
    unsigned char fieldFFC;
    unsigned char fieldFFD;
    unsigned char fieldFFE;
    unsigned char fieldFFF;
    unsigned char unknown1000[0x1008 - 0x1000];
};

#endif
