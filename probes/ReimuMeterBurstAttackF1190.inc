case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
#include "ReimuMeterCycleF1190.inc"
#if R1190_AIR
    if ((animationStage)>11 && y>g_ThresholdAt0065782C) {
        velocityY=velocityY-g_SubtractAt00657478;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(15);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
#endif
    if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        SetNonnegativeWordAt453E80(40);
        PlaySharedSound(0x17);
        SpawnAt453C80(R1190_AUX_EFFECT,x-float(facing*2),
            (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        UpdateGaugeTimer(500);
    }
    if ((animationStage)==4 && (animationFrame)==0) {
        SpawnTrackedAt453B50(0x3B6,(*(&x))+g_ThresholdAt0065782C,
            (*(&y))+g_ReimuMeterTrailYAt0065835C,facing,1,0,1);
    }
    if ((animationStage)==12 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<13) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(10);
    }
#if R1190_AIR
    if ((animationStage)==15 && (animationFrame)==0) SetAuxActionAt40FB40(13);
#endif
    break;
}
