#ifndef F637_EXIT
#define F637_EXIT break
#define F637_EXIT_LOCAL_DEFAULT
#endif

// F637 natural original case0x9E: timed ground approach + launch.
// This is a case within a still NONEXACT huge fighter Advance(),
// not an accepted whole original function or ASM byte substitution.
case 0x9E: {
    pendingSpellCharge=(pendingSpellCharge)+FloatConstants::One;
    if ((pendingSpellCharge)>GeometryConstants::Thousand)
        pendingSpellCharge=1000.0f;
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
    if (y>FloatConstants::Zero) {
#else
    if (y>=FloatConstants::Zero) {
#endif
        velocityY=velocityY-field05C;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetPrimaryCounters(0xA);
            y=0.0f;
            ClearMotionFields();
            F637_EXIT;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetPrimaryCounters(9);
    F637_EXIT;
}
#ifdef F637_EXIT_LOCAL_DEFAULT
#undef F637_EXIT_LOCAL_DEFAULT
#undef F637_EXIT
#endif
