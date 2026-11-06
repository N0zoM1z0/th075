case R1191_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
#if !R1191_AIR
        ResetAt453E20();
#endif
        S16(0xF00)=0;
    }
#if R1191_AIR
    if (S16(0x62)>=0) POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        POS48=0.0f; POS5C=0.0f; POS54=0.0f;
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetAuxActionAt40FB40(9);
#else
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
#endif
    if (S16(0x62)==R1191_FIRST_STAGE && S16(0x64)==0) {
#include "ReimuCounterShotF1191.inc"
    }
    if (S16(0x62)==R1191_FIRST_STAGE+1 && S16(0x64)==0) {
#include "ReimuCounterShotF1191.inc"
    }
    if (S16(0x62)==R1191_FIRST_STAGE+2 && S16(0x64)==0 &&
        S16(0xF00)<g_ReimuRepeatSettingAt006714D0*3+1) {
#include "ReimuCounterShotF1191.inc"
        SetAuxActionAt40FB40(R1191_FIRST_STAGE);
    }
    break;
}
