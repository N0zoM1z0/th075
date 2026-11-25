// F1125 original Japanese action 0x390 at 0051CB4A..0051CF28:
// 990 native CODE B /212 x86 inside ONE still-NONEXACT 81KB boss.
case 0x390: {
    if (owner->spellTimer<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        remainingHits=1;
        collisionResult=0;
        field0D8=0;
        SetPolarVelocity(field0C8,
            float(field0D8)*FloatConstants::OneTenth+GeometryConstants::TwentyFive);
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
            float(field0D8)*FloatConstants::OneTenth+GeometryConstants::TwentyFive);
        if (scaleX<FloatConstants::One) {
            scaleX=(scaleX)+FloatConstants::OneTenth;
            scaleY=(scaleY)+FloatConstants::OneTenth;
        }
    }
    if (collisionResult!=0 && animationStage==1) {
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
