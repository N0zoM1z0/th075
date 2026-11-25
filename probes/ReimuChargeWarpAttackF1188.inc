case R1188_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        remainingHits=1; collisionResult=0; field3AC=0;
    }
#include "ReimuChargeTransformF1188.inc"
    if (y>FloatConstants::Zero && (animationStage)<R1188_LAND_STAGE
#if R1188_HAS_GRAVITY_MIN
        && (animationStage)>3
#endif
    ) velocityY=velocityY-FloatConstants::SevenTenths;
    if ((animationStage)==R1188_LAND_STAGE || (animationStage)==R1188_LAND_STAGE+1) {
        if (y+velocityY<FloatConstants::Zero) {
            y=0.0f; velocityX=0.0f; velocityY=0.0f;
            ResetSecondaryCounter(R1188_LAND_STAGE+2);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==R1188_RETURN_STAGE && (animationFrame)==0) {
        x=opponent->x-float(facing*180);
        y=150.0f; velocityX=6.0f; velocityY=8.0f;
        PlaySound(2);
    }
    if ((animationStage)==R1188_LAND_STAGE-1 && (animationFrame)==0) {
        velocityX=5.0f; velocityY=-16.0f;
    }
    if ((animationStage)==R1188_LAND_STAGE+2 && (animationFrame)==0) ResetSecondaryCounter(R1188_LAND_STAGE);
    break;
}
