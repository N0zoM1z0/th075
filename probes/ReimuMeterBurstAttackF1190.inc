case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
#include "ReimuMeterCycleF1190.inc"
#if R1190_AIR
    if (S16(0x62)>11 && POS48>g_ThresholdAt0065782C) {
        POS54=POS54-g_SubtractAt00657478;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(15);
            POS48=0.0f;
            ResetAt453E20();
            break;
        }
    }
#endif
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==2 && S16(0x64)==0) {
        SetNonnegativeWordAt453E80(40);
        PrepareActionAt453D60(0x17);
        SpawnAt453C80(R1190_AUX_EFFECT,*reinterpret_cast<float*>(RAW+0x44)-float(*reinterpret_cast<signed char*>(RAW+0x66)*2),
            (*(&POS48))+g_ReimuCommandBackYAt006590A8,*reinterpret_cast<char*>(RAW+0x66),1);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        StartAnimationAt46D000(500);
    }
    if (S16(0x62)==4 && S16(0x64)==0) {
        SpawnTrackedAt453B50(0x3B6,(*(&F32(0x44)))+g_ThresholdAt0065782C,
            (*(&POS48))+g_ReimuMeterTrailYAt0065835C,*reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    }
    if (S16(0x62)==12 && S16(0x64)==0 && S16(0xF00)<13) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(10);
    }
#if R1190_AIR
    if (S16(0x62)==15 && S16(0x64)==0) SetAuxActionAt40FB40(13);
#endif
    break;
}
