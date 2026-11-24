// F1068: native real Japanese original 0050D17A..0050D53A,
// 960 original CODE bytes /209 x86. One case in still-NONEXACT
// original 81KB CharacterObject::Advance; not an independent callable.
case 0x330: {
    if (owner->action>0x45 &&
        owner->action<0x96 &&
        animationStage<3) {
        ClearFrameInfo();
        for (int shot=0;shot<5;++shot) {
            owner->SpawnBattleEffect(
                0x3E4, x, y,1,1);
        }
        if (owner->fieldEFA>25) {
            owner->fieldEFA=0;
            owner->SpawnBattleEffect(
                0x3E3, x, y,1,1);
        }
        return;
    }
    if (field07C==6) {
        ++field080;
        field07C=0;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,60.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field080=1;
        field07C=0;
        velocityY=26.5f;
        owner->PlaySound(3);
        owner->SpawnBattleEffect(
            0x345, x,y,
            facing,1);
    }
    y=y+velocityY;
    if (animationStage==1) {
        rotationZ=(rotationZ)+GeometryConstants::Thirty;
        velocityY=velocityY-FloatConstants::One;
        if (velocityY<FloatConstants::Zero)
            velocityY=0.0f;
    }
    if (animationStage==2) {
        velocityY=velocityY-FloatConstants::Half;
        y=y+velocityY;
        // Real native 0x330 TEST AH,0x41; JNP enters impact handling
        // directly, then checks collision status 0/6 on the other path.
        if (y+velocityY<=FloatConstants::Zero ||
            (field07C!=0 && field07C!=6)) {
            velocityY=0.0f;
            ResetSecondaryCounter(3);
            owner->PlaySound(5);
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    if (animationStage==2 && animationFrame==0) {
        owner->PlaySound(4);
        velocityX=-20.0f;
        rotationZ=0.0f;
    }
    return;
}
