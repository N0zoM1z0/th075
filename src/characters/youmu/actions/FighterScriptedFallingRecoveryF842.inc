// F842 native 005214B0 interior 12C/12D/12E falling/recovery cases.
// Stage/animation parameters recovered from ORIGINAL actor PE, not F653.
// Normal void-function direct return, not independent original CODE.
// Original fighter 00543210 falling-recovery handlers 0x12C..0x12E.
// This is one native switch case in the still-NONEXACT whole Advance().
// The F653_* parameters reflect the three distinct original action states.
case F653_ACTION: {
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
        ResetPrimaryCounters(F653_NEXT_ACTION);
#if F653_CLEAR_F00
        scriptCounterF00=0;
#endif
    }
    if ((animationStage)==F653_PREPARE_FRAME && (animationFrame)==0)
        PlaySharedSound(F653_PREPARE_ANIM);
    return;
}
