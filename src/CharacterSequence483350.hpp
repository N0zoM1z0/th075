#ifndef TH075_CHARACTER_SEQUENCE_483350_HPP
#define TH075_CHARACTER_SEQUENCE_483350_HPP
#include "Fighter.hpp"
#include "BattleStateMachine.hpp"

class CharacterSequence483350 : public Fighter {
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
    unsigned char unknownF10[0xF2C - 0xF10];
    float fieldF2C;
    float fieldF30;
    float fieldF34;
    float fieldF38;
    unsigned char unknownF3C[0xF54 - 0xF3C];
    float fieldF54;
    float fieldF58;
    float fieldF5C;
    float fieldF60;
    unsigned char unknownF64[0xFF4 - 0xF64];
    unsigned char fieldFF4;
    unsigned char fieldFF5;
    unsigned char fieldFF6;
    unsigned char fieldFF7;
};
namespace SequenceCamera { void SetOverride(unsigned char enabled, float x, float y, float zoom); }
namespace SequenceAudio { void Stop(); }
namespace SequenceStage { void Load(); }
// Narrow views of the observed byte writes; original declarations unknown.
extern unsigned char g_SequenceCounterAt00671622;
extern unsigned char g_SequenceStageAt0067161D;
#endif
