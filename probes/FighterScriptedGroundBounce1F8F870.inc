// F870 original native 1F8 complete 469B/143-x86/15 physical PE fields.
// Native FUCOMPP requires bare y==global, generating FLD global then FLD member.
// Actual x87 ground contact, stage3 sprite7F, stage7 sprite335, stage15 auxE.
// Full original giant remains register and two-final-JMP NONEXACT.
case 0x1F8: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1;
        field07C=0;
        field3AC=0;
    }
    if ((velocityX)>g_ThresholdAt0065782C) {
        if (y==g_ThresholdAt0065782C) {
            velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
            if ((velocityX)<g_ThresholdAt0065782C)
                velocityX=0.0f;
        }
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ClearMotionFields();
            ResetSecondaryCounter(0xF);
            y=0.0f;
            return;
        }
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=8.0f;
        velocityY=12.0f;
        field05C=0.8f;
        SpawnAuxEffect(0x7F,x,y,
            (facing),1);
    }
    if ((animationStage)==7 && (animationFrame)==0) {
        SpawnBattleEffect(0x335,x,y,
            (facing),1);
        PlaySound(4);
    }
    if ((animationStage)==0xF && (animationFrame)==0)
        ResetSecondaryCounter(0xE);
    return;
}
