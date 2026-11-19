#include "MeilingFighter.hpp"
#include "Fighter.hpp"
#include "FighterVirtualActionsF159.hpp"
void MeilingFighter::ResetRound()
{
    scriptCounterF00=0;
    scriptCounterF02=0;
    fieldF04=0;
    fieldF06=0;
    fieldF08=0;
    fieldEFA=0;
    fieldF0A=0;
    fieldF2A=0;
    fieldF0C=0;
    fieldF22=0;
    fieldF24=0;
    fieldF26=0;
    fieldF28=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    reinterpret_cast<Fighter*>(this)->Fighter::ResetRound();
    sequenceTimer=0;
    fieldEFE=0;
}
