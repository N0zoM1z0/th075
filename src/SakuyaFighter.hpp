#ifndef TH075_SAKUYA_FIGHTER_HPP
#define TH075_SAKUYA_FIGHTER_HPP
#include "Fighter.hpp"

// Sakuya's fighter: vtable Sakuya ctor F309 at 0x006594A8.
// Slot overrides use the Fighter slot names; the rest are helpers.
class SakuyaFighter : public Fighter {
public:
    SakuyaFighter();
    void RenderStage(signed char stage);
    virtual void Advance(); // slot 1: nonexact giant at 004AC040

    void ConfigureStage();
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void EnableRoundSound(int);
    void PollCommands();
    void AdvanceSequence();
    void ResetRound();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(CharacterObject** out);
    void SelectVariant();

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    short fieldF14;
    short fieldF16;
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
