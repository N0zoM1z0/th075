#include "engine/GeometryConstants.hpp"
#include "characters/marisa/MarisaFighter.hpp"
#include "battle/Fighter.hpp"
#include "battle/FighterVirtualActionsF159.hpp"
// Physical script-defined field view only: no complete owner allocation.
// R050 original x87: FILD dword stack signed index; FDIV dword [0x659308].
void MarisaFighter::ResetRound()
{
    scriptCounterF00=0;
    scriptCounterF02=0;
    fieldF04=0;
    fieldF06=0;
    fieldF08=0;
    fieldF0A=0;
    sequenceTimer=0;
    stageBannerHoldFrames=0;
    fieldEFA=0;
    longRangeFrames=0;
    fieldF0C=0;
    fieldF0E=0;
    trackingNodeOrbitAngle=0;
    trackingNodeOrbitPhase=0;
    orbitingNodesRemaining=0;
    trackingNodeDispatchSlot=0;
    trackingNodeLifetimeFrames=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    trackingNodeX[0]=0;
    trackingNodeX[1]=0;
    trackingNodeX[2]=0;
    trackingNodeX[3]=0;
    trackingNodeX[4]=0;
    trackingNodeX[5]=0;
    trackingNodeY[0]=0;
    trackingNodeY[1]=0;
    trackingNodeY[2]=0;
    trackingNodeY[3]=0;
    trackingNodeY[4]=0;
    trackingNodeY[5]=0;
    chainVisible=0;
    for (int i=0;i<=36;++i) {
       chain[i*2].rawX=0;
       chain[i*2].rawY=0;
       chain[i*2].rawZ=0;
       chain[i*2].alpha=1.0f;
       chain[i*2].flags=0xffffffffu;
       chain[i*2].phase=static_cast<float>(i)/GeometryConstants::ThirtySix;
       chain[i*2].tail=0;
       chain[i*2+1].rawX=0;
       chain[i*2+1].rawY=0;
       chain[i*2+1].rawZ=0;
       chain[i*2+1].alpha=1.0f;
       chain[i*2+1].flags=0xffffffffu;
       chain[i*2+1].phase=static_cast<float>(i)/GeometryConstants::ThirtySix;
       chain[i*2+1].tail=1.0f;
    }
    Fighter::ResetRound();
}
