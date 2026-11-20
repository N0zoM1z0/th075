// F1122: genuine Japanese original 0x38E 0051C91E..0051CAB0,
// 402 native CODE B /91 x86 inside ONE NONEXACT 81KB parent.
case 0x38E: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        field0D8=0;
        velocityX=field0C8;
    }
    if (animationStage==1 && animationFrame==0)
        owner->SpawnBattleEffect(
            0x38F,x,y,
            facing,1);
    if (x>g_F1101_RightAt00659424 ||
        x<g_F1101_LeftAt0065924C) {
        ClearFrameInfo();
        return;
    }
    x=float(facing)*velocityX+x;
    if (AdvanceNestedFrame()==animationStageCount) {
        if (field0D8<int(g_F1113_DifficultyAt006714D0)*8+10) {
            ++field0D8;
            ResetSecondaryCounter(1);
        }
    }
    return;
}
