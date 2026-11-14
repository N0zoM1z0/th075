#ifndef TH075_PATCHOULI_FIGHTER_HPP
#define TH075_PATCHOULI_FIGHTER_HPP
#include "Fighter.hpp"
class PatchouliOwnedObjectF469;

// Patchouli's fighter: vtable Patchouli ctor F309 at 0x00659768.
// Slot overrides use the Fighter slot names; the rest are helpers.
class PatchouliFighter : public Fighter {
public:
    void ChooseAction();
    void ChooseCardAction();
    int ChooseIntegerRange(int lower, int upper);
    static int cardCountdown;
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
    int Rand(int,int);
    void SpawnProjectile(int,float,float,unsigned char,int);
    void PollCommands();
    signed char MatchInputPattern(const char*, signed char, signed char);
    void AdvanceSequence();
    void SetNoticeMode(unsigned char mode);
    void InitializeNotice(short notice);
    unsigned char ProcessNotice();
    void ConfigureNoticeText(unsigned char enabled);
    void BeginNoticeTransition(unsigned char notice, unsigned char direction);
    void ClearNoticeTransition();
    void AdvanceNoticeLevels();
    void RenderStage(signed char stage);
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void CreateOwnedObject(PatchouliOwnedObjectF469** out);
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
};

#endif
