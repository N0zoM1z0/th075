#ifndef TH075_REMILIA_FIGHTER_HPP
#define TH075_REMILIA_FIGHTER_HPP
#include "Fighter.hpp"
class RemiliaOwnedObjectF469;

// Remilia's fighter: vtable Remilia ctor F311 at 0x00659A40.
// Slot overrides use the Fighter slot names; the rest are helpers.
class RemiliaFighter : public Fighter {
public:
    RemiliaFighter();
    virtual ~RemiliaFighter();
    virtual void Advance(); // slot 1, native 00543210, nonexact research parent

    // Complete native caller ABI hypotheses; these refer to existing Actor
    // and Fighter functions, not new independently reconstructed methods.
    void SpawnWithFloatAt453A70(int,int,float,char,int);
    void SpawnFloatXRawYAt453A70(int,float,int,char,int);
    void SpawnRawXYAt453C80(int,int,int,char,int);
    void SpawnMixedAt453C80(int,int,float,char,int);
    void SpawnSevenAt453B50(int,int,int,char,int,int,int);
    void SpawnAt453C80(int,float,float,char,int);

    void ConfigureStage();
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
    void PollCommands();
    void AdvanceSequence();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(RemiliaOwnedObjectF469** out);
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
};

#endif
