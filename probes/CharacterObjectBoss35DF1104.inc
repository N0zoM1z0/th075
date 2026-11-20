// F1104: Japanese original game action 0x35D at 00516517..00516646,
// genuine 303 native CODE B /67 x86 inside ONE still-NONEXACT boss.
case 0x35D: {
    if (animationStage==0 && animationFrame==0)
        field0D8=0;
    if (animationStage==1 && animationFrame==0) {
        owner->UpdateGaugeTimer(20);
        owner->SpawnBattleEffect(
            0x330,
            (*(&x))+g_F1057_YOffsetAt00657888-
                float(RecordedRange(0,200)),
            0.0f,facing,1);
        ++field0D8;
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        if (field0D8<5)
            ResetSecondaryCounter(1);
        else
            ClearFrameInfo();
    }
    return;
}
