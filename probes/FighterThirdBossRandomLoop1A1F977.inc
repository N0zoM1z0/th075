// F977 native Japanese TH075 original fighter action1A1, physical
// 004B42D1..004B450B, 570B/151 x86/12 true original PE fields.
// Real 5/8 shot loops with 30/20 - shot*10 + Rand(0,80/100)
// face-adjusted X require a live saved ESI across random calls.
// Natural whole VC7.1 source now emits original ESI PUSH prologue,
// complete 151 native mnemonic+width roles, but 67 GPR mismatches.
// Actual full original 82KB fighter remains NONEXACT, not case exact.
case 0x1A1: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        PlaySound(0);
        if (field39D==2) {
            for (int shot=0;shot<5;++shot) {
                field314=30.0f;
                field318=10.0f;
                Fighter::SpawnTrackedEffect(0x344,
                    float((30-shot*10+RecordedRange(0,80))*(facing))+(x),
                    ((*(&y))+g_F976_RandomYAt0065786C+shot*40)+float(RecordedRange(0,20)),
                    facing,1,0,1);
            }
        } else {
            for (int shot=0;shot<8;++shot) {
                field314=30.0f;
                field318=10.0f;
                Fighter::SpawnTrackedEffect(0x344,
                    float((20-shot*10+RecordedRange(0,100))*(facing))+(x),
                    ((*(&y))+g_F976_RandomYAt0065786C+shot*30)+float(RecordedRange(0,20)),
                    facing,1,0,1);
            }
        }
    }
    break;
}
