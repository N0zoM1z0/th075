// F1070: original Japanese PE 0050AD46..0050B150, 1034 CODE B /220 x86.
// Genuine gameplay inside ONE nonexact 81KB CharacterObject advance.
case 0x323: {
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
        field080=1;
        field07C=0;
        field0D8=0;
        SetPolarVelocity(field0C8,
            float(field0D8)*FloatConstants::OneTenth+
            GeometryConstants::Forty);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ=AngleAt00483300(
            velocityY,velocityX)/GeometryConstants::RadiansPerDegree;
    }
    ++field0D8;
    if (animationStage<2) {
        SetPolarVelocity(field0C8,
            float(field0D8)*FloatConstants::OneTenth+
            GeometryConstants::TwentyFive);
        if (scaleX<FloatConstants::One) {
            scaleX=(scaleX)+FloatConstants::OneTenth;
            scaleY=(scaleY)+FloatConstants::OneTenth;
        }
    }
    if (field07C==6) {
        field07C=0;
        ++field080;
    }
    if (field07C!=0 && animationStage==1) {
        ResetSecondaryCounter(2);
        scaleX=4.0f;
        scaleY=4.0f;
        velocityX=0.0f;
        velocityY=0.0f;
        return;
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (x>GeometryConstants::ThirteenHundredEighty ||
        x<GeometryConstants::NegativeHundred ||
        y>GeometryConstants::SixHundredForty ||
        y<GeometryConstants::NegativeHundredTwenty) {
        ClearFrameInfo();
        return;
    }
    if (animationStage>1) {
        if (color[0]>=25) {
            color[0]-=25;
            color[1]-=25;
            color[2]-=25;
            scaleX=(scaleX)*FloatConstants::EightyFiveHundredths;
            scaleY=(scaleY)*FloatConstants::EightyFiveHundredths;
        } else {
            color[0]=0;
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
