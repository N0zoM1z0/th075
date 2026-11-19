// Native Reimu CC/CD/CE motion loop. Parameters are actual actor policies;
// this source is included only by the live nonexact 0045DD70 parent.
case R1185_ACTION: {
    if ((*(&y)==g_ThresholdAt0065782C) || velocityY>g_ThresholdAt0065782C) {
        ConfigureStormAt454BC0(3,4,0xFF);
        field088=2;
    }
    if ((animationStage)==0 && (field3AC)==0) ClearMotionFields();
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
#if R1185_HAS_AUX
    if ((animationStage)==4 && velocityY<g_ExtraThresholdAt00657D14) ResetSecondaryCounter(5);
#endif
    ++animationFrame;
    if ((animationFrame)>=(field072)) {
        animationFrame=0;
        ++animationStage;
        if ((animationStage)==2) {
            velocityX=R1185_X_SPEED;
            velocityY=R1185_Y_SPEED;
            field05C=0.65f;
            field3AC=0;
            SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
        if ((animationStage)>=(field070)) animationStage=(animationStage)-2;
        BindAnimation();
    }
    break;
}
