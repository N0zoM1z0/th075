case R1187_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=(velocityX)*g_ProjectileFallAt006590B4;
        velocityY=(*(&velocityY))*g_ProjectileFallAt006590B4;
        field07C=1;
        scriptCounterF00=0;
    }
    if ((animationStage)>5) velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        ResetPrimaryCounters(10);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        break;
    }
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(9);
#include "ReimuThreeRandomShotsF1187.inc"
    break;
}
