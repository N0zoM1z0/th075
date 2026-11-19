case R1188_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1; field07C=0; field3AC=0;
    }
#include "ReimuChargeTransformF1188.inc"
    if (y>g_ThresholdAt0065782C && (animationStage)<R1188_LAND_STAGE
#if R1188_HAS_GRAVITY_MIN
        && (animationStage)>3
#endif
    ) velocityY=velocityY-g_ReimuChargeFallAt00659094;
    if ((animationStage)==R1188_LAND_STAGE || (animationStage)==R1188_LAND_STAGE+1) {
        if (y+velocityY<g_ThresholdAt0065782C) {
            y=0.0f; velocityX=0.0f; velocityY=0.0f;
            SetAuxActionAt40FB40(R1188_LAND_STAGE+2);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==R1188_RETURN_STAGE && (animationFrame)==0) {
        x=opponent->x-float(facing*180);
        y=150.0f; velocityX=6.0f; velocityY=8.0f;
        PlaySoundAt453D40(2);
    }
    if ((animationStage)==R1188_LAND_STAGE-1 && (animationFrame)==0) {
        velocityX=5.0f; velocityY=-16.0f;
    }
    if ((animationStage)==R1188_LAND_STAGE+2 && (animationFrame)==0) SetAuxActionAt40FB40(R1188_LAND_STAGE);
    break;
}
