// F628 original complete indexed actions 0x8C/0x8F/0x90: native
// fighter landing with true x87 ground boundary, 0x490 reflection,
// and stage3 animation counter. These are inner CASE bodies only;
// the original enclosing giant fighter Advance() remains NONEXACT.
case F628_CASE: {
    if (animationStage==0 && animationFrame==0) {
        velocityX=F628_START_POS;
        velocityY=0.0f;
        collisionResult=0;
        scriptCounterF00=0;
    }
    if ((velocityX)<FloatConstants::Zero) {
        velocityX=(velocityX)+FloatConstants::ThreeFifths;
        if ((velocityX)>FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (CheckHorizontalLimits() && field3BE)
        opponentVelocityDeltaX=(velocityX)*FloatConstants::ThreeQuartersDouble;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetPrimaryCounters(0);
    if (animationStage==3 && animationFrame==0 && scriptCounterF00<F628_LIMIT) {
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
    }
    break;
}
