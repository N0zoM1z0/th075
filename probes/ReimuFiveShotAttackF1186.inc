// Two real five-shot sequences with actor-observed per-shot parameter writes.
// The repeated expression evaluations are present in the original callable.
case R1186_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
    if ((animationStage)==8 && (animationFrame)==0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySound(0);
        UpdateGaugeTimer(100);
    }
    if ((animationStage)==10 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2 &&
        reinterpret_cast<unsigned int&>(inputC)>0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySound(0);
        UpdateGaugeTimer(25);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(8);
    }
    break;
}
