case R1191_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
#if !R1191_AIR
        ClearMotionFields();
#endif
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
#if R1191_AIR
    if ((animationStage)>=0) velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        break;
    }
    if (AdvanceNestedFrame()==(field070)) SetAuxActionAt40FB40(9);
#else
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
#endif
    if ((animationStage)==R1191_FIRST_STAGE && (animationFrame)==0) {
#include "ReimuCounterShotF1191.inc"
    }
    if ((animationStage)==R1191_FIRST_STAGE+1 && (animationFrame)==0) {
#include "ReimuCounterShotF1191.inc"
    }
    if ((animationStage)==R1191_FIRST_STAGE+2 && (animationFrame)==0 &&
        (reinterpret_cast<signed short&>(scriptCounterF00))<g_ReimuRepeatSettingAt006714D0*3+1) {
#include "ReimuCounterShotF1191.inc"
        SetAuxActionAt40FB40(R1191_FIRST_STAGE);
    }
    break;
}
