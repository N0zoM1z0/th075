#ifndef F641_EXIT
#define F641_EXIT break
#define F641_EXIT_LOCAL_DEFAULT
#endif

// F641: genuine original 71-instruction A3/A4/A5 timed landing
// actions with NO trajectory counter reset, unlike the earlier F633
// 73/75-x86 family. This is an inner case of a nonexact giant.
case F641_CASE: {
    pendingSpellCharge=(pendingSpellCharge)+FloatConstants::One;
    if ((pendingSpellCharge)>GeometryConstants::Thousand)
        pendingSpellCharge=1000.0f;
    if (animationStage==0 && animationFrame==0) {
        velocityX=F641_START_HEIGHT;
        velocityY=0.0f;
        collisionResult=0;
    }
    if ((velocityX)<FloatConstants::Zero) {
        velocityX=(velocityX)+FloatConstants::ThreeFifths;
        if ((velocityX)>FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (CheckHorizontalLimits() && field3BE)
        opponentVelocityDeltaX=(velocityX)*FloatConstants::ThreeQuartersDouble;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetPrimaryCounters(F641_NEXT_ACTION);
    F641_EXIT;
}
#ifdef F641_EXIT_LOCAL_DEFAULT
#undef F641_EXIT_LOCAL_DEFAULT
#undef F641_EXIT
#endif
