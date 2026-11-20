case F760_ACTION: {
    if ((*(&y)==g_ThresholdAt0065782C) ||
        velocityY>g_ThresholdAt0065782C) {
        SetCommandSelection(3,4,0xFF);
        field088=2;
    }
    if ((animationStage)==0 && (field3AC)==0)
        ClearMotionFields();
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetPrimaryCounters(0xA);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
#if F760_HAS_AUX
    if ((animationStage)==4 && velocityY<g_ExtraThresholdAt00657D14)
        ResetSecondaryCounter(5);
#endif
    ++animationFrame;
    if ((animationFrame)>=(animationFrameCount)) {
        animationFrame=0;
        ++animationStage;
        if ((animationStage)==2) {
            velocityX=F760_POS;
            velocityY=F760_SPEED;
            field05C=0.85f;
            field3AC=0;
            SpawnAuxEffect(0x3C,x,y,1,1);
        }
        if ((animationStage)>=(animationStageCount))
            animationStage=(animationStage)-2;
        BindAnimation();
    }
    break;
}
