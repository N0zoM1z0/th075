case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
    if ((animationStage)==6 && (animationFrame)==0) {
        SetNonnegativeWordAt453E80(40);
        PrepareActionAt453D60(0x17);
        SpawnAt453C80(R1190_AUX_EFFECT,float(facing*7)+(x),
            (*(&y))+g_ReimuMeterNearYAt00659088,reinterpret_cast<char&>(facing),1);
        field36C=(field36C)-g_ContactProjectionAt00657888;
    }
    if ((animationStage)==10 || (animationStage)==11) UpdateGaugeTimer(5);
    if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==8 && (animationFrame)==0) {
        SpawnFloatXAt453A70(R1190_EFFECT,(*(&x))+g_ThresholdAt0065782C+g_ThresholdAt0065782C,
            reinterpret_cast<int&>(y),reinterpret_cast<char&>(facing),1);
        PlaySoundAt453D40(R1190_SOUND);
    }
    if ((animationStage)==12 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<10) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(10);
    }
    if ((animationStage)==14 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        SetAuxActionAt40FB40(12);
    }
    break;
}
