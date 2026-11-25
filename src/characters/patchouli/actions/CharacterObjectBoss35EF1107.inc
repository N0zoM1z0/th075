// F1107 native original Japanese 0x35E at 00516646..00516CE4:
// 1694 original CODE B/350 x86 inside ONE still-NONEXACT 81KB Boss.
case 0x35E: {
    if (x>GeometryConstants::ThirteenHundredEighty ||
        x<GeometryConstants::NegativeHundred ||
        y>GeometryConstants::Thousand ||
        y<GeometryConstants::NegativeTwoHundredForty) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96) {
        ClearFrameInfo();
        for (int shot=0;shot<2;++shot)
            owner->SpawnBattleEffect(
                0x3E4,x,y,1,1);
        if (owner->fieldEFA>25) {
            owner->fieldEFA=0;
            owner->SpawnBattleEffect(
                0x3E3,x,y,1,1);
        }
        return;
    }
    if (collisionResult==5) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        remainingHits=1;
        collisionResult=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=60;
        field0DA=0;
        field0DE=0;
        field0DC=short(field0C8);
        rotationZ=AngleAt00483300(
            velocityY,velocityX)/GeometryConstants::RadiansPerDegree;
        SetPolarVelocity(float(field0DC),
            float(field0D8)*FloatConstants::OneTenth);
    }
    if (animationStage>0) {
        if (remainingHits==0) {
            ClearFrameInfo();
            owner->PlaySound(1);
            owner->SpawnBattleEffect(
                0x35F,x,y,
                facing,1);
            return;
        }
        field0D8=short(field0D8+2);
        rotationZ=AngleAt00483300(
            velocityY,velocityX)/GeometryConstants::RadiansPerDegree;
        field0DA=short(AngleAt00483300(
            owner->opponent->y-y+GeometryConstants::Hundred,
            (owner->opponent->x-x)*int(facing)) /
            GeometryConstants::RadiansPerDegree);
        if (field0DC>field0DA) {
            if (field0DC-field0DA<=180) {
                field0DC=short(field0DC-2);
                if (field0DC<-180)
                    field0DC=short(field0DC+360);
            } else {
                field0DC=short(field0DC+2);
                if (field0DC>180)
                    field0DC=short(field0DC-360);
            }
        }
        // Original PE independently checks the UPDATED angle against the
        // target after the greater-than case, not an exclusive else.
        if (field0DC<=field0DA) {
            if (field0DC-field0DA>=-180) {
                field0DC=short(field0DC+2);
                if (field0DC>180)
                    field0DC=short(field0DC-360);
            } else {
                field0DC=short(field0DC-2);
                if (field0DC<-180)
                    field0DC=short(field0DC+360);
            }
        }
    }
    SetPolarVelocity(float(field0DC),
        float(field0D8)*FloatConstants::OneTenth);
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(1);
    return;
}
