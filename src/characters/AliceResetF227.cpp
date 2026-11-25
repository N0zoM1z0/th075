#include "characters/AliceFighter.hpp"
#include "battle/Fighter.hpp"
#include "battle/FighterVirtualActionsF159.hpp"
void AliceFighter::ResetRound()
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
    fieldF0C=0;
    fieldF0E=0;
    fieldF10=0;
    fieldF12=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    reinterpret_cast<Fighter*>(this)->Fighter::ResetRound();
}
