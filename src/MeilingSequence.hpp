#ifndef TH075_MEILING_SEQUENCE_HPP
#define TH075_MEILING_SEQUENCE_HPP
#include "BattleStateMachine.hpp"

// Declaration-only view of existing receivers. Never construct or embed it.
// Original identity, declarations and complete owner layout remain unknown.
class MeilingFighter {
public:
    void DispatchSpecialStatesAt005F3D60();
    void SetNoticeMode(unsigned char mode);
    void InitializeNotice(short notice);
    unsigned char ProcessNotice();
    void ConfigureNoticeText(unsigned char enabled);
    void BeginNoticeTransition(unsigned char notice, unsigned char direction);
    void ClearNoticeTransition();
    void AdvanceNoticeLevels();
    void ResetPrimaryCounters(short state);
};
namespace SequenceCamera { void SetOverride(unsigned char enabled, float x, float y, float zoom); }
namespace SequenceAudio { void Stop(); }
namespace SequenceStage { void Load(); }
// Narrow views of the observed byte writes; original declarations unknown.
extern unsigned char g_SequenceCounterAt00671622;
extern unsigned char g_SequenceStageAt0067161D;
#endif
