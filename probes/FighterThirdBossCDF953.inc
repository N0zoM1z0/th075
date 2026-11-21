// F953 original Japanese TH075 giant 004AC040 action 0xCD native
// 435 complete inner CODE B /128 x86 and 11 true original typed
// PE external fields; this is NOT an independent whole function.
// Real state transition fires raw 0x3C projectile BEFORE writing
// the new frame/trajectory values. Full 82KB parent remains NONEXACT.
case 0xCD: {
    if ((*(&y) == g_ThresholdAt0065782C) ||
        velocityY > g_ThresholdAt0065782C) {
        SetCommandSelection(3,4,0xFF);
        field088=2;
    }
    if (animationStage==0 && (field3AC)==0)
        ClearMotionFields();
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
    if (animationStage==4 &&
        velocityY<g_ExtraThresholdAt00657D14)
        ResetSecondaryCounter(5);
    ++animationFrame;
    if (animationFrame>=animationFrameCount) {
        animationFrame=0;
        ++animationStage;
        if (animationStage==2) {
            // Original native call before the actual motion values are reset.
            SpawnAuxEffect(0x3C,x,y,1,1);
            velocityX=10.0f;
            velocityY=15.0f;
            field05C=0.7f;
            field3AC=0;
        }
        if (animationStage>=animationStageCount)
            animationStage=animationStage-2;
        BindAnimation();
    }
    break;
}
