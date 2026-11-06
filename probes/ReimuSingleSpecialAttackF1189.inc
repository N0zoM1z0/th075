case R1189_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
#if R1189_AIR
        POS=POS*g_BounceScaleAt00657F74;
        POS54=(*(&POS54))*g_BounceScaleAt00657F74;
        I32(0x7C)=1;
#else
        I32(0x7C)=1;
        ResetAt453E20();
#endif
    }
#if R1189_AIR
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
#endif
    if (S16(0x62)==R1189_FIRE_STAGE && S16(0x64)==0) {
#include "ReimuSpecialShotF1189.inc"
#if R1189_HAS_PREPARATION
        PrepareActionAt453D60(0x29);
#endif
        StartAnimationAt46D000(200);
    }
#if !R1189_AIR
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
#endif
    break;
}
