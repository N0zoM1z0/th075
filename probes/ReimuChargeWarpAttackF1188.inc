case R1188_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1; I32(0x7C)=0; FLAG=0;
    }
#include "ReimuChargeTransformF1188.inc"
    if (POS48>g_ThresholdAt0065782C && S16(0x62)<R1188_LAND_STAGE
#if R1188_HAS_GRAVITY_MIN
        && S16(0x62)>3
#endif
    ) POS54=POS54-g_ReimuChargeFallAt00659094;
    if (S16(0x62)==R1188_LAND_STAGE || S16(0x62)==R1188_LAND_STAGE+1) {
        if (POS48+POS54<g_ThresholdAt0065782C) {
            POS48=0.0f; POS=0.0f; POS54=0.0f;
            SetAuxActionAt40FB40(R1188_LAND_STAGE+2);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==R1188_RETURN_STAGE && S16(0x64)==0) {
        F32(0x44)=*reinterpret_cast<float*>(OWNER+0x44)-float(*reinterpret_cast<signed char*>(RAW+0x66)*180);
        POS48=150.0f; POS=6.0f; POS54=8.0f;
        PlaySoundAt453D40(2);
    }
    if (S16(0x62)==R1188_LAND_STAGE-1 && S16(0x64)==0) {
        POS=5.0f; POS54=-16.0f;
    }
    if (S16(0x62)==R1188_LAND_STAGE+2 && S16(0x64)==0) SetAuxActionAt40FB40(R1188_LAND_STAGE);
    break;
}
