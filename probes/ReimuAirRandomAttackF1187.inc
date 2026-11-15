case R1187_ACTION: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=(velocityX)*g_ProjectileFallAt006590B4;
        velocityY=(*(&velocityY))*g_ProjectileFallAt006590B4;
        field07C=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>5) velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        break;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(9);
#include "ReimuThreeRandomShotsF1187.inc"
    break;
}
