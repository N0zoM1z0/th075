// Native 194/195 airborne five-shot policy, with explicit per-shot values.
case R1187_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    velocityY=velocityY-field05C;
    if (GetNativeActionAt40FA30()==(field070)) SetNativeActionAt40FAC0(9);
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=-3.0f; velocityY=8.0f; field05C=0.55f;
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(100);
    }
    if ((animationStage)==6 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2 &&
        reinterpret_cast<unsigned int&>(inputC)>0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(25);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(4);
    }
    break;
}
