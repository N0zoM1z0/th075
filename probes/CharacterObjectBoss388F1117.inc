// F1117: genuine original Japanese action 0x388, PE
// 0051B89F..0051BB8B, 748 native CODE B /160 x86. One inner
// state of the still-NONEXACT 81KB CharacterObject Advance.
case 0x388: {
    if (owner->spellTimer<=0) {
        ClearFrameInfo();
        return;
    }
    if (collisionResult==6) {
        ++remainingHits;
        collisionResult=0;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,60.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        remainingHits=1;
        collisionResult=0;
        velocityY=22.5f;
        owner->PlaySound(3);
        owner->SpawnBattleEffect(
            0x345,x,y,
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
        // Native TEST AH,0x41; JNP jumps straight INTO the hit
        // body. Otherwise, only then consult native status 0/6.
        if (y+velocityY<=FloatConstants::Zero ||
            (collisionResult!=0 && collisionResult!=6)) {
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
        velocityX=-10.0f;
        rotationZ=0.0f;
    }
    return;
}
