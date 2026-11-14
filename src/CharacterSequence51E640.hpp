#ifndef TH075_CHARACTER_SEQUENCE_51E640_HPP
#define TH075_CHARACTER_SEQUENCE_51E640_HPP
#include "Fighter.hpp"
#include "BattleStateMachine.hpp"

class CharacterSequence51E640 : public Fighter {
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
    unsigned char unknownF10[0xF14 - 0xF10];
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
namespace SequenceCamera { void SetOverride(unsigned char enabled, float x, float y, float zoom); }
namespace SequenceAudio { void Stop(); }
namespace SequenceStage { void Load(); }
// Narrow views of the observed byte writes; original declarations unknown.
extern unsigned char g_SequenceCounterAt00671622;
extern unsigned char g_SequenceStageAt0067161D;
#endif
