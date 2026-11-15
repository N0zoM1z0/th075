case R1189_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
#if R1189_AIR
        velocityX=(velocityX)*g_BounceScaleAt00657F74;
        velocityY=(*(&velocityY))*g_BounceScaleAt00657F74;
        field07C=1;
#else
        field07C=1;
        ResetAt453E20();
#endif
    }
#if R1189_AIR
    if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(9);
#endif
    if ((animationStage)==R1189_FIRE_STAGE && (animationFrame)==0) {
#include "ReimuSpecialShotF1189.inc"
#if R1189_HAS_PREPARATION
        PrepareActionAt453D60(0x29);
#endif
        StartAnimationAt46D000(200);
    }
#if !R1189_AIR
    if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
#endif
    break;
}
