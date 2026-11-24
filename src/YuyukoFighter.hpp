#ifndef TH075_YUYUKO_FIGHTER_HPP
#define TH075_YUYUKO_FIGHTER_HPP
#include "Fighter.hpp"
class YuyukoOwnedObjectF469;

// Yuyuko's fighter: vtable Yuyuko ctor F311 at 0x00659B80.
// Slot overrides use the Fighter slot names; the rest are helpers.
class YuyukoFighter : public Fighter {
public:
    YuyukoFighter();
    virtual ~YuyukoFighter();
    virtual void Advance(); // slot 1: partial native move-state reconstruction at 00564BE0
    void ConfigureStage();
    void ChooseCardAction();
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void PollCommands();
    void AdvanceSequence();
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(YuyukoOwnedObjectF469** out);
    void SelectVariant();
    void ResetRound();

    // Fields after the shared Fighter layout.
    short fieldF10;
    unsigned char unknownF12[0xF14 - 0xF12];
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
};

#endif
