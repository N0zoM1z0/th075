case R1187_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=POS*g_ProjectileFallAt006590B4;
        POS54=(*(&POS54))*g_ProjectileFallAt006590B4;
        I32(0x7C)=1;
        S16(0xF00)=0;
    }
    if (S16(0x62)>5) POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        POS48=0.0f; POS5C=0.0f; POS54=0.0f;
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
#include "ReimuThreeRandomShotsF1187.inc"
    break;
}
