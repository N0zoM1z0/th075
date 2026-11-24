// F1126 genuine Japanese 0x391 at original PE 0051CF28..0051D413:
// 1,259 native CODE B /277 x86 in one incomplete 81KB Boss.
case 0x391: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=3.0f;
        velocityY=FloatConstants::FourAndHalf-float(RecordedRange(0,9));
        field0D8=0;
        field0DA=0;
        field0DC=0;
        field080=0;
        field07C=0;
    }
    if (scaleX<FloatConstants::One) {
        scaleX=(scaleX)+FloatConstants::OneTenth;
        scaleY=(scaleY)+FloatConstants::OneTenth;
    } else {
        scaleX=1.0f;
        scaleY=1.0f;
    }
    if (field0DC==0) {
        velocityY=velocityY-FloatConstants::FifteenHundredths;
        if (velocityY<FloatConstants::NegativeFourAndHalf)
            field0DC=1;
    }
    if (field0DC==1) {
        velocityY=(*(&velocityY))+FloatConstants::FifteenHundredths;
        if (velocityY>FloatConstants::FourAndHalf)
            field0DC=0;
    }
    if (scaleX==FloatConstants::One &&
        g_OptionsModeAt006714D0>1) {
        if (velocityX>FloatConstants::Zero &&
            x>GeometryConstants::TwelveHundredEighty) {
            velocityX=-velocityX;
        }
        if (velocityX<FloatConstants::Zero &&
            x<FloatConstants::Zero)
            velocityX=-velocityX;
    }
    if (field0DA==0 &&
        scaleX==FloatConstants::One) {
        if (owner->opponent->y<y &&
            AbsFloatAt00412D90(x-
                owner->opponent->x)<FloatConstants::Ten) {
            field0DA=1;
            velocityX=0.0f;
            velocityY=-30.0f;
            scaleX=0.1f;
            scaleY=1.0f;
        }
    }
    if (field0DA==1) {
        if (y+velocityY<=FloatConstants::Zero) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(
                0x392,x,0.0f,
                facing,1);
            return;
        }
    }
    if (x>g_F1126_RightAt00659884 ||
        x<GeometryConstants::NegativeHundredEighty) {
        ClearFrameInfo();
        return;
    }
    y=y+velocityY;
    x=float(facing)*velocityX+x;
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    if (animationStage==0x1F && animationFrame==0) {
        ResetSecondaryCounter(1);
        return;
    }
    return;
}
