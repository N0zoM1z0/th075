// F628 original complete indexed actions 0x8C/0x8F/0x90: native
// fighter landing with true x87 ground boundary, 0x490 reflection,
// and stage3 animation counter. These are inner CASE bodies only;
// the original enclosing giant fighter Advance() remains NONEXACT.
case F628_CASE: {
    if (animationStage==0 && animationFrame==0) {
        velocityX=F628_START_POS;
        velocityY=0.0f;
        field07C=0;
        I16(F628_COUNTER)=0;
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
    if (animationStage==3 && animationFrame==0 && I16(F628_COUNTER)<F628_LIMIT) {
        ++I16(F628_COUNTER);
        ResetSecondaryCounter(1);
    }
    break;
}
