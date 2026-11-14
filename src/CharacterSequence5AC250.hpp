#ifndef TH075_CHARACTER_SEQUENCE_5AC250_HPP
#define TH075_CHARACTER_SEQUENCE_5AC250_HPP
#include "Fighter.hpp"
#include "BattleStateMachine.hpp"

class CharacterSequence5AC250 : public Fighter {
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
    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF34 - 0xF10];
    float fieldF34;
    float fieldF38;
    float fieldF3C;
    float fieldF40;
    unsigned char unknownF44[0xF5C - 0xF44];
    float fieldF5C;
    float fieldF60;
    float fieldF64;
    float fieldF68;
    unsigned char unknownF6C[0xFFC - 0xF6C];
    unsigned char fieldFFC;
    unsigned char fieldFFD;
    unsigned char fieldFFE;
    unsigned char fieldFFF;
};
namespace SequenceCamera { void SetOverride(unsigned char enabled, float x, float y, float zoom); }
namespace SequenceAudio { void Stop(); }
// Narrow views of the observed byte writes; original declarations unknown.
extern unsigned char g_SequenceCounterAt00671622;
#endif
