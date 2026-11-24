// Youmu's ground recovery and effect 0x33A in action 0x136.
case 0x136: {
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
    if ((animationStage)>2 && (velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_AnimationDeltaAt0065747C;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    else if (animationStage < animationStageCount) {
        // Continue the current animation.
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnBattleEffect(0x33A,x,y,
            (facing),1);
        PlaySharedSound(0x1D);
    }
    return;
}
