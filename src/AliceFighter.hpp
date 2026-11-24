#ifndef TH075_ALICE_FIGHTER_HPP
#define TH075_ALICE_FIGHTER_HPP
#include "Fighter.hpp"

// Alice's fighter: vtable Alice ctor F309 at 0x00659608.
// Slot overrides use the Fighter slot names; the rest are helpers.
class AliceFighter : public Fighter {
public:
    AliceFighter();
    void ChooseAction();
    static int actionCountdown;
    void RenderStage(signed char stage);
    virtual void Advance(); // Slot 1 at 004D7E70.
    void ConfigureStage();
    void CreateOwnedObject(CharacterObject** output);
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void SelectVariant();
    void AdvanceAuxiliary();
    void ResetRound();
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void PollCommands();
    void AdvanceSequence();

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    short fieldF14;
    unsigned char unknownF16[0xF18 - 0xF16];
    float fieldF18;
    float fieldF1C;
    float fieldF20;
    float fieldF24;
    unsigned char unknownF28[0xF40 - 0xF28];
    float fieldF40;
    float fieldF44;
    float fieldF48;
    float fieldF4C;
    unsigned char unknownF50[0xFE0 - 0xF50];
    unsigned char fieldFE0;
    unsigned char fieldFE1;
    unsigned char fieldFE2;
    unsigned char fieldFE3;
    unsigned char unknownFE4[0xFEC - 0xFE4];
};

#endif
