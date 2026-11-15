case R1188_ACTION: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1; field07C=0; field3AC=0; reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
#include "ReimuChargeTransformF1188.inc"
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))>R1188_RETURN_STAGE-1) {
        velocityY=velocityY-g_AnimationDeltaAt0065747C;
        if (y+velocityY<=g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))<R1188_LAND_STAGE) {
            y=0.0f; velocityY=0.0f;
            SetAuxActionAt40FB40(R1188_LAND_STAGE);
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))>R1188_LAND_STAGE+1) {
        velocityX=(velocityX)-g_ReimuRepeatDragAt00659090;
        if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==R1188_RETURN_STAGE && (reinterpret_cast<signed short&>(animationFrame))==0) {
        x=float(facing*100)+(x);
        y=50.0f; velocityX=12.0f; velocityY=6.0f;
        PlaySoundAt453D40(2);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==R1188_LAND_STAGE+2 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        SetAuxActionAt40FB40(R1188_LAND_STAGE);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    break;
}
