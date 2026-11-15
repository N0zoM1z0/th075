#ifndef TH075_MARISA_FIGHTER_HPP
#define TH075_MARISA_FIGHTER_HPP
#include "Fighter.hpp"
class MarisaGeneratedF223;

// Marisa's fighter: vtable Marisa ctor F223 at 0x006592B8.
// Slot overrides use the Fighter slot names; the rest are helpers.
class MarisaFighter : public Fighter {
public:
    MarisaFighter();
    virtual ~MarisaFighter();
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
    void PollCommands();
    void AdvanceSequence();
    void PlaySharedSound(short sound);
    void RenderChain();
    void CreateOwnedObject(MarisaGeneratedF223** output);
    void ForwardBaseAction();
    void NoOpSlot18();
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    short fieldF14;
    short fieldF16;
    short fieldF18;
    short fieldF1A;
    short fieldF1C;
    short fieldF1E;
    short fieldF20;
    short fieldF22;
    short fieldF24;
    short fieldF26;
    short fieldF28;
    short fieldF2A;
    short fieldF2C;
    short fieldF2E;
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
    unsigned char unknown1000[0x1006 - 0x1000];
    unsigned char field1006;
};

#endif
