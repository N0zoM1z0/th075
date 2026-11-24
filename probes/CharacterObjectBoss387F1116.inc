// F1116: original Japanese action 0x387, PE 0051B5AF..0051B89F,
// 752 native CODE bytes/167 x86 within ONE still-NONEXACT 81KB boss.
case 0x387: {
    if (x>GeometryConstants::ThirteenHundredEighty ||
        x<GeometryConstants::NegativeHundred ||
        y>GeometryConstants::Thousand ||
        y<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ=float(RecordedRange(0,0x167));
        velocityX=float(RecordedRange(0,16)-8);
        velocityY=float(RecordedRange(0,6)+12);
    }
    // The native stage-zero guard jumps to ordinal 92: BOTH the
    // velocity decrement and angle nudge run on every frame.
    velocityY=velocityY-g_F1116_YOffsetAt00659888;
    rotationZ=(rotationZ)+GeometryConstants::Twenty;
    x=float(facing)*velocityX+x;
    y=y+velocityY;
    if (animationStage==1) {
        if (y+velocityY<=FloatConstants::Zero) {
            ResetSecondaryCounter(2);
            velocityY=-velocityY;
            y=0.0f;
        }
    }
    if (animationStage==2) {
        if (color[0]>15)
            color[0]-=15;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
