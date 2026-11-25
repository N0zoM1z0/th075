// Native Reimu CC/CD/CE motion loop. Parameters are actual actor policies;
// this source is included only by the live nonexact 0045DD70 parent.
case R1185_ACTION: {
    if ((*(&y)==FloatConstants::Zero) || velocityY>FloatConstants::Zero) {
        SetCommandSelection(3,4,0xFF);
        grazeFrames=2;
    }
    if ((animationStage)==0 && (field3AC)==0) ClearMotionFields();
    if (y>FloatConstants::Zero) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y=0.0f;
            ClearMotionFields();
            break;
        }
    }
#if R1185_HAS_AUX
    if ((animationStage)==4 && velocityY<FloatConstants::Four) ResetSecondaryCounter(5);
#endif
    ++animationFrame;
    if ((animationFrame)>=(animationFrameCount)) {
        animationFrame=0;
        ++animationStage;
        if ((animationStage)==2) {
            velocityX=R1185_X_SPEED;
            velocityY=R1185_Y_SPEED;
            field05C=0.65f;
            field3AC=0;
            SpawnAuxEffect(0x3C,x,y,1,1);
        }
        if ((animationStage)>=(animationStageCount)) animationStage=(animationStage)-2;
        BindAnimation();
    }
    break;
}
