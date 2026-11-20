#ifndef TH075_YOUMU_FIGHTER_HPP
#define TH075_YOUMU_FIGHTER_HPP
#include "Fighter.hpp"
#include "YoumuHistoryQueueF378.hpp"
class YoumuGeneratedF224;

// Youmu's fighter: vtable Youmu ctor F223 at 0x006598D0.
// Slot overrides use the Fighter slot names; the rest are helpers.
class YoumuFighter : public Fighter {
public:
    YoumuFighter();
    virtual ~YoumuFighter();
    virtual void Advance(); // slot 1: nonexact giant at 005214B0

    // Remaining nonshared call-shape probes. The 00453B50 and 00453C80
    // effects use Fighter's inherited typed methods.
    void SetupCollisionAt454BC0(int,int,int);
    void NativeGameEffectAt455B30();

    void ConfigureStage();
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    int ChooseRecordedIntegerRange(int lower, int upper);
    static int cardCountdown;
    void DispatchActions();
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short,float,float,signed char,signed char,unsigned char);
    void PollCommands();
    signed char CheckPattern(const char*, int, int);
    void AdvanceSequence();
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
    unsigned char unknownFE4[0xFEC - 0xFE4]; // unobserved fighter state
    ObservedEffectQueueF378 historyQueue;  // +0xFEC, native 12-byte std::list
};

typedef char YoumuHistoryListLayoutF378[
    offsetof(YoumuFighter, historyQueue) == 0xFEC &&
    sizeof(YoumuFighter) == 0xFF8 ? 1 : -1];

#endif
