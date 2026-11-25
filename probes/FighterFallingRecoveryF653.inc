// Shared falling recovery for actions 0x12C–0x12E. The F653_* parameters
// select each action's sound cue and transition.
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
    break;
}
