#include "MarisaFighter.hpp"
#include "Fighter.hpp"
#include "FighterVirtualActionsF159.hpp"
// Physical script-defined field view only: no complete owner allocation.
// R050 original x87: FILD dword stack signed index; FDIV dword [0x659308].
extern const float g_MarisaSequenceScaleAt00659308;
void MarisaFighter::ResetRound()
{
    scriptCounterF00=0;
    scriptCounterF02=0;
    fieldF04=0;
    fieldF06=0;
    fieldF08=0;
    fieldF0A=0;
    sequenceTimer=0;
    fieldEFE=0;
    fieldEFA=0;
    fieldF32=0;
    fieldF0C=0;
    fieldF0E=0;
    fieldF10=0;
    fieldF12=0;
    fieldF14=0;
    fieldF16=0;
    fieldF18=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    fieldF1A=0;
    fieldF1C=0;
    fieldF1E=0;
    fieldF20=0;
    fieldF22=0;
    fieldF24=0;
    fieldF26=0;
    fieldF28=0;
    fieldF2A=0;
    fieldF2C=0;
    fieldF2E=0;
    fieldF30=0;
    field1006=0;
    for (int i=0;i<=36;++i) {
       chain[i*2].rawX=0;
       chain[i*2].rawY=0;
       chain[i*2].rawZ=0;
       chain[i*2].alpha=1.0f;
       chain[i*2].flags=0xffffffffu;
       chain[i*2].phase=static_cast<float>(i)/g_MarisaSequenceScaleAt00659308;
       chain[i*2].tail=0;
       chain[i*2+1].rawX=0;
       chain[i*2+1].rawY=0;
       chain[i*2+1].rawZ=0;
       chain[i*2+1].alpha=1.0f;
       chain[i*2+1].flags=0xffffffffu;
       chain[i*2+1].phase=static_cast<float>(i)/g_MarisaSequenceScaleAt00659308;
       chain[i*2+1].tail=1.0f;
    }
    Fighter::ResetRound();
}
