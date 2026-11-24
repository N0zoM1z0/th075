#ifndef TH075_MEILING_FIGHTER_HPP
#define TH075_MEILING_FIGHTER_HPP
#include "Fighter.hpp"

// Meiling's fighter: vtable Meiling ctor F311 at 0x00659F50.
// Slot overrides use the Fighter slot names; the rest are helpers.
class MeilingFighter : public Fighter {
public:
    MeilingFighter();
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    static int cardCountdown;
    virtual void Advance(); // Slot 1 at 005D73C0.
    void DispatchActions();
    void AdvanceAuxiliary();
    void PollCommands();
    void ConfigureStage();
    void RenderStage(signed char);
    void AdvanceSequence();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(CharacterObject** out);
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF22 - 0xF10];
    short fieldF22;
    short fieldF24;
    short fieldF26;
    short fieldF28;
    short fieldF2A;
    float fieldF2C;
    float fieldF30;
    float fieldF34;
    float fieldF38;
    unsigned char unknownF3C[0xF54 - 0xF3C];
    float fieldF54;
    float fieldF58;
    float fieldF5C;
    float fieldF60;
    unsigned char unknownF64[0xFF4 - 0xF64];
    unsigned char fieldFF4;
    unsigned char fieldFF5;
    unsigned char fieldFF6;
    unsigned char fieldFF7;
    unsigned char unknownFF8[0x1000 - 0xFF8];
};

#endif
