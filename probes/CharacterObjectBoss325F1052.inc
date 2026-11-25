// Patchouli object action 0x325 at 0x0050B654–0x0050B821 (461 bytes).
case 0x325: {
    if (owner->action>49 &&
        owner->action<150 &&
        animationStage<2) {
        ClearFrameInfo();
        for (int shot=0;shot<3;++shot) {
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
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        remainingHits=1;
        collisionResult=0;
        owner->PlaySound(0x17);
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
