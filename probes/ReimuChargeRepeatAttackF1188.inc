case R1188_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1; I32(0x7C)=0; FLAG=0; S16(0xF00)=0;
    }
#include "ReimuChargeTransformF1188.inc"
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>R1188_RETURN_STAGE-1) {
        POS54=POS54-g_AnimationDeltaAt0065747C;
        if (POS48+POS54<=g_ThresholdAt0065782C && S16(0x62)<R1188_LAND_STAGE) {
            POS48=0.0f; POS54=0.0f;
            SetAuxActionAt40FB40(R1188_LAND_STAGE);
        }
    }
    if (S16(0x62)>R1188_LAND_STAGE+1) {
        POS=POS-g_ReimuRepeatDragAt00659090;
        if (POS<g_ThresholdAt0065782C) POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==R1188_RETURN_STAGE && S16(0x64)==0) {
        F32(0x44)=float(*reinterpret_cast<signed char*>(RAW+0x66)*100)+F32(0x44);
        POS48=50.0f; POS=12.0f; POS54=6.0f;
        PlaySoundAt453D40(2);
    }
    if (S16(0x62)==R1188_LAND_STAGE+2 && S16(0x64)==0 && S16(0xF00)<1) {
        SetAuxActionAt40FB40(R1188_LAND_STAGE);
        ++S16(0xF00);
    }
    break;
}
