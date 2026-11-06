case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
    if (S16(0x62)==0 && S16(0x64)==0) {
        SetNonnegativeWordAt453E80(40);
        PrepareActionAt453D60(0x17);
        SpawnAt453C80(R1190_AUX_EFFECT,float(*reinterpret_cast<signed char*>(RAW+0x66)*24)+F32(0x44),
            (*(&POS48))+g_ReimuMeterInitialYAt00659084,*reinterpret_cast<char*>(RAW+0x66),1);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
#if R1190_HAS_ANIMATION
        StartAnimationAt46D000(500);
#endif
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==7 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(R1190_EFFECT,(*(&F32(0x44)))+g_ContactProjectionAt00657888+
            (*reinterpret_cast<signed char*>(RAW+0x66)*128),
            (*(&POS48))+g_ReimuMeterShotYAt00659080,*reinterpret_cast<char*>(RAW+0x66),1);
        PlaySoundAt453D40(R1190_SOUND);
    }
    if (S16(0x62)==12 && S16(0x64)==0 && S16(0xF00)<R1190_LIMIT) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(10);
    }
    break;
}
