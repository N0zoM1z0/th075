// F824 original actor native 9E ground boost; direct void-function exits. Whole 243B/66 x86; never independent original CODE.
// F637 natural original case0x9E: timed ground approach + launch.
// This is a case within a still NONEXACT huge fighter Advance(),
// not an accepted whole original function or ASM byte substitution.
case 0x9E: {
    cardGauge=(cardGauge)+g_AnimationDeltaAt0065747C;
    if ((cardGauge)>g_AnimationMaximumAt006583B4)
        cardGauge=1000.0f;
    if (animationStage==0 && animationFrame==0) {
#if F637_EXTRA_FLAG && F637_EXTRA_BEFORE
        fieldF0A=0;
#endif
        velocityX=-6.0f;
        velocityY=8.0f;
        field05C=0.75f;
#if F637_EXTRA_FLAG && !F637_EXTRA_BEFORE
        fieldF0A=0;
#endif
    }
    // Original 005D73C0 uses a STRICT above-ground comparison:
    // native FCOMP/TEST AH,0x41/JNE. The other ten use >=, whose
    // genuine original TEST AH,1/JNE has different equality behavior.
#if F637_STRICT_ABOVE
    if (y>g_ThresholdAt0065782C) {
#else
    if (y>=g_ThresholdAt0065782C) {
#endif
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(0xA);
            y=0.0f;
            ResetAt453E20();
            return;
        }
    }
    if (GetNativeActionAt40FA30()==field070)
        SetNativeActionAt40FAC0(9);
    return;
}
