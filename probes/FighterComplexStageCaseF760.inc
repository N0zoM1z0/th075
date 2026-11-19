case F760_ACTION: {
    if ((*(&y)==g_ThresholdAt0065782C) ||
        velocityY>g_ThresholdAt0065782C) {
        ConfigureStormAt454BC0(3,4,0xFF);
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
    if ((animationFrame)>=(field072)) {
        animationFrame=0;
        ++animationStage;
        if ((animationStage)==2) {
            velocityX=F760_POS;
            velocityY=F760_SPEED;
            field05C=0.85f;
            field3AC=0;
            SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
        if ((animationStage)>=(field070))
            animationStage=(animationStage)-2;
        BindAnimation();
    }
    break;
}
