// F1102 original Japanese 0x35B, native 00515F65..005163BA:
// 1109 native CODE B /233 x86 in ONE still-NONEXACT 81KB parent.
case 0x35B: {
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<0x17) {
        ClearFrameInfo();
        for (int shot=0;shot<8;++shot)
            owner->SpawnBattleEffect(
                0x3E4,x,y,1,1);
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
        velocityX=22.0f;
        field0D8=0;
        field0DA=0;
        remainingHits=0;
        collisionResult=0;
    }
    velocityX=velocityX-FloatConstants::TwoFifths;
    if (velocityX<FloatConstants::One)
        velocityX=1.0f;
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
    if (collisionResult!=0)
        remainingHits=0;
    x=float(facing)*velocityX+x;
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
        field0DA<1) {
        ResetSecondaryCounter(1);
        ++field0DA;
    }
    return;
}
