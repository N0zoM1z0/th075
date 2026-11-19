case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
    if ((animationStage)==0 && (animationFrame)==0) {
        SetNonnegativeWordAt453E80(40);
        PlaySharedSound(0x17);
        SpawnAt453C80(R1190_AUX_EFFECT,float(facing*24)+(x),
            (*(&y))+g_ReimuMeterInitialYAt00659084,reinterpret_cast<char&>(facing),1);
        field36C=(field36C)-g_ContactProjectionAt00657888;
#if R1190_HAS_ANIMATION
        UpdateGaugeTimer(500);
#endif
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==7 && (animationFrame)==0) {
        SpawnFloatXYAt453A70(R1190_EFFECT,(*(&x))+g_ContactProjectionAt00657888+
            (facing*128),
            (*(&y))+g_ReimuMeterShotYAt00659080,reinterpret_cast<char&>(facing),1);
        PlaySound(R1190_SOUND);
    }
    if ((animationStage)==12 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<R1190_LIMIT) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(10);
    }
    break;
}
