// F1057: each of 33B/33D/33F/341/343 is 1908 ORIGINAL CODE B /402 x86
// in the ONE nonexact 0050A580 original CharacterObject Advance.
// Original PE proves the five share opcode, width, GPR, field/call policy.
// Only physical native stack scratch owners differ per independent case,
// and the native next-state sprite IDs are 33C/33E/340/342/344.
// The C++ source declares real per-case values; no fake locals/ASM.
// Original actor X/Y, target grandparent X/Y and actual native game calls.
case F1057_CASE: {
    if (x>GeometryConstants::ThirteenHundredEighty ||
        x<GeometryConstants::NegativeHundred ||
        y>GeometryConstants::Thousand ||
        y<GeometryConstants::NegativeTwoHundredForty) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>49 &&
        owner->action<150 &&
        animationStage<2) {
        ClearFrameInfo();
        for (int shot=0;shot<3;++shot) {
            owner->SpawnBattleEffect(
                0x3E4, x,y,1,1);
        }
        if (owner->fieldEFA>25) {
            owner->fieldEFA=0;
            owner->SpawnBattleEffect(
                0x3E3, x,y,1,1);
        }
        return;
    }
    if (collisionResult==5) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
        remainingHits=3;
        collisionResult=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=10;
        field0DA=0;
        field0DE=0;
        field0DC=short(field0C8);
    }
    if (animationStage<=1) {
        field0DA=short(AngleAt00483300(
            (owner->opponent->y-y)+GeometryConstants::Hundred,
            (owner->opponent->x-x)*float(facing)) /
            GeometryConstants::RadiansPerDegree);
        if (field0DA>field0DC+10)
            field0DC=short(field0DC+1);
        if (field0DA<field0DC-10)
            field0DC=short(field0DC-1);
        if (field0DC>90)
            field0DC=90;
        if (field0DC<-90)
            field0DC=-90;
    }
    if (animationStage<=1) {
        SetPolarVelocity(
            float(field0DC),
            float(field0D8)*FloatConstants::OneTenth+GeometryConstants::Fifteen);
        owner->SpawnBattleEffect(
            F1057_NEXT_CASE, x,y,
            facing,1);
        scaleX=float(double(RecordedRange(0,4)-2)*
            FloatConstants::OneTwentiethDouble+FloatConstants::OneDouble);
        scaleY=scaleX;
    }
    field0D8=short(field0D8+2);
    if (animationStage>0 && field0DA<60) {
        if ((*(&owner->opponent->y))+GeometryConstants::Hundred<y)
            field0C8=(field0C8)+FloatConstants::Two;
        if ((*(&owner->opponent->y))+GeometryConstants::Hundred>y)
            field0C8=(field0C8)-FloatConstants::Two;
        ++field0DA;
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (collisionResult!=0 && collisionResult!=6 && animationStage==1) {
        if (remainingHits==0 || collisionResult!=4) {
            velocityX=0.0f;
            velocityY=0.0f;
            ResetSecondaryCounter(2);
            scaleX=2.5f;
            scaleY=2.5f;
            return;
        }
        if (remainingHits>0 && collisionResult==4 && remainingHits>0)
            collisionResult=0;
    }
    if (animationStage>1) {
        scaleX=(scaleX)*g_F1055_FadeScaleAt006598A4;
        scaleY=(scaleY)*g_F1055_FadeScaleAt006598A4;
        if (color[0]>=25)
            color[0]-=25;
        else {
            color[0]=0;
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    if (animationStage==2 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
