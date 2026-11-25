// F1108/F1109: five separate original Japanese native actions 0x360..0x364.
// Source is one genuine repeated game-logic family, instantiated at five
// distinct physical PE switch entries inside ONE NONEXACT 81KB callable.
// Original each 206 x86, but native CODE width is 952/952/951/964/964 B.
// NEXT_ID must retain 0x365/0x366/0x367/0x368/0x369 respectively.
case F1108_CASE: {
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<2) {
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
    if (animationStage==0) {
        SetPolarVelocity(field0C8,
            float(field0D8));
        --field0D8;
        if (field0D8<0)
            field0D8=0;
        rotationZ=(rotationZ)+GeometryConstants::Thirty;
    }
    if (x>GeometryConstants::FourteenHundred ||
        x<GeometryConstants::NegativeHundredSixty ||
        y>GeometryConstants::Thousand ||
        y<GeometryConstants::NegativeHundredSixty) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        owner->field314=field0C8;
        owner->SpawnBattleEffect(
            F1108_NEXT_ID,x,y,
            facing,1);
        ClearFrameInfo();
    }
    return;
}
