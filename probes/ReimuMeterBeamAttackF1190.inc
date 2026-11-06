case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
    if (S16(0x62)==6 && S16(0x64)==0) {
        SetNonnegativeWordAt453E80(40);
        PrepareActionAt453D60(0x17);
        SpawnAt453C80(R1190_AUX_EFFECT,float(*reinterpret_cast<signed char*>(RAW+0x66)*7)+F32(0x44),
            (*(&POS48))+g_ReimuMeterNearYAt00659088,*reinterpret_cast<char*>(RAW+0x66),1);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
    }
    if (S16(0x62)==10 || S16(0x62)==11) StartAnimationAt46D000(5);
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==8 && S16(0x64)==0) {
        SpawnFloatXAt453A70(R1190_EFFECT,(*(&F32(0x44)))+g_ThresholdAt0065782C+g_ThresholdAt0065782C,
            I32(0x48),*reinterpret_cast<char*>(RAW+0x66),1);
        PlaySoundAt453D40(R1190_SOUND);
    }
    if (S16(0x62)==12 && S16(0x64)==0 && S16(0xF00)<10) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(10);
    }
    if (S16(0x62)==14 && S16(0x64)==0 && S16(0xF02)<5) {
        ++S16(0xF02);
        SetAuxActionAt40FB40(12);
    }
    break;
}
