// F840 original 005214B0 native CD 387 CODE B/113 x86/8 PE fields.
// Stage3 native velocityX 11, velocity17.5, drag0.8, original vtable call
// outside conditional subtract; native stage3-only field3AC clear.
// Original game interior, not independently callable exact CODE.
case 0xCD: {
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
            velocityX=11.0f;
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
