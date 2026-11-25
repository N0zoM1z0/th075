// F1051: native original 0050A80F..0050AC27 (1048B/229 x86), ONE case
// inside the nonexact 81KB original CharacterObject::Advance.
// Parent +0xE4, target grandparent +0x2E8 are borrowed, not embedded owners.
case 0x321: {
    if (owner->action != 0x2BC) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
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
    if (animationStage>5 &&
        y+velocityY <= FloatConstants::Zero) {
        y=0.0f;
        velocityY=0.0f;
        velocityX=0.0f;
        owner->PlaySound(0xB);
        ResetPrimaryCounters(0x322);
        owner->SpawnBattleEffect(
            0x347, x, y,
            facing, 1);
        owner->SpawnAuxEffect(0x7F, x, 0.0f, facing, 1);
        for (int shot=0; shot<20; ++shot) {
            owner->SpawnBattleEffect(
                0x33A, x, y,
                facing, 1);
        }
        owner->SetCameraShake(10.0f);
        return;
    }
    if (owner->animationStage==9 && animationStage<6) {
        ResetSecondaryCounter(animationStage+5);
        velocityX=
            float(facing) *
            (owner->opponent->x-x) /
            GeometryConstants::Twelve;
        if (velocityX<GeometryConstants::Six)
            velocityX=6.0f;
        velocityY=-24.0f;
    }
    x=float(facing)*velocityX+
        x;
    y=y+
        velocityY;
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetSecondaryCounter(6);
        return;
    }
    if (animationStage==6 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
