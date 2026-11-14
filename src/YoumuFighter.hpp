#ifndef TH075_YOUMU_FIGHTER_HPP
#define TH075_YOUMU_FIGHTER_HPP
#include "Fighter.hpp"
class YoumuGeneratedF224;

// Youmu's fighter: vtable Youmu ctor F223 at 0x006598D0.
// Slot overrides use the Fighter slot names; the rest are helpers.
class YoumuFighter : public Fighter {
public:
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    int ChooseIntegerRange(int lower, int upper);
    int ChooseRecordedIntegerRange(int lower, int upper);
    static int cardCountdown;
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short,float,float,signed char,signed char,unsigned char);
    void PollCommands();
    signed char CheckPattern(const char*, int, int);
    void AdvanceSequence();
    void SetNoticeMode(unsigned char mode);
    void InitializeNotice(short notice);
    unsigned char ProcessNotice();
    void ConfigureNoticeText(unsigned char enabled);
    void BeginNoticeTransition(unsigned char notice, unsigned char direction);
    void ClearNoticeTransition();
    void AdvanceNoticeLevels();
    void CreateOwnedObject(YoumuGeneratedF224** output);
    void ForwardBaseAction();
    void RenderChain();
    void NoOpSlot18();
    void SelectVariant();
    void ResetRound();

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
