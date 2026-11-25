// F901 original native 31B whole 248B/74 x86/8 physical PE calls.
// Stage4 actual native 454A70(0), 452B30() and sprite3E5;
// stage8 genuinely used short F00<8 and auxiliary6.
// Inner original game case, not independently callable exact CODE.
case 0x31B: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        collisionResult=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==4 && (animationFrame)==0) {
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
        SpawnBattleEffect(0x3E5,x,y,
            (facing),1);
    }
    if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<8) {
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
    }
    return;
}
