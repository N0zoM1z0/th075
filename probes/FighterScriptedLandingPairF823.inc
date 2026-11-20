// F823 true native 9B/9C natural landing states; each complete 276B/73 x86/9 fields; noncallable original interior.
// F633 genuine sibling original native action0x97/98/9A: timed float progress, x87
// ground correction, contact rebound and optional extra stage-zero
// projectile counter. Entire giant fighter Advance() is NONEXACT.
case F633_CASE: {
    cardGauge=(cardGauge)+g_AnimationDeltaAt0065747C;
    if ((cardGauge)>g_AnimationMaximumAt006583B4)
        cardGauge=1000.0f;
    if (animationStage==0 && animationFrame==0) {
#if F633_EXTRA_FLAG && F633_EXTRA_BEFORE
        // 0058AF60 alone clears this genuine extra flag BEFORE the
        // trajectory short; 00543210 clears it AFTER motion init.
        fieldF0A=0;
#endif
        scriptCounterF00=0;
        velocityX=F633_START_HEIGHT;
        velocityY=0.0f;
        field07C=0;
#if F633_EXTRA_FLAG && !F633_EXTRA_BEFORE
        fieldF0A=0;
#endif
    }
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=(velocityX)+g_JumpGroundCorrectionAt00658058;
        if ((velocityX)>g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (CheckHorizontalLimits() && field3BE)
        field490=(velocityX)*g_JumpReflectionAt006583E8;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetPrimaryCounters(F633_NEXT_ACTION);
    return;
}
