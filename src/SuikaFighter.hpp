#ifndef TH075_SUIKA_FIGHTER_HPP
#define TH075_SUIKA_FIGHTER_HPP
#include "Fighter.hpp"
class SuikaOwnedObjectF469;

// Suika's fighter: vtable Suika ctor F309 at 0x00659E30.
// Slot overrides use the Fighter slot names; the rest are helpers.
class SuikaFighter : public Fighter {
public:
    SuikaFighter();
    virtual ~SuikaFighter();
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
    void CreateOwnedObject(SuikaOwnedObjectF469** out);
    void SelectVariant();
    void ResetBaseRound();
    void ResetRound();
    int Rand(int min,int max);
    void SpawnProjectile(int pattern,float x,float y,unsigned char direction,int group);
    void AdvanceAuxiliary();

    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF1C - 0xF10];
    short fieldF1C;
    short fieldF1E;
    short fieldF20;
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
