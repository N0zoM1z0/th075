// F1119: real original TH075 game action 0x38A at PE
// 0051BFE2..0051C3ED, 1035 native CODE B/226 x86. Whole 81KB NONEXACT.
case 0x38A: {
    if (owner->spellTimer<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        remainingHits=1;
        collisionResult=0;
        field0D8=0;
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=0.0f;
        velocityY=0.0f;
    }
    if (animationStage<6) {
        scaleX=(scaleX)+FloatConstants::OneFifth;
        scaleY=(scaleY)+FloatConstants::OneFifth;
        if (scaleX>FloatConstants::One)
            scaleX=2.0f;
        if (scaleY>FloatConstants::One)
            scaleY=2.0f;
    }
    if (animationStage>5) {
        if (y+velocityY<=FloatConstants::Zero) {
            y=0.0f;
            velocityY=0.0f;
            velocityX=0.0f;
            owner->PlaySound(11);
            ResetPrimaryCounters(0x385);
            owner->SpawnBattleEffect(
                0x347,x,y,facing,1);
            int shot;
            for (shot=0;shot<15;++shot)
                owner->SpawnBattleEffect(
                    0x33A,x,y,facing,1);
            for (shot=0;shot<15;++shot)
                owner->SpawnBattleEffect(
                    0x389,x,y,facing,1);
            owner->SetCameraShake(5.0f);
            return;
        }
    }
    if (owner->animationStage==9 && animationStage<6) {
        ResetSecondaryCounter(animationStage+5);
        velocityX=float(RecordedRange(0,30)+10);
        velocityY=-20.0f;
    }
    x=float(facing)*velocityX+x;
    y=y+velocityY;
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetSecondaryCounter(6);
        return;
    }
    if (animationStage==6 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
