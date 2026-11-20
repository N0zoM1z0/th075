case R1187_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        scriptCounterF00=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
#include "ReimuThreeRandomShotsF1187.inc"
    break;
}
