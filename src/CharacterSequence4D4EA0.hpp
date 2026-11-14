#ifndef TH075_CHARACTER_SEQUENCE_4D4EA0_HPP
#define TH075_CHARACTER_SEQUENCE_4D4EA0_HPP
#include "Fighter.hpp"
#include "BattleStateMachine.hpp"

class CharacterSequence4D4EA0 : public Fighter {
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
    unsigned char unknownF10[0xF18 - 0xF10];
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
namespace SequenceCamera { void SetOverride(unsigned char enabled, float x, float y, float zoom); }
namespace SequenceAudio { void Stop(); }
namespace SequenceStage { void Load(); }
// Narrow views of the observed byte writes; original declarations unknown.
extern unsigned char g_SequenceCounterAt00671622;
extern unsigned char g_SequenceStageAt0067161D;
#endif
