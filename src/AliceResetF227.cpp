#include "AliceFighter.hpp"
#include "Fighter.hpp"
#include "FighterVirtualActionsF159.hpp"
void AliceFighter::ResetRound()
{
    reinterpret_cast<unsigned short&>(sequenceTimer)=0;
    fieldEFE=0;
    fieldEFA=0;
    fieldF14=0;
    scriptCounterF00=0;
    scriptCounterF02=0;
    reinterpret_cast<unsigned short&>(fieldF04)=0;
    fieldF06=0;
    fieldF08=0;
    reinterpret_cast<unsigned short&>(fieldF0A)=0;
    reinterpret_cast<unsigned short&>(fieldF0C)=0;
    reinterpret_cast<unsigned short&>(fieldF0E)=0;
    fieldF10=0;
    fieldF12=0;
    reinterpret_cast<unsigned short&>(aiWaitTimer)=0;
    reinterpret_cast<unsigned short&>(aiStep)=0;
    reinterpret_cast<unsigned short&>(aiCardTimer)=0;
    reinterpret_cast<Fighter*>(this)->Fighter::ResetRound();
}
