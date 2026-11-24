// F1013 original Japanese 004AC040 final states 31B and 31C.
// Entry resets F00, sets field07C and calls native 00453E20 to clear the
// four motion fields. State 31B transitions at stage 5 and repeats at stage
// 11/counter 9; state 31C transitions at stage 16 and repeats at stage 21/
// counter 19 while setting byte +0x3CF.
// F1013 original Japanese final fighter state 0x31B.
case 0x31B: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
        SpawnBattleEffect(0x3E5,x,
            (*(&y))+GeometryConstants::Hundred,
            facing,1);
    }
    if ((animationStage)==11 && (animationFrame)==0 && (scriptCounterF00)<8) {
        ++scriptCounterF00;
        ResetSecondaryCounter(9);
    }
    break;
}
// F1013 original Japanese final fighter state 0x31C.
case 0x31C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==16 && (animationFrame)==0) {
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
    }
    if ((animationStage)==21 && (animationFrame)==0 && (scriptCounterF00)<8) {
        ++scriptCounterF00;
        ResetSecondaryCounter(19);
        field3CF=1;
    }
    break;
}
