#ifndef TH075_REMILIA_FIGHTER_HPP
#define TH075_REMILIA_FIGHTER_HPP
#include "Fighter.hpp"
class RemiliaOwnedObjectF469;

// Remilia's fighter: vtable Remilia ctor F311 at 0x00659A40.
// Slot overrides use the Fighter slot names; the rest are helpers.
class RemiliaFighter : public Fighter {
public:
    void ChooseAction();
    static int actionCountdown;
    void ChooseCardAction();
    int ChooseIntegerRange(int lower, int upper);
    static int cardCountdown;
    void DispatchActions();
    void PackDirectionBits();
    void ResetPrimaryCounters(short state);
    void ClearAuxiliaryInput();
    void AdvanceAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
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
