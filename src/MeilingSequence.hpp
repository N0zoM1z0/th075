#ifndef TH075_MEILING_SEQUENCE_HPP
#define TH075_MEILING_SEQUENCE_HPP
#include "MeilingFighter.hpp"
#include "Fighter.hpp"
#include "BattleStateMachine.hpp"

namespace SequenceCamera { void SetOverride(unsigned char enabled, float x, float y, float zoom); }
namespace SequenceAudio { void Stop(); }
namespace SequenceStage { void Load(); }
// Narrow views of the observed byte writes; original declarations unknown.
extern unsigned char g_SequenceCounterAt00671622;
extern unsigned char g_SequenceStageAt0067161D;
#endif
