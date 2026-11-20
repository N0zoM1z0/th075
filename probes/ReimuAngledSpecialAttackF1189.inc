case R1189_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
#if R1189_AIR
        velocityX=(velocityX)*g_BounceScaleAt00657F74;
        velocityY=(*(&velocityY))*g_BounceScaleAt00657F74;
        field07C=1;
#else
        field07C=1;
        ClearMotionFields();
#endif
    }
#if R1189_AIR
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
#endif
    if ((animationStage)==R1189_FIRE_STAGE && (animationFrame)==0) {
#include "ReimuSpecialVolleyF1189.inc"
        UpdateGaugeTimer(R1189_ANIMATION);
        PlaySound(5);
    }
#if !R1189_AIR
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
#endif
    break;
}
