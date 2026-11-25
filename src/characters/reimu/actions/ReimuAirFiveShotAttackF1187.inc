// Native 194/195 airborne five-shot policy, with explicit per-shot values.
case R1187_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        collisionResult=1;
        scriptCounterF00=0;
    }
    velocityY=velocityY-verticalAcceleration;
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=-3.0f; velocityY=8.0f; verticalAcceleration=0.55f;
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySound(0);
        UpdateGaugeTimer(100);
    }
    if ((animationStage)==6 && (animationFrame)==0 && (scriptCounterF00)<2 &&
        static_cast<unsigned int>(inputC)>0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySound(0);
        UpdateGaugeTimer(25);
        ++scriptCounterF00;
        ResetSecondaryCounter(4);
    }
    break;
}
