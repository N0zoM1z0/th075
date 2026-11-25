// F839 real original selected 005214B0 caseCC 428B/126-x86/10 real PE fields.
// Native float evaluation order y+velocityY and vtable call OUTSIDE
// conditional stage-short decrement. Genuine direct parent exits.
// Not an independently callable original game function.
case 0xCC: {
    if (y==FloatConstants::Zero || velocityY>FloatConstants::Zero) {
        SetCommandSelection(3,4,0xFF);
        grazeFrames=2;
    }
    if (animationStage==0 && (field3AC)==0)
        ClearMotionFields();
    if (animationStage>2) {
        velocityY=velocityY-verticalAcceleration;
        if (y+velocityY<=FloatConstants::Zero) {
            ResetPrimaryCounters(0xA);
            y=0.0f;
            ClearMotionFields();
            return;
        }
    }
    if (animationStage==4 && velocityY<FloatConstants::Four)
        ResetSecondaryCounter(5);
    ++animationFrame;
    if (animationFrame>=animationFrameCount) {
        animationFrame=0;
        ++animationStage;
        if (animationStage==3) {
            velocityX=0.0f;
            velocityY=23.0f;
            verticalAcceleration=0.75f;
            SpawnAuxEffect(0x3C,x,y,1,1);
            field3AC=0;
        }
        if (animationStage>=animationStageCount)
            animationStage=animationStage-2;
        BindAnimation();
    }
    return;
}
