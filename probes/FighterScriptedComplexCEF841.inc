// F841 selected original actor 0xCE native 387B/113 x86/8 real PE fields.
// Distinct stage3 native -11.0f X, +17.5f velocity, +0.8f drag.
// Real unconditional virtual frame method, native x87 operand order.
// Interior case only, no independently callable exact CODE.
case 0xCE: {
    if (y==FloatConstants::Zero || velocityY>FloatConstants::Zero) {
        SetCommandSelection(3,4,0xFF);
        field088=2;
    }
    if (animationStage==0 && (field3AC)==0)
        ClearMotionFields();
    if (animationStage>2) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetPrimaryCounters(0xA);
            y=0.0f;
            ClearMotionFields();
            return;
        }
    }
    ++animationFrame;
    if (animationFrame>=animationFrameCount) {
        animationFrame=0;
        ++animationStage;
        if (animationStage==3) {
            velocityX=-11.0f;
            velocityY=17.5f;
            field05C=0.8f;
            SpawnAuxEffect(0x3C,x,y,1,1);
            field3AC=0;
        }
        if (animationStage>=animationStageCount)
            animationStage=animationStage-2;
        BindAnimation();
    }
    return;
}
