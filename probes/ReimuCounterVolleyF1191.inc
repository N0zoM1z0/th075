case R1191_ACTION: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=1;
#if !R1191_AIR
        ResetAt453E20();
#endif
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
#if R1191_AIR
    if ((reinterpret_cast<signed short&>(animationStage))>=0) velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        break;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetAuxActionAt40FB40(9);
#else
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
#endif
    if ((reinterpret_cast<signed short&>(animationStage))==R1191_FIRST_STAGE && (reinterpret_cast<signed short&>(animationFrame))==0) {
#include "ReimuCounterShotF1191.inc"
    }
    if ((reinterpret_cast<signed short&>(animationStage))==R1191_FIRST_STAGE+1 && (reinterpret_cast<signed short&>(animationFrame))==0) {
#include "ReimuCounterShotF1191.inc"
    }
    if ((reinterpret_cast<signed short&>(animationStage))==R1191_FIRST_STAGE+2 && (reinterpret_cast<signed short&>(animationFrame))==0 &&
        (reinterpret_cast<signed short&>(scriptCounterF00))<g_ReimuRepeatSettingAt006714D0*3+1) {
#include "ReimuCounterShotF1191.inc"
        SetAuxActionAt40FB40(R1191_FIRST_STAGE);
    }
    break;
}
