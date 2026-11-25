// F953 original Japanese TH075 giant 004AC040 action 0xCD native
// 435 complete inner CODE B /128 x86 and 11 true original typed
// PE external fields; this is NOT an independent whole function.
// Real state transition fires raw 0x3C projectile BEFORE writing
// the new frame/trajectory values. Full 82KB parent remains NONEXACT.
case 0xCD: {
    if ((*(&y) == FloatConstants::Zero) ||
        velocityY > FloatConstants::Zero) {
        SetCommandSelection(3,4,0xFF);
        grazeFrames=2;
    }
    if (animationStage==0 && (field3AC)==0)
        ClearMotionFields();
    if (y>FloatConstants::Zero) {
        velocityY=velocityY-verticalAcceleration;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
    if (animationStage==4 &&
        velocityY<FloatConstants::Four)
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
            verticalAcceleration=0.7f;
            field3AC=0;
        }
        if (animationStage>=animationStageCount)
            animationStage=animationStage-2;
        BindAnimation();
    }
    break;
}
