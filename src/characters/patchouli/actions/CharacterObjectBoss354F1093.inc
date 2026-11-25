// F1093 authentic Japanese original 0x354 at 00514B35..00514FE8,
// 1,203 original CODE B /251 x86 inside ONE nonexact 81KB Boss.
case 0x354: {
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<0x17) {
        ClearFrameInfo();
        for (int shot=0;shot<8;++shot) {
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
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=18.0f;
        velocityY=0.0f;
        field0D8=0;
        field0DA=0;
        remainingHits=0;
        collisionResult=0;
    }
    velocityX=velocityX-FloatConstants::TwoFifths;
    velocityY=(*(&velocityY))+FloatConstants::FifteenHundredths;
    if (velocityX<FloatConstants::Two)
        velocityX=2.0f;
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
            remainingHits=5;
        }
    }
    if (collisionResult==6) {
        collisionResult=0;
        ++remainingHits;
    }
    if (collisionResult==4 && remainingHits>0)
        collisionResult=0;
    if (collisionResult!=0) {
        ++field0D8;
        remainingHits=0;
    }
    x=float(facing)*velocityX+x;
    y=y+velocityY;
    if (remainingHits==0 && animationStage<0x17 &&
        field0D8>0) {
        ResetSecondaryCounter(0x17);
        return;
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0x17 && animationFrame==0 &&
        field0DA<0) {
        ResetSecondaryCounter(1);
        ++field0DA;
    }
    return;
}
