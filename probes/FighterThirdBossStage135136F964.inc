// F964 original Japanese 004AC040 movement states 135 and 136.
// Native entry/landing paths clear the cancellation state, not the four
// motion fields; ClearMotionFields would incorrectly zero X/Y velocity and
// both acceleration words. Preserve the native field07C/hit-stop writes.
// State 135 falls during stages 3/4, then damps X after stage 4; state 136
// uses exact ground-Y equality for its X drag and lands only before stage 12.
// The native ContextBase::ClearCancel call still lacks a typed source wrapper.
// Original third-fighter native game action 135, candidate.
case 0x135: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if ((animationStage)==3 || (animationStage)==4) {
        velocityY=velocityY-g_AnimationDeltaAt0065747C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            y=0.0f;
            ResetSecondaryCounter(5);
            SpawnAuxEffect(0x80,
                float((facing)*150)+(x),
                y,facing,1);
            break;
        }
    }
    if ((animationStage)>4) {
        velocityX=(velocityX)-g_F964_LateFallAt00658048;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=15.0f;
        velocityY=4.5f;
        field3AC=0;
    }
    if ((animationStage)==5 && (animationFrame)==0)
        velocityX=4.0f;
    break;
}
// Original third-fighter native game action 136, candidate.
case 0x136: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=2;
        field07C=0;
    }
    if ((field3AC)>0 && y==g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C && (animationStage)<12) {
            y=0.0f;
            ResetSecondaryCounter(0xC);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        velocityX=4.0f;
        velocityY=9.5f;
        field05C=1.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        Fighter::SpawnTrackedEffect(0x337,x,y,
            facing,1,0,1);
    }
    if ((animationStage)==9 && (animationFrame)==0)
        field07C=0;
    break;
}
