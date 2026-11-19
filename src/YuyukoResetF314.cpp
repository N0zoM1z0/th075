#include "YuyukoFighter.hpp"
#include "Fighter.hpp"
#include "FighterVirtualActionsF159.hpp"
void YuyukoFighter::ResetRound()
{
    sequenceTimer=0;
    fieldEFE=0;
    scriptCounterF00=0;
    scriptCounterF02=0;
    fieldF04=0;
    fieldF06=0;
    fieldF08=0;
    fieldF0A=0;
    fieldF0C=0;
    fieldF0E=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    reinterpret_cast<Fighter*>(this)->Fighter::ResetRound();
}
