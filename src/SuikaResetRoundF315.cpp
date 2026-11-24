#include "BattleSessionState.hpp"
#include "SuikaFighter.hpp"
#include "Fighter.hpp"
void SuikaFighter::ResetRound()
{
    sequenceTimer=0;
    fieldEFE=0;
    scriptCounterF00=0;
    scriptCounterF02=0;
    fieldF04=0;
    fieldF06=0;
    fieldEFA=0;
    fieldF06=0;
    fieldF26=0;
    fieldF1C=0;
    fieldF1E=0;
    fieldF20=0;
    fieldF22=0;
    fieldF24=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    g_SequenceByteAt0066C23A=0xff;
    g_SequenceByteAt0066C239=0xff;
    ResetBaseRound();
    fieldF28=0;
    fieldF2A=0;
}
