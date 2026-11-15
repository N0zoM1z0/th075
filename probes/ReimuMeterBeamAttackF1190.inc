case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SetNonnegativeWordAt453E80(40);
        PrepareActionAt453D60(0x17);
        SpawnAt453C80(R1190_AUX_EFFECT,float(facing*7)+(x),
            (*(&y))+g_ReimuMeterNearYAt00659088,reinterpret_cast<char&>(facing),1);
        field36C=(field36C)-g_ContactProjectionAt00657888;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==10 || (reinterpret_cast<signed short&>(animationStage))==11) StartAnimationAt46D000(5);
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnFloatXAt453A70(R1190_EFFECT,(*(&x))+g_ThresholdAt0065782C+g_ThresholdAt0065782C,
            reinterpret_cast<int&>(y),reinterpret_cast<char&>(facing),1);
        PlaySoundAt453D40(R1190_SOUND);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==12 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<10) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(10);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==14 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        SetAuxActionAt40FB40(12);
    }
    break;
}
