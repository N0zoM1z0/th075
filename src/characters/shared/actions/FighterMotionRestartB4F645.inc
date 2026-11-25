#ifndef F645_EXIT
#define F645_EXIT break
#define F645_EXIT_LOCAL_DEFAULT
#endif

// F645 genuine original native B4/B5 motion restart and ground
// threshold transition. This is inside a giant fighter Advance()
// whole source TU that remains NONEXACT, not a callable leaf.
case F645_CASE: {
    if (animationStage==0 && animationFrame==0) {
        ClearMotionFields();
        velocityX=F645_START_POS;
        velocityY=12.5f;
        verticalAcceleration=0.75f;
        rotationZ=0.0f;
        ClearTransformFlag();
    }
    if (y>FloatConstants::Zero) {
        velocityY=velocityY-verticalAcceleration;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetPrimaryCounters(0xA);
            y=0.0f;
            ClearMotionFields();
            F645_EXIT;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetSecondaryCounter(F645_AUX_ACTION);
        F645_EXIT;
    }
    F645_EXIT;
}
#ifdef F645_EXIT_LOCAL_DEFAULT
#undef F645_EXIT_LOCAL_DEFAULT
#undef F645_EXIT
#endif
