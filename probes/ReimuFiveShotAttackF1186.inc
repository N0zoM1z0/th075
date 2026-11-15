// Two real five-shot sequences with actor-observed per-shot parameter writes.
// The repeated expression evaluations are present in the original callable.
case R1186_ACTION: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=1;
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(100);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2 &&
        reinterpret_cast<unsigned int&>(inputC)>0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(25);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(8);
    }
    break;
}
