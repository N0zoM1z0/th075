#include "SuikaFighter.hpp"
#include "Fighter.hpp"
extern unsigned char g_SuikaGlobalMarkerAt0066C23A;
extern unsigned char g_SuikaGlobalModeAt0066C239;
void SuikaFighter::ResetRound()
{
    reinterpret_cast<unsigned short&>(sequenceTimer)=0;
    fieldEFE=0;
    scriptCounterF00=0;
    scriptCounterF02=0;
    reinterpret_cast<unsigned short&>(fieldF04)=0;
    fieldF06=0;
    fieldEFA=0;
    fieldF06=0;
    fieldF26=0;
    fieldF1C=0;
    fieldF1E=0;
    fieldF20=0;
    fieldF22=0;
    fieldF24=0;
    reinterpret_cast<unsigned short&>(aiWaitTimer)=0;
    reinterpret_cast<unsigned short&>(aiStep)=0;
    reinterpret_cast<unsigned short&>(aiCardTimer)=0;
    g_SuikaGlobalMarkerAt0066C23A=0xff;
    g_SuikaGlobalModeAt0066C239=0xff;
    ResetBaseRound();
    fieldF28=0;
    fieldF2A=0;
}
