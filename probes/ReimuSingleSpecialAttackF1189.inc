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
#include "ReimuSpecialShotF1189.inc"
#if R1189_HAS_PREPARATION
        PlaySharedSound(0x29);
#endif
        UpdateGaugeTimer(200);
    }
#if !R1189_AIR
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
#endif
    break;
}
