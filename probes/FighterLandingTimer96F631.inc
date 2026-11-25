// F631 original native action0x96: real timed float progress, x87
// ground correction, contact rebound and optional extra stage-zero
// projectile counter. Entire giant fighter Advance() is NONEXACT.
case 0x96: {
    pendingSpellCharge=(pendingSpellCharge)+FloatConstants::One;
    if ((pendingSpellCharge)>GeometryConstants::Thousand)
        pendingSpellCharge=1000.0f;
    if (animationStage==0 && animationFrame==0) {
#if F631_EXTRA_FLAG && F631_EXTRA_BEFORE
        // 0058AF60 alone clears this genuine extra flag BEFORE the
        // trajectory short; 00543210 clears it AFTER motion init.
        fieldF0A=0;
#endif
        scriptCounterF00=0;
        velocityX=-9.0f;
        velocityY=0.0f;
        collisionResult=0;
#if F631_EXTRA_FLAG && !F631_EXTRA_BEFORE
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
        ResetPrimaryCounters(0);
    break;
}
