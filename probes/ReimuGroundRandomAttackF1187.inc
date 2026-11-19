case R1187_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(0);
#include "ReimuThreeRandomShotsF1187.inc"
    break;
}
