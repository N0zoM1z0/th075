#include "YoumuFighter.hpp"
#include "Fighter.hpp"
#include "FighterVirtualActionsF159.hpp"
void YoumuFighter::ResetRound()
{
    sequenceTimer=0;
    fieldEFE=0;
    fieldEFA=0;
    fieldF14=0;
    scriptCounterF00=0;
    scriptCounterF02=0;
    fieldF04=0;
    fieldF06=0;
    fieldF08=0;
    fieldF0A=0;
    fieldF0E=0;
    fieldF10=0;
    fieldF12=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    Fighter::ResetRound();
    historyQueue.clear();
}
