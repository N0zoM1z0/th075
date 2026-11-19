// Original fighter 00543210 falling-recovery handlers 0x12C..0x12E.
// This is one native switch case in the still-NONEXACT whole Advance().
// The F653_* parameters reflect the three distinct original action states.
case F653_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(F653_NEXT_ACTION);
#if F653_CLEAR_F00
        scriptCounterF00=0;
#endif
    }
    if ((animationStage)==F653_PREPARE_FRAME && (animationFrame)==0)
        PlaySharedSound(F653_PREPARE_ANIM);
    break;
}
