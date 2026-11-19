// F858 native actual 0x192: 217B/64-x86/6 original PE field references.
// Original transition2, stage4 sprite320 and +0x314 3f, stage5 state flag.
// Complete game switch interior; independent original whole giant still nonexact.
case 0x192: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(2);
    if ((animationStage)==4 && (animationFrame)==0) {
        field314=3.0f;
        SpawnBattleEffect(0x320,x,y,
           (facing),1);
        UpdateGaugeTimer(0xFA);
        PlaySound(0);
    }
    if ((animationStage)==5 && (animationFrame)==0)
        field07C=1;
    return;
}
