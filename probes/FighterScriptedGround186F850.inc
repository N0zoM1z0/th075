// F850 current original native actor 0x186 natural falling/animation source.
// Entire original game case, not an independent callable function.
case 0x186: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
        velocityX=12.5f;
    }
    if ((animationStage)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        PlaySharedSound(0x1D);
        SpawnBattleEffect(0x341,x,y,(facing),1);
    }
    return;
}
