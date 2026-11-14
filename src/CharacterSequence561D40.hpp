#ifndef TH075_CHARACTER_SEQUENCE_561D40_HPP
#define TH075_CHARACTER_SEQUENCE_561D40_HPP
#include "Fighter.hpp"
#include "BattleStateMachine.hpp"

class CharacterSequence561D40 : public Fighter {
public:
    void AdvanceSequence();
    void SetNoticeMode(unsigned char mode);
    void InitializeNotice(short notice);
    unsigned char ProcessNotice();
    void ConfigureNoticeText(unsigned char enabled);
    void BeginNoticeTransition(unsigned char notice, unsigned char direction);
    void ClearNoticeTransition();
    void AdvanceNoticeLevels();
    void ResetPrimaryCounters(short state);
public:
    // Character-specific fields after the shared Fighter layout.
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
namespace SequenceCamera { void SetOverride(unsigned char enabled, float x, float y, float zoom); }
namespace SequenceAudio { void Stop(); }
namespace SequenceStage { void Load(); }
// Narrow views of the observed byte writes; original declarations unknown.
extern unsigned char g_SequenceCounterAt00671622;
extern unsigned char g_SequenceStageAt0067161D;
#endif
