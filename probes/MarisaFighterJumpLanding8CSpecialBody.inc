// Original Marisa 0x8C pre-switch landing branch.
// F628 original complete indexed actions 0x8C/0x8F/0x90: native
// fighter landing with true x87 ground boundary, 0x490 reflection,
// and stage3 animation counter. These are inner CASE bodies only;
// the original enclosing giant fighter Advance() remains NONEXACT.
action8CSpecial: {
    if (animationStage==0 && animationFrame==0) {
        velocityX=-11.0f;
        velocityY=0.0f;
        field07C=0;
        scriptCounterF00=0;
    }
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=(velocityX)+g_JumpGroundCorrectionAt00658058;
        if ((velocityX)>g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (CheckHorizontalLimits() && field3BE)
        field490=(velocityX)*g_JumpReflectionAt006583E8;
    if (AdvanceNestedFrame()==field070)
        ResetPrimaryCounters(0);
    if (animationStage==3 && animationFrame==0 && scriptCounterF00<5) {
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
    }
    return;
}
