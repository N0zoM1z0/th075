// F633 genuine sibling original native action0x97/98/9A: timed float progress, x87
// ground correction, contact rebound and optional extra stage-zero
// projectile counter. Entire giant fighter Advance() is NONEXACT.
case F633_CASE: {
    pendingSpellCharge=(pendingSpellCharge)+FloatConstants::One;
    if ((pendingSpellCharge)>GeometryConstants::Thousand)
        pendingSpellCharge=1000.0f;
    if (animationStage==0 && animationFrame==0) {
#if F633_EXTRA_FLAG && F633_EXTRA_BEFORE
        // 0058AF60 alone clears this genuine extra flag BEFORE the
        // trajectory short; 00543210 clears it AFTER motion init.
        fieldF0A=0;
#endif
        scriptCounterF00=0;
        velocityX=F633_START_HEIGHT;
        velocityY=0.0f;
        collisionResult=0;
#if F633_EXTRA_FLAG && !F633_EXTRA_BEFORE
        fieldF0A=0;
#endif
    }
    if ((velocityX)<FloatConstants::Zero) {
        velocityX=(velocityX)+FloatConstants::ThreeFifths;
        if ((velocityX)>FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (CheckHorizontalLimits() && field3BE)
        field490=(velocityX)*FloatConstants::ThreeQuartersDouble;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetPrimaryCounters(F633_NEXT_ACTION);
    break;
}
