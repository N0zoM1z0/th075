#ifndef TH075_ALICE_FIGHTER_HPP
#define TH075_ALICE_FIGHTER_HPP
#include "Fighter.hpp"
class AliceGeneratedF227;

// Alice's fighter: vtable Alice ctor F309 at 0x00659608.
// Slot overrides use the Fighter slot names; the rest are helpers.
class AliceFighter : public Fighter {
public:
    void CreateOwnedObject(AliceGeneratedF227** output);
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void SelectVariant();
    void AdvanceAuxiliary();
    void ResetRound();
    void ChooseCardAction();
    int ChooseIntegerRange(int lower, int upper);
    static int cardCountdown;
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
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

    // Fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
    short fieldF14;
    unsigned char unknownF16[0xF18 - 0xF16];
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
};

#endif
