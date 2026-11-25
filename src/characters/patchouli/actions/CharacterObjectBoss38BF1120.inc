// F1120: original Japanese 0x38B, PE 0051C3ED..0051C82D:
// 1,088 original CODE B /226 native x86 in ONE NONEXACT 81KB Boss.
case 0x38B: {
    if (x>GeometryConstants::ThirteenHundredEighty ||
        x<GeometryConstants::NegativeHundred ||
        y>GeometryConstants::Thousand ||
        y<GeometryConstants::NegativeTwoHundredForty) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0x80;
        velocityX=20.0f;
        field0D8=0;
        field0DA=0;
        field0DC=0;
        remainingHits=0;
        collisionResult=0;
    }
    if (field0DC==0) {
        velocityX=velocityX-FloatConstants::FourFifths;
        if (velocityX<FloatConstants::One) {
            velocityX=1.0f;
            field0DC=1;
        }
    }
    if (field0DC>0 && field0DC<30)
        ++field0DC;
    if (field0DC>29)
        velocityX=(*(&velocityX))+FloatConstants::Half;
    if (field0D8==0) {
        if (scaleX<FloatConstants::One) {
            scaleX=(scaleX)+FloatConstants::OneTenth;
            scaleY=(scaleY)+FloatConstants::OneTenth;
            color[0]=unsigned char(color[0]+25);
        } else {
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
        }
        if (color[0]==0xFF && field0D8==0) {
            ++field0D8;
            remainingHits=1;
        }
    }
    if (collisionResult==6) {
        collisionResult=0;
        ++remainingHits;
    }
    if (collisionResult!=0) {
        ++field0D8;
        if (field0D8>5) {
            field0D8=0;
            collisionResult=0;
        }
    }
    x=float(facing)*velocityX+x;
    if (remainingHits==0 && animationStage<0x17 && field0D8>0) {
        ResetSecondaryCounter(0x17);
        return;
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0x17 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
