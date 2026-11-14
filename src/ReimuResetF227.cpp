#include "Fighter.hpp"
#include "FighterVirtualActionsF159.hpp"
class ReimuRoundF227 : public Fighter {
public:
    void ResetRound();
public:
    // Fields after the shared Fighter layout.
    unsigned char unknownF10[0xF22 - 0xF10];
    unsigned short fieldF22;
    unsigned short fieldF24;
    unsigned short fieldF26;
    unsigned short fieldF28;
    unsigned short fieldF2A;
};
void ReimuRoundF227::ResetRound()
{
    scriptCounterF00=0;
    scriptCounterF02=0;
    reinterpret_cast<unsigned short&>(fieldF04)=0;
    fieldF06=0;
    fieldF08=0;
    fieldEFA=0;
    reinterpret_cast<unsigned short&>(fieldF0A)=0;
    fieldF2A=0;
    reinterpret_cast<unsigned short&>(fieldF0C)=0;
    fieldF22=0;
    fieldF24=0;
    fieldF26=0;
    fieldF28=0;
    reinterpret_cast<unsigned short&>(aiWaitTimer)=0;
    reinterpret_cast<unsigned short&>(aiStep)=0;
    reinterpret_cast<unsigned short&>(aiCardTimer)=0;
    reinterpret_cast<FighterBaseActionsF159*>(this)->FighterBaseActionsF159::ResetRound();
    reinterpret_cast<unsigned short&>(sequenceTimer)=0;
    fieldEFE=0;
}
