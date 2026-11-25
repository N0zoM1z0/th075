#ifndef TH075_REMILIA_FIGHTER_HPP
#define TH075_REMILIA_FIGHTER_HPP
#include "battle/Fighter.hpp"

// Remilia's fighter: vtable Remilia ctor F311 at 0x00659A40.
// Slot overrides use the Fighter slot names; the rest are helpers.
class RemiliaFighter : public Fighter {
public:
    RemiliaFighter();
    void RenderStage(signed char stage);
    virtual void Advance(); // slot 1, native 00543210, nonexact natural-C++ parent in RemiliaFighterAdvanceF1041.cpp

    // One remaining mixed-coordinate caller shape at 00453A70. The
    // independently exact 00453B50/00453C80 helpers are inherited directly.

    void ConfigureStage();
    void ChooseAction();
    static int actionCountdown;
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
    float fieldF10;
    float fieldF14;
    float fieldF18;
    float fieldF1C;
    unsigned char unknownF20[0xF38 - 0xF20];
    float fieldF38;
    float fieldF3C;
    float fieldF40;
    float fieldF44;
    unsigned char unknownF48[0xFD8 - 0xF48];
    unsigned char fieldFD8;
    unsigned char fieldFD9;
    unsigned char fieldFDA;
    unsigned char fieldFDB;
    unsigned char unknownFDC[0xFE4 - 0xFDC];
};

#endif
