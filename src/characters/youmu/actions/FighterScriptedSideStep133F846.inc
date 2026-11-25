// F846 selected actor original 0x133, 270B/78 x86/6 genuine PE fields.
// Native stage8 direction*70 integer-to-float conversion precedes ADD
// to observed Actor::x; this original GPR/x87 order naturally matches.
// This is a whole giant function interior, not independent callable CODE.
case 0x133: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        remainingHits=1;
        collisionResult=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        scriptCounterF00=0;
    }
    if ((animationStage)==5 && (animationFrame)==0)
        PlaySharedSound(0x1D);
    if ((animationStage)==8 && (animationFrame)==0)
        x=float((facing)*70)+(x);
    return;
}
