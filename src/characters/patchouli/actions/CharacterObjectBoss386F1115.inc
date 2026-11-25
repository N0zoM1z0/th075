// F1115: genuine original Japanese 0x386 game action at
// PE 0051B21D..0051B5AF, 914 native CODE B /195 ordered x86.
// One true state of ONE still-NONEXACT 81KB CharacterObject::Advance.
case 0x386: {
    if (x>GeometryConstants::ThirteenHundredEighty ||
        x<GeometryConstants::NegativeHundred ||
        y>GeometryConstants::Thousand ||
        y<GeometryConstants::NegativeTwoHundredForty) {
        ClearFrameInfo();
        return;
    }
    if (owner->spellTimer<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        remainingHits=1;
        collisionResult=0;
        field0D8=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=3.0f;
        velocityY=0.0f;
    }
    if (animationStage==1) {
        scaleX=float(RecordedRange(0,4))*
            FloatConstants::OneTenth+FloatConstants::FourFifthsDouble;
        scaleY=scaleX;
        if (AbsFloatAt00412D90(x-
            owner->opponent->x)<GeometryConstants::Twenty) {
            velocityX=0.0f;
            scaleX=1.0f;
            scaleY=1.0f;
            owner->SetCameraShake(5.0f);
            ResetSecondaryCounter(2);
            return;
        }
    }
    x=float(facing)*velocityX+x;
    y=y+velocityY;
    if (AdvanceNestedFrame()==animationStageCount) {
        owner->SetCameraShake(10.0f);
        for (int shot=0;shot<12;++shot) {
            owner->SpawnBattleEffect(
                0x387,
                (*(&x))+GeometryConstants::Sixty-float(RecordedRange(0,80)),
                float(RecordedRange(0,320)),
                facing,1);
        }
        ClearFrameInfo();
        return;
    }
    if (animationStage==2 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
