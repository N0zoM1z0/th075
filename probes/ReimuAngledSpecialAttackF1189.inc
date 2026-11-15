case R1189_ACTION: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
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
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(9);
#endif
    if ((reinterpret_cast<signed short&>(animationStage))==R1189_FIRE_STAGE && (reinterpret_cast<signed short&>(animationFrame))==0) {
#include "ReimuSpecialVolleyF1189.inc"
        StartAnimationAt46D000(R1189_ANIMATION);
        PlaySoundAt453D40(5);
    }
#if !R1189_AIR
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
#endif
    break;
}
