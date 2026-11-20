case R1188_ACTION: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f; velocityY=0.0f; field05C=0.0f;
        field080=1; field07C=0;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        velocityX=(velocityX)-g_ReimuLeapDragAt006583FC;
        if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f; velocityY=0.0f; field05C=0.0f; y=0.0f;
            ResetSecondaryCounter(10);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==4 && (animationFrame)==0) {
        SpawnBattleEffect(0x32D,x,y,facing,1);
        PlaySound(3);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=R1188_LEAP_X; velocityY=R1188_LEAP_Y; field05C=0.9f;
        SpawnAuxEffect(0x7F,x,y,facing,1);
    }
    if ((animationStage)==10 && (animationFrame)==0) ResetSecondaryCounter(8);
    break;
}
