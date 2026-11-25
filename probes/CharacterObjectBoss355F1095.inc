// F1095: independent Japanese original game action 0x355,
// 00514FE8..005154ED = 1285 original CODE B /270 native x86.
// One authentic state inside the still-NONEXACT 81KB CharacterObject.
case 0x355: {
    if (owner->action>0x45 &&
        owner->action<0x96) {
        ClearFrameInfo();
        for (int shot=0;shot<10;++shot) {
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
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=10.0f;
        velocityY=6.0f;
        field0D8=0;
        field0DA=0;
        field0DC=0;
        remainingHits=0;
        collisionResult=0;
    }
    if (scaleX<FloatConstants::OneAndThreeTenths) {
        scaleX=(scaleX)+FloatConstants::OneTenth;
        scaleY=(scaleY)+FloatConstants::OneTenth;
    } else if (field0D8==0) {
        remainingHits=10;
        ++field0D8;
    }
    if (velocityX>FloatConstants::Half) {
        velocityX=velocityX-FloatConstants::Half;
        if (velocityX<FloatConstants::Half)
            velocityX=0.5f;
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
    if (collisionResult==4 && remainingHits>0)
        collisionResult=0;
    if (collisionResult!=0 && animationStage<0x1F) {
        ResetSecondaryCounter(0x1F);
        velocityX=0.0f;
        velocityY=0.0f;
        field0DC=2;
    }
    if (animationStage==0x1F) {
        scaleX=(scaleX)+FloatConstants::OneFifth;
        scaleY=(scaleY)+FloatConstants::OneFifth;
        color[0]=unsigned char(color[0]-25);
    }
    y=y+velocityY;
    x=float(facing)*velocityX+x;
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    if (animationStage==0x1F && animationFrame==0) {
        if (field0DA<6) {
            ++field0DA;
            ResetSecondaryCounter(1);
            return;
        }
        velocityX=0.0f;
        velocityY=0.0f;
        field0DC=2;
    }
    return;
}
