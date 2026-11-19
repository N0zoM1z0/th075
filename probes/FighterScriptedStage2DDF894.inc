// F894 original 2DD physical native complete 535B/153x86, next physical handler 2E4.
// Stage3 truly used random0..6 FILD EBP-0x10C, stage18 sprite335 and stage26 aux24.
// This is an inner case, whole 46755B fighter NONEXACT and uncredited.
case 0x2DD: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        fieldF04=0;
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        field07C=0;
        field080=1;
        velocityX=10.0f;
        velocityY=0.0f;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)<26) {
        velocityY=velocityY-g_F894VerticalStageAt00659090;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetSecondaryCounter(26);
            velocityX=0.0f;
            velocityY=0.0f;
            y=0.0f;
            return;
        }
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        aiCardTimer=RecordedRange(0,60);
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        SpawnAuxEffect(0x7F,x,y,
            (facing),1);
        velocityX=float(RecordedRange(0,6))+g_F894RandomHeightAt006592A0;
        velocityY=16.0f;
        field07C=0;
        field080=1;
    }
    if ((animationStage)==18 && (animationFrame)==0) {
        SpawnBattleEffect(0x335,x,y,
            (facing),1);
        PlaySound(4);
    }
    if ((animationStage)==26 && (animationFrame)==0)
        ResetSecondaryCounter(24);
    return;
}
