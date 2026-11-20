// F896 original 0x2E6: 374B/102 native x86, true random-action cascade.
// Start action 0x2E5 iff random F00<30 and occupied; stage3 sprite38E.
// No fake source locals; entire original 46755B father NONEXACT.
case 0x2E6: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        field07C=0;
        field080=1;
    }
    velocityX=(velocityX)-g_F893FloatFallAt00657478;
    if ((velocityX)<g_ThresholdAt0065782C)
        velocityX=0.0f;
    if (AdvanceNestedFrame()==(animationStageCount)) {
        scriptCounterF00=RecordedRange(0,100);
        if (field07C==0) {
            ResetPrimaryCounters(0);
            aiCardTimer=RecordedRange(60,120);
            return;
        }
        if ((scriptCounterF00)<30) {
            ResetPrimaryCounters(0x2E5);
            return;
        }
        if ((scriptCounterF00)<60) {
            ResetPrimaryCounters(0x2E7);
            return;
        }
        ResetPrimaryCounters(0x2E8);
        return;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=15.0f;
        PlaySound(7);
        SpawnBattleEffect(0x38E,x,
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
    }
    return;
}
