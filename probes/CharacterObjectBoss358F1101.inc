// F1101: native Japanese 00515C0E..00515E7F action 0x358,
// 625 original CODE B/143 x86, within one still-NONEXACT 81KB owner.
case 0x358: {
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<0x17) {
        ClearFrameInfo();
        for (int shot=0;shot<10;++shot)
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
        field0D8=0;
        velocityX=8.0f;
    }
    if (animationStage==1 && animationFrame==0) {
        owner->PlaySound(2);
        owner->SpawnBattleEffect(
            0x359,x,y,
            facing,1);
    }
    if (x>g_F1101_RightAt00659424 ||
        x<g_F1101_LeftAt0065924C) {
        ClearFrameInfo();
        return;
    }
    x=float(facing)*velocityX+x;
    if (AdvanceNestedFrame()==field070) {
        if (field0D8<5) {
            ++field0D8;
            ResetSecondaryCounter(1);
        } else
            ClearFrameInfo();
    }
    return;
}
