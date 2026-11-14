#include "Fighter.hpp"
#include "FighterVirtualActionsF159.hpp"
class YuyukoRoundF314 : public Fighter {public: void ResetRound();};
void YuyukoRoundF314::ResetRound()
{
    reinterpret_cast<unsigned short&>(sequenceTimer)=0;
    fieldEFE=0;
    scriptCounterF00=0;
    scriptCounterF02=0;
    reinterpret_cast<unsigned short&>(fieldF04)=0;
    fieldF06=0;
    fieldF08=0;
    reinterpret_cast<unsigned short&>(fieldF0A)=0;
    reinterpret_cast<unsigned short&>(fieldF0C)=0;
    reinterpret_cast<unsigned short&>(fieldF0E)=0;
    reinterpret_cast<unsigned short&>(aiWaitTimer)=0;
    reinterpret_cast<unsigned short&>(aiStep)=0;
    reinterpret_cast<unsigned short&>(aiCardTimer)=0;
    reinterpret_cast<FighterBaseActionsF159*>(this)->FighterBaseActionsF159::ResetRound();
}
