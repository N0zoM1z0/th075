// F826 real original 0xA3/0xA4/0xA5: no 0xF00 reset, 264B/71 x86/9 PE fields each; direct original epilogue exit.
// F641: genuine original 71-instruction A3/A4/A5 timed landing
// actions with NO trajectory counter reset, unlike the earlier F633
// 73/75-x86 family. This is an inner case of a nonexact giant.
case F641_CASE: {
    cardGauge=(cardGauge)+FloatConstants::One;
    if ((cardGauge)>GeometryConstants::Thousand)
        cardGauge=1000.0f;
    if (animationStage==0 && animationFrame==0) {
        velocityX=F641_START_HEIGHT;
        velocityY=0.0f;
        field07C=0;
    }
    if ((velocityX)<FloatConstants::Zero) {
        velocityX=(velocityX)+FloatConstants::ThreeFifths;
        if ((velocityX)>FloatConstants::Zero)
            velocityX=0.0f;
    }
    if (CheckHorizontalLimits() && field3BE)
        field490=(velocityX)*FloatConstants::ThreeQuartersDouble;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetPrimaryCounters(F641_NEXT_ACTION);
    return;
}
