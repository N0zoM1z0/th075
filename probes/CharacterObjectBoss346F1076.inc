// F1076: genuine Japanese native 00511D25..005123B9 (1684B/365 x86).
// Real 0x346 source inside ONE original 81KB CharacterObject, NONEXACT.
case 0x346: {
    if (collisionResult==5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<5) {
        ClearFrameInfo();
        for (int shot=0;shot<3;++shot) {
            owner->SpawnBattleEffect(
                0x3E4,x,y,1,1);
        }
        if (owner->fieldEFA>25) {
            owner->fieldEFA=0;
            owner->SpawnBattleEffect(
                0x3E3,x,y,1,1);
        }
        return;
    }
    if (animationStage==0 && animationFrame==0 &&
        field0D8==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        collisionResult=0;
        remainingHits=1;
        field0D8=15;
        SetPolarVelocity(field0C8,
                                    float(field0D8));
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (animationStage==1) {
        SetPolarVelocity(field0C8,
                                    float(field0D8));
        --field0D8;
        if (field0D8<0)
            field0D8=0;
        rotationZ=(rotationZ)+GeometryConstants::FortyFive;
    }
    if (animationStage==2) {
        ++field0D8;
        scaleX=(scaleX)+FloatConstants::OneTenth;
        scaleY=(scaleY)*FloatConstants::NinetyEightHundredths;
        SetPolarVelocity(float(field0DC),
                                     float(field0D8));
        rotationZ=AngleAt00483300(
            velocityY,velocityX)/GeometryConstants::RadiansPerDegree;
        owner->field310=AngleAt00483300(
            velocityY,velocityX)/GeometryConstants::RadiansPerDegree;
    }
    if (animationStage==3) {
        ++field0D8;
        scaleX=(scaleX)+FloatConstants::OneTenth;
        scaleY=(scaleY)*FloatConstants::NinetyEightHundredths;
        SetPolarVelocity(float(field0DC),
                                     float(field0D8));
        rotationZ=AngleAt00483300(
            velocityY,velocityX)/GeometryConstants::RadiansPerDegree;
        if (color[0]>10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if ((collisionResult==2 || collisionResult==4) && animationStage==2) {
        ResetSecondaryCounter(3);
        return;
    }
    if (x>GeometryConstants::FourteenHundred ||
        x<GeometryConstants::NegativeHundredSixty ||
        y>GeometryConstants::Thousand ||
        y<GeometryConstants::NegativeHundredSixty) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    if (animationStage==2 && animationFrame==0) {
        field0DC=short(AngleAt00483300(
          ((*(&owner->opponent->y))+GeometryConstants::HundredTwentyEight-y),
          (owner->opponent->x-x)*int(facing)) /
          GeometryConstants::RadiansPerDegree);
    }
    if (animationStage==3 && animationFrame==0)
        ClearFrameInfo();
    return;
}
