case R1188_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1; field07C=0; field3AC=0; scriptCounterF00=0;
    }
#include "ReimuChargeTransformF1188.inc"
    if (y>FloatConstants::Zero && (animationStage)>R1188_RETURN_STAGE-1) {
        velocityY=velocityY-FloatConstants::One;
        if (y+velocityY<=FloatConstants::Zero && (animationStage)<R1188_LAND_STAGE) {
            y=0.0f; velocityY=0.0f;
            ResetSecondaryCounter(R1188_LAND_STAGE);
        }
    }
    if ((animationStage)>R1188_LAND_STAGE+1) {
        velocityX=(velocityX)-FloatConstants::FourFifths;
        if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==R1188_RETURN_STAGE && (animationFrame)==0) {
        x=float(facing*100)+(x);
        y=50.0f; velocityX=12.0f; velocityY=6.0f;
        PlaySound(2);
    }
    if ((animationStage)==R1188_LAND_STAGE+2 && (animationFrame)==0 && (scriptCounterF00)<1) {
        ResetSecondaryCounter(R1188_LAND_STAGE);
        ++scriptCounterF00;
    }
    break;
}
