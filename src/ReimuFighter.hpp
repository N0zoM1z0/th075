#ifndef TH075_REIMU_FIGHTER_HPP
#define TH075_REIMU_FIGHTER_HPP
#include "Fighter.hpp"
class ReimuGeneratedF227;

// Reimu's fighter: vtable Reimu ctor F311 at 0x006590D8.
// Slot overrides use the Fighter slot names; the rest are helpers.
class ReimuFighter : public Fighter {
public:
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
    void PollCommands();
    void AdvanceSequence();
    void ConfigureStage();
    void CreateOwnedObject(ReimuGeneratedF227** output);
    void DispatchActions();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
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
};

#endif
