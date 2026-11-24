#ifndef TH075_PATCHOULI_FIGHTER_HPP
#define TH075_PATCHOULI_FIGHTER_HPP
#include "Fighter.hpp"

// Patchouli's fighter: vtable Patchouli ctor F309 at 0x00659768.
// Slot overrides use the Fighter slot names; the rest are helpers.
class PatchouliFighter : public Fighter {
public:
    PatchouliFighter();
    virtual void Advance(); // Slot 1 at 004F7130.
    void ConfigureStage();
    void ChooseAction();
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void SpawnProjectile(int,float,float,unsigned char,int);
    void PollCommands();
    void AdvanceSequence();
    void RenderStage(signed char stage);
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(CharacterObject** out);
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    float fieldF14;
    float fieldF18;
    float fieldF1C;
    float fieldF20;
    unsigned char unknownF24[0xF3C - 0xF24];
    float fieldF3C;
    float fieldF40;
    float fieldF44;
    float fieldF48;
    unsigned char unknownF4C[0xFDC - 0xF4C];
    unsigned char fieldFDC;
    unsigned char fieldFDD;
    unsigned char fieldFDE;
    unsigned char fieldFDF;
    unsigned char unknownFE0[0xFE8 - 0xFE0];
};

#endif
